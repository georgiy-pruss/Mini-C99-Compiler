// debugging in vs2013 http://www.kipirvine.com/asm/debug/vstudio2013/index.htm
// crt file D:\VS2013\VC\crt\src\crtexe.c

int f(int p1, int p2, int p3)
{
  int v1;
  int v2;
  v1 = p1+p2;
  v2 = p3;
  return v1+v2;
}

int main()
{
  int r = f( 7,8,9 );
  return 0;
}
