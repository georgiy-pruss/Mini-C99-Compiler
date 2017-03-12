        .file   "t_defs.c"
        .intel_syntax noprefix


        .globl  _c1
        .data
        .align 4
_c1:
        .long   123


        .globl  _a1
        .align 4
_a1:
        .long   11
        .long   22
        .long   33


        .globl  _a2
        .align 4
_a2:
        .long   _a1


        .globl  _s1
        .align 4
_s1:
        .ascii "abcd\0"


        .globl  _s2
        .section .rdata,"dr"
LC0:
        .ascii "ABCD\0"
        .data
        .align 4
_s2:
        .long   LC0


        .def    ___main;        .scl    2;      .type   32;     .endef
        .section .rdata,"dr"
LC1:
        .ascii "{[(<>)]}\0"


        .text
        .globl  _main
        .def    _main;  .scl    2;      .type   32;     .endef
_main:
LFB0:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        and     esp, -16          # FFFFFFF0
        sub     esp, 32
        call    ___main

        mov     DWORD PTR _a2, 0

        mov     DWORD PTR [esp+28], 456      # cc1

        mov     eax, DWORD PTR [esp+28]
        imul    eax, eax, 789
        mov     DWORD PTR [esp+24], eax      # cc2

        mov     DWORD PTR [esp+4], -1        # aa1[0]
        mov     DWORD PTR [esp+8], -2        # aa1[1]
        mov     DWORD PTR [esp+12], -3       # aa1[2]

        lea     eax, [esp+4]
        mov     DWORD PTR [esp+20], eax      # aa2

        mov     DWORD PTR [esp], 8026488     # ss1  #007a7978

        mov     DWORD PTR [esp+16], OFFSET FLAT:LC1
        mov     eax, DWORD PTR [esp+28]      # ss2

        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE0:
        .ident  "GCC: (GNU) 5.4.0"
