// cc.c -- self-compiling C compiler - 2017 (C) G.Pruss
// gcc -fno-builtin-malloc -fno-builtin-strlen -O2 cc.c -o cc.exe
// -std=c99 is default

// stdlib ----------------------------------------------------------------------

int open( char* path, int oflag, int cmode ); // >0 if ok; mode: rwx(u)rwx(g)rwx(others)
int close( int fd );                          // 0 if ok
int read( int fd, char* buf, int count );     // fd=0 - stdin
int write( int fd, char* buf, int count );    // fd=1 - stdout, fd=2 - stderr
char* malloc( int size );
void free( char* ptr );
void exit( int status );

enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=512, O_TRUNC=1024, O_EXCL=2048 };
// O_TEXT=0x4000 O_BINARY=0x8000                  win: 256           512         1024

int is_abc( int c ) { return c>='a' && c<='z' || c>='A' && c<='Z' || c=='_'; }

int strlen( char* s ) { int n=0; while( *s ) { ++s; ++n; } return n; }
char* strcpy( char* d, char* s ) { char* r=d; while( *s ) { *d = *s; ++d; ++s; } *d = 0; return r; }
char* strcat( char* s, char* t ) { int n = strlen( s ); strcpy( s+n, t ); return s; }

char* strrev( char* s )
{
  int n = strlen(s); if( n<=1 ) return s;
  char* b = s; char* e = s + n - 1;
  while( b<e ) { char t = *e; *e = *b; *b = t; ++b; --e; }
  return s;
}

int strcmp( char* s, char* t )
{
  while( *s )
  {
    if( *t==0 || *s>*t ) return 1;
    if( *s<*t ) return -1;
    ++s; ++t;
  }
  if( *t ) return -1;
  return 0;
}

int strequ( char* s, char* t ) { return strcmp( s, t ) == 0; }

char* strrchr( char* s, int c )
{
  int n = strlen(s);
  while( n>0 ) { if( s[n-1] == c ) return s+(n-1); --n; }
  return 0;
}

char i2s_buf[16]; // buffer for i2s() if the second argument is 0

char* i2s( int value, char* str )
{
  if( str==0 ) str = i2s_buf; // use common buffer
  if( value==0 ) { *str = '0'; str[1] = 0; return str; }
  char* dst = str;
  if( value<0 )
  {
    if( value==(-2147483647-1) ) { strcpy( str, "-2147483648" ); return str; }
    *dst = '-'; ++dst;
    value = -value;
  }
  char* beg = dst;
  while( value != 0 ) { *dst = (char)(value % 10 + '0'); ++dst; value = value / 10; }
  *dst = 0;
  strrev( beg );
  return str;
}

int s2i( char* str )
{
  if( *str == '-' ) return -s2i( str+1 );
  int v = 0;
  while( *str >= '0' && *str <= '9' ) { v = 10*v + *str - '0'; ++str; }
  return v;
}

void assert( int cond, char* msg )
{
  if( cond != 0 ) return;
  write( 2, "ASSERT: ", 8 ); write( 2, msg, strlen(msg) ); write( 2, "\n", 1 );
  exit(1);
}

void p1( char* s ) { write( 1, s, strlen(s) ); }
void p2( char* s, char* s2 ) { p1( s ); p1( s2 ); }
void p3( char* s, char* s2, char* s3 ) { p1( s ); p1( s2 ); p1( s3 ); }
void p4( char* s, char* s2, char* s3, char* s4 ) { p1( s ); p1( s2 ); p1( s3 ); p1( s4 ); }

// Compiler Definitions --------------------------------------------------------

enum { Err, Eof, Num, Chr, Str, Id, // tokens
       // Op: = i d e n < > l g + - * / % & | a o ! (inc dec eq ne le ge and or)
       // Sep: ( ) [ ] { } , ;
       Kw=200 }; // actual tokens for keywors: Kw+k, where k is from below:
enum { Void, Char, Int, Enum, If, Else, While, Break, Return, Sizeof }; // keywords

int find_kw( char* s )
{
  if( strequ( s, "int"    ) ) return Int;    if( strequ( s, "char"   ) ) return Char;
  if( strequ( s, "void"   ) ) return Void;   if( strequ( s, "enum"   ) ) return Enum;
  if( strequ( s, "if"     ) ) return If;     if( strequ( s, "else"   ) ) return Else;
  if( strequ( s, "while"  ) ) return While;  if( strequ( s, "break"  ) ) return Break;
  if( strequ( s, "return" ) ) return Return; if( strequ( s, "sizeof" ) ) return Sizeof;
  return -1;
}

