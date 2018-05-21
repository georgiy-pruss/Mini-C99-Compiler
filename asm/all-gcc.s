
  # 1
  # 999
  # internal proc: sets hHeap, cmdline, argc, argv, hStdout
  .align 4
  .ascii "'\12\0"
  .ascii "--help\0"
  .ascii "-2147483648\0"
  .ascii "z\0"
  .bss
  .cfi_def_cfa 4,4
  .cfi_def_cfa_offset 8
  .cfi_def_cfa_register 5
  .cfi_endproc
  .cfi_offset 5,-8
  .cfi_restore 5
  .cfi_startproc
  .data
  .def  _close; .scl 2; .type 32; .endef
  .def  entrypoint; .scl 2; .type 32; .endef
  .equ maxargs,15 # 15 args is enough for simple programs
  .file "cc.c"
  .globl _warn
  .globl _write
  .globl entrypoint
  .ident  "Georgiy Pruss C99C 0.261497"
  .include "startup.s"
  .intel_syntax noprefix
  .long -1
  .long S9
  .section .rdata,"dr"
  .space 12
  .space 8000
  .text
  add ecx,4
  add esp,8
  add eax,1
  add eax,9
  add ecx,1
  add ebx,1
  add edx,1
  add eax,dword ptr [ebp-12] # i
  add eax,dword ptr [ebp+12] # nargs
  add eax,dword ptr _ZX
  add eax,ebx
  add esp,12
  add esp,8

  and eax,16
  and eax,2
  and esp,-16
  and eax,255

  call strdup_eax                   # allocate copy, will be split with '\0'
  call _CloseHandle@4
  call _assert
  cdq
  cld

  cmp al,32
  cmp al,9
  cmp dword ptr [ebp-12],0
  cmp dword ptr [ebp+16],2
  cmp dword ptr [ebp+8],2
  cmp ebx,-1
  cmp ebx,0
  cmp ebx,maxargs
  cmp eax,0
  cmp eax,1
  cmp eax,10
  cmp eax,500
  cmp eax,dword ptr [ebp-12] # e
  cmp eax,dword ptr [ebp+8] # id
  cmp eax,dword ptr _tL
  cmp eax,ebx

  idiv dword ptr _id_table_dim
  idiv ebx
  imul eax,dword ptr [ebp-4] # v
  imul eax,dword ptr [ebp-8] # itemsz
  imul eax,dword ptr [ebp-8] # n_args
  imul eax,dword ptr [ebp-8] # words
  imul eax,dword ptr [ebp+8] # n
  imul eax,eax,256
  imul eax,eax,4
  imul eax,eax,600
  imul eax,eax,66
  imul eax,ebx

  je    DNE
  jg    M18
  jmp   M10
  jmp Z96
  jne LAR
  jnz O103
  jnz O91
  js  M15
  jz  DNE
  lea eax,[eax+4*ebx]
  lea eax,[ebp-16]
  lea eax,byte ptr [ecx+1]
  lea eax,[eax+4*ebx]
  lea eax,[ebp-12] # s
  lea eax,[ebp-4] # o
  lea eax,[ebp-68] # cmd
  leave
  mov   al,byte ptr [edx]
  mov   byte ptr [edx],0
  mov   dword ptr [ebp-12],-2147483648
  mov   dword ptr [ebp-12],1073741824
  mov   dword ptr [ebp-12],eax
  mov   dword ptr [ebp+8],eax
  mov   dword ptr [ecx],edx
  mov   dword ptr [esp],eax
  mov   dword ptr [esp+12],eax
  mov   dword ptr [esp+20],128
  mov   dword ptr [esp+4],eax
  mov   dword ptr [esp+8],0
  mov   dword ptr [esp+8],eax
  mov   dword ptr argc,0
  mov   dword ptr argc,ebx
  mov   dword ptr cmdline,eax
  mov   dword ptr hHeap,eax
  mov   dword ptr hStdf+4,eax
  mov   eax,-1
  mov   eax,5
  mov   eax,dword ptr [eax]
  mov   eax,dword ptr [ebp-12]
  mov   eax,dword ptr [ebp+12]
  mov   eax,dword ptr [ebp+8] # size
  mov   eax,dword ptr argc
  mov   eax,ebx
  mov   eax,offset flat:argv
  mov   ebp,esp
  mov   ebx,dword ptr [ebp-20]
  mov   ebx,dword ptr [ebp+8]
  mov   ebx,dword ptr argc
  mov   ebx,eax
  mov   ecx,offset flat:argv
  mov   edi,eax
  mov   edx,dword ptr cmdlinecopy
  mov byte ptr [ebx],al
  mov dword ptr [ebp-12],eax # block_local_offset
  mov dword ptr [ebp-36],eax # block_local_offset
  mov dword ptr [ebp-72],eax # number
  mov dword ptr [ebp-76],eax # nn
  mov dword ptr [ebp+16],eax # n
  mov dword ptr [ebx],eax
  mov dword ptr _cg_file,eax
  mov eax,1
  mov eax,1009
  mov eax,50000
  mov eax,2147483647
  mov eax,127
  mov eax,128
  mov eax,dword ptr [eax]
  mov eax,dword ptr [ebp-12] # block_local_offset
  mov eax,dword ptr [ebp+12] # av
  mov eax,dword ptr [ebp+24] # init_exprs
  mov eax,dword ptr _cg_buffer
  mov eax,edx
  mov eax,OFFSET FLAT:S1
  mov ebp,esp
  mov ebx,10
  mov ebx,16777216
  mov ebx,256
  mov ebx,dword ptr [ebp-28] # i
  mov ebx,dword ptr [ebp+8] # n
  mov ebx,dword ptr _sc_num
  mov ebx,eax
  movsx eax,byte ptr [eax]
  movsx eax,byte ptr [ebp-16] # t
  movzx eax,al
  neg eax
  not ecx
  or  eax,-2147483648
  or  eax,1
  or  eax,32
  pop eax
  pop ecx # restore len+1
  pop esi # restore src
  pop ebx
  push  -10
  push  0
  push  eax # save, will goto esi
  push  ebp
  rep   movsb
  repne scasb
  ret
  sete  al
  setg  al
  setge al
  setl  al
  setle al
  setne al
  setnz al
  setz al
  sub   dword ptr [ebp+8],3
  sub   esp,56
  sub ecx,1
  sub edx,1
  sub eax,1
  sub eax,128
  sub eax,48
  sub eax,dword ptr [ebp-24] # items
  sub eax,ebx
  sub esp,4
  sub esp,76
  test  al,al
  test  eax,eax
  xor   eax,eax
  xor   ecx,ecx
  xor eax,eax

  .file	"startup.s"
	.align 32
	.align 4
	.ascii "'\12\0"
	.ascii "-h\0"
	.ascii "wrong syntax\0"
	.bss
	.cfi_def_cfa 4, 4
	.cfi_def_cfa_offset 8
	.cfi_def_cfa_register 5
	.cfi_endproc
	.cfi_offset 3, -12
	.cfi_offset 5, -8
	.cfi_restore 3
	.cfi_restore 5
	.cfi_startproc
	.comm	_cg_loop_label, 80, 5
	.comm	_rd_buf, 8000, 5
	.comm	_sc_num, 4, 2
	.data
	.def	_assert;	.scl	2;	.type	32;	.endef
	.file	"cc.c"
	.globl	_assert
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.intel_syntax noprefix
	.long	-1
	.long	1
	.long	LC0
	.section .rdata,"dr"
	.space 4
	.text
	add	DWORD PTR [ebp-12], eax
	add	DWORD PTR [ebp-32], 1
	add	DWORD PTR [ebp+12], 1
	add	DWORD PTR [ebp+12], eax
	add	DWORD PTR [esp+20], 1
	add	eax, -128
	add	eax, 1
	add	eax, 48
	add	eax, eax
	add	eax, ecx
	add	eax, edx
	add	ecx, 4
	add	ecx, ebx
	add	edx, 1
	add	edx, 16
	add	edx, eax
	add	edx, ecx
	add	esp, 36
	and	eax, 255
	and	edx, 16777215
	and	edx, 3
	and	esp, -16
	call	_assert
	cdq
	cmp	al, 1
	cmp	al, 111
	cmp	dl, al
	cmp	DWORD PTR [ebp-108], 1
	cmp	DWORD PTR [ebp-12], eax
	cmp	DWORD PTR [ebp-132], 0
	cmp	DWORD PTR [ebp-136], 1
	cmp	DWORD PTR [ebp+12], -1
	cmp	DWORD PTR [ebp+12], 57
	cmp	DWORD PTR [ebp+8], -2147483648
	cmp	DWORD PTR [ebp+8], 0
	cmp	DWORD PTR [ebp+8], 1
	cmp	DWORD PTR [ebp+28], 122
	cmp	DWORD PTR [ebp+28], eax
	cmp	eax, 1
	cmp	eax, 127
	cmp	eax, 128
	cmp	eax, 129
	cmp	eax, DWORD PTR [ebp-20]
	cmp	eax, DWORD PTR [ebp+12]
	cmp	ecx, eax
	cmp	edx, eax
	idiv	ecx
	imul	eax, DWORD PTR [ebp-16]
	imul	edx
	imul	edx, eax, 66
	ja	L382
	jg	L853
	jge	L219
	jl	L851
	jle	L130
	jmp	L98
	jne	L100
	jns	L125
	js	L794
	lea	eax, [ebp-10]
	lea	eax, [ebp-84]
	lea	ebx, [eax-1]
	lea	ebx, [eax+4]
	lea	ebx, [eax+edx]
	lea	edx, [0+eax*4]
	lea	edx, [0+eax*8]
	lea	edx, [eax-1]
	lea	edx, [eax+1]
	lea	edx, [eax+10]
	lea	edx, [eax+100000]
	leave
	mov	BYTE PTR [eax], 0
	mov	BYTE PTR [eax], 114
	mov	BYTE PTR [eax], dl
	mov	BYTE PTR [ebp-11], al
	mov	BYTE PTR [ebp-13], 0
	mov	BYTE PTR [edx], al
	mov	BYTE PTR _rd_buf[eax], 0
	mov	BYTE PTR _sc_text, al
	mov	BYTE PTR _sc_text+1, 0
	mov	DWORD PTR [eax], 0
	mov	DWORD PTR [eax], 1
	mov	DWORD PTR [eax], edx
	mov	DWORD PTR [ebp-100], eax
	mov	DWORD PTR [ebp-12], 0
	mov	DWORD PTR [ebp-12], 4
	mov	DWORD PTR [ebp-12], eax
	mov	DWORD PTR [ebp-12], edx
	mov	DWORD PTR [ebp-12], OFFSET FLAT:LC230
	mov	DWORD PTR [ebp-124], eax
	mov	DWORD PTR [ebp-132], eax
	mov	DWORD PTR [ebp-32], 111
	mov	DWORD PTR [ebp-4], 0
	mov	DWORD PTR [ebp-4], 5381
	mov	DWORD PTR [ebp-4], eax
	mov	DWORD PTR [ebp-4], OFFSET FLAT:_i2s_buf
	mov	DWORD PTR [ebp-96], eax
	mov	DWORD PTR [ebp+16], 1
	mov	DWORD PTR [ebp+8], eax
	mov	DWORD PTR [ebx], eax
	mov	DWORD PTR [edx], eax
	mov	DWORD PTR [esp], 0
	mov	DWORD PTR [esp], 1
	mov	DWORD PTR [esp], 43
	mov	DWORD PTR [esp], 1009
	mov	DWORD PTR [esp], eax
	mov	DWORD PTR [esp], edx
	mov	DWORD PTR [esp], OFFSET FLAT:LC100
	mov	DWORD PTR [esp+12], 0
	mov	DWORD PTR [esp+12], 4
	mov	DWORD PTR [esp+12], eax
	mov	DWORD PTR [esp+12], ecx
	mov	DWORD PTR [esp+12], edx
	mov	DWORD PTR [esp+24], OFFSET FLAT:LC306
	mov	DWORD PTR [esp+4], -1
	mov	DWORD PTR [esp+4], 0
	mov	DWORD PTR [esp+4], 1
	mov	DWORD PTR [esp+4], 33537
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp+4], edx
	mov	DWORD PTR [esp+4], OFFSET FLAT:LC129
	mov	DWORD PTR [esp+8], -1
	mov	DWORD PTR [esp+8], 0
	mov	DWORD PTR [esp+8], 1
	mov	DWORD PTR [esp+8], 10
	mov	DWORD PTR [esp+8], 438
	mov	DWORD PTR [esp+8], 7999
	mov	DWORD PTR [esp+8], eax
	mov	DWORD PTR [esp+8], ebx
	mov	DWORD PTR [esp+8], edx
	mov	DWORD PTR [esp+8], OFFSET FLAT:LC99
	mov	DWORD PTR _cg_buffer, 0
	mov	DWORD PTR _cg_buffer, eax
	mov	DWORD PTR _cg_loop_label[0+eax*4], edx
	mov	DWORD PTR _ET_TRACE, 1
	mov	DWORD PTR _rd_char, -1
	mov	DWORD PTR _rd_char, 13
	mov	eax, -1
	mov	eax, 0
	mov	eax, 1
	mov	eax, 47
	mov	eax, DWORD PTR [eax]
	mov	eax, DWORD PTR [eax+4]
	mov	eax, DWORD PTR [ebp-100]
	mov	eax, DWORD PTR [ebp-92]
	mov	eax, DWORD PTR [esp+28]
	mov	eax, DWORD PTR _cg_buffer
	mov	eax, DWORD PTR _st_type_str[0+eax*4]
	mov	eax, ecx
	mov	eax, edx
	mov	eax, OFFSET FLAT:_i2s_buf
	mov	eax, OFFSET FLAT:_str_repr_buf
	mov	eax, OFFSET FLAT:LC2
	mov	ebp, esp
	mov	ebx, DWORD PTR [eax]
	mov	ebx, DWORD PTR [ebp+8]
	mov	ebx, eax
	mov	ecx, DWORD PTR [ebp-12]
	mov	ecx, DWORD PTR [ebp-120]
	mov	ecx, DWORD PTR [ebp+8]
	mov	ecx, DWORD PTR [ecx]
	mov	ecx, DWORD PTR [edx]
	mov	ecx, DWORD PTR _PRC
	mov	ecx, eax
	mov	edx, 1717986919
	mov	edx, DWORD PTR [eax]
	mov	edx, DWORD PTR [ebp-120]
	mov	edx, DWORD PTR [ebp-16]
	mov	edx, DWORD PTR [ebp+24]
	mov	edx, DWORD PTR [edx]
	mov	edx, DWORD PTR _OPS
	mov	edx, DWORD PTR _st_kind_str[0+eax*4]
	mov	edx, eax
	mov	edx, ecx
	movsx	eax, al
	movsx	edx, dl
	movzx	eax, al
	movzx	eax, BYTE PTR _rd_buf[eax]
	movzx	eax, BYTE PTR [eax]
	movzx	edx, BYTE PTR [eax]
	movzx	edx, BYTE PTR [ebp-13]
	movzx	edx, BYTE PTR [edx]
	movzx	edx, dl
	neg	DWORD PTR [ebp+8]
	neg	eax
	nop
	pop  ebp
	pop  ebx
	push ebp
	push ebx
	ret
	#sal	DWORD PTR [ebp-24], 2
	#sal	eax, 2
	#sal	eax, 8
	#sal	ecx, 2
	#sal	edx, 2
	#sar	eax, 2
	#sar	eax, 31
	#sar	eax, 8
	#sar	edx, 2
	sete	al
	setg	al
	setne	al
	#shr	eax, 30
	#shr	eax, 8
	sub	DWORD PTR [ebp-16], 1
	sub	DWORD PTR [ebp-4], 1
	sub	DWORD PTR [ebp-8], 1
	sub	DWORD PTR [ebp+16], 1
	sub	DWORD PTR [ebp+16], eax
	sub	DWORD PTR [ebp+8], 1
	sub	eax, -128
	sub	eax, 1
	sub	eax, 256
	sub	eax, 48
	sub	eax, DWORD PTR [ebp-28]
	sub	eax, DWORD PTR [ebp-40]
	sub	eax, edx
	sub	ecx, eax
	sub	edx, 48
	sub	edx, eax
	sub	esp, 120
	sub	esp, 152
	sub	esp, 16
	sub	esp, 20
	sub	esp, 24
	sub	esp, 32
	sub	esp, 36
	sub	esp, 40
	sub	esp, 56
	sub	esp, 72
	sub	esp, 8
	sub	esp, 88
	test	al, al
	test	eax, eax
# stdlib for C99C - must be included before other code
_assert:
_lseek: # lseek( int fd, int offset, int whence )
argc: .space 4
argv: .space 4*maxargs
hStdf: .space 3*4      # standard handles: stdin, stdout, stderr
Z96:
