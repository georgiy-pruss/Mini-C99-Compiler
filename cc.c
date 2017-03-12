
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
enum { Asg, Inc, Dec, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, LAnd, LOr }; // ops

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

char sc_text[200]; // for Id and Sep
int  sc_kw;      // for Kw
int  sc_op;     // for Op
int  sc_num; // for Num and Chr

int sc_next() // scan for next token,
{
  char* tt;
  if( rd_char < 0 ) { rd_next(); rd_line = 1; p1( i2s(rd_line,0) ); }
  while( rd_char==' ' || rd_char==10 || rd_char==13 )
  {
    if( rd_char==10 ) { ++rd_line; p2( "\n", i2s(rd_line,0) ); }
    rd_next();
  }
  if( rd_char<0 ) return Eof;
  if( rd_char>='0' && rd_char<='9' )
  {
    tt = sc_text;
    while( rd_char>='0' && rd_char<='9' ) { *tt = rd_char; ++tt; rd_next(); }
    *tt = 0;
    sc_num = s2i( sc_text );
    return Num;
  }
  else if( is_abc(rd_char) )
  {
    tt = sc_text;
    while( is_abc(rd_char) || rd_char>='0' && rd_char<='9' ) { *tt = rd_char; ++tt; rd_next(); }
    *tt = 0;
    if(      strcmp( sc_text, "int"    )==0 ) { sc_kw = Int; return Kw; }
    else if( strcmp( sc_text, "char"   )==0 ) { sc_kw = Char; return Kw; }
    else if( strcmp( sc_text, "void"   )==0 ) { sc_kw = Void; return Kw; }
    else if( strcmp( sc_text, "enum"   )==0 ) { sc_kw = Enum; return Kw; }
    else if( strcmp( sc_text, "if"     )==0 ) { sc_kw = If; return Kw; }
    else if( strcmp( sc_text, "else"   )==0 ) { sc_kw = Else; return Kw; }
    else if( strcmp( sc_text, "while"  )==0 ) { sc_kw = While; return Kw; }
    else if( strcmp( sc_text, "break"  )==0 ) { sc_kw = Break; return Kw; }
    else if( strcmp( sc_text, "return" )==0 ) { sc_kw = Return; return Kw; }
    else if( strcmp( sc_text, "sizeof" )==0 ) { sc_kw = Sizeof; return Kw; }
    return Id;
  }
  else if( rd_char=='"' )
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
  else if( rd_char==39 ) // '  apostrophe - char like 'x'
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
    sc_text[0] = (char)rd_char; sc_text[1] = 0; rd_next();
    return Sep;
  }
  else if( rd_char=='=' || rd_char=='<' || rd_char=='>' )
  {
    char ccc = rd_char;
    rd_next();
    if( rd_char == '=' ) // <= >=
    {
      rd_next();
      sc_op = Eq; if( ccc=='<' ) sc_op = Le; else if( ccc=='>' ) sc_op = Ge;
    }
    else
    {
      sc_op = Asg; if( ccc=='<' ) sc_op = Lt; else if( ccc=='>' ) sc_op = Gt;
    }
    return Op;
  }
  else if( rd_char=='*' )
  {
    rd_next();
    sc_op = Mul;
    return Op;
  }
  else if( rd_char=='+' || rd_char=='-' || rd_char=='&' || rd_char=='|' )
  {
    char ccc = rd_char;
    rd_next();
    if( rd_char == ccc ) // ++ -- && ||
    {
      rd_next();
      sc_op = Inc; if( ccc=='-' ) sc_op = Dec;
      else if( ccc=='&' ) sc_op = LAnd; else if( ccc=='|' ) sc_op = LOr;
    }
    else
    {
      sc_op = Add; if( ccc=='-' ) sc_op = Sub;
      else if( ccc=='&' || ccc=='|' ) return Err; // no & or |
    }
    return Op;
  }
  else if( rd_char=='/' )
  {
    rd_next();
    if( rd_char == '/' ) // comment
    {
      rd_next();
      while( rd_char!=10 && rd_char>0 )
        rd_next();
      if( rd_char==10 ) { ++rd_line; p2( "\n", i2s(rd_line,0) ); }
      if(rd_char>0) rd_next();
      return sc_next();
    }
    else if( rd_char == '*' ) // /* comment */
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
  else if( rd_char=='%' )
  {
    rd_next();
    sc_op = Mod;
    return Op;
  }
  else if( rd_char=='!' )
  {
    rd_next();
    if( rd_char != '=' ) return Err; // no unary '!'
    rd_next();
    sc_op = Ne;
    return Op;
  }
  else
  {
    sc_text[0] = rd_char; sc_text[1] = 0;
    rd_next();
    return Err;
  }
}

// Parser ----------------------------------------------------------------------

// Main compiler function ------------------------------------------------------

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
    else if( t==Sep ) { p2( " ", sc_text ); }
    else if( t==Kw )  { p4( " ", i2s( sc_kw, 0 ), "~", sc_text ); }
    else if( t==Op )  { p2( " `", OPS + (3*sc_op) ); }
    else if( t==Str ) { p3( " \"", sc_text, "\"" ); }
    else if( t==Chr ) { p2( " \'", i2s( sc_num, 0 ) ); }
    else /* error */  { p3( "\n\n??????", sc_text, "\n" ); }
  }

  close( rd_file );
  return 0;
}

int main( int ac, char** av )
{
  return scanfile( av[1] );
}
