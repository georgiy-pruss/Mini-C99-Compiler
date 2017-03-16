	.file	"t_global_vars.c"
	.intel_syntax noprefix
	.comm	_ii, 4, 2
	.comm	_cc, 1, 0
	.comm	_jj, 40, 5
	.comm	_ss, 100, 5
	.comm	_pp, 4, 2
	.comm	_qq, 16, 2
	.globl	_o0
	.data
_o0:
	.byte	120
	.globl	_a1
	.align 4
_a1:
	.ascii "abc\0"
	.globl	_b2
	.section .rdata,"dr"
LC0:
	.ascii "ijk\0"
LC1:
	.ascii "mn\0"
	.data
	.align 4
_b2:
	.long	LC0
	.long	LC1
	.globl	_c3
	.align 4
_c3:
	.long	1
	.long	2
	.long	3
	.globl	_a4
	.align 4
_a4:
	.long	-1
	.globl	_b5
	.section .rdata,"dr"
LC2:
	.ascii "xyz\0"
	.data
	.align 4
_b5:
	.long	LC2
	.globl	_c6
	.bss
	.align 4
_c6:
	.space 8
	.globl	_d7
	.align 32
_d7:
	.space 400
	.globl	_x
	.data
	.align 4
_x:
	.ascii "str1\0"
	.globl	_y
	.align 4
_y:
	.ascii "str2\0"
	.globl	_z
	.align 4
_z:
	.long	_x
	.long	_y
	.globl	_xx
	.align 4
_xx:
	.long	1
	.long	2
	.globl	_yy
	.align 4
_yy:
	.long	3
	.long	4
	.globl	_zz
	.align 4
_zz:
	.long	_xx
	.long	_yy
	.comm	_u, 40000, 5
	.globl	_v
	.align 32
_v:
	.long	-1
	.long	-2
	.space 44436
	.globl	_w
	.align 32
_w:
	.ascii "+-*/\0"
	.space 24995
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB0:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	and	esp, -16
	call	___main
	mov	eax, 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.ident	"GCC: (GNU) 5.4.0"
