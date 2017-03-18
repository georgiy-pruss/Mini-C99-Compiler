// cc.c -- self-compiling C compiler - 2017 (C) G.Pruss
// gcc -fno-builtin-malloc -fno-builtin-strlen -O2 cc.c -o cc.exe
// -std=c99 is default in gcc

// TODO chars '\x', ops & ^ | ~

// Parameters ------------------------------------------------------------------

enum { INTSZ = 4,    // all this is for 32-bit architecture; int and int* is 4 bytes
  STR_MAX_SZ=260,    // max size of any string (line, name, etc.)
  ID_TABLE_LEN=1009, // for id freezing; should be prime number
  ST_LEN=1000,       // symbol table; max length is 1000 (it's for scopes current state!)
  RD_BUF=8000 };     // buffer for reading program text

int SC_DEBUG=0; // -T - tokens trace
int RD_LINES=0; // -L - lines
int PA_TRACE=0; // -P - parser trace
int IT_DEBUG=0; // -I - id table trace
int IT_DUMP=0;  // -D - id table dump
int ST_DUMP=0;  // -S - symbol table dump

// stdlib ----------------------------------------------------------------------

int open( char* path, int oflag, int cmode ); // >0 if ok; mode: rwx(u)rwx(g)rwx(others)
int close( int fd );                          // 0 if ok
int read( int fd, char* buf, int count );     // fd=0 - stdin
int write( int fd, char* buf, int count );    // fd=1 - stdout, fd=2 - stderr
char* malloc( int size );
void free( char* ptr );
void exit( int status );

enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=512, O_TRUNC=1024, O_EXCL=2048 };
// O_TEXT=0x4000 O_BINARY=0x8000                  win: 256           512         1024

int is_abc( int c ) { return c>='a' && c<='z' || c>='A' && c<='Z' || c=='_'; }

int strlen( char* s ) { char* b=s; while( *s ) ++s; return s-b; }
char* strcpy( char* d, char* s ) { char* r=d; for( ; *s ; ++d, ++s ) *d=*s; *d=0; return r; }
char* strcat( char* s, char* t ) { strcpy( s + strlen( s ), t ); return s; }
char* strdup( char* s ) { return strcpy( malloc( strlen(s) + 1 ), s ); }

char* strrev( char* s )
{
  int n = strlen(s); if( n<=1 ) return s;
  for( char *b = s, *e = s + n - 1; b<e; ++b, --e ) { char t = *e; *e = *b; *b = t; }
  return s;
}

int strcmp( char* s, char* t )
{
  for( ; *t; ++s, ++t )
  {
    if( *s==0 || *s<*t ) return -1;
    if( *s>*t ) return 1;
  }
  return *s!=0;
}

int strequ( char* s, char* t ) { return strcmp( s, t ) == 0; }

char* strrchr( char* s, int c )
{
  for( int n = strlen(s); n>0; --n ) if( s[n-1] == c ) return s + (n-1);
  return 0;
}

char i2s_buf[12]; // buffer for return value of i2s(x)

char* i2s( int value )
{
  if( value==0 ) return "0";
  char* dst = i2s_buf;
  if( value<0 )
  {
    if( value==(-2147483647-1) ) return "-2147483648"; // minimal 32-bit integer
    *dst = '-'; ++dst;
    value = -value;
  }
  char* to_rev = dst;
  for( ; value != 0; ++dst ) { *dst = (char)(value % 10 + '0'); value = value / 10; }
  *dst = 0;
  strrev( to_rev );
  return i2s_buf;
}

void assert( int cond, char* msg )
{
  if( cond != 0 ) return;
  write( 2, "ASSERT: ", 8 ); write( 2, msg, strlen(msg) ); write( 2, "\n", 1 );
  exit(1);
}

void p1( char* s ) { write( 1, s, strlen(s) ); }
void p2( char* s, char* s2 ) { p1( s ); p1( s2 ); }
void p3( char* s, char* s2, char* s3 ) { p1( s ); p1( s2 ); p1( s3 ); }
void p4( char* s, char* s2, char* s3, char* s4 ) { p1( s ); p1( s2 ); p1( s3 ); p1( s4 ); }

// Compiler Definitions --------------------------------------------------------

enum { Err, Eof, Num, Chr, Str, Id, // tokens
       // Op: = i d e n (++ -- == !=) < > l g (<= >=) + - * / % & ^ | ~ ! a o (&& ||)
       // Sep: ( ) [ ] { } , ;
       Kw=128 }; // actual tokens for keywors: Kw+k, where k is from below:
