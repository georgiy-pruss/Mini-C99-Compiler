// gcc -S -masm=intel x.c -o x.s
// gcc -masm=intel x.s -o x.exe


BEGIN
                      .file   "intmain.c"
                      .intel_syntax noprefix

int i0;
                      .comm _i0, 4, 2

char c01;
                      .comm _c01, 1, 0

char c02;
                      .comm _c02, 1, 0

int gl[24];
                      .comm _gl, 96, 5      // 96 = 4*24

char s1[80];
                      .comm _s1, 80, 5

char s2[] = "\0\1\x09\x10\x11" "123ABC" "\x7F\x80" "zzz" "\xFE\xFF";
                      .globl  _s2
                      .data
                      .align 4
_s2:
                      .ascii "\0\1\11\20\21"  // can't be \21123...
                      .ascii "123ABC\177\200zzz\376\377\0"

int write( int f, char* s, int n );
                      <at the very end:>
                      .def  _write; .scl    2;      .type   32;     .endef

int c1 = 123;
                      .globl  _c1
                      .data
                      .align 4
              _c1:
                      .long   123

int a1[] = { 11, 22, 33 };
                      .globl  _a1
                      .align 4
              _a1:
                      .long   11
                      .long   22
                      .long   33

int* a2 = a1;
                      .globl  _a2
                      .align 4
              _a2:
                      .long   _a1          // just var name here

char s1[] = "abcd";
                      .globl  _s1
                      .align 4
              _s1:
                      .ascii "abcd\0"

char* s2 = "ABCD";
                      .globl  _s2
                      .section .rdata,"dr"
              LC1:
                      .ascii "ABCD\0"
                      .data
                      .align 4
              _s2:
                      .long   LC1


enum { e1, e2, e3=3, e4 };
                      // nothing it the code, they are all compile-time only
                      // maybe this can be used:
                      .equ    e1, 0
                      .equ    e2, 1
                      .equ    e3, 3
                      .equ    e4, 4

int strlen( char* s )
                      .text
                      .globl  _strlen
                      .def    _strlen;        .scl    2;      .type   32;     .endef
              _strlen:

{
                      .cfi_startproc
                      push    ebp
                      .cfi_def_cfa_offset 8
                      .cfi_offset 5, -8
                      mov     ebp, esp
                      .cfi_def_cfa_register 5

int n
                      sub     esp, 16

n=0
                      mov     DWORD PTR [ebp-4], 0

i0 = 1;
                      mov     DWORD PTR _i0, 1       // global var
c01 = 2;
                      mov     BYTE PTR _c01, 2       // global var
c02 = 3;
                      mov     BYTE PTR _c02, 3       // global var
gl[20] = 4;
                      mov     DWORD PTR _gl+80, 4    // global item

s1[20] = '5';
                      mov     BYTE PTR _s1+20, 53    // global item


                      mov     DWORD PTR [esp+12], 6  // local var
                      mov     BYTE PTR [esp+11], 7   // local char var
                      mov     DWORD PTR [esp+4], 8
                      mov     BYTE PTR [esp+3], 9    // local char var

c01 = lc1+lc2;
                      movzx   edx, BYTE PTR [esp+11] // local char var
                      movzx   eax, BYTE PTR [esp+3]  // local char var
                      add     eax, edx
                      mov     BYTE PTR _c01, al      // global char var

i0 = c01 + c02;
                      movzx   eax, BYTE PTR _c01     // global char var
                      movsx   edx, al                // ext sign
                      movzx   eax, BYTE PTR _c02     // global char var
                      movsx   eax, al                // ext sign
                      add     eax, edx
                      mov     DWORD PTR _i0, eax     // to global int var

...(int p1,int p2)
int v1
v1 = p1 + p2
                      mov     edx, DWORD PTR [ebp+8]    // parameter 1
                      mov     eax, DWORD PTR [ebp+12]   // parameter 2
                      add     eax, edx
                      mov     DWORD PTR [ebp-4], eax    // local var 1

v2 = p3
                      mov     eax, DWORD PTR [ebp+16]   // parameter 3
                      mov     DWORD PTR [ebp-8], eax    // local var 2

for( (while) *s (post) ++s )
                      jmp     L2
             L3:

++n
                      add     DWORD PTR [ebp-4], 1    // local var n in strlen

<for...>
             L2:
                      mov     eax, DWORD PTR [ebp+8]  // s = 1st arg
                      lea     edx, [eax+1]            // s+1
                      mov     DWORD PTR [ebp+8], edx  // back to s in memory
                      movzx   eax, BYTE PTR [eax]     // *s
                      test    al, al                  // !=0
                      jne     L3

return n
                      mov     eax, DWORD PTR [ebp-4]  // local var n

}
                      leave
                      .cfi_restore 5
                      .cfi_def_cfa 4, 4
                      ret
                      .cfi_endproc

