        .file   "vars.c"
        .intel_syntax noprefix

        # remove two refs to __main
        # gcc -c vars.s -o vars.o
        # gcc vars.o -nostdlib -lkernel32 -o vars.exe
        # objdump -M intel --insn-width=11 -D vars.exe >vars-exe.dis

        # undef

        .comm   _iu, 4, 2
        .comm   _cu, 1, 0
        .comm   _i10u, 40, 5
        .comm   _c10u, 10, 2
        .comm   _pu, 4, 2

        # initialized

        .globl  _i
        .data
        .align 4
_i:
        .long   33
        .globl  _c
_c:
        .byte   34
        .globl  _i10
        .align 32
_i10:
        .long   100
        .long   101
        .long   102
        .space 28
        .globl  _c10
        .align 4
_c10:
        .ascii "abc\0"
        .space 6
        .align 4
_p:
        .long   LC0

        # constants

        .globl  _p
        .section .rdata,"dr"
LC0:
        .ascii "xyz\0"
LC1:
        .ascii "012345\0"

        # code

#       .def    ___main;        .scl    2;      .type   32;     .endef
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
        and     esp, -16
#       call    ___main

        mov     eax, DWORD PTR _i
        mov     DWORD PTR _iu, eax
        mov     DWORD PTR _i, 10
        movzx   eax, BYTE PTR _c
        mov     BYTE PTR _cu, al
        mov     BYTE PTR _c, 111
        mov     eax, DWORD PTR _i10
        mov     DWORD PTR _i10u, eax
        movzx   eax, BYTE PTR _c10
        mov     BYTE PTR _c10u, al
        mov     eax, DWORD PTR _p
        mov     DWORD PTR _pu, eax
        mov     DWORD PTR _p, OFFSET FLAT:LC1
        mov     eax, DWORD PTR _i

        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE0:
        .ident  "GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
