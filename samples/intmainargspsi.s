    .file "intmainargsps.c"
    .intel_syntax noprefix
    .text
    .globl  _strlen
  _strlen:
  LFB0:
    push  ebp
    mov ebp, esp
    sub esp, 16
    mov DWORD PTR [ebp-4], 0

    jmp L2
  L3:
    add DWORD PTR [ebp-4], 1
  L2:
    mov eax, DWORD PTR [ebp+8]
    lea edx, [eax+1]
    mov DWORD PTR [ebp+8], edx
    movzx eax, BYTE PTR [eax]
    test  al, al
    jne L3
    mov eax, DWORD PTR [ebp-4]
    leave
    ret
  LFE0:
    .section .rdata,"dr"
  LC0:
    .ascii "\12\0"
    .text
    .globl  _main
  _main:
  LFB1:
    push  ebp
    mov ebp, esp
    and esp, -16
    sub esp, 32
    call  ___main

    mov DWORD PTR [esp+28], 0

    jmp L6
  L7:
    mov eax, DWORD PTR [esp+28]
    lea edx, [0+eax*4]

    mov eax, DWORD PTR [ebp+12]
    add eax, edx
    mov eax, DWORD PTR [eax]
    mov DWORD PTR [esp], eax
    call  _strlen

    mov edx, eax
    mov eax, DWORD PTR [esp+28]
    lea ecx, [0+eax*4]

    mov eax, DWORD PTR [ebp+12]
    add eax, ecx
    mov eax, DWORD PTR [eax]
    mov DWORD PTR [esp+8], edx
    mov DWORD PTR [esp+4], eax
    mov DWORD PTR [esp], 1

    call  _write

    mov DWORD PTR [esp+8], 1

    mov DWORD PTR [esp+4], OFFSET FLAT:LC0

    mov DWORD PTR [esp], 1

    call  _write

    add DWORD PTR [esp+28], 1

  L6:
    mov eax, DWORD PTR [esp+28]
    cmp eax, DWORD PTR [ebp+8]
    jl  L7
    mov eax, DWORD PTR [ebp+8]
    leave
    ret
  LFE1:
    .ident  "GCC: (GNU) 5.4.0"