enum { Void, Char, Int, Enum, If, Else, While, For, Break, Return }; // keywords

int op_prec[128] = {0}; // operator precedence

void set_prec()
{
  char* opchar = "=oa|^&en<>lg+-*/%";
  for( char* p = "134567889999BBCCC"; *p; ++opchar, ++p ) op_prec[*opchar]=*p-'0';
}

int find_kw( char* s )
{
  if( strequ( s, "int"    ) ) return Int;    if( strequ( s, "char"   ) ) return Char;
  if( strequ( s, "void"   ) ) return Void;   if( strequ( s, "enum"   ) ) return Enum;
  if( strequ( s, "if"     ) ) return If;     if( strequ( s, "else"   ) ) return Else;
  if( strequ( s, "while"  ) ) return While;  if( strequ( s, "for"    ) ) return For;
  if( strequ( s, "break"  ) ) return Break;  if( strequ( s, "return" ) ) return Return;
  return -1;
}

// File reader -----------------------------------------------------------------

char rd_buf[RD_BUF];
int  rd_buf_len  = -1; // actual length of buffer; init <rd_char_pos to start rd_next
int  rd_char_pos =  0; // position in buffer
int  rd_char     = -1; // current/last char; also <0 to start in sc_read_next
int  rd_file     = -1; // file descriptor for rd_next
int  rd_line     = -1; // line number

void rd_next() // read next character, save it in rd_char; <0 if eof
{
  if( rd_char_pos >= rd_buf_len )
  {
    rd_buf_len = read( rd_file, rd_buf, RD_BUF-1 );
    if( rd_buf_len <= 0 ) { rd_char = -1; return; } // eof
    rd_buf[ rd_buf_len ] = 0;
    rd_char_pos = 0;
  }
  rd_char = rd_buf[ rd_char_pos ]; ++rd_char_pos;
}

// Id Table --------------------------------------------------------------------

char** id_table = 0;
int id_table_len = 0;
int id_count = 0;
int collisions = 0;

void id_table_create( int n )
{
  id_table = (char**)malloc( 4*n );
  id_table_len = n;
  for( int i = 0; i<n; ++i ) id_table[i] = 0;
}

int id_hash( char* s )
{
  int h = 5381;
  for( ; *s; ++s ) h = (h*66 + *s) % 16777216;
  return h;
}

int id_index( char* s ) // looks up in the table or adds there if needed
{
  if( IT_DEBUG ) p1( s );
  if( id_table==0 ) id_table_create( ID_TABLE_LEN );
  int h = id_hash( s ) % id_table_len;
  int collision = 0;
  while( id_table[h] )
  {
    if( strequ( id_table[h], s ) ) { if( IT_DEBUG ) p3( " == ", i2s(h), "\n" ); return h; }
    h = (h+1) % id_table_len;
    collision = 1;
  }
  if( collision ) ++collisions;
  if( IT_DEBUG ) p3( " ++ ", i2s(h), "\n" );
  id_table[h] = strdup( s );
  ++id_count;
  return h;
}

void id_table_dump()
{
  int k=0;
  for( int i=0; i<id_table_len; ++i )
    if( id_table[i] ) { ++k; p4( i2s(i), " ", id_table[i], "\n" ); }
  p1( "-------------------------------------\n" );
  p2( i2s(k), " ids, " );
  if( k!=id_count ) p3( " BUT MUST BE: ", i2s(id_count), ", " );
  p2( i2s(collisions), " collisions\n" );
}

// Scanner ---------------------------------------------------------------------

int  sc_tkn;              // current token
char sc_text[STR_MAX_SZ]; // for Id, Kw, Num, Str
int  sc_num;              // for Num and Chr, also id_number for Id

void sc_do_backslash()
{
  rd_next();
  if( rd_char=='n' ) rd_char = '\n';
  else if( rd_char=='r' ) rd_char = '\r';
  else if( rd_char=='b' ) rd_char = '\b';
  else if( rd_char=='0' ) rd_char = 0;
}

