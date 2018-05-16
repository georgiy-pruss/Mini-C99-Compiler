gcc -S -masm=intel cc.c -o cc.s
gcc cc.s -o cc.exe
strip cc.exe
d2u.py cc.s

cc.exe cc.c -o cc_cc.s
gcc -nostdlib cc_cc.s -lkernel32 -o cc_cc.exe
strip cc_cc.exe

cc_cc.exe cc.c -o cc_cc_cc.s
diff cc_cc.s cc_cc_cc.s
