int write( int fd, char* str, int len );

int main()
{
  write( 1, "Hello world!\n", 13 ); // no strlen yet
  return 0;
}
