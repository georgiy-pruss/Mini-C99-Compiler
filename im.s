         .file "intmainargsps.c"
         .text
Ltext0:
         .globl  _strlen
_strlen:
LFB0:
         .file 1 "intmainargsps.c"
# int strlen( char* s ) { int n=0; while( *s++ ) ++n; return n; }
         pushl %ebp
         movl  %esp, %ebp
         subl  $16, %esp

         movl  $0, -4(%ebp)        # n=0
L2:
         movl  8(%ebp), %eax       # arg1
         leal  1(%eax), %edx       # s++
         movl  %edx, 8(%ebp)
         movzbl  (%eax), %eax      # *s
         testb %al, %al
         je LL3
L3:
         addl  $1, -4(%ebp)        # ++n
         jmp L2
LL3:
         movl  -4(%ebp), %eax      # n
         leave
         ret
LFE0:
        .section .rdata,"dr"

LC0:
        .ascii "\12\0"

        .text
        .globl  _main
_main:
LFB1:
# int main( int ac, char** av )
         pushl %ebp
         movl  %esp, %ebp
         andl  $-16, %esp          # ??
         subl  $32, %esp

         call  ___main

# int i=0;
         movl  $0, 28(%esp)        # i

# while( i<ac )

L6:
        movl  28(%esp), %eax       # i
        cmpl  8(%ebp), %eax        # ac - 1st arg is 8(%ebp)
        jnl  L8
L7:
# write( 1, av[i], strlen(av[i] ) ); write( 1, "\n", 1 );

        movl  28(%esp), %eax      # i
        leal  0(,%eax,4), %edx

        movl  12(%ebp), %eax    # av[i] - 2nd arg is 4(%ebp)
        addl  %edx, %eax
        movl  (%eax), %eax
        movl  %eax, (%esp)
        call  _strlen

        movl  %eax, %edx
        movl  28(%esp), %eax
        leal  0(,%eax,4), %ecx
        movl  12(%ebp), %eax
        addl  %ecx, %eax
        movl  (%eax), %eax
        movl  %edx, 8(%esp)
        movl  %eax, 4(%esp)
        movl  $1, (%esp)
        call  _write

        movl  $1, 8(%esp)
        movl  $LC0, 4(%esp)
        movl  $1, (%esp)
        call  _write

#  ++i;
        addl  $1, 28(%esp)
        jmp L6
L8:

#   return ac;

        movl  8(%ebp), %eax

        leave
        ret

LFE1:
Letext0:
        .ident  "GCC: (GNU) 5.4.0"