int sc_read_next()        // scan for next token
{
  if( rd_char < 0 ) { rd_next(); rd_line = 1; if(RD_LINES) p3( "[", i2s(rd_line), "]" ); }
  while( rd_char==' ' || rd_char=='\n' || rd_char=='\r' )
  {
    if( rd_char=='\n' ) { ++rd_line; if(RD_LINES) p3( "\n[", i2s(rd_line), "]" ); }
    rd_next();
  }
  if( rd_char<0 ) return Eof;
  if( rd_char>='0' && rd_char<='9' ) // Number
  {
    int v = rd_char - '0';
    for( rd_next(); rd_char>='0' && rd_char<='9'; rd_next() ) v = 10*v + rd_char - '0';
    sc_num = v;
    return Num;
  }
  if( is_abc(rd_char) ) // Id or Keyword
  {
    char* p = sc_text;
    while( is_abc(rd_char) || rd_char>='0' && rd_char<='9' ) { *p = rd_char; ++p; rd_next(); }
    *p = 0;
    int k = find_kw( sc_text );
    if( k >= 0 ) return Kw+k;
    sc_num = id_index( sc_text );
    return Id;
  }
  if( rd_char=='"' ) // String literal
  {
    rd_next();
    char* p = sc_text;
    while( rd_char!='"' )
    {
      if( rd_char == '\\' ) sc_do_backslash();
      *p = rd_char; ++p; rd_next();
    }
    *p = 0;
    rd_next();
    return Str;
  }
  if( rd_char=='\'' ) // Character literal (actually ''' is ok too :)
  {
    rd_next();
    if( rd_char == '\\' ) sc_do_backslash();
    sc_num = rd_char;
    rd_next();
    if( rd_char!='\'' ) return Err; // must end with apostrophe
    rd_next();
    return Chr;
  }
  if( rd_char=='{' || rd_char=='}' || rd_char=='(' || rd_char==')' ||
      rd_char=='[' || rd_char==']' || rd_char==',' || rd_char==';' ||
      rd_char=='*' || rd_char=='%' || rd_char=='^' || rd_char=='~' )
  {
    int c = rd_char; rd_next();
    return c;
  }
  if( rd_char=='=' || rd_char=='<' || rd_char=='>' || rd_char=='!' )
  {
    int c = rd_char; rd_next();
    if( rd_char == '=' ) // == <= >= != convert to: e l g n
    {
      rd_next();
      if( c=='=' ) c = 'e'; else if( c=='<' ) c = 'l'; else if( c=='>' ) c = 'g'; else c = 'n';
    }
    return c;
  }
  if( rd_char=='+' || rd_char=='-' )
  {
    int c = rd_char; rd_next();
    if( rd_char == c ) { rd_next(); if( c=='+' ) c = 'i'; else c = 'd'; } // ++ --
    return c;
  }
  if( rd_char=='&' || rd_char=='|' )
  {
    int c = rd_char; rd_next();
    if( rd_char == c ) { rd_next(); if( c=='&' ) c = 'a'; else c = 'o'; } // && ||
    return c;
  }
  if( rd_char=='/' ) // comment //... or /*...*/ or divide /
  {
    rd_next();
    if( rd_char == '/' ) // //...
    {
      rd_next();
      while( rd_char!='\n' && rd_char>0 )
        rd_next();
      if( rd_char=='\n' ) { ++rd_line; if(RD_LINES) p3( "[//]\n[", i2s(rd_line), "]" ); }
      if(rd_char>0) rd_next();
      return sc_read_next();
    }
    if( rd_char == '*' ) // /*...*/
    {
      rd_next();
      if( rd_char=='\n' ) { ++rd_line; if(RD_LINES) p3( "[/*]\n[", i2s(rd_line), "]" ); }
      while(1)
      {
        while( rd_char!='*' && rd_char>0 )
        {
          rd_next();
          if( rd_char=='\n' ) { ++rd_line; if(RD_LINES) p3( "[**]\n[", i2s(rd_line), "]" ); }
        }
        if(rd_char>0) rd_next();
        if( rd_char == '/' )
          break;
      }
      if(rd_char>0) rd_next();
      return sc_read_next();
    }
    return '/';
  }
  sc_text[0] = rd_char; sc_text[1] = 0;
  return Err;
}

char* KWDS[11] = { "void","char","int","enum","if","else","while","for","break","return" };

char str_repr_buf[STR_MAX_SZ];
char* str_repr( char* s )
{
  char* d = str_repr_buf; *d = '"'; ++d;
  for( ; *s; ++d, ++s )
  {
    if( *s=='\n' ) { *d='\\'; ++d; *d='n'; }
    else if( *s==0 ) { *d='\\'; ++d; *d='0'; }
    else if( *s=='\b' ) { *d='\\'; ++d; *d='b'; }
    else if( *s=='\r' ) { *d='\\'; ++d; *d='r'; }
    else *d=*s;
  }
  *d = '"'; ++d; *d = 0;
  return str_repr_buf;
}