int main()
int main( int ac, char* av[] )
                      .def    ___main;        .scl    2;      .type   32;     .endef

<if data present in main>
                      .section .rdata,"dr"    // located after .def ___main
              LC0:
                      .ascii "\12\12\0"       // "\n\n" converted to octal

                      .section .rdata,"dr"    // not needed if same section
              LC2:
                      .ascii "{[(<>)]}\0"

                      .text                   // no need to put it if we're in .text
                      .globl  _main
                      .def    _main;  .scl    2;      .type   32;     .endef
                      // this def not in intel
              _main:

{ <main>
                      .cfi_startproc        // not in intel
                      push    ebp
                      .cfi_def_cfa_offset 8  // not in intel
                      .cfi_offset 5, -8      // not in intel
                      mov     ebp, esp
                      .cfi_def_cfa_register 5  // not in intel
                      and     esp, -16

<if locals present:>
                      sub     esp, 32

                      call    ___main

a2 = 0;
                      mov     DWORD PTR _a2, 0      // global var

int cc2 = cc1*789;
                      mov     eax, DWORD PTR [esp+28]
                      imul    eax, eax, 789
                      mov     DWORD PTR [esp+24], eax      # cc2

int aa1[] = { -1, -2, -3 };
                      mov     DWORD PTR [esp+4], -1        # aa1[0]
                      mov     DWORD PTR [esp+8], -2        # aa1[1]
                      mov     DWORD PTR [esp+12], -3       # aa1[2]
int* aa2 = aa1;
                      lea     eax, [esp+4]
                      mov     DWORD PTR [esp+20], eax      # aa2

char ss1[] = "xyz";
                      mov     DWORD PTR [esp], 8026488     # ss1  #007a7978

char* ss2 = "{[(<>)]}";
                      mov     DWORD PTR [esp+16], OFFSET FLAT:LC1

int i=0;
                      mov     DWORD PTR [esp+28], 0 // local var i

while( i<ac )
<see also @ L2>
                      jmp     L2
              L3:

write( 1, av[i], 1 )
                      mov     eax, DWORD PTR [esp+28]  // i
                      lea     edx, [0+eax*4]           // i*4 (INTSZ)
                      mov     eax, DWORD PTR [ebp+12]  // av - second arg
                      add     eax, edx                 // av + i*4
                      mov     eax, DWORD PTR [eax]     // *(...)

                      mov     DWORD PTR [esp], eax     // instead of push
                      call    _strlen

                      mov     DWORD PTR [esp+8], edx // 3rd arg to stack from dx
                      mov     DWORD PTR [esp+8], 1   // 3rd arg if was constant
                      mov     DWORD PTR [esp+4], eax // 2nd arg to stack
                      mov     DWORD PTR [esp], 1 // 1st arg to stack
                      call    _write

++i;
                      add     DWORD PTR [esp+28], 1  // local var i

<...( i<ac )>
              L2:
                      mov     eax, DWORD PTR [esp+28] // i
                      cmp     eax, DWORD PTR [ebp+8]  // first arg ac
                      jl      L3


write( 1, "\n\n", 2 );
                      mov     DWORD PTR [esp+8], 2     // will be 3rd arg
                      mov     DWORD PTR [esp+4], OFFSET FLAT:LC0 // data at beginning
                      mov     DWORD PTR [esp], 1       // and 1st arg
                      call    _write

return ac;
                      mov     eax, DWORD PTR [ebp+8] // first arg ac

w/o return
                      mov     eax, 0

}
                      leave
                      .cfi_restore 5
                      .cfi_def_cfa 4, 4
                      ret
                      .cfi_endproc

END
                      .ident  "GCC: (GNU) 5.4.0"
