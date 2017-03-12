        .file   "t_calls.c"
        .intel_syntax noprefix
        .globl  _nm

        .data
        .align 4
# char nm[] = "file name";
_nm:
        .ascii "file name\0"
# char buf[200];
        .comm   _buf, 200, 5
# int fd;
        .comm   _fd, 4, 2
# char* mem;
        .comm   _mem, 4, 2
# int cnt;
        .comm   _cnt, 4, 2

        .def    ___main;        .scl    2;      .type   32;     .endef
        .text
        .globl  _main
# int main()
        .def    _main;  .scl    2;      .type   32;     .endef
_main:
LFB0:
# {
        .cfi_startproc
        push    ebp
        .cfi_def_cfa_offset 8
        .cfi_offset 5, -8
        mov     ebp, esp
        .cfi_def_cfa_register 5
        and     esp, -16
        sub     esp, 16
        call    ___main
# fd = open( nm, 128, 511 );
        mov     DWORD PTR [esp+8], 511
        mov     DWORD PTR [esp+4], 128
        mov     DWORD PTR [esp], OFFSET FLAT:_nm
        call    _open
        mov     DWORD PTR _fd, eax
# cnt = read( fd, buf, 100 );
        mov     eax, DWORD PTR _fd
        mov     DWORD PTR [esp+8], 100
        mov     DWORD PTR [esp+4], OFFSET FLAT:_buf
        mov     DWORD PTR [esp], eax
        call    _read
        mov     DWORD PTR _cnt, eax
# cnt = write( fd, buf, cnt );
        mov     edx, DWORD PTR _cnt
        mov     eax, DWORD PTR _fd
        mov     DWORD PTR [esp+8], edx
        mov     DWORD PTR [esp+4], OFFSET FLAT:_buf
        mov     DWORD PTR [esp], eax
        call    _write
        mov     DWORD PTR _cnt, eax
# close( fd );
        mov     eax, DWORD PTR _fd
        mov     DWORD PTR [esp], eax
        call    _close
# mem = malloc( 50 );
        mov     DWORD PTR [esp], 50
        call    _malloc
        mov     DWORD PTR _mem, eax
# free( mem )
        mov     eax, DWORD PTR _mem
        mov     DWORD PTR [esp], eax
        call    _free
# exit( 0 )
        mov     DWORD PTR [esp], 0
        call    _exit
# }
        .cfi_endproc
LFE0:
        .ident  "GCC: (GNU) 5.4.0"
        .def    _open;  .scl    2;      .type   32;     .endef
        .def    _read;  .scl    2;      .type   32;     .endef
        .def    _write; .scl    2;      .type   32;     .endef
        .def    _close; .scl    2;      .type   32;     .endef
        .def    _malloc;        .scl    2;      .type   32;     .endef
        .def    _free;  .scl    2;      .type   32;     .endef
        .def    _exit;  .scl    2;      .type   32;     .endef
