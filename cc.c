
// stdlib ----------------------------------------------------------------------

int open( char *path, int oflag, int cmode ); // >0 if ok; mode: rwx(u)rwx(g)rwx(others)
int close( int fd ); // 0 if ok
int read( int fd, char* buf, int count );  // fd=0 - stdin
int write( int fd, char* buf, int count ); // fd=1 - stdout, fd=2 - stderr
char* malloc( int size );
void free( char* ptr );
void exit( int status );

enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=512, O_TRUNC=1024, O_EXCL=2048 };

int is_abc( int c ) { return c>='a' && c<='z' || c>='A' && c<='Z' || c=='_'; }

int strlen( char* s ) { int n=0; while( *s ) { ++s; ++n; } return n; }
char* strcpy( char* d, char* s ) { char* r=d; while( *s ) { *d = *s; ++d; ++s; } *d = 0; return r; }
char* strcat( char* s, char* t ) { int n = strlen( s ); strcpy( s+n, t ); return s; }

char* strrev( char* s )
{
  char* b = s; char* e = s + strlen(s) - 1;
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
    if( value==-2147483648 ) { strcpy( str, "-2147483648" ); return str; }
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
  while( *str == ' ' ) ++str; // skip leading blanks
  int minus = 0;
  if( *str == '-' ) { minus = 1; ++str; }
  int v = 0;
  while( *str >= '0' && *str <= '9' ) { v = 10*v + *str - '0'; ++str; }
  if( minus ) v = -v;
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

enum { Eof, Num, Chr, Str, Op, Sep, Id, Kw, Err }; // tokens
enum { Void, Char, Int, Enum, If, Else, While, Break, Return, Sizeof }; // keywords
enum { Asg, Inc, Dec, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, LAnd, LOr, LNot }; // ops

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

char rd_buf[10000];
int  rd_buf_len = 0;
int  rd_char = -1;                 // current/last char
int  rd_char_pos = sizeof(rd_buf); // position in buffer
int  rd_file = -1;                 // file descriptor
int  rd_line = -1;                 // line number

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

char sc_text[200]; // for Id
int  sc_kw;        // for Kw
int  sc_op;        // for Op
int  sc_sep;       // for Sep
int  sc_num;       // for Num and Chr

int sc_next();
int sc_next1() // scan for next token,
{
  char* tt;
  if( rd_char < 0 ) { rd_next(); rd_line = 1; p1( i2s(rd_line,0) ); }
  while( rd_char==' ' || rd_char==10 || rd_char==13 )
  {
    if( rd_char==10 ) { ++rd_line; p2( "\n", i2s(rd_line,0) ); }
    rd_next();
  }
  if( rd_char<0 ) return Eof;
  if( rd_char>='0' && rd_char<='9' ) // Number
  {
    tt = sc_text;
    while( rd_char>='0' && rd_char<='9' ) { *tt = rd_char; ++tt; rd_next(); }
    *tt = 0;
    sc_num = s2i( sc_text );
    return Num;
  }
  else if( is_abc(rd_char) ) // Id or Keyword
  {
    tt = sc_text;
    while( is_abc(rd_char) || rd_char>='0' && rd_char<='9' ) { *tt = rd_char; ++tt; rd_next(); }
    *tt = 0;
    sc_kw = find_kw( sc_text );
    if( sc_kw >= 0 ) return Kw;
    return Id;
  }
  else if( rd_char=='"' ) // String
  {
    tt = sc_text;
    rd_next();
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
      *tt = rd_char; ++tt; rd_next();
    }
    *tt = 0;
    rd_next();
    return Str;
  }
  else if( rd_char==39 ) // Character literal 'x' (but can't be '\x')
  {
    rd_next();
    sc_num = rd_char;  // we take anything from inside, w/o '\'
    rd_next();
    if( rd_char!=39 ) return Err; // must end with 'x'
    rd_next();
    return Chr;
  }
  else if( rd_char=='{' || rd_char=='}' || rd_char=='(' || rd_char==')' ||
           rd_char=='[' || rd_char==']' || rd_char==',' || rd_char==';' )
  {
    sc_sep = rd_char; return Sep;
  }
  else if( rd_char=='=' || rd_char=='<' || rd_char=='>' || rd_char=='!' )
  {
    char c = rd_char; rd_next();
    if( rd_char == '=' ) // == <= >= !=
    {
      rd_next(); sc_op = Eq;
      if( c=='<' ) sc_op = Le; else if( c=='>' ) sc_op = Ge; else if( c=='!' ) sc_op = Ne;
    }
    else
    {
      sc_op = Asg;
      if( c=='<' ) sc_op = Lt; else if( c=='>' ) sc_op = Gt; else if( c=='!' ) sc_op = LNot;
    }
    return Op;
  }
  else if( rd_char=='*' || rd_char=='%' )
  {
    sc_op = Mul; if( rd_char=='%' ) sc_op = Mod; rd_next(); return Op;
  }
  else if( rd_char=='+' || rd_char=='-' || rd_char=='&' || rd_char=='|' )
  {
    char c = rd_char; rd_next();
    if( rd_char == c ) // ++ -- && ||
    {
      rd_next();
      sc_op = Inc; if( c=='-' ) sc_op = Dec;
      else if( c=='&' ) sc_op = LAnd; else if( c=='|' ) sc_op = LOr;
    }
    else
    {
      sc_op = Add; if( c=='-' ) sc_op = Sub;
      else if( c=='&' || c=='|' ) return Err; // no & or | yet
    }
    return Op;
  }
  else if( rd_char=='/' ) // comment //... or /*...*/ or divide /
  {
    rd_next();
    if( rd_char == '/' ) // //...
    {
      rd_next();
      while( rd_char!=10 && rd_char>0 )
        rd_next();
      if( rd_char==10 ) { ++rd_line; p2( "\n", i2s(rd_line,0) ); }
      if(rd_char>0) rd_next();
      return sc_next();
    }
    else if( rd_char == '*' ) // /*...*/
    {
      rd_next();
      if( rd_char==10 ) { ++rd_line; p2( "\n", i2s(rd_line,0) ); }
      while(1)
      {
        while( rd_char!='*' && rd_char>0 )
        {
          rd_next();
          if( rd_char==10 ) { ++rd_line; p2( "\n", i2s(rd_line,0) ); }
        }
        if(rd_char>0) rd_next();
        if( rd_char == '/' )
          break;
      }
      if(rd_char>0) rd_next();
      return sc_next();
    }
    else
    {
      sc_op = Div;
    }
    return Op;
  }
  else
  {
    sc_text[0] = rd_char; sc_text[1] = 0;
    rd_next();
    return Err;
  }
}

