# gcc test.s -o test.exe
# objdump -d test.exe >test.asm
  .file "test.s"
  .intel_syntax noprefix
  .def  ___main;  .scl  2;  .type 32; .endef
  .text
  .globl  _printf
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
  call  ___main

  mov eax,1
  mov ebx,3
  lea eax,[eax+4*ebx]

  push eax
  push OFFSET FLAT:_S1
  call _printf
  add esp,8

  mov eax,1
  mov ebx,3
  lea eax,[4*eax+ebx]

  push eax
  push OFFSET FLAT:_S1
  call _printf
  add esp,8

  mov ebx,500000110  # 110
  lea ebx,[4*ebx+10] # 450
  mov eax,3
  sal eax,2          # 12
  sub ebx,eax        # 450-12 = 438

  push ebx
  push OFFSET FLAT:_S1
  call _printf
  add esp,8

  mov ecx,0x12345678
  mov eax,ecx

  imul ebx                    # f7 eb
  imul DWORD PTR _w1          # f7 2d 6c 30 40 00
  imul DWORD PTR [ebp+8]      # f7 6d 08

  imul eax,ebx                # 0f af c3
  imul eax,DWORD PTR _w1      # 0f af 05 6c 30 40 00
  imul eax,DWORD PTR [ebp+8]  # 0f af 45 08

  imul eax,100                # 6b c0 64           = eax,eax,100
  imul eax,eax,100            # 6b c0 64
  imul eax,30000              # 69 c0 30 75 00 00  = eax,eax,...
  imul eax,eax,30000          # 69 c0 30 75 00 00
  imul eax,2000000000         # 69 c0 00 94 35 77  = eax,eax,...
  imul eax,eax,2000000000     # 69 c0 00 94 35 77

  mov eax,0
  xor eax,eax
  leave
  .cfi_restore 5
  .cfi_def_cfa 4, 4
  ret
  .cfi_endproc
LFE0:

  .section .rdata,"dr"
_S1: .ascii "Int: %d\n\0"
  .align 4
_w1: .long 10

  .ident  "GCC: (GNU) 5.4.0"
