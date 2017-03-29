  .file "t_global_vars.c"
  .intel_syntax noprefix

# char cc1;
# char cc2[2];
# char cc3[3];
  .comm _cc1, 1, 0
  .comm _cc2, 2, 0
  .comm _cc3, 3, 0 # 1 to 3 -- 2**0=1

# int ii;
# int* pp;
# int* qq[4];
# char cc5[5];
# char cc9[9];
# int ii2[2];
# int ii3[3];
# int ii7[7];
  .comm _ii, 4, 2    # char 4 to 31 -- 2**2=4
  .comm _pp, 4, 2    # int 1 to 7 (len=28)
  .comm _qq, 16, 2
  .comm _cc5, 5, 2
  .comm _cc9, 9, 2
  .comm _ii2, 8, 2
  .comm _ii3, 12, 2
  .comm _ii7, 28, 2

# int jj[10];
# int jj1[11];
# char ss[100];
# char ss1[101];

  .comm _jj, 40, 5    # char 32+ -- 2**5=32
  .comm _jj1, 44, 5   # int 8+ (len=32+)
  .comm _ss, 100, 5
  .comm _ss1, 101, 5

# char o0 = 'x';
  .globl  _o0
  .data
_o0:
  .byte 120

# int i01 = 11;
  .globl  _i01
  .align 4
_i01:
  .long 11

# char p1[1] = "0";
  .globl  _p1
  .data
_p1:
  .ascii "0"

# char p2[2] = "0";
  .globl  _p2
_p2:
  .ascii "0\0"

# char p3[3] = "0";
  .globl  _p3
_p3:
  .ascii "0\0"
  .space 1

# char p4[4] = "0";
  .globl  _p4
  .align 4
_p4:
  .ascii "0\0"
  .space 2

# char p5[5] = {0};
  .globl  _p5
  .bss
  .align 4
_p5:
  .space 5

# char p6[6] = "0";
  .globl  _p6
  .data
  .align 4
_p6:
  .ascii "0\0"
  .space 4

# char p23[23] = "0";
  .globl  _p23
  .align 4
_p23:
  .ascii "0\0"
  .space 21

# char p24[24] = {0};
  .globl  _p24
  .bss
  .align 4
_p24:
  .space 24

# int q15[15] = {0}; // any length
  .globl  _q15
  .bss               // if needed
  .align 32
_q15:
  .space 60

# // repead def:

# int q10;           // no .comm!
# int q11;
# int q20[20];
# int q21[21];

# int q10 = 0;
# int q11 = 1;
# int q20[20] = {0};
# int q21[21] = {1};

  .globl  _q10
  [.bss]
  .align 4
_q10:
  .space 4

  .globl  _q11
  .data
  .align 4
_q11:
  .long 1

  .globl  _q20
  .bss
  .align 32
_q20:
  .space 80

  .globl  _q21
  .data
  .align 32
_q21:
  .long 1
  .space 80


# char o2[2] = "xy";
  .globl  _o2
_o2:
  .ascii "xy"

# int i02 = 22;
  .globl  _i02
  .align 4
_i02:
  .long 22

# char a1[] = "abc"; // ARRAY!
  .globl  _a1
  .align 4
_a1:
  .ascii "abc\0"

# char* b2[] = {"ijk","mn",0};
  .globl  _b2
  .section .rdata,"dr"
LC0:
  .ascii "ijk\0"
LC1:
  .ascii "mn\0"
  .data
  .align 4
_b2:
  .long LC0
  .long LC1
  .long 0

# int c3[] = {1,2,3};
  .globl  _c3
  .align 4
_c3:
  .long 1
  .long 2
  .long 3

# int iix = 0;
  .globl  _iix
  .bss
  .align 4
_iix:
  .space 4

# char ccx = '\0';
  .globl  _ccx
_ccx:
  .space 1

# int iiy;
  .comm _iiy, 4, 2

# char ccy[999] = {0};
  .globl  _ccy
  .align 32
_ccy:
  .space 999

# int a4=-1;
  .globl  _a4
  .data
  .align 4
_a4:
  .long -1

# char* b5 = "xyz"; // POINTER!
  .globl  _b5
  .section .rdata,"dr"
LC2:
  .ascii "xyz\0"
  .data
  .align 4
_b5:
  .long LC2

# int** c6[] = {0,0};
  .globl  _c6
  .bss
  .align 4
_c6:
  .space 8

# int d7[100] = {0};
  .globl  _d7
  .align 32
_d7:
  .space 400

# char x[] = "str1";
  .globl  _x
  .data
  .align 4
_x:
  .ascii "str1\0"

# char y[] = "str2";
  .globl  _y
  .align 4
_y:
  .ascii "str2\0"

# char* z[] = { x, y }; // !
  .globl  _z
  .align 4
_z:
  .long _x
  .long _y

# int xx[] = {1,2};
  .globl  _xx
  .align 4
_xx:
  .long 1
  .long 2

# int yy[] = {3,4};
  .globl  _yy
  .align 4
_yy:
  .long 3
  .long 4

# int* zz[] = { xx, yy }; // !
  .globl  _zz
  .align 4
_zz:
  .long _xx
  .long _yy

# int u[10001];
# int v[11001];
  .comm _u, 40004, 5
  .comm _v, 44004, 5

# int w[11111] = { -1, -2 };
  .globl  _w
  .align 32
_w:
  .long -1
  .long -2
  .space 44436

# char xw[25000] = "+-*/";
  .globl  _xw
  .align 32
_xw:
  .ascii "+-*/\0"
  .space 24995


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
  call  ___main
  mov eax, DWORD PTR _ii2
  leave
  .cfi_restore 5
  .cfi_def_cfa 4, 4
  ret
  .cfi_endproc
LFE0:
  .ident  "GCC: (GNU) 5.4.0"
