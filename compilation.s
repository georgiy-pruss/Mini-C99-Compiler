BEGIN
                      .file   "intmain.c"
                      .intel_syntax noprefix

int write( int f, char* s, int n );
                      <at the very end:>
                      .def  _write; .scl    2;      .type   32;     .endef
                      // but not in intel listing!

int strlen( char* s )

                      .text
                      .globl  _strlen
                      .def    _strlen;        .scl    2;      .type   32;     .endef
                      // def is not in intel listing!
              _strlen:

{
                      .cfi_startproc             // not in intel
                      push    ebp
                      .cfi_def_cfa_offset 8      // not in intel
                      .cfi_offset 5, -8
                      mov     ebp, esp           // R2L in intel
                      .cfi_def_cfa_register 5    // not in intel

int n
                      sub     esp, 16

n=0
                      mov     DWORD PTR [ebp-4], 0

for( (while) *s (post) ++s )
                      jmp     L2
             L3:

++n
                      add     DWORD PTR [ebp-4], 1  // local var n in strlen
             L2:
                      mov     eax, DWORD PTR [ebp+8]  // s = 1st arg
                      lea     edx, [eax+1]            // s+1
                      mov     DWORD PTR [ebp+8], edx  // back to s in memory
                      movzx   eax, BYTE PTR [eax]     // *s
                      test    al, al                  // !=0
                      jne     L3

return n
                      mov     eax, DWORD PTR [ebp-4]  // local var n
                      leave
                      .cfi_restore 5              // not in intel
                      .cfi_def_cfa 4, 4           // not in intel
                      ret
                      .cfi_endproc                // not in intel

int main()
int main( int ac, char* av[] )
                      .def    ___main;        .scl    2;      .type   32;     .endef
                      // this def not in intel

<if data present in main>
                      .section .rdata,"dr"
              LC0:
                      .ascii "\12\12\0"       // "\n\n"

                      .text
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
                      movl    $0, %eax

}
                      leave
                      .cfi_restore 5
                      .cfi_def_cfa 4, 4
                      ret
                      .cfi_endproc


END
                      .ident  "GCC: (GNU) 5.4.0"
