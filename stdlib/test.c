int write( int f, char* b, int s );

int strlen( char* s ) { char* b=s; while( *s ) ++s; return s-b; }

int main( int ac, char** av )
{
  write( 1, av[0], strlen(av[0]) );
  if( ac>1 ) write( 1, av[1], strlen(av[1]) );
  if( ac>2 ) write( 1, av[2], strlen(av[2]) );
  return 0;
}
