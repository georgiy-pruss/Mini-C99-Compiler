  .file "hw.c"
  .intel_syntax noprefix

  .def ___main; .scl 2; .type 32; .endef
  .text
  .globl _main
  .def _main; .scl 2; .type 32; .endef
_main:
  .cfi_startproc
  push ebp
  .cfi_def_cfa_offset 8
  .cfi_offset 5,-8
  mov ebp,esp
  .cfi_def_cfa_register 5
  # no local variables
  call ___main

  mov eax,OFFSET FLAT:S0
  push eax
  call _puts
  add esp,4
  mov eax,1
  jmp R1
R1:
  leave
  .cfi_restore 5
  .cfi_def_cfa 4,4
  ret
  .cfi_endproc

  .section .rdata,"dr"
S0:
  .ascii "Hello world\0"

  .ident  "Georgiy Pruss C99C 0.26149"

  .def _puts; .scl 2; .type 32; .endef
