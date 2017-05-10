void printf( char* s );
int main()
{
  int x=1,y=2,z=3;

  if( 0 && 0 && 0 ) printf( "n" ); else printf( "y" );
  if( 0 && 0 || 0 ) printf( "n" ); else printf( "y" );
  if( 0 || 0 && 0 ) printf( "n" ); else printf( "y" );
  if( 0 || 0 || 0 ) printf( "n" ); else printf( "y" );
  if( 1 && 1 && 1 ) printf( "y" );
  if( 1 && 1 || 1 ) printf( "y" );
  if( 1 || 1 && 1 ) printf( "y" );
  if( 1 || 1 || 1 ) printf( "y" );
  if( x && y ) printf( "y" );
  if( x || y ) printf( "y" );
  if( !x && !y ) printf( "n" );
  if( !x || !y ) printf( "n" );
  if( x==0 && y==0 ) printf( "n" );
  if( x==1 && y==1 ) printf( "n" );
  if( x==1 && y==2 ) printf( "y" );
  if( x==1 || y==1 ) printf( "y" );
  if( x==2 || y==2 ) printf( "y" );
  if( x==3 || y==3 ) printf( "n" );
  if( x<y && y<z && x!=z ) printf( "y" );
  if( x>y || y>z || x==z ) printf( "n" ); else printf( "y" );
  if( 1<2 && 3<4 || 1<3 && 5<7 ) printf( "y" );
  if( 1<1 && 3<4 || 1<3 && 7<7 ) printf( "n" );
  printf("\n");
  return 0;
}
