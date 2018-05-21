# gcc -c all.s -o all.o && objdump -M intel --insn-width=11 -d all.o | untab.py >all.pp

  # blah blah blah
  .file "cc.c" # <---------------------------- TODO all pseudocommands
  .intel_syntax noprefix
  .include "null.s"
  .data
_tL:
  .long -1
  .long S9 # address of S9
  .section .rdata,"dr"
  .align 4
_ZX:
S9:
  .ascii "'\12\0"
Z96: .ascii "--help\0"
  .ascii "-2147483648\0"
  .ascii "z\0"
  .bss
_assert:
_lseek: # label with comment
hStdf: .space 12    # standard handles: stdin, stdout, stderr
argc: .space 4
argv:
      .space 60
  .globl _assert
  .def  _assert; .scl 2; .type 32; .endef
  #.cfi_def_cfa 4,4 <---------------------------- TODO all pseudocommands
  #.cfi_def_cfa_offset 8
  #.cfi_def_cfa_register 5
  #.cfi_endproc
  #.cfi_offset 5,-8
  #.cfi_restore 5
  #.cfi_startproc
  .text
  # 1:1
strdup_eax:
#------------------- done
  cdq
  cld
  leave
  ret
  rep   movsb
  repne scasb
  # stack
  push  -10
  push  0
  push  100
  push  12345678
  push  -123456789
  nop
  push  eax # save, will goto esi
  push  ecx
  push  ebp
  pop eax
  pop ecx # restore len+1
  pop esi # restore src
  pop ebx
  # unary ops
  neg eax
  neg ebx
  not eax
  not ecx
  # flag ops
  sete  al
  setg  al
  setge al
  setl  al
  setle al
  setne al
  setnz al
  setz  al
  # some ops
  test al,al
  test eax,eax
  idiv ebx
  imul eax,eax,4
  imul eax,eax,66
  imul eax,eax,256
  imul eax,eax,600
  imul eax,ebx
  # binops with immed
  add eax,5
  add ecx,5
  add edx,5
  add ebx,5
  add esp,5
  add ebp,5
  add esi,5
  add edi,5
  add eax,5
  or  eax,5
  and eax,5
  sub eax,5
  xor eax,5
  cmp eax,5
  add eax,1
  add eax,9
  add ecx,1
  add ecx,4
  add ebx,1
  add edx,1
  add esp,8
  add esp,12
  and eax,16
  and eax,2
  sub eax,1
  sub eax,48
  or  eax,1
  or  eax,32
  cmp eax,0
  cmp eax,1
  cmp eax,10
  and esp,-16
  cmp ebx,-1
  cmp ebx,0
  cmp ebx,123
  sub ecx,1
  sub edx,1
  sub esp,76
  add eax,12345
  and eax,255
  or  eax,-21474836
  or  eax,-2147483648
  cmp eax,-8888888
  cmp eax,500
  sub eax,128
  xor eax,3333
  xor eax,-222
  # binops al,immed
  cmp al,32
  cmp al,9
  # binops reg,reg
  add eax,eax
  add eax,ecx
  add eax,edx
  add eax,ebx
  add  eax,eax
  add  ecx,eax
  add  edx,eax
  add  ebx,eax
  add eax,eax
  add ecx,ecx
  add edx,edx
  cmp  eax,eax
  sub  eax,eax
  xor  eax,eax
  and  eax,eax
  or   eax,eax
  cmp eax,ebx
  sub eax,ebx
  sub ecx,ebx
  sub ecx,eax
  xor ecx,ecx
  # movzx
  movzx eax,al
  # move reg,reg
  mov eax,eax
  mov eax,edx
  mov eax,ecx
  mov eax,ebx
  mov edx,eax
  mov ecx,eax
  mov ebx,eax
  mov ebp,esp
  mov edi,eax
  # mov reg,immed
  mov eax,1
  mov ecx,1
  mov ebx,10
  mov eax,-1
  mov eax,5
  mov eax,127
  mov eax,128
  mov ebx,256
  mov eax,1009
  mov eax,50000
  mov eax,12345678
  mov ebx,16777216
  mov eax,2147483647
  mov ecx,-16777216
  mov esi,-1111
  mov edi,-11
  mov edx,0x1234567
  mov edx,0x87654321
  # mov al,memory
  mov al,byte ptr [eax]
  mov al,byte ptr [ecx]
  mov al,byte ptr [edx]
  mov al,byte ptr [ebx]
  mov al,byte ptr [esp] # special cases esp (+24) ebp (+00)
  mov al,byte ptr [ebp]
  # mov al,memory
  mov al,byte ptr [ebp-16]   #    8a 45 f0
  mov al,byte ptr [ebx-16]   #    ...
  mov al,byte ptr [esp-16]   #    ...
  # mov*
  movsx eax,byte ptr [eax]   # only eax,[eax]
  # movsz
  movsx eax,byte ptr [ebp-16]  # 0f be 45 f0
  movsx eax,byte ptr [esp-16]
  movsx eax,byte ptr [edx+12]
  movsx eax,byte ptr [edi+12]
  # mov reg,memory
  mov eax,dword ptr [eax]
  mov ecx,dword ptr [eax]
  mov eax,dword ptr [ecx]
  mov ebx,dword ptr [esi]
  mov eax,dword ptr [esp] # special cases esp (+24) ebp (+00)
  mov eax,dword ptr [ebp]
  mov eax,dword ptr [ebp-12] # block_local_offset
  mov eax,dword ptr [ebp+8] # ok
  mov ebx,dword ptr [ebp+8] # n
  mov ebx,dword ptr [ebp-28] # i
  mov eax,dword ptr [ebx+666]
  mov ebx,dword ptr [esp+4]    # special case esp
  mov esi,dword ptr [esp+8888]
  # mov byte,al
  mov byte ptr [edx],al
  mov byte ptr [ebx],al
  # move memory,reg
  mov dword ptr [eax],eax
  mov dword ptr [edx],eax
  mov dword ptr [ecx],eax
  mov dword ptr [ebx],eax
  mov dword ptr [esp],eax # special case esp ebp
  mov dword ptr [esp],ebx
  mov dword ptr [ebp],eax
  mov dword ptr [ebp],ecx
  mov dword ptr [eax],edx
  mov dword ptr [ecx],edx
  # mov memory,reg
  mov dword ptr [edx+4],eax
  mov dword ptr [edx+4],ecx
  mov dword ptr [ebp-12],eax
  mov dword ptr [ebp+8],eax
  mov dword ptr [esp+12],eax
  mov dword ptr [esp+4],eax
  mov dword ptr [esp+8],eax
  mov dword ptr [ebp+8000],eax
  mov dword ptr [ebp-8000],eax
  mov dword ptr [esp+8000],eax
  mov dword ptr [esp-8000],eax
  mov dword ptr [ebx+8000],eax
  mov dword ptr [ebx-8000],eax
  # mov bytememory,immed (no mov byte ptr [reg+ofs],immed)
  mov byte ptr [eax],0
  mov byte ptr [edx],0
  mov byte ptr [edx],120
  mov byte ptr [edx],-120
  mov byte ptr [edx],0xff
  # mov memory,immed (no mov dword ptr [reg],immed)
  mov dword ptr [edx+8],0
  mov dword ptr [esp+8],0
  mov dword ptr [esp+20],128
  mov dword ptr [esp+222],128
  mov dword ptr [ebp-8],15
  mov dword ptr [ebp-12],-2147483648
  mov dword ptr [ebp-12],1073741824
  mov dword ptr [ebp-1220],1073741824
  # lea
  lea eax,[ecx]
  lea eax,[ecx+1]
  lea eax,[ebp]
  lea eax,[ebp+8]
  lea eax,[ebp+448]
  lea eax,[ebp-16]
  lea eax,[ebp-68] # cmd
  lea eax,[esp]
  lea eax,[esp+8]
  lea eax,[esp+888]
  lea eax,[esp-12]
  lea eax,[eax+4*ebx]
  lea eax,[ebx+4*eax]
  # ops with eax,memory
  imul eax,dword ptr [ebp-4] # v
  imul eax,dword ptr [ebp-8] # itemsz
  imul eax,dword ptr [ebp-888]
  imul eax,dword ptr [ebp+8] # n
  add eax,dword ptr [ebp-12] # i
  add eax,dword ptr [ebp+12] # nargs
  cmp eax,dword ptr [ebp-12] # e
  cmp eax,dword ptr [ebp+8] # id
  sub eax,dword ptr [ebp-24] # items
  # binop memory,immed
  cmp dword ptr [ebp-12],0
  cmp dword ptr [ebp+16],2
  cmp dword ptr [ebp+8],2
  cmp dword ptr [ebp+400],2
  cmp dword ptr [ebp+8],2222
  cmp dword ptr [ebp+400],2222
  add dword ptr [ebp+8],3 # not used probably but let's see
  sub dword ptr [ebp+8],3
  sub dword ptr [ebp+444],3
  sub dword ptr [ebp+8],3333
  sub dword ptr [ebp+444],3333

