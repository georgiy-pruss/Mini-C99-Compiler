// gcc -S -masm=intel -nostdlib stdlib.c -o stdlib.s
// gcc -nostdlib stdlib.s -lkernel32 -o stdlib.exe && strip stdlib.exe

char* argv[4];
int argc;

int main(int,char**);
void prepare_main();
void prepare_exit();
int __start()
{
  int rc;
  prepare_main();
  // parse args with GetCommandLineA() in fact
  argv[0] = "a.exe";
  argv[1] = "a1";
  argv[2] = "a2";
  argc = 3;
  rc = main(argc,argv);
  // free memory
  prepare_exit();
  return rc;
}

// stdlib ----------------------------------------------------------------------

int open( char* path, int oflag ); // >0 if ok; flags below - own flags!
int close( int fd );                          // 0 if ok
int read( int fd, char* buf, int count );     // fd=0 - stdin
int write( int fd, char* buf, int count );    // fd=1 - stdout, fd=2 - stderr
int lseek( int fd, int offset, int whence ); // if bad: -1, if std: 0
char* malloc( int size );
void free( char* ptr );
void exit( int status );
enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=16, O_TRUNC=32, O_EXCL=64 };
enum { SEEK_SET, SEEK_CUR, SEEK_END };

// open the file for read-only, write-only, or read/write.
// O_APPEND Before each write(2), the file offset is positioned at the end of the file.
// O_CREAT  If pathname does not exist, create it as a regular file.
// O_EXCL   Ensure that this call creates the file, in conjunction with O_CREAT.
// O_TRUNC  O_RDWR or O_WRONLY file will be truncated to length 0.

// O_RDONLY - not compatible with any other
//            -   O_APPEND   O_TRUNC    -  O_CREAT  O_CREAT|O_EXCL
// O_WRONLY
// O_RDWR

// GENERIC_READ | GENERIC_WRITE or FILE_APPEND_DATA
// CREATE_ALWAYS - overwrite if exists
// CREATE_NEW - create if not exists, new file only
// OPEN_ALWAYS - create if not exists
// OPEN_EXISTING
// TRUNCATE_EXISTING - must be with GENERIC_WRITE


// stdlib

#define DWORD                    int
#define HANDLE                   int
#define GENERIC_READ             0x80000000
#define GENERIC_WRITE            0x40000000
#define FILE_APPEND_DATA         0x00000004
#define FILE_ATTRIBUTE_NORMAL    0x00000080
#define CREATE_NEW               1
#define CREATE_ALWAYS            2
#define OPEN_EXISTING            3
#define OPEN_ALWAYS              4
#define TRUNCATE_EXISTING        5
#define STD_INPUT_HANDLE         (DWORD)(0xfffffff6)
#define STD_OUTPUT_HANDLE        (DWORD)(0xfffffff5)
#define STD_ERROR_HANDLE         (DWORD)(0xfffffff4)
#define INVALID_HANDLE_VALUE     (HANDLE)(-1)
#define FILE_BEGIN               0
#define FILE_CURRENT             1
#define FILE_END                 2
#define INVALID_SET_FILE_POINTER ((DWORD)(-1))

// kernel32 imports:
int __stdcall GetStdHandle( int nStdHandle );
int __stdcall CreateFileA( char* filename, int mode, int share, int security,
                                          int extmode, int attr, int template);
int __stdcall ReadFile( int h, void* b, int n, int* w, int o );
int __stdcall WriteFile( int h, void* b, int n, int* w, int o );
int __stdcall SetFilePointer( int hFile, int lDistanceToMove, int lDH, int mode );
int __stdcall CloseHandle( int h );
char* __stdcall GetCommandLineA();
int __stdcall GetProcessHeap();
char* __stdcall HeapAlloc( int heap, int o, int size );
int __stdcall HeapFree( int heap, int o, char* addr );
void __stdcall ExitProcess( int status );

int hHeap;
int STDFD[3]; // initialized with GetStdHandler

int open( char *path, int oflag )
{
  int f,x;
  if( oflag & O_WRONLY ) { f = GENERIC_WRITE; x = OPEN_ALWAYS; } // CREATE_ALWAYS in example
  else if( oflag & O_RDWR ) f = GENERIC_READ | GENERIC_WRITE;
  else /* O_RDONLY */ { f = GENERIC_READ; x = OPEN_EXISTING; /*assert f==O_RDONLY;*/ }

  if( f & (O_CREAT|O_EXCL) ) x = OPEN_ALWAYS;
  if( oflag & O_APPEND )
  {
    //assert f & GENERIC_WRITE;
    f = FILE_APPEND_DATA; // instead of GENERIC_WRITE
  }
  //...
  int hFile = CreateFileA(path,f,0,0,x,FILE_ATTRIBUTE_NORMAL,0);
  if( hFile == INVALID_HANDLE_VALUE ) return 0;
  //assert hFile>=0;
  return hFile + 3;
}

int read( int fd, char* buf, int count )
{
  if( fd < 3 ) fd = STDFD[fd]; else fd -= 3;
  int read = 0;
  int b = ReadFile(fd, buf, count, &read, 0);
  return b ? read : -1; // read=0 means EOF
}
int write( int fd, char* buf, int count )
{
  if( fd < 3 ) fd = STDFD[fd]; else fd -= 3;
  int written = 0;
  int b = WriteFile(fd, buf, count, &written, 0);
  return b ? written : -1;
}
int close( int fd )
{
  if( fd < 3 ) return -1;
  fd -= 3;
  return CloseHandle( fd ) ? 0 : -1;
}
int lseek( int fd, int offset, int whence ) // if bad: -1, if std: 0
{
  if( fd < 3 ) return 0;
  fd -= 3;
  int md = whence==SEEK_END ? FILE_END : (whence==SEEK_CUR ? FILE_CURRENT : FILE_BEGIN );
  int r = SetFilePointer( fd, offset, 0, md );
  return r == INVALID_SET_FILE_POINTER ? -1 : r;
}

void prepare_main()
{
  hHeap = GetProcessHeap();
  STDFD[0] = GetStdHandle(-10); // STD_INPUT_HANDLE
  STDFD[0] = GetStdHandle(STD_INPUT_HANDLE); // STD_INPUT_HANDLE
  STDFD[1] = GetStdHandle(-11); // STD_OUTPUT_HANDLE
  STDFD[2] = GetStdHandle(-12); // STD_ERROR_HANDLE
  // also args...
}

void prepare_exit()
{
}

char* malloc( int size ) { return HeapAlloc( hHeap, 0, size ); }
void free( char* ptr ) { HeapFree( hHeap, 0, ptr ); }
void exit( int status ) { ExitProcess( status ); }

// https://msdn.microsoft.com/en-us/library/windows/desktop/aa363778(v=vs.85).aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/aa363858(v=vs.85).aspx

// test

int strlen( char* s ) { char* b=s; while( *s ) ++s; return s-b; }

void __main() {}

int main(int argc,char** argv)
{
  int i;
  write(1,"hello!\n",7);

  char s[] = "x:";
  for(i=0;i<argc;++i)
  {
    s[0]='0'+i; write(1,s,2); write(1,argv[i],strlen(argv[i])); write(1,"\n",1);
  }
  return 0;
}
