gcc -S -masm=intel -nostdlib stdlib.c -o stdlib.s
gcc -nostdlib stdlib.s -lkernel32 -o stdlib.exe
strip stdlib.exe
stdlib.exe
