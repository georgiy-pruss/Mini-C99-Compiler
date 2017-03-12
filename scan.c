#include "cclib.c"

enum { Nul, Eof, Num, Chr, Str, Op, Sep, Id, Kw, Pre, Err };
enum { Void, Char, Int, Enum, If, Else, While, For, Break, Return, Sizeof, Include };
char* KWS[] = {"void","char","int","enum","if","else","while","for","break","return",
       "sizeof","include"};
enum { Asg, Inc, Dec, Not, LNot, Eq, Ne, Lt, Gt, Le, Ge, // = ++ -- ~ ! == != < > <= >=
       Add, Sub, Mul, Div, Mod, Shl, Shr, And, Or, Xor, LAnd, LOr, // + - * / % << >> & | ^ && ||
       AAdd, ASub, AMul, ADiv, AMod, AShl, AShr, AAnd, AOr, AXor }; // += -= *= /= %= &= |= <<= ...
char OPS[] = "=  ++ -- !  ~  == != <  >  <= >= "
             "+  -  *  /  %  << >> &  |  ^  && || "
             "+= -= *= /= %= <<=>>=&= |= ^= ";


char inbuf[10000];
int inbuflen = 0;
int curchar = -1;
int curcharpos = sizeof(inbuf);
int srcfile; // file
int lineno;

int getchar()
{
  if( curcharpos>=inbuflen )
  {
    inbuflen = read( srcfile, inbuf, sizeof(inbuf)-1 );
    if( inbuflen<=0 ) return -1; // eof
    inbuf[inbuflen] = '\0';
    curcharpos = 0;
  }
  return inbuf[curcharpos++];
}

int* saveiostate()
{
  char* bf = (char*)malloc(inbuflen+1);
  strcpy( bf, inbuf );
  int* sv = (int*)malloc(sizeof(int)*6);
  sv[0] = (int)bf;
  sv[1] = inbuflen;
  sv[2] = curchar;
  sv[3] = curcharpos;
  sv[4] = srcfile;
  sv[5] = lineno;
  return sv;
}

void restorestate( int* sv )
{
  strcpy( inbuf, (char*)sv[0] );
  free((void*)sv[0]);
  inbuflen = sv[1];
  curchar = sv[2];
  curcharpos = sv[3];
  srcfile = sv[4];
  lineno = sv[5];
  free(sv);
}


char tokentext[400];
char separator[2] = ".";
int kw;
int radix;
int opkind;
int numvalue; // for Num and Chr; separator itself for Sep

