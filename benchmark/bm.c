#include <stdio.h>

int main()
{
  int i,j,k,n,s,t;
  int N,M;
  N=500;
  M=100;
  i = 0;
  t = 0;
  while( i<N )
  {
    j = 0;
    while( j<M )
    {
      s = 0;
      k = 0;
      n = i*j;
      while( k<n )
      {
        if( k%7==0 || k%11==0 )
          s = s + k/3;
        if( (5*k)%13==0 )
          s = s + k*19;
        ++k;
      }
      t = t + (s>>2);
      ++j;
    }
    ++i;
  }
  printf("%d\n",t); // 1574300082 2.17s 1m27s | 64: 2.00s | tcc64: 5s
  return 0;
}
