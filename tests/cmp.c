int printf( char* s );
int main()
{
  int a=1, b=2, c;
  if( a==1 ) printf( "a==1\n" ); else printf( "not a==1\n" );
  if( a==b ) printf( "a==b\n" ); else printf( "not a==b\n" );
  if( b!=2 ) printf( "b!=2\n" ); else printf( "not b!=2\n" );
  if( 3<5  ) printf( "3<5\n" );  else printf( "not 3<5\n" );
  if( 3<=5 ) printf( "3<=5\n" ); else printf( "not 3<=5\n" );
  if( 3>5  ) printf( "3>5\n" );  else printf( "not 3>5\n" );
  if( 3>=5 ) printf( "3>=5\n" ); else printf( "not 3>=5\n" );
  if( 3==5 ) printf( "3==5\n" ); else printf( "not 3==5\n" );
  if( 3!=5 ) printf( "3!=5\n" ); else printf( "not 3!=5\n" );
  return c;
}