int sc_next() { int t=sc_next1(); /* p4( i2s(t,0), " - ", sc_text, "\n" ); */ return t; }

// Parser ----------------------------------------------------------------------

int t; // token
char pa_value[200];

enum { F, T }; // False, True

int pa_block(); int pa_type(); int pa_stars(); int pa_intexpr(); // have to be declared
int pa_enumdef(); int pa_vars(); int pa_expr();

int pa_primary()
{
  if( t==Num || t==Char || t==Str || t==Id ) { t = sc_next(); return T; }
  if( t==Sep && sc_sep=='(' )
  {
    t = sc_next(); if( !pa_expr() ) return F;
    if( t==Sep && sc_sep==')' ) { t = sc_next(); return T; }
  }
  return F;
}

int pa_exprs()
{
  if( !pa_expr() ) return F;
  while( t==Sep && sc_sep==',' ) { t = sc_next(); if( !pa_expr() ) return F; }
  return T;
}

int pa_call_or_index()
{
  if( t==Sep && sc_sep=='(' )
  {
    t = sc_next();
    if( t==Sep && sc_sep==')' ) { t = sc_next(); return T; }
    if( !pa_exprs() ) return F;
    if( t==Sep && sc_sep==')' ) { t = sc_next(); return T; }
    return F;
  }
  if( t==Sep && sc_sep=='[' )
  {
    t = sc_next();
    if( !pa_expr() ) return F;
    if( t==Sep && sc_sep==']' ) { t = sc_next(); return T; }
  }
  return F;
}

int pa_base()
// "sizeof" '(' type stars ')' | primary { call_or_index }
{ return T; }

