#include <stdlib.h>
#include <stdio.h>

void printf( char* fmt, int a1, int a2 );
int atoi( char* s );

int fib(int n)
{
  //printf( "f %d\n", n );
    if (n <= 2)
        return 1;
    else
        return fib(n-1) + fib(n-2);
}

int main( int argc, char** argv )
{
  int n;
  if( argc < 2 )
  {
    printf( "%s\n%s\n", "usage: fib n", "compute n-th Fibonacci number" );
    return 1;
  }
  // n = atoi(argv[1]);
  for( n=0; n<=13; ++n )
    printf( "fib(%d) = %d\n", n, fib(n) );
  return 0;
}