// File reader -----------------------------------------------------------------

char rd_buf[8000];
int  rd_buf_len  = -1; // actual length of buffer; init <rd_char_pos to start rd_next
int  rd_char_pos =  0; // position in buffer
int  rd_char     = -1; // current/last char; also <0 to start in sc_read_next
int  rd_file     = -1; // file descriptor for rd_next
int  rd_line     = -1; // line number

void rd_next() // read next character, save it in rd_char; <0 if eof
{
  if( rd_char_pos >= rd_buf_len )
  {
    rd_buf_len = read( rd_file, rd_buf, sizeof(rd_buf)-1 );
    if( rd_buf_len <= 0 ) { rd_char = -1; return; } // eof
    rd_buf[ rd_buf_len ] = 0;
    rd_char_pos = 0;
  }
  rd_char = rd_buf[ rd_char_pos ]; ++rd_char_pos;
}

// Scanner ---------------------------------------------------------------------

int  sc_tkn;       // current token
char sc_text[260]; // for Id, Kw, Num, Str
int  sc_num;       // for Num and Chr

int sc_read_next() // scan for next token
{
  if( rd_char < 0 ) { rd_next(); rd_line = 1; p3( "[", i2s(rd_line,0), "]" ); }
  while( rd_char==' ' || rd_char==10 || rd_char==13 )
  {
    if( rd_char==10 ) { ++rd_line; p3( "\n[", i2s(rd_line,0), "]" ); } // line no
    rd_next();
  }
  if( rd_char<0 ) return Eof;
  if( rd_char>='0' && rd_char<='9' ) // Number
  {
    char* p = sc_text;
    while( rd_char>='0' && rd_char<='9' ) { *p = rd_char; ++p; rd_next(); }
    *p = 0;
    sc_num = s2i( sc_text );
    return Num;
  }
  else if( is_abc(rd_char) ) // Id or Keyword
  {
    char* p = sc_text;
    while( is_abc(rd_char) || rd_char>='0' && rd_char<='9' ) { *p = rd_char; ++p; rd_next(); }
    *p = 0;
    int k = find_kw( sc_text );
    if( k >= 0 ) return Kw+k;
    return Id;
  }
  else if( rd_char=='"' ) // String
  {
    rd_next();
    char* p = sc_text;
    while( rd_char!='"' )
    {
      if( rd_char == 92 ) // \ - backslash in strings (only; not in chars!)
      {
        rd_next();
        if( rd_char=='n' ) rd_char = 10;
        else if( rd_char=='r' ) rd_char = 13;
        else if( rd_char=='b' ) rd_char = 8;
        else if( rd_char=='0' ) rd_char = 0;
      }
      *p = rd_char; ++p; rd_next();
    }
    *p = 0;
    rd_next();
    return Str;
  }
  else if( rd_char==39 ) // Character literal 'x' (but can't be '\x')
  {
    rd_next();
    sc_num = rd_char;    // we take anything from inside, w/o '\'
    rd_next();
    if( rd_char!=39 ) return Err; // must end with 'x'
    rd_next();
    return Chr;
  }
  else if( rd_char=='{' || rd_char=='}' || rd_char=='(' || rd_char==')' ||
           rd_char=='[' || rd_char==']' || rd_char==',' || rd_char==';' ||
           rd_char=='*' || rd_char=='%' )
  {
    int c = rd_char; rd_next(); return c;
  }
  else if( rd_char=='=' || rd_char=='<' || rd_char=='>' || rd_char=='!' )
  {
    int c = rd_char; rd_next();
    if( rd_char == '=' ) // == <= >= != --> e l g n
    {
      rd_next();
      if( c=='=' ) c = 'e'; else if( c=='<' ) c = 'l'; else if( c=='>' ) c = 'g'; else c = 'n';
    }
    return c;
  }
  else if( rd_char=='+' || rd_char=='-' || rd_char=='&' || rd_char=='|' )
  {
    int c = rd_char; rd_next();
    if( rd_char == c ) // ++ -- && ||
    {
      rd_next();
      if( c=='+' ) c = 'i'; else if( c=='-' ) c = 'd'; else if( c=='&' ) c = 'a'; else c = 'o';
    }
    return c;
  }
  else if( rd_char=='/' ) // comment //... or /*...*/ or divide /
  {
    rd_next();
    if( rd_char == '/' ) // //...
    {
      rd_next();
      while( rd_char!=10 && rd_char>0 )
        rd_next();
      if( rd_char==10 ) { ++rd_line; p3( "[//]\n[", i2s(rd_line,0), "]" ); } // line no
      if(rd_char>0) rd_next();
      return sc_read_next();
    }
    else if( rd_char == '*' ) // /*...*/
    {
      rd_next();
      if( rd_char==10 ) { ++rd_line; p3( "[/*]\n[", i2s(rd_line,0), "]" ); }
      while(1)
      {
        while( rd_char!='*' && rd_char>0 )
        {
          rd_next();
          if( rd_char==10 ) { ++rd_line; p3( "[**]\n[", i2s(rd_line,0), "]" ); }
        }
        if(rd_char>0) rd_next();
        if( rd_char == '/' )
          break;
      }
      if(rd_char>0) rd_next();
      return sc_read_next();
    }
    else
      return '/';
  }
  else
  {
    sc_text[0] = rd_char; sc_text[1] = 0;
    rd_next();
    return Err;
  }
}

