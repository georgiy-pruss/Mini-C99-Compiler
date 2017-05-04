int f(int x)
{
  return 2*x;
}

int main()
{
  int a[4]={1,f(1),f(f(1)),f(f(f(1)))};
  return a[3];
}