void sc_next() // read and put token into sc_tkn
{
  sc_tkn = sc_read_next();
  if( SC_DEBUG )
  {
    p3( " ", i2s(sc_tkn), " - " );
    if (sc_tkn >= Kw)        p2( "kw ", KWDS[ sc_tkn - Kw ] );
    else if( sc_tkn == Id )  p4( "id ", sc_text, " #",i2s(sc_num) );
    else if( sc_tkn == Str ) p2( "str ", str_repr(sc_text) );
    else if( sc_tkn == Num ) p2( "num ", i2s(sc_num) );
    else if( sc_tkn == Chr ) p2( "chr ", i2s(sc_num) );
    else if( sc_tkn == Eof ) p1( "eof" );
    else if( sc_tkn == Err ) p2( "err", sc_text );
    else if( sc_tkn < Kw ) { char o[2] = "."; o[0]=sc_tkn; p2( "op/sep ", o ); }
    else p2( "?", sc_text );
    p1("\n");
  }
}

// Symbol table ----------------------------------------------------------------

int st_len = 0; // symbol table length; no ST initially, create dynamically
int* st_id;     // ref to id_table
char* st_level; // 0 global 1+ scope levels
char* st_type;  // 0 void 1 2 3 char^ 4 5 6 int^
char* st_kind;  // Enum    Var    Array  Arg    Func
int* st_value;  // --value --addr --addr --addr --addr
int* st_prop;   //                --len         --nargs
int  st_count;  // number of symbols in ST

enum { T_v, T_c, T_cp, T_cpp, T_i, T_ip, T_ipp }; // st_type
enum { K_enum, K_var, K_array, K_arg, K_fn };

char* st_type_str( int t )
{
  char* s[] = {"Void","Char","Char*","Char**","Int","Int*","Int**","?"};
  return s[t];
}

char* st_kind_str( int k )
{
  char* s[] = {"Enum","Var","Array","Arg","Fn"};
  return s[k];
}

void st_create( int n )
{
  // array of struct is split into set of arrays. b/c no struct in the language
  st_id = (int*)malloc( INTSZ*n );
  st_level = malloc( n );
  st_type = malloc( n );
  st_kind = malloc( n );
  st_value = (int*)malloc( INTSZ*n );
  st_prop = (int*)malloc( INTSZ*n );
  st_len = n;
  st_count = 0;
}

int st_check( int id, int level )
{
  if( st_len==0 ) st_create( ST_LEN );
  int i = st_count;
  if( i>= st_len ) p1( "ERROR TOO MANY NAMES IN SCOPES\n" ); // exit(9);
  // check if already there
  st_id[i] = id;
  st_level[i] = level;
  ++st_count;
  return i;
}

void st_add_enum( int level, int id, int value )
{
  int i = st_check( id, level );
  st_type[i] = T_i;
  st_kind[i] = K_enum;
  st_value[i] = value;
}

void st_add_var( int level, int id, int type, int addr )
{
  int i = st_check( id, level );
  st_type[i] = type;
  st_kind[i] = K_var;
  st_value[i] = addr;
}

void st_add_array( int level, int id, int type, int addr, int dim )
{
  int i = st_check( id, level );
  st_type[i] = type;
  st_kind[i] = K_array;
  st_value[i] = addr;
  st_prop[i] = dim;
}

void st_add_arg( int level, int id, int type, int addr )
{
  int i = st_check( id, level );
  st_type[i] = type;
  st_kind[i] = K_arg;
  st_value[i] = addr;
}

void st_add_fn( int level, int id, int type, int addr, int nargs )
{
  int i = st_check( id, level );
  st_type[i] = type;
  st_kind[i] = K_fn;
  st_value[i] = addr;
  st_prop[i] = nargs;
}

void st_clean( int level )
{
  if( level==0 ) return;
  while( st_count>0 && st_level[st_count-1]==level )
    --st_count;
}

int st_count_at( int level )
{
  int i = st_count, n = 0;
  for( ; i>0 && st_level[i-1]==level; --i )
    ++n;
  return n;
}

int st_find( int id )
{
  for( int i=st_count-1; i>=0; --i )
    if( st_id[i]==id ) return i;
  return -1;
}

