# pseudo commands
  .ascii "Z\0"
  .bss
  .data
  .text
  .section .rdata,"dr"
  .def _assert; .scl 2; .type 32; .endef
  .equ maxargs, 15
  .include "startup.c"
  .globl _assert
  .ident "Georgiy Pruss C99C 0.261"
  .long -1
  .long NAME0
  .space 12
  .space 3*4
  .space 4*maxargs
# no arguments and special cases
  cdq
  cld
  leave
  ret
  repne scasb
  sete al
  setg al
  setge al
  setl al
  setle al
  setne al
  setnz al
  setz al
  test al,al
  test eax,eax
  xor eax,eax
  movzx eax,al
  dec edx
  inc edx
  neg eax
  not ecx
  idiv ebx
  imul eax,ebx
# one argument - variants
  idiv dword ptr _id_table_dim
  imul eax,dword ptr [ebp+8]
  imul eax,dword ptr [ebp-4]
  imul eax,eax,4
  imul eax,eax,600
  lea eax,[eax+4*ebx]
  lea eax,[ebp-12] # op_s
  lea eax,byte ptr [ecx+1]
  movsx eAX,byte ptr [eax]
  movsx eAX,byte ptr [ebp-16] # t
# one argument - immediate
  and eax,255
  or eax,1
  or eax,1024
# one argument - register or immediate
  pop ebx
  push eax
  push ebp
  push -10
  push 0
# one argument - address/name
  jmp C16
  jnz O103
  jz A100
  je SKIP
  call _assert
# two arguments
  add eax,1                     # esp,ecx
  add eaX,dword ptr [ebp+16]
  add eax,dword ptr [ebp-8]
  add eax,dword ptr _rd_char
  add eax,ebx
  sub eax,128
  sub eAX,dword ptr [ebp-4] # b
  sub eax,ebx
  sub esp,8
  cmp al, 32
  cmp eax,128
  cmp eax,dword ptr [ebp+12]
  cmp eax,dword ptr [ebp-8]
  cmp eax,dword ptr _st_dim
  cmp eax,ebx
  cmp ebx, maxargs
  mov byte ptr [edx], 0
  mov byte ptr [ebx],al
  mov dword ptr [ebx],eax
  mov dword ptr [ebp+12],eax
  mov dword ptr [ebp-12],eax
  mov dword ptr _cg_bss_align,eax
  mov dword ptr hStdf+4, eax
  mov al, byte ptr [edx]
  mov eax,123
  mov eax,edx                # ebp,esp ebx,eax
  mov eax,dword ptr [eax]
  mov eax,dword ptr [ebp+12] # ebx   esp+
  mov eax,dword ptr [ebp-16] # ebx   esp-
  mov eAX,dword ptr _OPS     # edx
  mov eax,offset flat:_KWDS  # ecx
# assert it's present
  .intel_syntax noprefix
# ignore
  .file "cc.c"
  .cfi_def_cfa 4,4
  .cfi_def_cfa_offset 8
  .cfi_def_cfa_register 5
  .cfi_endproc
  .cfi_offset 5,-8
  .cfi_restore 5
  .cfi_startproc

