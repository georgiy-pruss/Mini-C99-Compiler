  .file "t_ops.c"
  .intel_syntax noprefix
  .def  ___main;  .scl  2;  .type 32; .endef
  .text
  .globl  _main
  .def  _main;  .scl  2;  .type 32; .endef
_main:
LFB0:
  .cfi_startproc
  push  ebp
  .cfi_def_cfa_offset 8
  .cfi_offset 5, -8
  mov ebp, esp
  .cfi_def_cfa_register 5
  and esp, -16
  sub esp, 16
  call  ___main

  mov DWORD PTR [esp+8], 1        # a = 1
  mov DWORD PTR [esp+4], 2        # b = 2
  mov BYTE PTR [esp+15], -1       # c = -1

  cmp DWORD PTR [esp+8], 9        # if( a<10 && b<11 )
  jg  L2
  cmp DWORD PTR [esp+4], 10
  jg  L2

  mov eax, DWORD PTR [esp+8]      # c = 5 - a;
  mov edx, 5
  sub edx, eax
  mov eax, edx
  mov BYTE PTR [esp+15], al
L2:

  cmp DWORD PTR [esp+8], 11       # if( a<12 || b<13 )
  jle L3
  cmp DWORD PTR [esp+4], 12
  jg  L4
L3:
  mov eax, DWORD PTR [esp+8]      # c = 6 - a;
  mov edx, 6
  sub edx, eax
  mov eax, edx
  mov BYTE PTR [esp+15], al
L4:

  mov eax, DWORD PTR [esp+8]      # a = a*b + c;
  imul  eax, DWORD PTR [esp+4]
  mov edx, eax
  movsx eax, BYTE PTR [esp+15]
  add eax, edx
  mov DWORD PTR [esp+8], eax

  mov eax, DWORD PTR [esp+8]      # a = a/b - c;
  cdq
  idiv  DWORD PTR [esp+4]
  mov edx, eax
  movsx eax, BYTE PTR [esp+15]
  sub edx, eax
  mov eax, edx
  mov DWORD PTR [esp+8], eax

  mov eax, DWORD PTR [esp+8]      # a = (a&b) ^ (c|15);
  and eax, DWORD PTR [esp+4]
  mov edx, eax
  movzx eax, BYTE PTR [esp+15]
  or  eax, 15
  movsx eax, al
  xor eax, edx
  mov DWORD PTR [esp+8], eax

  mov eax, DWORD PTR [esp+4]      # a = ~b;
  not eax
  mov DWORD PTR [esp+8], eax

  cmp DWORD PTR [esp+4], 0        # b = !b;
  sete  al
  movzx eax, al
  mov DWORD PTR [esp+4], eax

  mov eax, DWORD PTR [esp+4]      # b = b % a;
  cdq
  idiv  DWORD PTR [esp+8]
  mov DWORD PTR [esp+4], edx

  movzx eax, BYTE PTR [esp+15]    # c = -c;
  neg eax
  mov BYTE PTR [esp+15], al

  movsx eax, BYTE PTR [esp+15]    # a = b<=c;
  cmp eax, DWORD PTR [esp+4]
  setge al
  movzx eax, al
  mov DWORD PTR [esp+8], eax

  movsx eax, BYTE PTR [esp+15]    # a = b>=c;
  cmp eax, DWORD PTR [esp+4]
  setle al
  movzx eax, al
  mov DWORD PTR [esp+8], eax

  mov eax, DWORD PTR [esp+8]      # a = (a==b) < (a!=b);
  cmp eax, DWORD PTR [esp+4]
  sete  al
  movzx edx, al
  mov eax, DWORD PTR [esp+8]
  cmp eax, DWORD PTR [esp+4]
  setne al
  movzx eax, al
  cmp edx, eax
  setl  al
  movzx eax, al
  mov DWORD PTR [esp+8], eax

  mov eax, DWORD PTR [esp+8]

  leave
  .cfi_restore 5
  .cfi_def_cfa 4, 4
  ret
  .cfi_endproc
LFE0:
  .ident  "GCC: (GNU) 5.4.0"