char* KWDS[10] = { "void","char","int","enum","if","else","while","break","return","sizeof" };

void sc_next() // put token into sc_tkn
{
  sc_tkn = sc_read_next();
  p3( " ", i2s( sc_tkn, 0 ), " - " );
  if (sc_tkn >= Kw)        p2( "kw ", KWDS[ sc_tkn - Kw ] );
  else if( sc_tkn == Id )  p2( "id ", sc_text );
  else if( sc_tkn == Str ) p2( "str ", sc_text );
  else if( sc_tkn == Num ) p2( "num ", i2s( sc_num, 0 ) );
  else if( sc_tkn == Chr ) p2( "chr ", i2s( sc_num, 0 ) );
  else if( sc_tkn == Eof ) p1( "eof" );
  else if( sc_tkn == Err ) p2( "err", sc_text );
  else if( sc_tkn < Kw ) { char o[2] = "."; o[0]=sc_tkn; p2( "op/sep ", o ); }
  else p2( "?", sc_text );
  p1("\n");
}

// Parser ----------------------------------------------------------------------

enum { F, T }; // False, True

// Due to recursive nature and difficult syntax, some fns have to be pre-declared
int pa_expr(); int pa_term(); int pa_type(); int pa_stars(); int pa_exprtail();
int pa_block(); int pa_enumdef(); int pa_vars(int k); int pa_intexpr();

int pa_primary()
{
  p1("pa_primary\n");
  if( sc_tkn==Num || sc_tkn==Chr || sc_tkn==Str || sc_tkn==Id ) { sc_next(); return T; }
  if( sc_tkn!='(' ) return F;
  sc_next(); if( !pa_expr() ) return F;
  if( sc_tkn!=')' ) return F;
  sc_next(); return T;
}

int pa_exprs()
{
  p1("pa_exprs\n");
  if( !pa_expr() ) return F;
  while( sc_tkn==',' ) { sc_next(); if( !pa_expr() ) return F; }
  return T;
}

int pa_call_or_index()
{
  p1("pa_call_or_index\n");
  if( sc_tkn=='(' )
  {
    sc_next();
    if( sc_tkn==')' ) { sc_next(); return T; }
    if( !pa_exprs() ) return F;
    if( sc_tkn==')' ) { sc_next(); return T; }
    return F;
  }
  if( sc_tkn=='[' )
  {
    sc_next();
    if( !pa_expr() ) return F;
    if( sc_tkn==']' ) { sc_next(); return T; }
  }
  return F; // not error but to indicate nothing happened here
}

int pa_postfix()
{
  p1("pa_postfix\n");
  if( !pa_primary() ) return F;
  while( pa_call_or_index() )
    ;
  return T;
}

int pa_unexpr()
{
  p1("pa_unexpr\n");
  if( sc_tkn=='i' || sc_tkn=='d' ) { sc_next(); return pa_unexpr(); }
  if( sc_tkn=='-' || sc_tkn=='!' || sc_tkn=='*' ) { sc_next(); return pa_term(); }
  if( sc_tkn==Kw+Sizeof )
  {
    sc_next();
    if( sc_tkn=='(' )
    {
      sc_next();
      if( pa_type() )
      {
        if( !pa_stars() ) return F;
        if( sc_tkn==')' ) { sc_next(); return T; }
        return F;
      }
      return pa_exprtail();
    }
    return pa_unexpr();
  }
  return pa_postfix();
}

