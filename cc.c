#include "cclib.c"


int main( int argc, char** argv )
{
  int i = 0;
  /*while( i<argc )*/
  {
    //char a[200];
    //itoa(
    //write( STDOUT_FILENO, "Hello world!\n", 13 );
  }

  int a[] = {0,1,2,3,8,9,10,11,14,15,16,17,31,32,33,1000,1024,1750,32768,32769,1234567890,0x7fffffff};
  for(i=0;i<sizeof(a)/sizeof(a[0]);++i)
  {
    int k, r;
    char x[100];
    itoa( a[i], x, 10 ); put(x);
    itoa( a[i], x, 2 ); put( "  2: " ); put(x);
    itoa( a[i], x, 8 ); put("  8: " ); put(x);
    itoa( a[i], x, 16 ); put( "  16: " ); put(x);
    itoa( -a[i], x, 36 ); put( "  36: " ); put(x);
    for( r=2; r<=36; ++r )
    {
      itoa( a[i], x, r ); k = atoi( x, r ); assert( k==a[i], "k==a[i]" );
      strupr( x ); k = atoi( x, r ); assert( k==a[i], "k==a[i], uppercase" );
    }
    put("\n");
  }
  char name[100];
  put( "Your name: " );
  int n = read( STDIN_FILENO, name, sizeof(name) );
  if( n>0 )
  {
    name[n] = '\0';
    write( STDERR_FILENO, name, n );
  }
  int f = open( "cc.c", O_RDONLY );
  if( f>0 )
  {
    int MAXBUF = 20000;
    char* buf = malloc(MAXBUF);
    int n = read( f, buf, MAXBUF );
    if( n>=0 )
    {
      int t = open( "cc.copy", O_WRONLY|O_CREAT|O_EXCL, 0777 );
      if( t>0 )
      {
        write( t, buf, n );
        close( t );
      }
    }
    free( buf );
    close( f );
  }
  exit(0);
}

/*
ax bx cx dx si di bp sp

push r
pop  r
mov  r,rs
add  r,rs  sub mul div and or xor
lea  r,m
ldw  r,m
ldb  r,m  ; expanded sign bit
stw  r,m
stb  r,m
jmp  a
cmp  r,rs
jeq  a     jne jlt jle jgt jge
call a
ret
*/

/*

type name [= value];
type name[ [value] ] [= {value[,...]}];
type name ( [args] );
type name ( [args] ) { body }


type name [= expr][, ...];
type: void|char|int [*][...]

if( expr ) stmt [else stmt]
while( expr ) stmt
for( expr; expr; expr ) stmt
return expr;
expr;
break;

expr: lvalue [=|+=|-=|...] rvalue

*/