int pa_unop()
{
  if( t==Op && (sc_op==Sub || sc_op==LNot || sc_op==Mul || sc_op==Inc || sc_op==Dec) )
    { t = sc_next(); return T; }
  if( t==Kw && sc_kw==Sizeof ) { t = sc_next(); return T; }
  if( t==Sep && sc_sep=='(' )
  {
    t = sc_next();
    if( !pa_type() || !pa_stars() ) return F;
    if( t==Sep && sc_sep==')' ) { t = sc_next(); return T; }
  }
  return F;
}

int pa_binop()
// : '*' | '/' | '%'                       // pri. 5
// | '+' | '-'                             // pri. 6
// | '<' | '>' | '<''=' | '>''='           // pri. 8
// | '=''=' | '!''='                       // pri. 9
// | '&''&'                                // pri. 13
// | '|''|'                                // pri. 14
// | '='                                   // pri. 16
{ return T; }

int pa_term()
// { unop } base
{ return T; }

int pa_expr()
// term { binop term }
{ return T; }

int pa_stmt()
// | type stars @Name vars
{
  if( t==Sep && sc_sep==';' ) { t = sc_next(); return T; } // ';'
  if( t==Sep && sc_sep=='{' )
    return pa_block();
  if( t==Kw )
  {
    if( sc_kw==Break )
    {
      t = sc_next(); if( t!=Sep || sc_sep!=';' ) return F; t = sc_next(); return T;
    }
    if( sc_kw==Return )
    {
      t = sc_next();
      if( t==Sep && sc_sep==';' ) { t = sc_next(); return T; }
      if( !pa_expr() ) return F;
      if( t!=Sep || sc_sep!=';' ) return F;
      t = sc_next(); return T;
    }
    if( sc_kw==While )
    {
      t = sc_next(); if( t!=Sep || sc_sep!='(' ) return F; t = sc_next();
      if( !pa_expr() ) return F;
      if( t!=Sep || sc_sep!=')' ) return F;
      t = sc_next();
      return pa_stmt();
    }
    if( sc_kw==If )
    {
      t = sc_next(); if( t!=Sep || sc_sep!='(' ) return F; t = sc_next();
      if( !pa_expr() ) return F;
      if( t!=Sep || sc_sep!=')' ) return F;
      t = sc_next();
      if( !pa_stmt() ) return F;
      if( t==Kw && sc_kw==Else )
      {
        t = sc_next();
        if( !pa_stmt() ) return F;
      }
      return T;
    }
    if( sc_kw==Enum )
    {
      t = sc_next();
      return pa_enumdef();
    }
    if( sc_kw==Int || sc_kw==Char || sc_kw==Void ) // type stars @Name vars
    {
      if( !pa_type() || !pa_stars() ) return F;
      if( t != Id ) return F;
      t = sc_next();
      return pa_vars();
    }
    return F;
  }
  if( !pa_expr() ) return F;
  if( t!=Sep || sc_sep!=';' ) return F;
  t = sc_next(); return T;
}

int pa_enumerator()
{
  if( t != Id ) return F;
  t = sc_next();
  if( t==Op && sc_op==Asg )
  {
    t = sc_next();
    if( !pa_intexpr() ) return F;
  }
  return T;
}

int pa_enumdef()
{
  if( t!=Sep || sc_sep!='{' ) return F;
  t = sc_next();
  if( !pa_enumerator() ) return F;
  while( t==Sep && sc_sep==',' )
  {
    t = sc_next();
    if( !pa_enumerator() ) return F;
  }
  if( t!=Sep || sc_sep!='}' ) return F;
  t = sc_next();
  if( t!=Sep || sc_sep!=';' ) return F;
  t = sc_next();
  return T;
}

int pa_argdef()
{
  if( !pa_type() || !pa_stars() ) return F;
  if( t != Id ) return F;
  t = sc_next();
  return T;
}

int pa_args()
{
  if( !pa_argdef() ) return T;
  while( t==Sep && sc_sep==',' )
  {
    t = sc_next();
    if( !pa_argdef() ) return F;
  }
  return T;
}

int pa_number()
{
  if( t!=Num && t!=Char ) return F;
  // i2s( sc_num, tmp );
  t = sc_next();
  return T;
}

int pa_intexpr()
{
  if( t==Op && sc_op==Sub ) // '-'
    t = sc_next();
  return pa_number();
}