void st_dump_level( int level )
{
  int i;
  for( i=0; i<st_count; ++i )
    if( st_level[i]==level )
      break;
  p3( "level ",i2s(level),"\n" );
  for( ; i<st_count; ++i )
  {
    assert( st_level[i]==level, "levels !=" );
    p2( i2s(i), " - " ); p3( id_table[st_id[i]]," #", i2s( st_id[i] ) );
    p4( " ", st_type_str(st_type[i]), " ", st_kind_str(st_kind[i]) );
    p2( " v=", i2s(st_value[i]) ); p3( " p=", i2s(st_prop[i]), "\n");
  }
}

void st_dump()
{
  for( int i=0; i<st_count; ++i )
  {
    p2( i2s(i), " - " ); p3( id_table[st_id[i]]," #", i2s( st_id[i] ) );
    p2( " @", i2s(st_level[i]) );
    p4( " ", st_type_str(st_type[i]), " ", st_kind_str(st_kind[i]) );
    p2( " v=", i2s(st_value[i]) ); p3( " p=", i2s(st_prop[i]), "\n");
  }
}

// Semantic variables ----------------------------------------------------------

int se_type;
int se_stars; // 0, 1, 2 - number of stars in "type stars"
int se_value; // value of constant expr, e.g. "integer"
int se_level = 0; // 0 is global
int se_enum; // value of enumerator in enum
int se_args; // number of arguments in fn

// Parser ----------------------------------------------------------------------

int tL = 0; // indent level
void tI() { p1("            "); int i=0; while(i<tL) { p1( "." ); ++i; } }
void t1( char* s ) { if( PA_TRACE ) { tI(); p2( s,"\n" ); ++tL; } }
void t2( char* s, char* s2 ) { if( PA_TRACE ) { tI(); p3( s,s2,"\n" ); ++tL; } }
void t3( char* s, char* s2, char* s3 ) { if( PA_TRACE ) { tI(); p4( s,s2,s3,"\n" ); ++tL; } }
int t_( int r )  { if( PA_TRACE ) { --tL; tI(); p3( "<< ", i2s(r), "\n" ); } return r; }

enum { F, T }; // Boolean result of pa_* functions: False, True

// Due to recursive nature and difficult syntax, some fns have to be pre-declared
int pa_expr(int min_prec); int pa_term(); int pa_vars(); int pa_block(); int pa_vardef_or_expr();

int pa_primary()
{
  t1("pa_primary");
  if( sc_tkn==Num || sc_tkn==Chr || sc_tkn==Str || sc_tkn==Id )
  {
    // if( sc_tkn==Num || sc_tkn==Chr ) p3( "=number ",i2s(sc_num),"\n");
    // else if( sc_tkn==Str ) p3( "=str ",str_repr(sc_text),"\n");
    // else if( sc_tkn==Id ) p3( "=id ",sc_text,"\n");

    sc_next(); return t_(T);
  }
  if( sc_tkn!='(' ) return t_(F);
  sc_next(); if( !pa_expr(0) ) return t_(F);
  if( sc_tkn!=')' ) return t_(F);
  sc_next();
  se_type = T_i; // elaborate!...
  return t_(T);
}

int pa_integer() // has value at compile time
{
  t1("pa_integer");
  if( sc_tkn!=Num && sc_tkn!=Chr && sc_tkn!=Id ) return t_(F);
  se_type = T_i;
  if( sc_tkn==Id ) // Id must be enum
  {
    int i = st_find( sc_num );
    if( i<0 || st_kind[i] != K_enum ) return t_(F);
    se_value = st_value[i];
  }
  else
  {
    se_value = sc_num;
    if( sc_tkn==Chr ) se_type = T_c;
  }
  sc_next();
  return t_(T);
}

int pa_exprs()
{
  t1("pa_exprs");
  if( !pa_expr(0) ) return t_(F);
  while( sc_tkn==',' ) { sc_next(); if( !pa_expr(0) ) return t_(F); }
  return t_(T);
}

int pa_call_or_index()
{
  t1("pa_call_or_index");
  while( sc_tkn=='(' || sc_tkn=='[' )
  {
    if( sc_tkn=='[' ) { sc_next(); if( !pa_expr(0) || sc_tkn!=']' ) return t_(F); }
    else /* '(' */ { sc_next(); if( sc_tkn!=')' ) { if( !pa_exprs() || sc_tkn!=')' ) return t_(F); } }
    sc_next();
  }
  return t_(T);
}

