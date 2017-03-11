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

int strlen( char* s ) { int n=0; while( *s++ ) ++n; return n; }

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

