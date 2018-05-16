# stdlib for C99C - must be included before other code

    .bss
    .align 4
hHeap: .space 4        # memory heap, from _GetProcessHeap
hStdf: .space 3*4      # standard handles: stdin, stdout, stderr
cmdline: .space 4        # as returned from _GetCommandLineA
cmdlinecopy: .space 4    # a copy with modifications
    .equ maxargs,15 # 15 args is enough for simple programs
argc: .space 4
argv: .space 4*maxargs

    .text
    .globl entrypoint
    .def  entrypoint; .scl 2; .type 32; .endef
entrypoint:
    push  ebp
    mov   ebp,esp
    and   esp,-16
    call  prepare_main
    mov   eax,offset flat:argv
    push  eax
    mov   eax,dword ptr argc
    push  eax
    call  _main
    add   esp,8
    push  eax # save main result
    call  prepare_exit
    pop   eax
    leave
    ret

    # internal proc: sets hHeap, cmdline, argc, argv, hStdout
prepare_main:
    call  _GetProcessHeap@0            # setup memory heap for malloc/free
    mov   dword ptr hHeap,eax
    call  _GetCommandLineA@0           # get command line as string
    mov   dword ptr cmdline,eax
    call  strdup_eax                   # allocate copy, will be split with '\0'
    mov   dword ptr cmdlinecopy,eax # and argv[i] will point inside it
    mov   dword ptr argc,0
    mov   ecx,offset flat:argv
    mov   edx,dword ptr cmdlinecopy
    dec   edx
SKP:
    inc   edx
    mov   al,byte ptr [edx]
    cmp   al,32
    je    SKP
    cmp   al,9
    je    SKP
    test  al,al
    jz    DNE
    mov   ebx,dword ptr argc
    cmp   ebx,maxargs
    je    DNE
    inc   ebx
    mov   dword ptr argc,ebx
    mov   dword ptr [ecx],edx
    add   ecx,4
LAR:
    inc   edx
    mov   al,byte ptr [edx]
    test  al,al
    jz    DNE
    cmp   al,32
    je    EAR
    cmp   al,9
    jne   LAR
EAR:
    mov   byte ptr [edx],0
    jmp   SKP
DNE:
    push  -10
    call  _GetStdHandle@4
    mov   dword ptr hStdf,eax
    push  -11
    call  _GetStdHandle@4
    mov   dword ptr hStdf+4,eax
    push  -12
    call  _GetStdHandle@4
    mov   dword ptr hStdf+8,eax
    ret

prepare_exit:
    mov   eax,dword ptr cmdlinecopy
    call  free_eax
    ret

strdup_eax:
    push  eax # save, will goto esi
    call  strlen_eax_ecx
    lea   eax,byte ptr [ecx+1]
    push  eax # save len+1, will go to ecx
    call  malloc_eax
    mov   edi,eax
    pop   ecx # restore len+1
    pop   esi # restore src
    rep   movsb
    ret

strlen_eax_ecx:
    mov   edi,eax
    xor   ecx,ecx
    xor   eax,eax
    not   ecx
    cld
    repne scasb
    not   ecx
    dec   ecx
    ret

malloc_eax:
    push  eax
    push  0
    mov   eax,dword ptr hHeap
    push  eax
    call  _HeapAlloc@12
    ret

free_eax:
    push  eax
    push  0
    mov   eax,dword ptr hHeap
    push  eax
    call  _HeapFree@12
    ret

    .globl _exit
    .def  _exit; .scl 2; .type 32; .endef
_exit:
    push  ebp
    mov   ebp,esp
    mov   eax,dword ptr [ebp+8] # size
    push  eax
    call  _ExitProcess@4
    # no return from _ExitProcess

    .globl _malloc
    .def  _malloc; .scl 2; .type 32; .endef
_malloc:
    push  ebp
    mov   ebp,esp
    mov   eax,dword ptr [ebp+8] # size
    call  malloc_eax
    leave
    ret

    .globl _free
    .def  _free; .scl 2; .type 32; .endef
_free:
    push  ebp
    mov   ebp,esp
    mov   eax,dword ptr [ebp+8] # size
    call  free_eax
    leave
    ret

    .globl _open
    .def  _open; .scl 2; .type 32; .endef
_open:  # open( char *path, int oflag )
    push  ebp
    mov   ebp,esp
    sub   esp,56
# int f = GENERIC_READ, x = OPEN_EXISTING; // for O_RDONLY
    mov   dword ptr [ebp-12],-2147483648
    mov   dword ptr [ebp-16],3
