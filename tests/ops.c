enum { MINUS_ONE=-1 };

int n[10];
char t[20];

int main()
{
  int i,j,k;
  int m[10];
  int* p;
  int* q;
  char c;
  char s[20];
  char *d;
  char *e;

  i = 0;
  j = 1;
  k = 1000000000;
  c = MINUS_ONE;
  d = "abcd";

  i = j;
  k = j = 1;
  k = j = i;
  k = c = i;

  k = c;
  c = k;

  k = (int)c;
  c = (char)k;

  p = m;
  d = (char*)m;
  e = s;
  q = (int*)s;

  p = n;
  d = t;

  i = -1;
  j = ~2;
  k = !3;
  k = c = (char)!0;

  k = i && j;
  k = i || j;

  k = c && i || d && j;
  k = s || p && q || m;

  i == 0;
  i == 1;
  i == j;
  i == c;
  i == 1+1;

  c == 0;
  c == 2;
  c == i;
  c == c;

  p == q;
  p == (int*)d;
  p == 0;
  p == q+1;
  p == q+i;
  p == q+(i*2);

  i != j;
  d != e;
  d != 0;
  d != s+1;

  i < 1;
  i <= 2;
  i > 3;
  i >= 4;

  c < 5;
  c < *s;

  i < j;
  i < c;
  i < j+1;

  i & 0377;
  i & j;
  i ^ j;
  i ^ j & k;
  i | j ^ k;
  c & i ^ j | k;

  i * 3;
  i * k;
  i * (2*i);

  i*k + j*c;

  i / 10;
  i / j;
  i / (int)c;

  i % 10;
  i % j;
  i % (int)c;

  return 0;
}
