## Mini-C99-Compiler — Yet another C99 subset compiler

### Description

The input file is compiled with `cc` into assembler file (default name is `a.s`).
The GNU compiler or rather assembler can compile it into an executable (`gcc a.s -o a.exe`),
or later `cc` will be able to translate it into an executable file (that's the plan).

### Comments, Preprocessor (#include, #define, #pragma etc)

Comments can be both the C comments (inline and multi-line `/*...*/`) and the C++
end-of-line comments (`//...`). Any text starting with `#` is also treated as a
a comment, that is all the preprocessor directives are ignored, although they can be
present in the program text — that's proably good for includes, but bad for defines.

### Number, Character, String literals

The compiler accepts decimal and octal integer (32-bit) numbers in range `-2147483648` to `2147483647`.
Characters are signed, i.e. with the range of `-128` to `127`.
Characters and strings can contain these escape sequences: `\n` (NL), `\r` (CR), `\b` (BS),
`\0` (NUL). All the rest "escaped" characters are copied as-is. The strings can't be
concatenated (i.e. `"abc" "def"` won't be understood.)

### Program, enum declarations, global variables, functions

The program consists of these entities:

* **enum** declarations; they can't have enum type name; they define integer constants,
can have their value specified: `enum { Zero, One, Two, Four=4, Eight=8 };`

* **global varable** definitions; simple variables of these types: `char`, `char*`, `char**`,
`int`, `int*`, `int**`, and arrays of types: `char`, `char*`, `int`, `int*`; they can have
initial values, that must be constants (literals), maybe simple expressions; arrays can be
initialized with strings (for `char*` and `char[]`) and with array values (for `char*[]`,
`int[]`, `int*[]`); *note:* Global variables can be only defined, not declared, i.e.
if the compiler sees a variable declaration (i.e. without initial value), it treats it as
a definition with the zero value. There cannot be multiple declarations and definition of the same variable.

    ```
    char* a = "012345";
    char  b[] = "abc";
    char* c[] = {"ijk","mn"};
    int d[] = {1,2,3};
    int e[100] = {0};
    int* f[] = {0,0,0};
    int g; // actually defines g with initial value 0; it can't be defined later with explicit value
    ```

* **function declaration**; can be used for external functions (see [Library functions](#library-functions))
and for preliminary declarations of the functions defined later -- it can be necessary
if there's a recursion in the function calls;

* **function definitions**; the return type can be `void` or one of the same as for the
variables: `char`, `char*`, `char**`, `int`, `int*`, `int**`. The arguments can have the
same set of types, except `void`. No array arguments (`T a[]`) -- they are in fact just
pointers, so do express it explicitely (`T* a`). Variable definitions can mix with statements.

### Statements

These statements are permitted:

* **empty** statement: `;`

* **expression** (used for calls, increments, assignments): `foo(1); ++i; c=(a+b)/2;`

* **block** (it introduces a new scope): `{ int t=a; a=b; b=t; }`

* **break** (for leaving loops): `break;`

* **return** with a value or without it: `return 2*x;`

* **if/else**: `if( x>0 ) t=x; else t=0;`

* **while**: `while( more_data() ) do_something();`

* **for** with the possibility to define variables in the first part of the header
and with the possibility to have several expressions in the last part -- the *comma*
operator is allowed only in this place: `for( int a=N,*t=s; *t; ++t, --a ) {...}`.
(In plans: allow comma in the first part, as well as in expr-stmt and return-stmt.)

* **variable** definition(s) -- it's also a statement and can be placed anywhere in a block.

### Expressions

* Unary operators: `- ~ ! *`. No `&`.

* Binary operators: `* / %`, `+ -`, `< > <= >=`, `== !=`, `&`, `^`, `|`, `&&`, `||`, `=`.
No shifts (`<<` `>>`), no conditional (`?:`), no operators with assignment (`+=` `-=` etc).
Maybe these will be added later.

* Calls, indexing, prefix `++` and `--`, type cast.

* No `sizeof`. No postfix `++` and `--`.

### Library functions

These functions can be used:

    int open( char* path, int oflag, int cmode );
    int close( int fd );
    int read( int fd, char* buf, int count );
    int write( int fd, char* buf, int count );
    char* malloc( int size );
    void free( char* ptr );
    void exit( int status );

In the `open` function, `oflag` is system-dependent. For cygwin-32 it accepts these
values: `enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=512, O_TRUNC=1024, O_EXCL=2048 };`

### Limits

All the strings and lines are limited to less than 260 characters; No more than 1000 names
in a program, no more than 500 variables in all "active" scopes at any given place. The loops can't
be nested more than 20 levels. Some other limits may apply.