int pa_exprtail()
{
  p1("pa_exprtail\n");
  if( !pa_expr() ) return F;
  if( sc_tkn!=')' ) return F;
  sc_next();
  while( pa_call_or_index() )
    ;
  return T;
}

int pa_term()
{
  p1("pa_term\n");
  if( sc_tkn=='(' )
  {
    sc_next();
    if( pa_type() )
    {
      if( !pa_stars() ) return F;
      if( sc_tkn!=')' ) return F;
      sc_next();
      return pa_term();
    }
    return pa_exprtail();
  }
  return pa_unexpr();
}

int pa_binop()
{
  p1("pa_binop\n");
  if( sc_tkn=='*' || sc_tkn=='/' || sc_tkn=='%' ||                // 3
      sc_tkn=='+' || sc_tkn=='-' ||                               // 4
      sc_tkn=='<' || sc_tkn=='>' || sc_tkn=='l' || sc_tkn=='g' || // 6
      sc_tkn=='e' || sc_tkn=='n' ||                               // 7
      sc_tkn=='&' || sc_tkn=='|' ||                               // 8 10
      sc_tkn=='a' || sc_tkn=='o' || sc_tkn=='=' )                 // 11 12 14
    { sc_next(); return T; }
  return F;
}

int pa_expr()
{
  p1("pa_expr\n");
  if( !pa_term() ) return F;
  while( pa_binop() ) if( !pa_term() ) return F;
  return T;
}

int pa_stmt()
{
  p1("pa_stmt\n");
  if( sc_tkn==';' ) { sc_next(); return T; } // empty stmt ';'
  if( sc_tkn=='{' ) { sc_next(); return pa_block(); }
  if( sc_tkn==Kw+Break )
  {
    sc_next(); if( sc_tkn!=';' ) return F; sc_next(); return T;
  }
  if( sc_tkn==Kw+Return )
  {
    sc_next();
    if( sc_tkn==';' ) { sc_next(); return T; }
    if( !pa_expr() ) return F;
    if( sc_tkn!=';' ) return F;
    sc_next(); return T;
  }
  if( sc_tkn==Kw+While )
  {
    sc_next(); if( sc_tkn!='(' ) return F; sc_next();
    if( !pa_expr() ) return F;
    if( sc_tkn!=')' ) return F;
    sc_next();
    return pa_stmt();
  }
  if( sc_tkn==Kw+If )
  {
    sc_next(); if( sc_tkn!='(' ) return F; sc_next();
    if( !pa_expr() ) return F;
    if( sc_tkn!=')' ) return F;
    sc_next();
    if( !pa_stmt() ) return F;
    if( sc_tkn==Kw+Else )
    {
      sc_next();
      if( !pa_stmt() ) return F;
    }
    return T;
  }
  if( sc_tkn==Kw+Enum )
  {
    sc_next();
    return pa_enumdef();
  }
  if( sc_tkn==Kw+Int || sc_tkn==Kw+Char || sc_tkn==Kw+Void )
  {
    if( !pa_type() || !pa_stars() ) return F;
    if( sc_tkn != Id ) return F;
    sc_next();
    return pa_vars(1);
  }
  // expr ';'
  if( !pa_expr() ) return F; if( sc_tkn!=';' ) return F; sc_next(); return T;
}

int pa_enumerator()
{
  p1("pa_enumerator\n");
  if( sc_tkn != Id ) return F;
  sc_next();
  if( sc_tkn=='=' )
  {
    sc_next();
    if( !pa_intexpr() ) return F;
  }
  return T;
}

int pa_enumdef()
{
  p1("pa_enumdef\n");
  if( sc_tkn != '{' ) return F;
  sc_next();
  if( !pa_enumerator() ) return F;
  while( sc_tkn==',' )
  {
    sc_next();
    if( !pa_enumerator() ) return F;
  }
  if( sc_tkn != '}' ) return F;
  sc_next();
  if( sc_tkn != ';' ) return F;
  sc_next();
  return T;
}

int pa_argdef()
{
  p1("pa_argdef\n");
  if( !pa_type() || !pa_stars() ) return F;
  if( sc_tkn != Id ) return F;
  sc_next();
  return T;
}

