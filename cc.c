
// stdlib ----------------------------------------------------------------------

int open( char *path, int oflag, int cmode ); // >0 if ok; mode: rwx(u)rwx(g)rwx(others)
int close( int fd ); // 0 if ok
int read( int fd, char* buf, int count );  // fd=0 - stdin
int write( int fd, char* buf, int count ); // fd=1 - stdout, fd=2 - stderr
char* malloc( int size );
void free( char* ptr );
void exit( int status );

enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=512, O_TRUNC=1024, O_EXCL=2048 };

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



enum { Nul, Eof, Num, Chr, Str, Op, Sep, Id, Kw, Err };
enum { Void, Char, Int, Enum, If, Else, While, Break, Return, Sizeof };
enum { Asg, Inc, Dec, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, LAnd, LOr };


char inbuf[10000];
int inbuflen = 0;
int curchar = -1;
int curcharpos = sizeof(inbuf);
int srcfile; // file
int lineno = 1;

int getchar()
{
  if( curcharpos>=inbuflen )
  {
    inbuflen = read( srcfile, inbuf, sizeof(inbuf)-1 );
    if( inbuflen<=0 ) return -1; // eof
    inbuf[inbuflen] = 0;
    curcharpos = 0;
  }
  return inbuf[curcharpos++];
}

char tokentext[400];
char separator[2] = ".";
int kw;
int radix;
int opkind;
int numvalue; // for Num and Chr; separator itself for Sep

int isabc( int c ) { return c>='a' && c<='z' || c>='A' && c<='Z' || c=='_'; }