int gettoken()
{
  char* tt;
  if( curchar < 0 ) { curchar = getchar(); lineno = 1; }
  while( curchar==' ' || curchar=='\n' || curchar=='\r' || curchar=='\t' )
  {
    if( curchar=='\n' ) { write( 1, "\n", 1 ); ++lineno; }
    curchar = getchar();
  }
  if( curchar<0 ) return Eof;
  if( curchar>='0' && curchar<='9' )
  {
    tt = tokentext;
    *tt++ = curchar;
    curchar = getchar();
    *tt = '\0';
    if( tokentext[0]=='0' && (curchar=='b' || curchar=='x' || curchar=='B' || curchar=='X') )
    {
      *tt++ = curchar;
      curchar = getchar();
    }
    radix = 10;
    if( tokentext[1]=='b' || tokentext[1]=='B' )
      radix = 2;
    else if( tokentext[1]=='x' || tokentext[1]=='X' )
      radix = 16;
    else if( tokentext[0]=='0' && tokentext[1]>='0' && tokentext[1]<='8' )
      radix = 8;
    while( curchar>='0' && (radix==2 && curchar<='1' || radix==8 && curchar<='7' ||
          curchar<='9' || curchar>='a' && curchar<='f' || curchar>='A' && curchar<='F') )
    {
      *tt++ = curchar;
      curchar = getchar();
    }
    *tt = '\0';
    if( radix==10 ) numvalue = atoi( tokentext, 10 );
    else if( radix==16 ) numvalue = atoi( tokentext+2, 16 );
    else if( radix==2 ) numvalue = atoi( tokentext+2, 2 );
    else numvalue = atoi( tokentext, 8 );
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
    int i;
    for( i=0; i<sizeof(KWS)/sizeof(KWS[0]); ++i )
      if( strcmp( tokentext, KWS[i] )==0 ) { kw = i; return Kw; }
    return Id;
  }
  else if( curchar=='"' )
  {
    tt = tokentext;
    curchar = getchar();
    while( curchar!='"' )
    {
      if( curchar == '\\' )
      {
        curchar = getchar();
        if( curchar=='n' ) curchar = '\n';
        else if( curchar=='r' ) curchar = '\r';
        else if( curchar=='t' ) curchar = '\t';
        else if( curchar=='b' ) curchar = '\b';
        else if( curchar=='0' ) curchar = '\0';
      }
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
    if( curchar == '\\' )
    {
      curchar = getchar();
      if( curchar=='n' ) curchar = '\n';
      else if( curchar=='r' ) curchar = '\r';
      else if( curchar=='t' ) curchar = '\t';
      else if( curchar=='b' ) curchar = '\b';
      else if( curchar=='0' ) curchar = '\0';
    }
    numvalue = curchar;
    curchar = getchar();
    if( curchar!='\'' ) return Err;
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
  else if( curchar=='<' || curchar=='>' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == '=' ) // <= >=
    {
      curchar = getchar();
      opkind = Le; if( ccc=='>' ) opkind = Ge;
    }
    else if( ccc==curchar ) // << >>
    {
      curchar = getchar();
      if( curchar == '=' ) // <<= >>=
      {
        curchar = getchar();
        opkind = AShl; if( ccc=='>' ) opkind = AShr;
      }
      else
      {
        opkind = Shl; if( ccc=='>' ) opkind = Shr;
      }
    }
    else
    {
      opkind = Lt; if( ccc=='>' ) opkind = Gt;
    }
    return Op;
  }
  else if( curchar=='=' || curchar=='*' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == '=' ) // == *=
    {
      curchar = getchar();
      opkind = Eq; if( ccc=='*' ) opkind = AMul;
    }
    else
    {
      opkind = Asg; if( ccc=='*' ) opkind = Mul;
    }
    return Op;
  }
  else if( curchar=='+' || curchar=='-' || curchar=='&' || curchar=='|' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == '=' ) // += -= &= |=
    {
      curchar = getchar();
      opkind = AAdd; if( ccc=='-' ) opkind = ASub;
      else if( ccc=='&' ) opkind = AAnd; else if( ccc=='|' ) opkind = AOr;
    }
    else if( curchar == ccc ) // ++ -- && ||
    {
      curchar = getchar();
      opkind = Inc; if( ccc=='-' ) opkind = Dec;
      else if( ccc=='&' ) opkind = LAnd; else if( ccc=='|' ) opkind = LOr;
    }
    else
    {
      opkind = Add; if( ccc=='-' ) opkind = Sub;
      else if( ccc=='&' ) opkind = And; else if( ccc=='|' ) opkind = Or;
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
      if(curchar>0) curchar = getchar();
      return gettoken();
    }
    else if( curchar == '=' ) // /=
    {
      curchar = getchar();
      opkind = ADiv;
    }
    else if( curchar == '*' ) // /* comment */
    {
      curchar = getchar();
      while(1)
      {
        while( curchar!='*' && curchar>0 )
          curchar = getchar();
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
  else if( curchar=='%' || curchar=='^' )
  {
    char ccc = curchar;
    curchar = getchar();
    if( curchar == '=' ) // %= ^=
    {
      curchar = getchar();
      opkind = AMod; if( ccc=='^' ) opkind = AXor;
    }
    else
    {
      opkind = Mod; if( ccc=='-' ) opkind = Xor;
    }
    return Op;
  }
  else if( curchar=='!' )
  {
    curchar = getchar();
    if( curchar == '=' )
    {
      curchar = getchar();
      opkind = Ne;
    }
    else
    {
      opkind = LNot;
    }
    return Op;
  }
  else if( curchar=='~' )
  {
    curchar = getchar();
    opkind = Not;
    return Op;
  }
  else if( curchar=='#' )
  {
    curchar = getchar();
    return Pre;
  }
  else
  {
    tokentext[0] = curchar;
    tokentext[1] = 0;
    curchar = getchar();
    return Err;
  }
}

int scanfile( char* fn )
{
  srcfile = open( fn, O_RDONLY );
  if( srcfile<=0 ) return 1;

  int t,t1=Err,t2=Err;
  while( (t = gettoken()) != Eof )
  {
    // print t
    if( t==Num )
    {
      char rdx[8];
      write( 1, " ", 1 );
      itoa( radix, rdx, 10 );
      write( 1, rdx, strlen(rdx) );
      write( 1, "#", 1 );
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
      write( 1, KWS[kw], strlen(KWS[kw]) ); // tokentext has it too
    }
    else if( t==Op )
    {
      write( 1, " `", 2 );
      write( 1, &OPS[3*opkind], 3 );
    }
    else if( t==Sep )
    {
      write( 1, " ", 1 );
      write( 1, separator, 1 );
    }
    else if( t==Str )
    {
      write( 1, " \"", 2 );
      write( 1, tokentext, strlen(tokentext) );

      if( t2==Pre && t1==Kw && kw==Include )
      {
        char fni[400];
        strcpy( fni, fn );
        char* dir = strrchr( fni, '/' );
        if( dir != 0 ) ++dir; else dir = strrchr( fni, '\\' );
        if( dir != 0 ) ++dir; else dir = fni;
        strcpy( dir, tokentext );
        write( 1, "\n>>>>>> ", 8 );
        write( 1, fni, strlen(fni) );
        write( 1, "\n", 1 );

        int* sv = saveiostate();
        inbuflen = 0;
        curchar = -1;
        curcharpos = sizeof(inbuf);
        srcfile = -1;
        lineno = 0;
        int rc = scanfile( fni );
        restorestate( sv );
        write( 1, "\n<<<<<<\n", 8 );
      }
    }
    else if( t==Chr )
    {
      write( 1, " \'", 2 );
      char chr[8];
      itoa( numvalue, chr, 10 );
      write( 1, chr, strlen(chr) );
    }
    else if( t==Pre )
    {
      write( 1, " #", 2 );
    }
    else
    {
      write( 1, " ?", 2 );
      write( 1, tokentext, 1 );
    }
    t2 = t1;
    t1 = t;
  }

  close(srcfile);
  return 0;
}

int main( int ac, char** av )
{
  scanfile( av[1] );
  return 0;
}

