// gcc -S -masm=intel t_defs.c -o t_defs.s
//     ... -g -c -Wa,-alh
// gcc -masm=intel t_defs.s -o t_defs.exe

int c1 = 123;
/* int c2 = c1;              // must be constant! */
int a1[] = { 11, 22, 33 };
int* a2 = a1;
char s1[] = "abcd";
char* s2 = "ABCD";
enum { e1, e2, e3=3, e4 };

int main()
{
  a2 = 0;

  int cc1 = 456;
  int cc2 = cc1*789;
  int aa1[] = { -1, -2, -3 };
  int* aa2 = aa1;
  char ss1[] = "xyz";
  char* ss2 = "{[(<>)]}";
  enum { ee1, ee2, ee3=33, ee4 };
  int ii = e2 + ee3;

  return cc1;
}