int pa_postfix()
{
  t1("pa_postfix");
  if( !pa_primary() ) return t_(F);
  return t_(pa_call_or_index());
}

int pa_unexpr()
{
  t1("pa_unexpr");
  if( sc_tkn=='i' || sc_tkn=='d' ) { sc_next(); return t_(pa_unexpr()); }
  if( sc_tkn=='-' || sc_tkn=='!' || sc_tkn=='*' || sc_tkn=='~') { sc_next(); return t_(pa_term()); }
  return t_(pa_postfix());
}

int pa_type()
{
  t1("pa_type");
  if( sc_tkn==Kw+Int || sc_tkn==Kw+Char || sc_tkn==Kw+Void)
  {
    sc_next();
    if( sc_tkn==Kw+Int ) se_type = T_i;
    else if( sc_tkn==Kw+Char ) se_type = T_c;
    else se_type = T_v;
    return t_(T);
  }
  return t_(F);
}

int pa_stars()
{
  t1("pa_stars");
  se_stars = 0;
  if( sc_tkn=='*' ) { sc_next(); se_stars = 1; if( sc_tkn=='*' ) { sc_next(); se_stars = 2; } }
  //if( se_stars>0 && se_type==T_v ) p1( "CAN'T HAVE POINTER TO VOID" );
  return t_(T);
}

int pa_term()
{
  t1("pa_term");
  if( sc_tkn=='(' )
  {
    sc_next();
    if( pa_type() )
    {
      pa_stars(); if( sc_tkn!=')' ) return t_(F);
      sc_next(); return t_(pa_term());
    }
    if( !pa_expr(0) || sc_tkn!=')' ) return t_(F);
    sc_next();
    return t_(pa_call_or_index());
  }
  return t_(pa_unexpr());
}

int pa_binop_na() // na = no advance, sc_next() must be called in the caller
{
  t1("pa_binop");
  if( sc_tkn=='*' || sc_tkn=='/' || sc_tkn=='%' ||                // C
      sc_tkn=='+' || sc_tkn=='-' ||                               // B   A: << >>
      sc_tkn=='<' || sc_tkn=='>' || sc_tkn=='l' || sc_tkn=='g' || // 9   2: ?:
      sc_tkn=='e' || sc_tkn=='n' ||                               // 8
      sc_tkn=='&' || sc_tkn=='^' || sc_tkn=='|' ||                // 7 6 5
      sc_tkn=='a' || sc_tkn=='o' || sc_tkn=='=' )                 // 4 3 1
    return t_(T);
  return t_(F);
}

int pa_expr( int min_prec ) // precedence climbing
{
  t2("pa_expr ",i2s(min_prec));

  if( !pa_term() ) return t_(F);
  // left = result of term()

  while( pa_binop_na() && min_prec < op_prec[sc_tkn] )
  {
    int t = sc_tkn;
    int p = op_prec[t];

    sc_next();

    if( !pa_expr( p ) )
      // probably no need for sc_next() here
      return t_(F);

    //char ops[3]; ops[0]=(char)t; ops[1]='\n'; ops[2]='\0';
    //p2( "exec ",ops ); or some other semantics
  }

  // maybe sc_next() here
  return t_(T);
}

int pa_vardef_or_expr()
{
  t1("pa_vardef_or_expr");
  if( sc_tkn == Kw + Int || sc_tkn == Kw + Char || sc_tkn == Kw + Void )
  {
    if( !pa_type() || !pa_stars() ) return t_(F);
    if( sc_tkn != Id ) return t_(F);
    st_add_var( se_level, sc_num, T_i, 0 );
    sc_next(); return t_(pa_vars());
  }
  if( !pa_expr(0) || sc_tkn != ';' ) return t_(F); // expr ';'
  sc_next();
  return t_(T);
}

