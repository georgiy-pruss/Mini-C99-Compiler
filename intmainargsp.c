int write( int f, char* s, int n );

int main( int ac, char** av )
{
  int i=0;
  while( i<ac )
  {
    write( 1, av[i], 1 );
    ++i;
  }
  return ac;
}
