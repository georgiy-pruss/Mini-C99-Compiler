        .file   "t_procs.c"
        .intel_syntax noprefix
        .text

# void proc_v_v() {}
        .globl  _proc_v_v
        .def    _proc_v_v;      .scl    2;      .type   32;     .endef
_proc_v_v:
LFB0:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5

        nop

        pop     ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE0:

# int proc_i_c( char c ) { return c+1; }
        .globl  _proc_i_c
        .def    _proc_i_c;      .scl    2;      .type   32;     .endef
_proc_i_c:
LFB1:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5

        sub     esp, 4                     # for temp var, char
        mov     eax, DWORD PTR [ebp+8]     # arg-1
        mov     BYTE PTR [ebp-4], al       # temp var
        movsx   eax, BYTE PTR [ebp-4]      # Move byte to doubleword, sign-extension
        add     eax, 1

        leave                              # mov esp, ebp & pop ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE1:

# char proc_c_i( int i ) { return (char)(i-1); }
        .globl  _proc_c_i
        .def    _proc_c_i;      .scl    2;      .type   32;     .endef
_proc_c_i:
LFB2:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5

        mov     eax, DWORD PTR [ebp+8]     # temp var in eax -- from arg-1
        sub     eax, 1
                                           # ret char is the same as ret int
        pop     ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE2:

# void proc_ip_v( int i, int* p ) { *p = i; }
        .globl  _proc_ip_v
        .def    _proc_ip_v;     .scl    2;      .type   32;     .endef
_proc_ip_v:
LFB3:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5

        mov     eax, DWORD PTR [ebp+12]  # arg-2
        mov     edx, DWORD PTR [ebp+8]   # arg-1
        mov     DWORD PTR [eax], edx

        nop

        pop     ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE3:

# void proc_cs_v( char c, char* s ) { *s = c; }
        .globl  _proc_cs_v
        .def    _proc_cs_v;     .scl    2;      .type   32;     .endef
_proc_cs_v:
LFB4:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5

        sub     esp, 4                     # temp var for char

        mov     eax, DWORD PTR [ebp+8]     # arg-1
        mov     BYTE PTR [ebp-4], al       # making char
        mov     eax, DWORD PTR [ebp+12]    # arg-2
        movzx   edx, BYTE PTR [ebp-4]      # Move byte to doubleword, zero-extension
        mov     BYTE PTR [eax], dl

        nop

        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE4:

# void proc_ipx_v( int i, int* p, int** x ) { *x = p + i; }
        .globl  _proc_ipx_v
        .def    _proc_ipx_v;    .scl    2;      .type   32;     .endef
_proc_ipx_v:
LFB5:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5

        mov     eax, DWORD PTR [ebp+8]     # arg-1 i
        lea     edx, [0+eax*4]                       # i*4
        mov     eax, DWORD PTR [ebp+12]    # arg-2
        add     edx, eax                             # p + i*4
        mov     eax, DWORD PTR [ebp+16]    # arg-3
        mov     DWORD PTR [eax], edx                 # *x = ...

        nop

        pop     ebp
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc
LFE5:
        .ident  "GCC: (GNU) 5.4.0"

