// gcc -S -masm=intel t_calls.c -o t_calls.s
// gcc -masm=intel t_calls.s -o t_calls.exe

int open( char* path, int oflag, int mode ); // >0 if ok; 3rd arg = cr.mode
int close(int fd); // 0 if ok
int read(int fd, char* buf, int count);
int write(int fd, char* buf, int count);
char* malloc( int size );
void free( char* ptr );
void exit(int status);

char nm[] = "file name";
char buf[200];
int fd;
char* mem;
int cnt;

int main()
{
  fd = open( nm, 128, 511 );
  cnt = read( fd, buf, 100 );
  cnt = write( fd, buf, cnt );
  close( fd );
  mem = malloc( 50 );
  free( mem );
  exit( 0 );
}

