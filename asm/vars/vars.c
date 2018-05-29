// test vars
// gcc -S -masm=intel vars.c -o vars.s
// gcc -c vars.s -o vars.o
// gcc vars.o -nostdlib -lkernel32 -o vars.exe

int iu;                       // 405048                            .bss
char cu;                      // 405000
int i10u[10];                 // 405020
char c10u[10];                // 405004
char* pu;                     // 40504c

int i = 33;                   // 402000 = 21 00 00 00              .data
char c = 34;                  // 402004 = 22
int i10[10] = {100,101,102};  // 402020 = 64 00 00 00 65 00 00 00 66 00 00 00 ...
char c10[10] = "abc";         // 402048 = 61 62 63 00 ...
char* p = "xyz";              // 402054 = 403000

                              // 403000 = 78 79 7a 00              .rdata
                              // 403004 = 30 31 32 33 34 35 00

int main()                    // 401000   [1000=4KB]               .text
{
  iu = i;
  i = 10;
  cu = c;
  c = 'o';
  i10u[0] = i10[0];
  c10u[0] = c10[0];
  pu = p;
  p = "012345";               // 403004

  return i;
}
