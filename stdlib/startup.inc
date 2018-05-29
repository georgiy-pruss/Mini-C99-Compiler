        .bss
        .align  4
hHeap:  .space  4  # memory heap, from _GetProcessHeap
hStd:   # standard handles
hStdin:  .space  4
hStdout: .space  4
hStderr: .space  4
cmdline: .space  4     # as returned from _GetCommandLineA
cmdlinecopy: .space  4 # a copy with modifications
        .equ maxargs, 16
argc:   .space  4
argv:   .space  4*maxargs

        .text
        .globl  startup
        .def    startup;  .scl    2;      .type   32;     .endef
startup:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        call    prepare_main
        push    offset flat:argv
        push    dword ptr [argc]
        call    _main
        add     esp, 8
        push    eax # save main result
        call    prepare_exit
        pop     eax
        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc

        # internal proc: sets hHeap, cmdline, argc, argv, hStdout
prepare_main:
        call    _GetProcessHeap@0            # setup memory heap for malloc/free
        mov     dword ptr [hHeap], eax
        call    _GetCommandLineA@0           # get command line as string
        mov     dword ptr [cmdline], eax
        call    strdup_eax                   # allocate copy, will be split with '\0'
        mov     dword ptr [cmdlinecopy], eax # and argv[i] will point inside it
        mov     dword ptr [argc], 0
        mov     ecx, offset flat:argv
        mov     edx, dword ptr [cmdlinecopy]
        dec     edx
SKP:    inc     edx
        mov     al, byte ptr [edx]
        cmp     al, 32
        je      SKP
        cmp     al, 9
        je      SKP
        test    al, al
        jz      DONE
        mov     ebx, dword ptr [argc]
        cmp     ebx, maxargs
        je      DONE
        inc     ebx
        mov     dword ptr [argc], ebx
        mov     dword ptr [ecx], edx
        add     ecx, 4
LAR:    inc     edx
        mov     al, byte ptr [edx]
        test    al, al
        jz      DONE
        cmp     al, 32
        je      EAR
        cmp     al, 9
        jne     LAR
EAR:    mov     byte ptr [edx], 0
        jmp     SKP
DONE:   push    -10
        call    _GetStdHandle@4
        mov     dword ptr [hStdin], eax
        push    -11
        call    _GetStdHandle@4
        mov     dword ptr [hStdout], eax
        push    -12
        call    _GetStdHandle@4
        mov     dword ptr [hStderr], eax
        ret

prepare_exit:
        mov     eax, dword ptr [cmdlinecopy]
        call    free_eax
        ret

strdup_eax:
        push    eax # save, will goto esi
        call    strlen_eax_ecx
        lea     eax, byte ptr [ecx+1]
        push    eax # save len+1, will go to ecx
        call    malloc_eax
        mov     edi, eax
        pop     ecx # restore len+1
        pop     esi # restore src
        rep     movsb
        ret

strlen_eax_ecx:
        mov     edi, eax
        xor     ecx, ecx
        xor     al, al
        not     ecx
        cld
        repne   scasb
        not     ecx
        dec     ecx
        ret

malloc_eax:
        push    eax
        push    0
        push    dword ptr [hHeap]
        call    _HeapAlloc@12
        ret

free_eax:
        push    eax
        push    0
        push    dword ptr [hHeap]
        call    _HeapFree@12
        ret

        .globl  _exit
        .def _exit; .scl 2; .type 32; .endef
_exit:
        .cfi_startproc
        call    _ExitProcess@4
        # no return, so this could be jmp
        .cfi_endproc

        .globl  _malloc
        .def _malloc; .scl 2; .type 32; .endef
_malloc:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        mov     eax,DWORD PTR [ebp+8] # size
        call    malloc_eax
        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc

        .globl  _free
        .def _free; .scl 2; .type 32; .endef
_free:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        mov     eax,DWORD PTR [ebp+8] # size
        call    free_eax
        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc

        .globl  _write
        .def    _write; .scl    2;      .type   32;     .endef
_write:
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        sub     esp, 56
        cmp     DWORD PTR [ebp+8], 2
        jg      L18
        mov     eax, DWORD PTR [ebp+8]
        mov     eax, DWORD PTR hStd[0+eax*4]
        mov     DWORD PTR [ebp+8], eax
        jmp     L19
L18:
        sub     DWORD PTR [ebp+8], 3
L19:
        mov     DWORD PTR [ebp-16], 0 # written
        mov     DWORD PTR [esp+16], 0
        lea     eax, [ebp-16] # written
        mov     DWORD PTR [esp+12], eax
        mov     eax, DWORD PTR [ebp+16]
        mov     DWORD PTR [esp+8], eax
        mov     eax, DWORD PTR [ebp+12]
        mov     DWORD PTR [esp+4], eax
        mov     eax, DWORD PTR [ebp+8]
        mov     DWORD PTR [esp], eax
        call    _WriteFile@20
        sub     esp, 20
        cmp     eax, 0
        je      L20
        mov     eax, DWORD PTR [ebp-16] # written
        jmp     L22
L20:
        mov     eax, -1
L22:
        leave
        .cfi_restore 5
        .cfi_def_cfa 4, 4
        ret
        .cfi_endproc

# TODO
#  .def _open; .scl 2; .type 32; .endef
#  .def _close; .scl 2; .type 32; .endef
#  .def _read; .scl 2; .type 32; .endef

        .def    _GetProcessHeap@0;  .scl 2; .type 32; .endef
        .def    _GetCommandLineA@0; .scl 2; .type 32; .endef
        .def    _GetStdHandle@4;    .scl 2; .type 32; .endef
        .def    _ExitProcess@4;     .scl 2; .type 32; .endef
        .def    _WriteFile@20;      .scl 2; .type 32; .endef

