#include <stdlib.h>
#include <stdio.h>
int printf();
int atoi();

int fib(int n)
{
  if(n <= 2)
    return 1;
  else
    return fib(n-1) + fib(n-2);
}

int main(int argc, char **argv)
{
  int n;
  if(argc < 2)
  {
    printf("usage: fib n\nCompute nth Fibonacci number\n");
    return 1;
  }

  n = atoi(argv[1]);
  printf("fib(%d) = %d\n", n, fib(n, 2));
  return 0;
}