int pa_args()
{
  p1("pa_args\n");
  if( !pa_argdef() ) return T;
  while( sc_tkn==',' )
  {
    sc_next();
    if( !pa_argdef() ) return F;
  }
  return T;
}

int pa_number()
{
  p1("pa_number\n");
  if( sc_tkn!=Num && sc_tkn!=Chr ) return F;
  // i2s( sc_num, tmp );
  sc_next();
  return T;
}

int pa_intexpr()
{
  p1("pa_intexpr\n");
  if( sc_tkn=='-' )
    sc_next();
  return pa_number();
}

int pa_constexpr()
{
  p1("pa_constexpr\n");
  if( sc_tkn==Id ) { sc_next(); return T; }  // array variable as address
  if( sc_tkn==Str ) { sc_next(); return T; } // string as array of char
  if( sc_tkn!='{' ) return pa_intexpr();
  sc_next();
  if( !pa_constexpr() ) return F;
  while( sc_tkn==',' )
  {
    sc_next();
    if( !pa_constexpr() ) return F;
  }
  if( sc_tkn!='}' ) return F;
  sc_next();
  return T;
}

int pa_vartail(int k)
{
  p1("pa_vartail\n");
  if( sc_tkn=='[' )
  {
    sc_next();
    if( !pa_number() ) return F;
    if( sc_tkn!=']' ) return F;
    sc_next();
  }
  if( sc_tkn=='=' )
  {
    sc_next();
    if( k==0 ) return pa_constexpr(); else /* 1 */ return pa_expr();
  }
  return T;
}

int pa_vars(int k)
{
  p3("pa_vars^",i2s(k,0),"\n");
  if( !pa_vartail(k) ) return F;
  while( sc_tkn==',' )
  {
    sc_next();
    if( !pa_stars() ) return F;
    if( sc_tkn != Id ) return F;
    sc_next();
    if( !pa_vartail(k) ) return F;
  }
  if( sc_tkn!=';' ) return F;
  sc_next();
  return T;
}

int pa_block() // no check, checks done outside; next token right away
{
  p1("pa_block\n");
  while( sc_tkn!='}' )
    if( !pa_stmt() ) return F; // error
  sc_next();
  return T;
}

int pa_fntail()
{
  p1("pa_fntail\n");
  if( sc_tkn == ';' ) { sc_next(); return T; }          // fn declaration
  if( sc_tkn == '{' ) { sc_next(); return pa_block(); } // fn definition
  return F;
}

int pa_fn_or_vars()
{
  p1("pa_fn_or_vars\n");
  if( sc_tkn != '(' ) return pa_vars(0);
  sc_next();
  if( ! pa_args() ) return F;
  if( sc_tkn != ')' ) return F;
  sc_next();
  return pa_fntail();
}

int pa_stars()
{
  p1("pa_stars\n");
  if( sc_tkn=='*' ) { sc_next(); if( sc_tkn=='*' ) sc_next(); }
  return T;
}

int pa_type()
{
  p1("pa_type\n");
  if( sc_tkn==Kw+Int || sc_tkn==Kw+Char || sc_tkn==Kw+Void) { sc_next(); return T; }
  return F;
}

int pa_decl_or_def()
{
  p1("pa_decl_or_def\n");
  if( sc_tkn==Kw+Enum ) { sc_next(); return pa_enumdef(); }
  if( !pa_type() || !pa_stars() ) return F;
  if( sc_tkn != Id ) return F;
  sc_next();
  return pa_fn_or_vars();
}

int pa_file( char* fn )
{
  p3("pa_file ",fn,"\n");
  rd_file = open( fn, O_RDONLY, 0 );
  if( rd_file<=0 ) return T;

  int rc = T;
  sc_next();
  while( sc_tkn!=Eof )
    if( !pa_decl_or_def() )
      { rc = F; break; }

  close( rd_file );
  return rc;
}

// Main compiler function ------------------------------------------------------

int main( int ac, char** av )
{
  char* m[] = {"0","-0","1","-1","1234","-1234","000007","-00007","42",
    "2147000000","2147483647","-2147483647","2147483648","-2147483648", "2147483649", "" };
  int i=0; while( *m[i] )
  {
    char* s = m[i];
    int n = s2i( s ); p4( s, " ", i2s( n, 0 ), "\n" );
    ++i;
  }
  if( !pa_file( av[1] ) ) { p2( "Error in ", av[1] ); return 1; }
  return 0;
}
