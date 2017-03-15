// cc.c -- self-compiling C compiler - 2017 (C) G.Pruss
// gcc -fno-builtin-malloc -fno-builtin-strlen -O2 cc.c -o cc.exe
// -std=c99 is default

int DEBUG=0;
int PA_TRACE=0;

// stdlib ----------------------------------------------------------------------

int open( char* path, int oflag, int cmode ); // >0 if ok; mode: rwx(u)rwx(g)rwx(others)
int close( int fd );                          // 0 if ok
int read( int fd, char* buf, int count );     // fd=0 - stdin
int write( int fd, char* buf, int count );    // fd=1 - stdout, fd=2 - stderr
char* malloc( int size );                     // unsigned long long for 64-bit architecture
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

char* strdup( char* s )
{
  int n = strlen(s);
  char* t = malloc( n+1 );
  strcpy( t, s );
  return t;
}

char i2s_buf[16]; // buffer for i2s(v)

char* i2s( int value )
{
  char* str = i2s_buf;
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
       // Op: = i d e n (++ -- == !=) < > l g (<= >=) + - * / % & | ! (3 logical ops)
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
  if( rd_char < 0 ) { rd_next(); rd_line = 1; if(DEBUG) p3( "[", i2s(rd_line), "]" ); }
  while( rd_char==' ' || rd_char==10 || rd_char==13 )
  {
    if( rd_char==10 ) { ++rd_line; if(DEBUG) p3( "\n[", i2s(rd_line), "]" ); }
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
    if( rd_char == '=' ) // == <= >= != convert to: e l g n
    {
      rd_next();
      if( c=='=' ) c = 'e'; else if( c=='<' ) c = 'l'; else if( c=='>' ) c = 'g'; else c = 'n';
    }
    return c;
  }
  else if( rd_char=='+' || rd_char=='-' )
  {
    int c = rd_char; rd_next();
    if( rd_char == c ) { rd_next(); if( c=='+' ) c = 'i'; else c = 'd'; } // ++ --
    return c;
  }
  else if( rd_char=='&' || rd_char=='|' )
  {
    int c = rd_char; rd_next();
    if( rd_char == c ) { rd_next(); return c; } // && ||
    sc_text[0] = c; sc_text[1] = 0; return Err;
  }
  else if( rd_char=='/' ) // comment //... or /*...*/ or divide /
  {
    rd_next();
    if( rd_char == '/' ) // //...
    {
      rd_next();
      while( rd_char!=10 && rd_char>0 )
        rd_next();
      if( rd_char==10 ) { ++rd_line; if(DEBUG) p3( "[//]\n[", i2s(rd_line), "]" ); }
      if(rd_char>0) rd_next();
      return sc_read_next();
    }
    else if( rd_char == '*' ) // /*...*/
    {
      rd_next();
      if( rd_char==10 ) { ++rd_line; if(DEBUG) p3( "[/*]\n[", i2s(rd_line), "]" ); }
      while(1)
      {
        while( rd_char!='*' && rd_char>0 )
        {
          rd_next();
          if( rd_char==10 ) { ++rd_line; if(DEBUG) p3( "[**]\n[", i2s(rd_line), "]" ); }
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

char escape_s[200];
char* escape( char* s )
{
  char* d = escape_s;
  while( *s )
  {
    if( *s==10 ) { *d=92; ++d; *d='n'; }
    else if( *s==13 ) { *d=92; ++d; *d='r'; }
    else if( *s==8 ) { *d=92; ++d; *d='b'; }
    else if( *s==0 ) { *d=92; ++d; *d='0'; }
    else if( *s==32 ) { *d=92; ++d; *d='_'; } // \_ for space
    else *d=*s;
    ++d;
    ++s;
  }
  *d = 0;
  return escape_s;
}

char** names = 0;
int nnames = 0;
int fnames = 0;
int collisions = 0;

void allocnames( int n )
{
  names = (char**)malloc( 4*n );
  nnames = n;
  int i = 0;
  while( i<n ) { names[i] = 0; ++i; }
}

int hash( char* s )
{
  int h = 5381;
  int i = 0;
  while( s[i] )
  {
    h = (h*66 + s[i]) % 16777216;
    ++i;
  }
  return h;
}

int freeze_name( char* s )
{
  /*p2( s, "  " );*/
  int M=1009;
  if( names==0 ) allocnames( M );
  int h = hash( s );
  int x = h % M;
  while( names[x] )
  {
    if( strequ( names[x], s ) ) { /*p3( "== ", i2s(x), "\n" );*/ return x; }
    x = (x+1) % M;
    ++collisions;
  }
  /*p3( "++ ", i2s(x), "\n" );*/
  names[x] = strdup( s );
  ++fnames;
  return x;
}

void dump_names()
{
  int i=0, k=0;
  while( i<nnames )
  {
    if( names[i] ) { ++k; p4( i2s(i), " ", names[i], "\n" ); }
    ++i;
  }
  p1( "---------\n" );
  p2( i2s(k), " ^^^\n" );
  p2( i2s(fnames), " names\n" );
  p2( i2s(collisions), " colls\n" );
}


void sc_next() // put token into sc_tkn
{
  sc_tkn = sc_read_next();
  if( sc_tkn == Id ) freeze_name( sc_text );
  if( DEBUG )
  {
    p3( " ", i2s(sc_tkn), " - " );
    if (sc_tkn >= Kw)        p2( "kw ", KWDS[ sc_tkn - Kw ] );
    else if( sc_tkn == Id )  p4( "id ", sc_text, " #",i2s(freeze_name( sc_text )) );
    else if( sc_tkn == Str ) p2( "str ", escape(sc_text) );
    else if( sc_tkn == Num ) p2( "num ", i2s(sc_num) );
    else if( sc_tkn == Chr ) p2( "chr ", i2s(sc_num) );
    else if( sc_tkn == Eof ) p1( "eof" );
    else if( sc_tkn == Err ) p2( "err", sc_text );
    else if( sc_tkn < Kw ) { char o[2] = "."; o[0]=sc_tkn; p2( "op/sep ", o ); }
    else p2( "?", sc_text );
    p1("\n");
  }
}

// Semantics & Code generation -------------------------------------------------

enum { INTSZ = 4 };

// Parser ----------------------------------------------------------------------

int tL = 0; // indent level
void tI() { p1("                    "); int i=0; while(i<tL) { p1( "." ); ++i; } }
void t1( char* s ) { if( PA_TRACE ) { tI(); p2( s,"\n" ); ++tL; } }
void t2( char* s, char* s2 ) { if( PA_TRACE ) { tI(); p3( s,s2,"\n" ); ++tL; } }
void t3( char* s, char* s2, char* s3 ) { if( PA_TRACE ) { tI(); p4( s,s2,s3,"\n" ); ++tL; } }
int t_( int r )  { if( PA_TRACE ) { --tL; tI(); p3( "<< ", i2s(r), "\n" ); } return r; }

enum { F, T }; // Boolean result of pa_* functions: False, True

// Due to recursive nature and difficult syntax, some fns have to be pre-declared
int pa_expr(); int pa_term(); int pa_block(); int pa_vars(int k);

int pa_primary()
{
  t1("pa_primary");
  if( sc_tkn==Num || sc_tkn==Chr || sc_tkn==Str || sc_tkn==Id ) { sc_next(); return t_(T); }
  if( sc_tkn!='(' ) return t_(F);
  sc_next(); if( !pa_expr() ) return t_(F);
  if( sc_tkn!=')' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_exprs()
{
  t1("pa_exprs");
  if( !pa_expr() ) return t_(F);
  while( sc_tkn==',' ) { sc_next(); if( !pa_expr() ) return t_(F); }
  return t_(T);
}

int pa_call_or_index()
{
  t1("pa_call_or_index");
  while( sc_tkn=='(' || sc_tkn=='[' )
  {
    if( sc_tkn=='[' ) { sc_next(); if( !pa_expr() || sc_tkn!=']' ) return t_(F); }
    else /* '(' */ { sc_next(); if( sc_tkn!=')' ) { if( !pa_exprs() || sc_tkn!=')' ) return t_(F); } }
    sc_next();
  }
  return t_(T);
}

int pa_postfix()
{
  t1("pa_postfix");
  if( !pa_primary() ) return t_(F);
  return t_(pa_call_or_index());
}

int pa_type()
{
  t1("pa_type");
  if( sc_tkn==Kw+Int || sc_tkn==Kw+Char || sc_tkn==Kw+Void) { sc_next(); return t_(T); }
  return t_(F);
}

int pa_stars()
{
  t1("pa_stars");
  if( sc_tkn=='*' ) { sc_next(); if( sc_tkn=='*' ) sc_next(); }
  return t_(T);
}

int pa_sizeofexpr()
{
  t1("pa_sizeofexpr");
  if( sc_tkn!='(' ) return t_(F);
  sc_next();
  if( pa_type() )
  {
    pa_stars(); if( sc_tkn==')' ) { sc_next(); return t_(T); }
    return t_(F);
  }
  if( sc_tkn!=Id ) return t_(F);
  sc_next();
  if( sc_tkn=='[' )
  {
    sc_next(); if( sc_tkn!=Num ) return t_(F);
    sc_next(); if( sc_tkn!=']' ) return t_(F);
    sc_next();
  }
  if( sc_tkn==')' ) { sc_next(); return t_(T); }
  return t_(F);
}

int pa_unexpr()
{
  t1("pa_unexpr");
  if( sc_tkn=='i' || sc_tkn=='d' ) { sc_next(); return t_(pa_unexpr()); }
  if( sc_tkn=='-' || sc_tkn=='!' || sc_tkn=='*' ) { sc_next(); return t_(pa_term()); }
  if( sc_tkn==Kw+Sizeof ) { sc_next(); return t_(pa_sizeofexpr()); }
  return t_(pa_postfix());
}

int pa_term()
{
  t1("pa_term");
  if( sc_tkn=='(' )
  {
    sc_next();
    if( pa_type() )
    {
      pa_stars(); if( sc_tkn!=')' ) return t_(F);
      sc_next(); return t_(pa_term());
    }
    if( !pa_expr() ) return t_(F);
    if( sc_tkn!=')' )return t_(F);
    sc_next();
    return t_(pa_call_or_index());
  }
  return t_(pa_unexpr());
}

int pa_binop()
{
  t1("pa_binop");
  if( sc_tkn=='*' || sc_tkn=='/' || sc_tkn=='%' ||                // 3
      sc_tkn=='+' || sc_tkn=='-' ||                               // 4
      sc_tkn=='<' || sc_tkn=='>' || sc_tkn=='l' || sc_tkn=='g' || // 6
      sc_tkn=='e' || sc_tkn=='n' ||                               // 7
      sc_tkn=='&' || sc_tkn=='|' || sc_tkn=='=' )                 // 11 12 14
    { sc_next(); return t_(T); }
  return t_(F);
}

int pa_expr()
{
  t1("pa_expr");
  if( !pa_term() ) return t_(F);
  while( pa_binop() ) if( !pa_term() ) return t_(F);
  return t_(T);
}

int pa_stmt()
{
  t1("pa_stmt");
  if( sc_tkn==';' ) { sc_next(); return t_(T); }                // empty stmt ';'
  if( sc_tkn=='{' ) { sc_next(); return t_(pa_block()); }
  if( sc_tkn==Kw+Break )
  {
    sc_next(); if( sc_tkn!=';' ) return F; sc_next(); return T;
  }
  if( sc_tkn==Kw+Return )
  {
    sc_next(); if( sc_tkn==';' ) { sc_next(); return t_(T); }
    if( !pa_expr() || sc_tkn!=';' ) return t_(F);
    sc_next(); return t_(T);
  }
  if( sc_tkn==Kw+While )
  {
    sc_next(); if( sc_tkn!='(' ) return t_(F);
    sc_next(); if( !pa_expr() || sc_tkn!=')' ) return t_(F);
    sc_next(); return t_(pa_stmt());
  }
  if( sc_tkn==Kw+If )
  {
    sc_next(); if( sc_tkn!='(' ) return t_(F);
    sc_next(); if( !pa_expr() || sc_tkn!=')' ) return t_(F);
    sc_next(); if( !pa_stmt() ) return t_(F);
    if( sc_tkn==Kw+Else ) { sc_next(); if( !pa_stmt() ) return t_(F); }
    return t_(T);
  }
  if( sc_tkn==Kw+Int || sc_tkn==Kw+Char || sc_tkn==Kw+Void )
  {
    if( !pa_type() || !pa_stars() ) return t_(F);
    if( sc_tkn != Id ) return t_(F);
    sc_next();
    return t_(pa_vars(1));
  }
  // expr ';'
  if( !pa_expr() || sc_tkn!=';' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_number()
{
  t1("pa_number");
  if( sc_tkn!=Num && sc_tkn!=Chr ) return t_(F);
  // i2s( sc_num, tmp );
  sc_next();
  return t_(T);
}

int pa_intexpr()
{
  t1("pa_intexpr");
  if( sc_tkn==Kw+Sizeof ) { sc_next(); return t_(pa_sizeofexpr()); }
  if( sc_tkn=='-' || sc_tkn=='!' ) sc_next();
  return t_(pa_number());
}

int pa_constexpr()
{
  t1("pa_constexpr");
  if( sc_tkn==Id ) { sc_next(); return t_(T); }  // array variable as address
  if( sc_tkn==Str ) { sc_next(); return t_(T); } // string as array of char
  if( sc_tkn!='{' ) return t_(pa_intexpr());
  sc_next();
  if( !pa_constexpr() ) return t_(F);
  while( sc_tkn==',' ) { sc_next(); if( !pa_constexpr() ) return t_(F); }
  if( sc_tkn!='}' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_vartail(int k)
{
  t2("pa_vartail__",i2s(k));
  if( sc_tkn=='[' )
  {
    sc_next(); if( !pa_number() ) return t_(F); if( sc_tkn!=']' ) return t_(F);
    sc_next();
  }
  if( sc_tkn=='=' )
  {
    sc_next(); if( k==0 ) return t_(pa_constexpr()); else /* 1 */ return t_(pa_expr());
  }
  return t_(T);
}

int pa_vars(int k)
{
  t2("pa_vars__",i2s(k));
  if( !pa_vartail(k) ) return t_(F);
  while( sc_tkn==',' )
  {
    sc_next(); pa_stars(); if( sc_tkn != Id ) return t_(F);
    sc_next(); if( !pa_vartail(k) ) return t_(F);
  }
  if( sc_tkn!=';' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_enumerator()
{
  t1("pa_enumerator");
  if( sc_tkn != Id ) return t_(F);
  sc_next(); if( sc_tkn=='=' ) { sc_next(); if( !pa_intexpr() ) return t_(F); }
  return t_(T);
}

int pa_enumdef()
{
  t1("pa_enumdef");
  if( sc_tkn != '{' ) return t_(F);
  sc_next(); if( !pa_enumerator() ) return t_(F);
  while( sc_tkn==',' ) { sc_next(); if( !pa_enumerator() ) return t_(F); }
  if( sc_tkn != '}' ) return t_(F);
  sc_next(); if( sc_tkn != ';' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_block() // no check, checks done outside; next token right away
{
  t1("pa_block");
  while( sc_tkn!='}' ) if( !pa_stmt() ) return t_(F); // error
  sc_next();
  return t_(T);
}

int pa_fntail()
{
  t1("pa_fntail");
  if( sc_tkn == ';' ) { sc_next(); return t_(T); }          // fn declaration
  if( sc_tkn == '{' ) { sc_next(); return t_(pa_block()); } // fn definition
  return t_(F);
}

int pa_argdef()
{
  t1("pa_argdef");
  if( !pa_type() ) return t_(F);
  pa_stars();
  if( sc_tkn != Id ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_args()
{
  t1("pa_args");
  if( !pa_argdef() ) return t_(T);
  while( sc_tkn==',' ) { sc_next(); if( !pa_argdef() ) return t_(F); }
  return t_(T);
}

int pa_fn_or_vars()
{
  t1("pa_fn_or_vars");
  if( sc_tkn != '(' ) return t_(pa_vars(0));
  sc_next(); if( ! pa_args() ) return t_(F);
  if( sc_tkn != ')' ) return t_(F);
  sc_next();
  return t_(pa_fntail());
}

int pa_decl_or_def()
{
  t1("pa_decl_or_def");
  if( sc_tkn==Kw+Enum ) { sc_next(); return t_(pa_enumdef()); }
  if( !pa_type() ) return t_(F);
  pa_stars();
  if( sc_tkn != Id ) return t_(F);
  sc_next();
  return t_(pa_fn_or_vars());
}

int pa_program( char* fn )
{
  t2("pa_program ",fn);
  rd_file = open( fn, O_RDONLY, 0 );
  if( rd_file<=0 ) return t_(F);

  int rc = T;
  sc_next(); // start parsing<-scanning<-reading
  while( sc_tkn!=Eof ) if( !pa_decl_or_def() ) { rc = F; break; }

  close( rd_file );
  return t_(rc);
}

// Main compiler function ------------------------------------------------------

int main( int ac, char** av )
{
  if( ac!=2 ) { p1( "No file name provided\n" ); return 0; }
  if( !pa_program( av[1] ) ) { p3( "\n*** Error in ", av[1], " ***\n" ); return 1; }
  p1( "ok\n" );
  dump_names();
  return 0;
}