int pa_stmt()
{
  t1("pa_stmt");
  if( sc_tkn==';' ) { sc_next(); return t_(T); } // empty stmt ';'
  if( sc_tkn=='{' ) { sc_next(); return t_(pa_block()); }
  if( sc_tkn==Kw+Break )
  {
    sc_next(); if( sc_tkn!=';' ) return t_(F); sc_next(); return t_(T);
  }
  if( sc_tkn==Kw+Return )
  {
    sc_next(); if( sc_tkn==';' ) { sc_next(); return t_(T); }
    if( !pa_expr(0) || sc_tkn!=';' ) return t_(F);
    sc_next(); return t_(T);
  }
  if( sc_tkn==Kw+While )
  {
    sc_next(); if( sc_tkn!='(' ) return t_(F);
    sc_next(); if( !pa_expr(0) || sc_tkn!=')' ) return t_(F);
    sc_next(); return t_(pa_stmt());
  }
  if( sc_tkn==Kw+If )
  {
    sc_next(); if( sc_tkn!='(' ) return t_(F);
    sc_next(); if( !pa_expr(0) || sc_tkn!=')' ) return t_(F);
    sc_next(); if( !pa_stmt() ) return t_(F);
    if( sc_tkn==Kw+Else ) { sc_next(); if( !pa_stmt() ) return t_(F); }
    return t_(T);
  }
  if( sc_tkn==Kw+For )
  {
    sc_next(); if( sc_tkn != '(' ) return t_(F);
    sc_next();
    ++se_level; // for makes a new scope
    if( sc_tkn!=';' )
    {
      if( !pa_vardef_or_expr() )
      {
        st_clean(se_level);
        --se_level;
        return t_(F);
      }
    }
    else sc_next();
    if( sc_tkn!=';' )
      if( !pa_expr(0) )
      {
        st_clean(se_level);
        --se_level;
        return t_(F);
      }
    sc_next();
    if( sc_tkn!=')' )
      if( !pa_exprs() )
      {
        st_clean(se_level);
        --se_level;
        return t_(F); // opt. post-expressions
      }
    if( sc_tkn!=')' )
    {
      st_clean(se_level);
      --se_level;
      return t_(F);
    }
    sc_next();
    int rc = pa_stmt();
    int nv = st_count_at( se_level );
    if( nv>0 )
    {
      p1("for-scope\n");
      st_dump_level( se_level );
      st_clean( se_level );
    }
    --se_level;
    return t_( rc );
  }
  return t_(pa_vardef_or_expr());
}

int pa_block() // no check for '{', it's done outside; next token right away
{
  t1("pa_block");
  ++se_level;
  while( sc_tkn!='}' ) if( !pa_stmt() ) return t_(F); // error
  int nv = st_count_at( se_level );
  if( nv>0 )
  {
    p1("block\n");
    st_dump_level( se_level );
    st_clean( se_level );
  }
  --se_level;
  sc_next();
  return t_(T);
}