# if( oflag & (O_WRONLY|O_RDWR) )
    mov   eax,dword ptr [ebp+12]
    and   eax,3
    test  eax,eax
    je    M4
# if( oflag & O_APPEND ) f = FILE_APPEND_DATA; else f = GENERIC_WRITE;
    mov   eax,dword ptr [ebp+12]
    and   eax,8
    test  eax,eax
    je    M5
    mov   dword ptr [ebp-12],4
    jmp   M6
M5:
    mov   dword ptr [ebp-12],1073741824
M6:
# if( oflag & O_RDWR ) f |= GENERIC_READ;
    mov   eax,dword ptr [ebp+12]
    and   eax,2
    test  eax,eax
    je    M7
    mov   eax,dword ptr [ebp-12]
    or    eax,-2147483648
    mov   dword ptr [ebp-12],eax
M7:
# if( oflag & O_CREAT ) x = oflag & O_EXCL ? CREATE_NEW : CREATE_ALWAYS;
# else x = oflag & O_APPEND ? OPEN_ALWAYS : TRUNCATE_EXISTING; // no O_CREAT
    mov   eax,dword ptr [ebp+12]
    and   eax,16
    test  eax,eax
    je    M8
    mov   eax,dword ptr [ebp+12]
    and   eax,64
    test  eax,eax
    je    M9
    mov   eax,1
    jmp   M10
M9:
    mov   eax,2
M10:
    mov   dword ptr [ebp-16],eax
    jmp   M4
M8:
    mov   eax,dword ptr [ebp+12]
    and   eax,8
    test  eax,eax
    je    M11
    mov   eax,4
    jmp   M12
M11:
    mov   eax,5
M12:
    mov   dword ptr [ebp-16],eax
M4:
# int hFile = CreateFileA(path,f,0,0,x,FILE_ATTRIBUTE_NORMAL,0);
    mov   dword ptr [esp+24],0
    mov   dword ptr [esp+20],128
    mov   eax,dword ptr [ebp-16]
    mov   dword ptr [esp+16],eax
    mov   dword ptr [esp+12],0
    mov   dword ptr [esp+8],0
    mov   eax,dword ptr [ebp-12]
    mov   dword ptr [esp+4],eax
    mov   eax,dword ptr [ebp+8]
    mov   dword ptr [esp],eax
    call  _CreateFileA@28
    sub   esp,28
# if( hFile == INVALID_HANDLE_VALUE ) return 0;
# return hFile>=0 ? hFile + 3 : 0;
    mov   ebx,dword ptr [ebp-20]
    mov   ebx,eax
    cmp   ebx,-1
    je    M15
M13:
    cmp   ebx,0
    js    M15
    mov   eax,ebx
    add   eax,3
    jmp   M14
M15:
    mov   eax,0
M14:
    leave
    ret

    .globl _read
    .def  _read; .scl 2; .type 32; .endef
_read:  # read( int fd, char* buf, int count )
# if( fd < 3 ) fd = hStdf[fd]; else fd -= 3;
# int read = 0;
# int b = ReadFile(fd, buf, count, &read, 0);
# return b ? read : -1; // read=0 means EOF
    push  ebp
    mov   ebp,esp
    sub   esp,56
    cmp   dword ptr [ebp+8],2
    jg    M18
    mov   ebx,dword ptr [ebp+8]
    mov   eax,offset flat:hStdf
    lea   eax,[eax+4*ebx]
    mov   eax,dword ptr [eax]
    mov   dword ptr [ebp+8],eax
    jmp   M19
M18:
    sub   dword ptr [ebp+8],3
M19:
    mov   dword ptr [ebp-16],0
    mov   dword ptr [esp+16],0
    lea   eax,[ebp-16]
    mov   dword ptr [esp+12],eax
    mov   eax,dword ptr [ebp+16]
    mov   dword ptr [esp+8],eax
    mov   eax,dword ptr [ebp+12]
    mov   dword ptr [esp+4],eax
    mov   eax,dword ptr [ebp+8]
    mov   dword ptr [esp],eax
    call  _ReadFile@20
    sub   esp,20
    mov   dword ptr [ebp-12],eax
    cmp   dword ptr [ebp-12],0
    je    M20
    mov   eax,dword ptr [ebp-16]
    jmp   M22
M20:
    mov   eax,-1
M22:
    leave
    ret

    .globl _write
    .def  _write; .scl 2; .type 32; .endef
