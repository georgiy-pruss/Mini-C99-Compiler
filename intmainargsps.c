int strlen( char* s ) { int n=0; while( *s++ ) ++n; return n; }

int write( int f, char* s, int n );

int main( int ac, char** av )
{
  int i=0;
  while( i<ac )
  {
    write( 1, av[i], strlen(av[i] ) ); write( 1, "\n", 1 );
    ++i;
  }
  return ac;
}
