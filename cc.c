enum { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO };

int S_IRUSR = 0400; /* Read by owner.  */
int S_IWUSR = 0200; /* Write by owner.  */
int S_IXUSR = 0100; /* Execute by owner.  */

int S_IRGRP = 0040; /* Read by group.  */
int S_IWGRP = 0020; /* Write by group.  */
int S_IXGRP = 0010; /* Execute by group.  */

int S_IROTH = 0004; /* Read by others.  */
int S_IWOTH = 0002; /* Write by others.  */
int S_IXOTH = 0001; /* Execute by others.  */

int O_RDONLY = 0; /* read enabled */
int O_WRONLY = 1; /* write enabled */
int O_RDWR   = 2; /* read/write */
int O_APPEND = 8; /* append (writes guaranteed at the end) */
int O_CREAT  = 0x0200; /* open with file create */
int O_TRUNC  = 0x0400; /* open with truncation */
int O_EXCL   = 0x0800; /* error on open if file exists */

int open( char *path, int oflag, ... ); // >0 if ok; 3rd arg = cr.mode
int close(int fd); // 0 if ok
int read(int fd, char* buf, int count);
int write(int fd, char* buf, int count);
void* malloc( int size );
void free( void* ptr );
void exit(int status);

int strlen( char* s ) { for( int n = 0; *s++; ) ++n; return n; }

void strupr( char* s ) { while( *s ) { if( *s>='a' && *s<='z' ) *s = *s-'a'+'A'; ++s; } }

int errno = 0;

char* itoa( int value, char* str, int base )
{
  if( base<2 || base>36 ) { errno = 1; return 0; }
  char buf[80];
  char* ptr = buf+sizeof(buf);
  char* dst = str;
  if( value<0 ) { *dst++ = '-'; value = -value; }
  if( value==0 )
    *--ptr = '0';
  else
    while( value!=0 )
    {
      int d = value % base; value = value / base;
      if( d<=9 ) d += '0'; else d += 'a' - 10;
      *--ptr = (char)d;
    }
  while( ptr != buf+sizeof(buf) )
    *dst++ = *ptr++;
  *dst = '\0';
  errno = 0;
  return str;
}

int atoi( char* str, int base ) // also '_' in numbers is ignored
{
  if( base<2 || base>36 ) { errno = 1; return 0; }
  while( *str == ' ' ) // skip leading blanks
    ++str;
  int minus = 0;
  if( *str == '-' ) { minus = 1; ++str; }
  int v = 0;
  while( *str>='0' )
  {
    if( base<=10 )
    {
      if( *str<'0'+base )
        v = base*v + *str - '0';
      else if( *str != '_' )
        break;
    }
    else
    {
      if( *str<='9' )
        v = base*v + *str - '0';
      else if( *str>='a' && *str<'a'+base-10 )
        v = base*v + *str - 'a' + 10;
      else if( *str>='A' && *str<'A'+base-10 )
        v = base*v + *str - 'A' + 10;
      else if( *str != '_' )
        break;
    }
    ++str;
  }

  if( minus ) v = -v;
  errno = 0;
  return v;
}

void assert( int cond, char* msg )
{
  if( cond == 0 )
  {
    write( STDERR_FILENO, "ASSERT: ", 8 );
    write( STDERR_FILENO, msg, strlen(msg) );
    write( STDERR_FILENO, "\n", 1 );
    exit(1);
  }
}

void put( char* s )
{
  write( STDOUT_FILENO, s, strlen(s) );
}


int main( int argc, char** argv )
{
  int i = 0;
  /*while( i<argc )*/
  {
    //char a[200];
    //itoa(
    //write( STDOUT_FILENO, "Hello world!\n", 13 );
  }

  int a[] = {0,1,2,3,8,9,10,11,14,15,16,17,31,32,33,1000,1024,1750,32768,32769,1234567890,0x7fffffff};
  for(i=0;i<sizeof(a)/sizeof(a[0]);++i)
  {
    int k, r;
    char x[100];
    itoa( a[i], x, 10 ); put(x);
    itoa( a[i], x, 2 ); put( "  2: " ); put(x);
    itoa( a[i], x, 8 ); put("  8: " ); put(x);
    itoa( a[i], x, 16 ); put( "  16: " ); put(x);
    itoa( -a[i], x, 36 ); put( "  36: " ); put(x);
    for( r=2; r<=36; ++r )
    {
      itoa( a[i], x, r ); k = atoi( x, r ); assert( k==a[i], "k==a[i]" );
      strupr( x ); k = atoi( x, r ); assert( k==a[i], "k==a[i], uppercase" );
    }
    put("\n");
  }
  char name[100];
  put( "Your name: " );
  int n = read( STDIN_FILENO, name, sizeof(name) );
  if( n>0 )
  {
    name[n] = '\0';
    write( STDERR_FILENO, name, n );
  }
  int f = open( "cc.c", O_RDONLY );
  if( f>0 )
  {
    int MAXBUF = 20000;
    char* buf = malloc(MAXBUF);
    int n = read( f, buf, MAXBUF );
    if( n>=0 )
    {
      int t = open( "cc.copy", O_WRONLY|O_CREAT|O_EXCL, 0777 );
      if( t>0 )
      {
        write( t, buf, n );
        close( t );
      }
    }
    free( buf );
    close( f );
  }
  exit(0);
}

/*
ax bx cx dx si di bp sp

push r
pop  r
mov  r,rs
add  r,rs  sub mul div and or xor
lea  r,m
ldw  r,m
ldb  r,m  ; expanded sign bit
stw  r,m
stb  r,m
jmp  a
cmp  r,rs
jeq  a     jne jlt jle jgt jge
call a
ret
*/

/*

type name [= value];
type name[ [value] ] [= {value[,...]}];
type name ( [args] );
type name ( [args] ) { body }


type name [= expr][, ...];
type: void|char|int [*][...]

if( expr ) stmt [else stmt]
while( expr ) stmt
for( expr; expr; expr ) stmt
return expr;
expr;
break;

expr: lvalue [=|+=|-=|...] rvalue

*/