int gettoken()
{
  char* tt;
  if( curchar < 0 ) { curchar = getchar(); lineno = 1; p1( i2s(lineno,0) ); }
  while( curchar==' ' || curchar==10 || curchar==13 )
  {
    if( curchar==10 ) { ++lineno; p2( "\n", i2s(lineno,0) ); }
    curchar = getchar();
  }
  if( curchar<0 ) return Eof;
  if( curchar>='0' && curchar<='9' )
  {
    tt = tokentext;
    while( curchar>='0' && curchar<='9' )
    {
      *tt = curchar; ++tt;
      curchar = getchar();
    }
    *tt = 0;
    numvalue = s2i( tokentext );
    return Num;
  }
  else if( isabc(curchar) )
  {
    tt = tokentext;
    while( isabc(curchar) || curchar>='0' && curchar<='9' )
    {
      *tt++ = curchar;
      curchar = getchar();
    }
    *tt = 0;
    if(      strcmp( tokentext, "int"    )==0 ) { kw = Int; return Kw; }
    else if( strcmp( tokentext, "char"   )==0 ) { kw = Char; return Kw; }
    else if( strcmp( tokentext, "void"   )==0 ) { kw = Void; return Kw; }
    else if( strcmp( tokentext, "enum"   )==0 ) { kw = Enum; return Kw; }
    else if( strcmp( tokentext, "if"     )==0 ) { kw = If; return Kw; }
    else if( strcmp( tokentext, "else"   )==0 ) { kw = Else; return Kw; }
    else if( strcmp( tokentext, "while"  )==0 ) { kw = While; return Kw; }
    else if( strcmp( tokentext, "break"  )==0 ) { kw = Break; return Kw; }
    else if( strcmp( tokentext, "return" )==0 ) { kw = Return; return Kw; }
    else if( strcmp( tokentext, "sizeof" )==0 ) { kw = Sizeof; return Kw; }
    return Id;
  }
  else if( curchar=='"' )
  {
    tt = tokentext;
    curchar = getchar();
    while( curchar!='"' )
    {
      if( curchar == 92 ) // \ - backslash in strings (only; not in chars!)
      {
        curchar = getchar();
        if( curchar=='n' ) curchar = 10;
        else if( curchar=='r' ) curchar = 13;
        else if( curchar=='b' ) curchar = 8;
        else if( curchar=='0' ) curchar = 0;
      }
      *tt++ = curchar;
      curchar = getchar();
    }
    *tt = 0;
    curchar = getchar();
    return Str;
  }
  else if( curchar==39 ) // '  apostrophe - char like 'x'
  {
    curchar = getchar();
    numvalue = curchar;  // we take anything from inside, w/o '\'
    curchar = getchar();
    if( curchar!=39 ) return Err; // must end with 'x'
    curchar = getchar();
    return Chr;
  }
  else if( curchar=='{' || curchar=='}' || curchar=='(' || curchar==')' ||
           curchar=='[' || curchar==']' || curchar==',' || curchar==';' )
  {
    separator[0] = (char)curchar;
    curchar = getchar();
    return Sep;
  }
  else if( curchar=='=' || curchar=='<' || curchar=='>' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == '=' ) // <= >=
    {
      curchar = getchar();
      opkind = Eq; if( ccc=='<' ) opkind = Le; else if( ccc=='>' ) opkind = Ge;
    }
    else
    {
      opkind = Asg; if( ccc=='<' ) opkind = Lt; else if( ccc=='>' ) opkind = Gt;
    }
    return Op;
  }
  else if( curchar=='*' )
  {
    curchar = getchar();
    opkind = Mul;
    return Op;
  }
  else if( curchar=='+' || curchar=='-' || curchar=='&' || curchar=='|' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == ccc ) // ++ -- && ||
    {
      curchar = getchar();
      opkind = Inc; if( ccc=='-' ) opkind = Dec;
      else if( ccc=='&' ) opkind = LAnd; else if( ccc=='|' ) opkind = LOr;
    }
    else
    {
      opkind = Add; if( ccc=='-' ) opkind = Sub;
      else if( ccc=='&' || ccc=='|' ) return Err; // no & or |
    }
    return Op;
  }
  else if( curchar=='/' )
  {
    curchar = getchar();
    if( curchar == '/' ) // comment
    {
      curchar = getchar();
      while( curchar!=10 && curchar>0 )
        curchar = getchar();
      if( curchar==10 ) { ++lineno; p2( "\n", i2s(lineno,0) ); }
      if(curchar>0) curchar = getchar();
      return gettoken();
    }
    else if( curchar == '*' ) // /* comment */
    {
      curchar = getchar();
      if( curchar==10 ) { ++lineno; p2( "\n", i2s(lineno,0) ); }
      while(1)
      {
        while( curchar!='*' && curchar>0 )
        {
          curchar = getchar();
          if( curchar==10 ) { ++lineno; p2( "\n", i2s(lineno,0) ); }
        }
        if(curchar>0) curchar = getchar();
        if( curchar == '/' )
          break;
      }
      if(curchar>0) curchar = getchar();
      return gettoken();
    }
    else
    {
      opkind = Div;
    }
    return Op;
  }
  else if( curchar=='%' )
  {
    curchar = getchar();
    opkind = Mod;
    return Op;
  }
  else if( curchar=='!' )
  {
    curchar = getchar();
    if( curchar != '=' ) return Err; // no unary !
    curchar = getchar();
    opkind = Ne;
    return Op;
  }
  else
  {
    tokentext[0] = curchar; tokentext[1] = 0;
    curchar = getchar();
    return Err;
  }
}


char* OPS = "=\0\0++\0--\0==\0!=\0<\0\0>\0\0<=\0>=\0+\0\0-\0\0*\0\0/\0\0%\0\0&&\0||\0";

int scanfile( char* fn )
{
  srcfile = open( fn, O_RDONLY, 0 );
  if( srcfile<=0 ) return 1;

  int t,t1=Err,t2=Err;
  while( (t = gettoken()) != Eof )
  {
    if( t==Num )      { p2( " #", i2s( numvalue, 0 ) ); }
    else if( t==Id )  { p2( " ", tokentext ); }
    else if( t==Kw )  { p4( " ", i2s( kw, 0 ), "|", tokentext ); }
    else if( t==Op )  { p2( " `", OPS + (3*opkind) ); }
    else if( t==Sep ) { p2( " ", separator ); }
    else if( t==Str ) { p3( " \"", tokentext, "\"" ); }
    else if( t==Chr ) { p2( " \'", i2s( numvalue, 0 ) ); }
    else /* error */  { p3( "\n\n??????", tokentext, "\n" ); }
  }

  close(srcfile);
  return 0;
}


int main( int ac, char** av )
{
  scanfile( av[1] );
  return 0;
}

