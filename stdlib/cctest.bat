gcc -S -masm=intel cc_0.c -o cc.s
gcc cc.s -o cc.exe

cc.exe cc.c -o cc2.s
d2u cc2.s
gcc -nostdlib cc2.s -lkernel32 -o cc2.exe

cc2.exe cc.c -o cc3.s
diff cc2.s cc3.s
