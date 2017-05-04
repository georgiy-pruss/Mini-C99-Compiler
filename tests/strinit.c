int printf( char* f, char* s );

char* p = "p"; // now only this works
char s[] = "";
char t[] = "t";
char u[] = "uv";
char x[] = "xyz";
//char z[8] = "zz";

int main()
{
  printf( "|%s|\n", p );
  printf( "|%s|\n", s );
  printf( "|%s|\n", t );
  printf( "|%s|\n", u );
  printf( "|%s|\n", x );
  //printf( "|%s|\n", z );

  char* ip = "p"; // now only this works
  char is[] = "";
  char it[] = "t";
  char iu[] = "uv";
  char ix[] = "xyz";
  //char iz[8] = "zz";

  printf( "|%s|\n", ip );
  printf( "|%s|\n", is );
  printf( "|%s|\n", it );
  printf( "|%s|\n", iu );
  printf( "|%s|\n", ix );
  //printf( "|%s|\n", iz );

  return 0;
}
