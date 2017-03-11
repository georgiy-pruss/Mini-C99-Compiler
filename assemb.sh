gcc -Wa,-adhln -g intmainargsps.c >intmainargsps.s2
-masm=intel
remove -g
-Wa,-ahls -o yourfile.o yourfile.cpp>yourfile.asm

-g: Produce debugging information
-Wa,option: Pass option as an option to the assembler
-adhln:
a: turn on listings
d: omit debugging directives; n: omit forms processing
h: include high-level source
l: include assembly

gcc intmainargspsi.s -masm=intel -o im.exe

https://sourceware.org/binutils/docs/as/index.html#Top