#------------------- TODO INDEX MEMORY

  nop
  nop


#------------------- TODO SYMBOLIC MEMORY

  mov eax,dword ptr argc
  mov edx,dword ptr argc
  mov ebx,dword ptr argc
  mov eax,OFFSET FLAT:S1
  mov eax,offset flat:argv
  mov ecx,offset flat:argv
  # store
  mov dword ptr argc,0
  mov dword ptr argc,eax
  mov dword ptr hStdf+4,eax
  mov dword ptr argc,ebx

  add eax,dword ptr _ZX
  cmp eax,dword ptr _tL

  # spec ops
  idiv dword ptr argc
  nop
  nop
  nop

  # long jums
  jmp FAR # e9 0x00010210
  nop
  je  FAR # 0f 84 xxxxxxxx
  jne FAR #    85
  js  FAR #    88
  jns FAR #    89
  jl  FAR #    8c
  jge FAR #    8d
  jle FAR #    8e
  jg  FAR #    8f
  nop
  # jump, call
  jmp M0 # eb 16
  nop
  je  M0 # 74 xx
  jz  M0
  jne M0 # 75
  jnz M0
  js  M0 # 78
  jns M0 # 79
  jl  M0 # 7c
  jge M0 # 7d
  jle M0 # 7e
  jg  M0 # 7f
  nop
M0:
  call strdup_eax       # e8 xx xx xx xx - relative address
  call _CloseHandle@4
  call _assert

  .space 200
FAR:
  ret

  .ident  "Georgiy Pruss C99C 0.261497"

