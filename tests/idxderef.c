int main()
{
  int i;
  char c;
  int* p;
  int* q;
  char* s;
  char* d;
  int x[10];
  char z[15];

  *p = 1;
  *p = i;
  *p = c;
  *p = i+c;
  *(int*)d = 11;

  *d = 0;
  *d = '\0';
  *d = c;
  *d = i;
  *d = c+i;
  *(char*)p = '0';

  *(p+10) = 1;
  *(d+10) = 2;

  *p = *q = 3;
  *++p = 4;

  *q = *p;
  *d = *s;

  i = *p;
  *q = i;

  c = *s;
  *d = c;

  i = x[1];
  x[2] = i;
  x[3] = c;
  *(x+3) = c; // same
  *(3+x) = c;
  x[4] = *p;
  x[5] = q[2];
  x[5] = *(q+2); // same
  x[6] = *(int*)d;
  x[7] = ((int*)d)[3];
  x[7] = *((int*)d + 3); // same

  c = z[1];
  z[2] = c;
  *(z+2) = c; // same
  *(2+z) = c;
  z[3] = i;
  z[4] = *s;
  z[5] = d[2];
  z[6] = *(char*)p;
  z[7] = ((char*)q)[3];

  i = i*(c+1);
  i = i*c;
  i = i*i;
  i = i*3;

  return 0;
}
