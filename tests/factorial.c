#include <stdio.h>

void printf( char* fmt, int a1, int a2 );

int f(int n)
{
  if( n <= 1 ) return 1;
  return n*f(n-1);
}

int main()
{
  for( int n=0; n<=12; ++n ) // 12! is max to fit in int32
    printf( "%d! = %d\n", n, f(n) );
  return 0;
}