int pa_arrayinit()
{
  t1("pa_arrayinit");
  if( sc_tkn==Str ) { sc_next(); return t_(T); } // string as array of char
  if( sc_tkn!='{' ) return t_(F);
  sc_next();
  if( sc_tkn==Str )
  {
    sc_next();
    while( sc_tkn==',' )
    {
      sc_next();
      if( sc_tkn!=Str ) return t_(F);
      sc_next();
    }
  }
  else
  {
    if( !pa_integer() ) return t_(F);
    while( sc_tkn==',' )
    {
      sc_next();
      if( !pa_integer() ) return t_(F);
    }
  }
  if( sc_tkn!='}' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_vartail()
{
  t1("pa_vartail");
  if( sc_tkn=='=' )
  {
    sc_next();
    return t_(pa_expr(0)); // must be calculable for globals
  }
  if( sc_tkn!='[' ) return t_(T); // without initial value
  sc_next();
  if( sc_tkn==']' ) // take length from the initial value
  {
    sc_next();
    if( sc_tkn!='=' ) return t_(F);
    sc_next();
    return t_(pa_arrayinit());
  }
  else // length is specified
  {
    if( !pa_integer() ) return t_(F);
    if( sc_tkn!=']' ) return t_(F);
    sc_next();
    if( sc_tkn!='=' ) return t_(T); // no initialization
    sc_next();
    return t_(pa_arrayinit());
  }
}

int pa_vars(int k)
{
  t1("pa_vars");
  // can't have 'void' var
  // disallow array of double-pointers, like T** V[N];
  if( !pa_vartail(k) ) return t_(F);
  while( sc_tkn==',' )
  {
    sc_next(); pa_stars(); if( sc_tkn != Id ) return t_(F);
    st_add_var( se_level, sc_num, T_i, 0 );
    sc_next(); if( !pa_vartail(k) ) return t_(F);
  }
  if( sc_tkn!=';' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_argdef()
{
  t1("pa_argdef");
  if( !pa_type() ) return t_(F);
  // can't have 'void' arg
  pa_stars();
  if( sc_tkn != Id ) return t_(F);
  ++se_args;
  st_add_arg( se_level, sc_num, T_c, se_args );
  sc_next();
  return t_(T);
}

int pa_args()
{
  t1("pa_args");
  int se_args = 0;
  if( !pa_argdef() ) return t_(T);
  while( sc_tkn==',' ) { sc_next(); if( !pa_argdef() ) return t_(F); }
  return t_(T);
}

int pa_fn_or_vars()
{
  t1("pa_fn_or_vars");
  if( sc_tkn != '(' ) return t_(pa_vars(0));
  sc_next();
  ++se_level; // for args
  if( !pa_args() || sc_tkn != ')' ) return t_(F);
  sc_next();
  if( sc_tkn == ';' ) // fn declaration
  {
    st_clean( se_level ); // args were in vain
    --se_level;
    sc_next(); return t_(T);
  }
  if( sc_tkn == '{' ) // fn definition
  {
    sc_next(); int rc = pa_block();
    int nv = st_count_at( se_level );
    if( nv>0 )
    {
      p1("args\n");
      st_dump_level( se_level );
      st_clean( se_level );
    }
    --se_level;
    return t_(rc);
  }
  return t_(F);
}

int pa_enumerator()
{
  t1("pa_enumerator");
  if( sc_tkn != Id ) return t_(F);
  int id = sc_num;
  sc_next();
  if( sc_tkn=='=' )
  {
    sc_next(); if( !pa_integer() ) return t_(F);
    se_enum = se_value;
  }
  st_add_enum( se_level, id, se_enum );
  ++se_enum;
  return t_(T);
}

int pa_enumdef()
{
  t1("pa_enumdef");
  if( sc_tkn != '{' ) return t_(F);
  se_enum = 0;
  sc_next(); if( !pa_enumerator() ) return t_(F);
  while( sc_tkn==',' ) { sc_next(); if( !pa_enumerator() ) return t_(F); }
  if( sc_tkn != '}' ) return t_(F);
  sc_next(); if( sc_tkn != ';' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_decl_or_def()
{
  t1("pa_decl_or_def");
  if( sc_tkn==Kw+Enum ) { sc_next(); return t_(pa_enumdef()); }
  if( !pa_type() ) return t_(F);
  pa_stars();
  if( sc_tkn != Id ) return t_(F);
  sc_next();
  return t_(pa_fn_or_vars());
}

int pa_program( char* fn )
{
  t1("pa_program");
  set_prec();
  rd_file = open( fn, O_RDONLY, 0 );
  if( rd_file<=0 ) return t_(F);
  int rc = T;
  sc_next(); // start parsing<-scanning<-reading
  while( sc_tkn!=Eof ) if( !pa_decl_or_def() ) { rc = F; break; }
  close( rd_file );
  return t_(rc);
}

// Main compiler function ------------------------------------------------------

int main( int ac, char** av )
{
  if( ac==1 || ac==2 && (strequ( av[1], "-h" ) || strequ( av[1], "--help" )) )
  {
    p1( "cc.exe [options] file.c\n" );
    p1( "-T  show tokens\n" );
    p1( "-L  show line numbers\n" );
    p1( "-P  show parser trace\n" );
    p1( "-I  show id table trace\n" );
    p1( "-D  dump id table data\n" );
    p1( "-S  dump symbol table\n" );
    return 0;
  }
  char* filename = 0;
  for( int i=1; i<ac; ++i )
  {
    if( *av[i] != '-' )
      filename = av[i];
    else
    {
      if( av[i][1] == 'T' ) SC_DEBUG=1;
      if( av[i][1] == 'L' ) RD_LINES=1;
      if( av[i][1] == 'P' ) PA_TRACE=1;
      if( av[i][1] == 'I' ) IT_DEBUG=1;
      if( av[i][1] == 'D' ) IT_DUMP=1;
      if( av[i][1] == 'S' ) ST_DUMP=1;
    }
  }

  if( !filename ) { p1( "No file name provided\n" ); return 1; }
  int rc = 0;
  if( !pa_program( filename ) )
  {
    p3( "\n*** Error in ", filename, " around line " ); p2( i2s( rd_line ), " ***\n" );
    rc = 2;
  }
  if( IT_DUMP ) id_table_dump();
  if( ST_DUMP )
  {
    p1("globals\n");
    st_dump();
  }
  return rc;
}
