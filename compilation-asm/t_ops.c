
int main()
{
  int a=1, b=2;
  char c=-1;

  if( a<10 && b<11 ) c = 5 - a;
  if( a<12 || b<13 ) c = 6 - a;

  a = a*b + c;

  a = a/b - c;

  a = (a&b) ^ (c|15);

  a = ~b;

  b = !b;

  b = b % a;

  c = -c;

  a = b<=c;

  a = b>=c;

  a = (a==b) < (a!=b);

  return a;
}