_write:
# if( fd < 3 ) fd = hStdf[fd]; else fd -= 3;
# int written = 0;
# int b = WriteFile(fd, buf, count, &written, 0);
# return b ? written : -1;
    push  ebp
    mov   ebp,esp
    sub   esp,56
    cmp   dword ptr [ebp+8],2
    jg    M24
    mov   ebx,dword ptr [ebp+8]
    mov   eax,offset flat:hStdf
    lea   eax,[eax+4*ebx]
    mov   eax,dword ptr [eax]
    mov   dword ptr [ebp+8],eax
    jmp   M25
M24:
    sub   dword ptr [ebp+8],3
M25:
    mov   dword ptr [ebp-16],0
    mov   dword ptr [esp+16],0
    lea   eax,[ebp-16]
    mov   dword ptr [esp+12],eax
    mov   eax,dword ptr [ebp+16]
    mov   dword ptr [esp+8],eax
    mov   eax,dword ptr [ebp+12]
    mov   dword ptr [esp+4],eax
    mov   eax,dword ptr [ebp+8]
    mov   dword ptr [esp],eax
    call  _WriteFile@20
    sub   esp,20
    mov   dword ptr [ebp-12],eax
    cmp   dword ptr [ebp-12],0
    je    M26
    mov   eax,dword ptr [ebp-16]
    jmp   M28
M26:
    mov   eax,-1
M28:
    leave
    ret

    .globl _close
    .def  _close; .scl 2; .type 32; .endef
_close:
# if( fd < 3 ) return -1;
# fd -= 3;
# return CloseHandle( fd ) ? 0 : -1;
    push  ebp
    mov   ebp,esp
    sub   esp,24
    cmp   dword ptr [ebp+8],2
    jg    M30
    mov   eax,-1
    jmp   M31
M30:
    sub   dword ptr [ebp+8],3
    mov   eax,dword ptr [ebp+8]
    mov   dword ptr [esp],eax
    call  _CloseHandle@4
    sub   esp,4
    test  eax,eax
    je    M32
    mov   eax,0
    jmp   M31
M32:
    mov   eax,-1
M31:
    leave
    ret

    .globl _lseek
    .def  _lseek; .scl 2; .type 32; .endef
_lseek: # lseek( int fd, int offset, int whence )
# if( fd < 3 ) return 0;
# fd -= 3;
# int md = whence==SEEK_END ? FILE_END : (whence==SEEK_CUR ? FILE_CURRENT : FILE_BEGIN );
# int r = SetFilePointer( fd, offset, 0, md );
# return r == INVALID_SET_FILE_POINTER ? -1 : r;
    push  ebp
    mov   ebp,esp
    sub   esp,40
    cmp   dword ptr [ebp+8],2
    jg    M35
    mov   eax,0
    jmp   M36
M35:
    sub   dword ptr [ebp+8],3
    cmp   dword ptr [ebp+16],2
    je    M37
    cmp   dword ptr [ebp+16],1
    sete  al
    movzx eax,al
    jmp   M38
M37:
    mov   eax,2
M38:
    mov   dword ptr [ebp-12],eax
    mov   eax,dword ptr [ebp-12]
    mov   dword ptr [esp+12],eax
    mov   dword ptr [esp+8],0
    mov   eax,dword ptr [ebp+12]
    mov   dword ptr [esp+4],eax
    mov   eax,dword ptr [ebp+8]
    mov   dword ptr [esp],eax
    call  _SetFilePointer@16
    sub   esp,16
    mov   dword ptr [ebp-16],eax
    mov   eax,dword ptr [ebp-16]
M36:
    leave
    ret

    .def  _GetCommandLineA@0; .scl 2; .type 32; .endef
    .def  _GetProcessHeap@0;  .scl 2; .type 32; .endef
    .def  _GetStdHandle@4;    .scl 2; .type 32; .endef
    .def  _SetFilePointer@16; .scl 2; .type 32; .endef
    .def  _CreateFileA@28;    .scl 2; .type 32; .endef
    .def  _ReadFile@20;       .scl 2; .type 32; .endef
    .def  _WriteFile@20;      .scl 2; .type 32; .endef
    .def  _CloseHandle@4;     .scl 2; .type 32; .endef
    .def  _HeapAlloc@12;      .scl 2; .type 32; .endef
    .def  _HeapFree@12;       .scl 2; .type 32; .endef
    .def  _ExitProcess@4;     .scl 2; .type 32; .endef

