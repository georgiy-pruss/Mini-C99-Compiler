#include "D:\Cygwin32\home\Geo\cclib.c"

enum { Nul, Eof, Num, Chr, Str, Op, Sep, Id, Kw, Err };
enum { Void, Char, Int, Enum, If, Else, While, For, Return, Sizeof };

char inbuf[1000];
int inbuflen=0;
int curchar = -1;
int curcharpos = sizeof(inbuf);
int f; // file

int getchar()
{
  if( curcharpos>=inbuflen )
  {
    inbuflen = read( f, inbuf, sizeof(inbuf) );
    if( inbuflen<=0 ) return -1;
    curcharpos = 0;
  }
  return inbuf[curcharpos++];
}


int strcmp( char* s, char* t )
{
  while( *s )
  {
    if( *t==0 || *s>*t ) return 1;
    if( *s<*t ) return -1;
    ++s;
    ++t;
  }
  if( *t ) return -1;
  return 0;
}


char tokentext[200];
char* tt;
int kw;

int get_token()
{
  if( curchar < 0 ) curchar = getchar();
  while( curchar==' ' || curchar=='\n' || curchar=='\r' || curchar=='\t' )
  {
    if( curchar=='\n' ) write( 1, "\n", 1 );
    curchar = getchar();
  }
  if( curchar<0 ) return Eof;
  if( curchar>='0' && curchar<='9' )
  {
    tt = tokentext;
    *tt++ = curchar;
    curchar = getchar();
    while( curchar>='0' && curchar<='9' )
    {
      *tt++ = curchar;
      curchar = getchar();
    }
    *tt = '\0';
    return Num;
  }
  else if( curchar>='a' && curchar<='z' || curchar>='A' && curchar<='Z' || curchar=='_' )
  {
    tt = tokentext;
    *tt++ = curchar;
    curchar = getchar();
    while( curchar>='0' && curchar<='9' || curchar>='a' && curchar<='z' ||
                                           curchar>='A' && curchar<='Z' || curchar=='_' )
    {
      *tt++ = curchar;
      curchar = getchar();
    }
    *tt = '\0';
    if( strcmp( tokentext, "if" )==0 ) { kw = If; return Kw; }
    if( strcmp( tokentext, "else" )==0 ) { kw = Else; return Kw; }
    if( strcmp( tokentext, "while" )==0 ) { kw = While; return Kw; }
    if( strcmp( tokentext, "for" )==0 ) { kw = For; return Kw; }
    if( strcmp( tokentext, "return" )==0 ) { kw = Return; return Kw; }
    if( strcmp( tokentext, "void" )==0 ) { kw = Void; return Kw; }
    if( strcmp( tokentext, "char" )==0 ) { kw = Char; return Kw; }
    if( strcmp( tokentext, "int" )==0 ) { kw = Int; return Kw; }
    if( strcmp( tokentext, "enum" )==0 ) { kw = Enum; return Kw; }
    if( strcmp( tokentext, "sizeof" )==0 ) { kw = Sizeof; return Kw; }
    return Id;
  }
  else if( curchar=='"' )
  {
    tt = tokentext;
    curchar = getchar();
    while( curchar!='"' )
    {
      if( curchar == '\\' )
        curchar = getchar();
      *tt++ = curchar;
      curchar = getchar();
    }
    *tt = '\0';
    curchar = getchar();
    return Str;
  }
  else if( curchar=='\'' )
  {
    curchar = getchar();
    tokentext[0] = curchar;
    tokentext[1] = '\0';
    curchar = getchar();
    if( curchar!='\'' ) return -1;
    curchar = getchar();
    return Chr;
  }
  else if( curchar=='{' || curchar=='}' || curchar=='(' || curchar==')' ||
           curchar=='[' || curchar==']' || curchar==',' || curchar==';' ) // || curchar==':' )
  {
    tokentext[0] = curchar;
    tokentext[1] = 0;
    curchar = getchar();
    return Sep;
  }
  else if( curchar=='<' || curchar=='>' || curchar=='=' || curchar=='*' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == '=' ) // <= >= == *=
    {
      tokentext[0] = ccc;
      tokentext[1] = curchar;
      tokentext[2] = 0;
      curchar = getchar();
    }
    else
    {
      tokentext[0] = ccc;
      tokentext[1] = 0;
    }
    return Op;
  }
  else if( curchar=='+' || curchar=='-' || curchar=='&' || curchar=='|' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == '=' ) // += -=
    {
      tokentext[0] = ccc;
      tokentext[1] = curchar;
      tokentext[2] = 0;
      curchar = getchar();
    }
    else if( curchar == ccc ) // ++ -- && ||
    {
      tokentext[0] = ccc;
      tokentext[1] = ccc;
      tokentext[2] = 0;
      curchar = getchar();
    }
    else
    {
      tokentext[0] = ccc;
      tokentext[1] = 0;
    }
    return Op;
  }
  else if( curchar=='/' )
  {
    curchar = getchar();
    if( curchar == '/' ) // comment
    {
      curchar = getchar();
      while( curchar!='\n' && curchar>0 )
        curchar = getchar();
      return get_token();
    }
    else if( curchar == '=' ) // /=
    {
      tokentext[0] = '/';
      tokentext[1] = '=';
      tokentext[2] = 0;
      curchar = getchar();
    }
    else
    {
      tokentext[0] = '/';
      tokentext[1] = 0;
    }
    return Op;
  }
  else if( curchar=='%' || curchar=='^' )
  {
    char ccc = curchar;
    if( curchar == '=' ) // %= ^=
    {
      tokentext[0] = ccc;
      tokentext[1] = curchar;
      tokentext[2] = 0;
      curchar = getchar();
    }
    else
    {
      tokentext[0] = ccc;
      tokentext[1] = 0;
    }
    return Op;
  }
  else
  {
    tokentext[0] = curchar;
    tokentext[1] = 0;
    curchar = getchar();
    return Err;
  }
}

int main( int ac, char** av )
{
  char* fn = av[1];
  f = open( fn, O_RDONLY );
  if( f<=0 ) return 1;

  int t;
  while( (t = get_token()) != Eof )
  {
    // print t
    if( t==Num )
    {
      write( 1, " #", 2 );
      write( 1, tokentext, strlen(tokentext) );
    }
    else if( t==Id )
    {
      write( 1, " :", 2 );
      write( 1, tokentext, strlen(tokentext) );
    }
    else if( t==Kw )
    {
      write( 1, " $", 2 );
      write( 1, tokentext, strlen(tokentext) );
    }
    else if( t==Op )
    {
      write( 1, " `", 2 );
      write( 1, tokentext, strlen(tokentext) );
    }
    else if( t==Sep )
    {
      write( 1, " ", 1 );
      write( 1, tokentext, strlen(tokentext) );
    }
    else if( t==Str )
    {
      write( 1, " \"", 2 );
      write( 1, tokentext, strlen(tokentext) );
    }
    else if( t==Chr )
    {
      write( 1, " \'", 2 );
      write( 1, tokentext, 1 );
    }
    else
    {
      write( 1, " ?", 2 );
      write( 1, tokentext, 1 );
    }
  }

  close(f);
  return 0;
}