int pa_constexpr()
{
  if( t==Id ) { t = sc_next(); return T; }  // array variable as address
  if( t==Str ) { t = sc_next(); return T; } // string as array of char
  if( t!=Sep || sc_sep!='{' ) return pa_intexpr();
  t = sc_next();
  if( !pa_constexpr() ) return F;
  while( t==Sep && sc_sep==',' )
  {
    t = sc_next();
    if( !pa_constexpr() ) return F;
  }
  if( t!=Sep || sc_sep!='}' ) return F;
  t = sc_next();
  return T;
}

int pa_vartail()
{
  if( t==Sep && sc_sep=='[' )
  {
    t = sc_next();
    if( !pa_number() ) return F;
    if( t!=Sep || sc_sep!=']' ) return F;
    t=sc_next();
  }
  if( t==Op && sc_op==Asg )
  {
    t = sc_next();
    if( !pa_constexpr() ) return F;
  }
  return T;
}

int pa_vars()
{
  if( !pa_vartail() ) return F;
  while( t==Sep && sc_sep==',' )
  {
    t = sc_next();
    if( !pa_stars() ) return F;
    if( t != Id ) return F;
    t = sc_next();
    if( !pa_vartail() ) return F;
  }
  if( t!=Sep || sc_sep!=';' ) return F;
  t=sc_next();
  return T;
}

int pa_block() // no check, checks done outside; next token right away
{
  t = sc_next();
  while( t!=Sep || sc_sep!='}' )
    if( !pa_stmt() ) return F;     // error
  t = sc_next();
  return T;
}

int pa_fntail()
{
  if( t==Sep && sc_sep==';' ) return T; // declaration
  if( t==Sep && sc_sep=='{' )
    return pa_block();
  return F;
}

int pa_fn_or_vars()
{
  if( t != Sep || sc_sep != '(' ) return pa_vars();
  t = sc_next();
  if( ! pa_args() ) return F;
  if( t != Sep || sc_sep != ')' ) return F;
  t = sc_next();
  return pa_fntail();
}

int pa_stars()
{
  if( t==Op && sc_op==Mul ) t = sc_next();
  if( t==Op && sc_op==Mul ) t = sc_next();
  return T;
}

int pa_type()
{
  if( t==Kw && (sc_kw==Int || sc_kw==Char || sc_kw==Void) ) { t = sc_next(); return T; }
  return F;
}

int pa_decl_or_def()
{
  if( t==Kw && sc_kw==Enum ) { t = sc_next(); return pa_enumdef(); }
  if( !pa_type() || !pa_stars() ) return F;
  if( t != Id ) return F;
  t = sc_next();
  return pa_fn_or_vars();
}

int pa_file( char* fn )
{
  rd_file = open( fn, O_RDONLY, 0 );
  if( rd_file<=0 ) return T;

  t = sc_next();
  while( t!=Eof && pa_decl_or_def() )
    ;

  close( rd_file );
  return F;
}

char* OPS = "=\0\0++\0--\0==\0!=\0<\0\0>\0\0<=\0>=\0+\0\0-\0\0*\0\0/\0\0%\0\0&&\0||\0";

int scanfile( char* fn ) // scan file; return 0 if OK
{
  rd_file = open( fn, O_RDONLY, 0 );
  if( rd_file<=0 ) return 1;

  int t;
  while( (t = sc_next()) != Eof ) // let's not stop at Err
  {
    if( t==Num )      { p2( " #", i2s( sc_num, 0 ) ); }
    else if( t==Id )  { p2( " ", sc_text ); }
    else if( t==Sep ) { char s[3]=" ?"; s[1]=sc_sep; p1( s ); }
    else if( t==Kw )  { p4( " ", i2s( sc_kw, 0 ), "~", sc_text ); }
    else if( t==Op )  { p2( " `", OPS + (3*sc_op) ); }
    else if( t==Str ) { p3( " \"", sc_text, "\"" ); }
    else if( t==Chr ) { p2( " \'", i2s( sc_num, 0 ) ); }
    else /* error */  { p3( "\n\n??????", sc_text, "\n" ); }
  }

  close( rd_file );
  return 0;
}

// Main compiler function ------------------------------------------------------

int main( int ac, char** av )
{
  // return scanfile( av[1] );
  int rc = pa_file( av[1] );
  return rc;
}
