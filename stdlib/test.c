// gcc -S -masm=intel -nostdlib test.c -o test.s
// insert [.include "startup.s"]
// remove ___main in two places
// remove defs at the end
// gcc -nostdlib test.s -lkernel32 -o test.exe
// test.exe a1 arg2 arg_3

// cc2.exe test.c -o test.s
// gcc -nostdlib test.s -lkernel32 -o test.exe
// test xxx yyy zzz

int open(char*p,int f);enum{O_RDONLY,O_WRONLY,O_RDWR,O_APPEND=8,O_CREAT=16,O_TRUNC=32,O_EXCL=64};
int lseek(int f,int o,int w);enum{SEEK_SET,SEEK_CUR,SEEK_END};char*malloc(int n);void free(char*a);
int close(int f);int read(int f,char*b,int c);int write(int f,char*b,int c);void exit(int s);

int strlen( char* s ) { char* b=s; while( *s ) ++s; return s-b; }

int main( int argc, char** argv )
{
  int i,k;
  write(1,"hello!\n",7);

  char s[3]; s[0] = 'x'; s[1] = ':'; s[2] = '\0';
  for(i=0;i<argc;++i)
  {
    s[0]='0'+i; write(1,s,2); write(1,argv[i],strlen(argv[i])); write(1,"\n",1);
  }

  int f = open( "aaa.txt", O_WRONLY|O_APPEND );
  if( !f ) { write(2,"err",3); return 0; }
  write( f, "11111", 5 );
  close( f );

  int g = open( "aaa.txt", O_RDONLY );
  char b[32];
  int n = read( g, b, 32-1 ); b[n] = 0;
  close( g );

  write( 2, b, strlen(b) );

  return 0;
}
