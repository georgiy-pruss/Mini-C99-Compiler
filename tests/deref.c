enum { A,B,C };

int G[4];
int H[4] = {0}; // not impl

int main()
{
  int v,x; // mov DWORD PTR [esp+12],0
  int* p;  // etc
  int a[3];
  int b[3] = {0}; // not impl

  p = a; // lea eax,[esp+24] + mov DWORD PTR [esp+44],eax
  p = b; // lea eax,[esp+12] + mov DWORD PTR [esp+44],eax
  p = G; // mov DWORD PTR [esp+44], OFFSET FLAT:_G
  p = H; // mov DWORD PTR [esp+44], OFFSET FLAT:_H

  x = A;
  x = (char)1;
  x = (int)"xxx";
  x = B+C;
  x = v;
  x = (int)p;
  x = (int)a;
  x = 10;
  p;
  a;

  x = 11;
  x = *p;
  x = 12;
  x = *a;

  x = 13;
  x = p[1];
  x = 14;
  x = a[1];

  x = 21;
  *p = 1;
  *a = 2;
  *(p+4) = 3;

  return 0;
}
