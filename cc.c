// cc.c -- self-compiling C compiler - 2017 (C) G.Pruss
// gcc -fno-builtin-malloc -fno-builtin-strlen -O2 cc.c -o cc.exe
// -std=c99 is default in gcc

// Parameters ------------------------------------------------------------------

enum { INTSZ = 4,    // all this is for 32-bit architecture; int and int* is 4 bytes
  STR_MAX_SZ=260,    // max size of any string (line, name, etc.)
  ID_TABLE_LEN=1009, // for id freezing; should be prime number
  ST_LEN=500,        // symbol table; max length is 500 (it's for all scopes at a moment)
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
  char t, *b = s, *e; int n = strlen(s); if( n<=1 ) return s;
  for( e = s + n - 1; b<e; ++b, --e ) { t = *e; *e = *b; *b = t; }
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
  int n;
  for( n = strlen(s); n>0; --n ) if( s[n-1] == c ) return s + (n-1);
  return 0;
}

char i2s_buf[12]; // buffer for return value of i2s(x)

char* i2s( int value )
{
  char* dst; char* to_rev;
  if( value==0 ) return "0";
  dst = i2s_buf;
  if( value<0 )
  {
    if( value==(-2147483647-1) ) return "-2147483648"; // minimal 32-bit integer
    *dst = '-'; ++dst;
    value = -value;
  }
  to_rev = dst;
  for( ; value != 0; ++dst ) { *dst = (char)(value % 10 + '0'); value = value / 10; }
  *dst = 0;
  strrev( to_rev );
  return i2s_buf;
}

void before_exit(); // to call if compilation fails, before calling exit()

void p1( char* s ) { write( 1, s, strlen(s) ); }
void p2( char* s, char* s2 ) { p1( s ); p1( s2 ); }
void p3( char* s, char* s2, char* s3 ) { p1( s ); p1( s2 ); p1( s3 ); }
void p4( char* s, char* s2, char* s3, char* s4 ) { p1( s ); p1( s2 ); p1( s3 ); p1( s4 ); }
void p0l() { write( 1, "\n", 1 ); }
void p1l( char* s ) { write( 1, s, strlen(s) ); write( 1, "\n", 1 ); }
void p2l( char* s, char* s2 ) { p1( s ); p1( s2 ); write( 1, "\n", 1 ); }
void p3l( char* s, char* s2, char* s3 ) { p1( s ); p1( s2 ); p1( s3 ); write( 1, "\n", 1 ); }

void assert( int cond, char* msg )
{
  if( cond != 0 ) return;
  write( 2, "ASSERT FAILED: ", 15 ); write( 2, msg, strlen(msg) ); write( 2, "\n", 1 );
  before_exit();
  exit(1);
}

// Compiler Definitions --------------------------------------------------------

enum { Err, Eof, Num, Chr, Str, Id, // tokens
       // Op: = i d e n (++ -- == !=) < > l g (<= >=) + - * / % & ^ | ~ ! a o (&& ||)
       // Sep: ( ) [ ] { } , ;
       Kw=128 }; // actual tokens for keywors: Kw+k, where k is from below:
enum { Void, Char, Int, Enum, If, Else, While, For, Break, Return }; // keywords

int op_prec[128] = {0}; // operator precedence

void op_set_prec()
{
  char* o = "=oa|^&en<>lg+-*/%";
  char* p = "134567889999BBCCC"; for( ; *o; ++o, ++p ) op_prec[*o] = *p-'0';
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

void err( char* msg )
{
  p3( "\n*** Error (~line ", i2s( rd_line ), "): " ); p2( msg, " ***\n" );
}

// Id Table --------------------------------------------------------------------

char** id_table = 0;
int id_table_len = 0;
int id_count = 0;
int collisions = 0;

void id_table_create( int n )
{
  id_table = (char**)malloc( 4*n ); id_table_len = n;
  for( --n; n>=0; --n ) id_table[n] = 0;
}

int id_hash( char* s )
{
  int h = 5381; for( ; *s; ++s ) h = (h*66 + *s) % 16777216;
  return h;
}

int id_index( char* s ) // looks up in the table or adds there if needed
{
  int h, collision = 0;
  if( IT_DEBUG ) p1( s );
  if( id_table==0 ) id_table_create( ID_TABLE_LEN );
  h = id_hash( s ) % id_table_len;
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
  int i,k;
  for( k=i=0; i<id_table_len; ++i )
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
  int v,k,c; char* p;
  if( rd_char < 0 ) { rd_next(); rd_line = 1; if(RD_LINES) p3( "[", i2s(rd_line), "]" ); }
  while( rd_char==' ' || rd_char=='\n' || rd_char=='\r' )
  {
    if( rd_char=='\n' ) { ++rd_line; if(RD_LINES) p3( "\n[", i2s(rd_line), "]" ); }
    rd_next();
  }
  if( rd_char<0 ) return Eof;
  if( rd_char>='0' && rd_char<='9' ) // Number
  {
    v = rd_char - '0';
    for( rd_next(); rd_char>='0' && rd_char<='9'; rd_next() ) v = 10*v + rd_char - '0';
    sc_num = v;
    return Num;
  }
  if( is_abc(rd_char) ) // Id or Keyword
  {
    p = sc_text;
    while( is_abc(rd_char) || rd_char>='0' && rd_char<='9' ) { *p = rd_char; ++p; rd_next(); }
    *p = 0;
    k = find_kw( sc_text );
    if( k >= 0 ) return Kw+k;
    sc_num = id_index( sc_text );
    return Id;
  }
  if( rd_char=='"' ) // String literal
  {
    rd_next();
    p = sc_text;
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
    c = rd_char; rd_next();
    return c;
  }
  if( rd_char=='=' || rd_char=='<' || rd_char=='>' || rd_char=='!' )
  {
    c = rd_char; rd_next();
    if( rd_char == '=' ) // == <= >= != convert to: e l g n
    {
      rd_next();
      if( c=='=' ) c = 'e'; else if( c=='<' ) c = 'l'; else if( c=='>' ) c = 'g'; else c = 'n';
    }
    return c;
  }
  if( rd_char=='+' || rd_char=='-' )
  {
    c = rd_char; rd_next();
    if( rd_char == c ) { rd_next(); if( c=='+' ) c = 'i'; else c = 'd'; } // ++ --
    return c;
  }
  if( rd_char=='&' || rd_char=='|' )
  {
    c = rd_char; rd_next();
    if( rd_char == c ) { rd_next(); if( c=='&' ) c = 'a'; else c = 'o'; } // && ||
    return c;
  }
  if( rd_char=='#' ) // comment #...
  {
    rd_next();
    while( rd_char!='\n' && rd_char>0 )
      rd_next();
    if(rd_char>0) rd_next();
    return sc_read_next();
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

int sc_n_tokens = 0;

void sc_next() // read and put token into sc_tkn
{
  char o[2] = ".";
  sc_tkn = sc_read_next();
  ++sc_n_tokens;
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
    else if( sc_tkn < Kw ) { o[0]=sc_tkn; p2( "op/sep ", o ); }
    else p2( "?", sc_text );
    p1("\n");
  }
}

// Symbol table ----------------------------------------------------------------

int st_len = 0; // symbol table length; no ST initially, create dynamically
int* st_id;     // ref to id_table
char* st_level; // 0 global 1 fn levels
char* st_type;  // 0 void 1 2 3 char^ 4 5 6 int^
char* st_kind;  // Enum    Var    Array  Arg    Func
int* st_value;  // --value --n    --n    --n    --addr
int* st_prop;   //         --offs --len         --nargs
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
  int i;
  if( st_len==0 ) st_create( ST_LEN );
  i = st_count;
  if( i>= st_len ) { err( "too many names in scopes" ); before_exit(); exit(9); }
  // no check if already there
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

int st_add_fn( int level, int id, int type, int addr, int nargs )
{
  int i = st_check( id, level );
  st_type[i] = type;
  st_kind[i] = K_fn;
  st_value[i] = addr;
  st_prop[i] = nargs;
  return i;
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
  int i;
  for( i=st_count-1; i>=0; --i )
    if( st_id[i]==id ) return i;
  return -1;
}

void st_dump_level( int level )
{
  int i;
  for( i=0; i<st_count; ++i )
    if( st_level[i]==level )
      break;
  if( level==0 )
    p1( "globals\n" );
  else
    p3( "level ",i2s(level),"\n" );
  for( ; i<st_count; ++i )
  {
    assert( st_level[i]==level, "levels !=" );
    p2( i2s(i), " - " ); p3( id_table[st_id[i]]," #", i2s( st_id[i] ) );
    p4( " ", st_type_str(st_type[i]), " ", st_kind_str(st_kind[i]) );
    p2( " v=", i2s(st_value[i]) );
    if( st_kind[i]==K_array || st_kind[i]==K_fn )
      p2( " p=", i2s(st_prop[i]));
    p1("\n");
  }
}

// Semantic variables ----------------------------------------------------------

int se_type;
int se_stars; // 0, 1, 2 - number of stars in "type stars"
int se_value; // value of constant expr, e.g. "integer"
int se_level = 0; // 0 is global
int se_enum; // value of enumerator in enum
int se_args; // number of arguments in fn
int se_lvars = 0; // local vars
int se_gvars = 0; // global vars

// Code generation -------------------------------------------------------------

int cg_file = 0;
char* cg_section = ""; // current section

void cg_o( char* s ) { write( cg_file, s, strlen(s) ); }
void cg_n( char* s ) { write( cg_file, s, strlen(s) ); write( cg_file, "\n", 1 ); }

void cg_begin( char* fn )
{
  cg_o( "  .file \"" ); cg_o( fn ); cg_n( "\"" );
  cg_n( "  .intel_syntax noprefix" );
}

void cg_end()
{
  // put declared but not defined functions here instead!
  char* nm[] = {"open","read","write","close","malloc","free","exit"}; int i,N=7;
  cg_n( "  .ident  \"GCC: (GNU) 5.4.0\"" );
  for( i=0; i<N; ++i ) { cg_o( "  .def _" ); cg_o( nm[i] ); cg_n( "; .scl 2; .type 32; .endef" ); }
}

void cg_fn_begin( char* name, int local_sz )
{
  if( strequ( name, "main" ) )
    cg_n( "  .def ___main; .scl 2; .type 32; .endef" );
  if( strcmp( cg_section, ".text" ) ) { cg_section = ".text"; cg_n( "  .text" ); }
  cg_o( "  .globl _" ); cg_n( name );
  cg_o( "  .def  _" ); cg_o( name ); cg_n( "; .scl 2; .type 32; .endef" );
  cg_o( "_" ); cg_o( name ); cg_n( ":" );
  cg_n( "  .cfi_startproc" );
  cg_n( "  push  ebp" );
  cg_n( "  .cfi_def_cfa_offset 8" );
  cg_n( "  .cfi_offset 5, -8" );
  cg_n( "  mov ebp, esp" );
  cg_n( "  .cfi_def_cfa_register 5" );
  if( strequ( name, "main" ) )
    cg_n( "  and esp, -16" );
  cg_o( "  sub esp, " ); cg_o( i2s(local_sz) ); cg_n( "" );
  if( strequ( name, "main" ) )
    cg_n( "  call ___main" );
  cg_n( "" );
}

void cg_fn_end( int ret0 )
{
  if( ret0 )
    cg_n( "  mov eax, 0" );
  cg_n( "  leave" );
  cg_n( "  .cfi_restore 5" );
  cg_n( "  .cfi_def_cfa 4, 4" );
  cg_n( "  ret" );
  cg_n( "  .cfi_endproc" );
  cg_n( "" );
}

// Parser ----------------------------------------------------------------------

int tL = 0; // indent level
void tI() { int i; p1("            "); for( i=0; i<tL; ++i ) p1( "." ); }
void t1( char* s ) { if( PA_TRACE ) { tI(); p2( s,"\n" ); ++tL; } }
void t2( char* s, char* s2 ) { if( PA_TRACE ) { tI(); p3( s,s2,"\n" ); ++tL; } }
void t3( char* s, char* s2, char* s3 ) { if( PA_TRACE ) { tI(); p4( s,s2,s3,"\n" ); ++tL; } }
int t_( int r )  { if( PA_TRACE ) { --tL; tI(); p3( "<< ", i2s(r), "\n" ); } return r; }

enum { F, T }; // Boolean result of pa_* functions: False, True

// Due to recursive nature and difficult syntax, some fns have to be pre-declared
int pa_expr(int min_prec); int pa_term();

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
  int i,neg=0;
  t1("pa_integer");
  if( sc_tkn=='-' ) { neg=1; sc_next(); }
  if( sc_tkn!=Num && sc_tkn!=Chr && sc_tkn!=Id ) return t_(F);
  se_type = T_i;
  if( sc_tkn==Id ) // Id must be enum
  {
    i = st_find( sc_num );
    if( i<0 || st_kind[i] != K_enum ) { err("Can't find enum Id"); return t_(F); }
    se_value = st_value[i];
  }
  else
  {
    se_value = sc_num;
    if( sc_tkn==Chr ) se_type = T_c;
  }
  if( neg ) se_value = -se_value;
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
  int t;
  t1("pa_type");
  if( sc_tkn==Kw+Int || sc_tkn==Kw+Char )
  {
    t = sc_tkn;
    sc_next();
    if( t==Kw+Int ) se_type = T_i;
    else se_type = T_c;
    return t_(T);
  }
  return t_(F);
}

int pa_stars()
{
  t1("pa_stars");
  se_stars = 0;
  if( sc_tkn=='*' ) { sc_next(); se_stars = 1; if( sc_tkn=='*' ) { sc_next(); se_stars = 2; } }
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
  int t,p;
  char ops[3];
  t2("pa_expr ",i2s(min_prec));

  if( !pa_term() ) return t_(F);
  // left = result of term()

  while( pa_binop_na() && min_prec < op_prec[sc_tkn] )
  {
    t = sc_tkn;
    p = op_prec[t];

    sc_next();

    if( !pa_expr( p ) )
      // probably no need for sc_next() here
      return t_(F);

    //ops[0]=(char)t; ops[1]='\n'; ops[2]='\0';
    //p2( "exec ",ops ); // or some other semantics
  }
  //p3( "sc_tkn: ", i2s(sc_tkn),"\n");
  // maybe sc_next() here
  return t_(T);
}

int pa_stmt()
{
  t1("pa_stmt");
  if( sc_tkn==';' ) { sc_next(); return t_(T); } // empty stmt ';'
  if( sc_tkn=='{' )
  {
    sc_next();
    while( sc_tkn!='}' ) if( !pa_stmt() ) return t_(F); // error
    sc_next();
    return t_(T);
  }
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
    if( sc_tkn!=';' ) if( !pa_expr(0) ) return t_(F); sc_next();
    if( sc_tkn!=';' ) if( !pa_expr(0) ) return t_(F); sc_next();
    if( sc_tkn!=')' ) if( !pa_exprs() ) return t_(F); // opt. post-expressions
    if( sc_tkn!=')' ) return t_(F); sc_next();
    return t_( pa_stmt() );
  }
  if( !pa_expr(0) || sc_tkn != ';' ) return t_(F); // expr ';'
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
    while( sc_tkn==',' ) { sc_next(); if( sc_tkn!=Str ) return t_(F); sc_next(); }
  }
  else
  {
    if( !pa_integer() ) return t_(F);
    while( sc_tkn==',' ) { sc_next(); if( !pa_integer() ) return t_(F); }
  }
  if( sc_tkn!='}' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_vartail()
{
  int t,id,k;
  t1("pa_vartail");
  t = se_type + se_stars;
  id = sc_num;
  if( se_level==0 ) { ++se_gvars; k=se_gvars; }
  else { ++se_lvars; k=se_lvars; }
  if( sc_tkn=='=' )
  {
    st_add_var( se_level, id, t, k ); // 1 - let's mark it has value :)
    sc_next();
    return t_(pa_expr(0)); // must be calculable for globals
  }
  if( sc_tkn!='[' )
  {
    st_add_var( se_level, id, t, k );
    return t_(T); // without initial value
  }
  sc_next();
  if( sc_tkn==']' ) // take length from the initial value
  {
    sc_next();
    if( sc_tkn!='=' ) return t_(F);
    st_add_array( se_level, id, t, k, -1 ); // calc dim
    sc_next();
    return t_(pa_arrayinit());
  }
  else // length is specified
  {
    if( !pa_integer() ) return t_(F); // value in se_value
    if( sc_tkn!=']' ) return t_(F);
    st_add_array( se_level, id, t, k, se_value );
    sc_next();
    if( sc_tkn!='=' ) return t_(T); // no initialization
    sc_next();
    return t_(pa_arrayinit());
  }
}

int pa_vars()
{
  t1("pa_vars");
  // disallow array of double-pointers, like T** V[N];
  if( !pa_vartail() ) return t_(F);
  while( sc_tkn==',' )
  {
    sc_next(); pa_stars();
    if( sc_tkn != Id ) return t_(F);
    sc_next();
    if( !pa_vartail() ) return t_(F);
  }
  if( sc_tkn!=';' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_vardef()
{
  int t;
  t1("pa_vardef");
  if( sc_tkn != Kw + Int && sc_tkn != Kw + Char ) return t_(F);

  if( !pa_type() || !pa_stars() ) return t_(F);
  t = se_type + se_stars;
  if( sc_tkn != Id ) return t_(F);
  sc_next();
  return t_(pa_vars());
}

int pa_argdef()
{
  t1("pa_argdef");
  if( !pa_type() ) return t_(F);
  pa_stars();
  if( sc_tkn != Id ) return t_(F);
  ++se_args;
  st_add_arg( se_level, sc_num, T_c, se_args );
  sc_next();
  return t_(T);
}

int se_args;

int pa_args()
{
  t1("pa_args");
  se_args = 0;
  if( !pa_argdef() ) return t_(T);
  while( sc_tkn==',' )
  {
    sc_next();
    if( !pa_argdef() ) return t_(F);
  }
  return t_(T);
}

int pa_fn_or_vars()
{
  int id,t,nv,k;
  t1("pa_fn_or_vars");
  if( sc_tkn != '(' ) return t_(pa_vars());
  id=sc_num; t=se_type+se_stars;
  k = st_find( id );
  if( k>=0 && se_level==st_level[k] )
    p3( "dupl fn ",id_table[id],"\n" );
  k = st_add_fn( se_level, id, t, 0, 0 ); // or lookup for double def
  sc_next();
  ++se_level; // args and vars inside fn are at level 1 actually
  if( !pa_args() || sc_tkn != ')' ) return t_(F);
  st_prop[k] = se_args; // correct number of arguments
  // also need args types
  sc_next();
  if( sc_tkn == ';' ) // fn declaration
  {
    st_clean( se_level ); // args were in vain
    --se_level;
    sc_next(); return t_(T);
  }
  if( sc_tkn == '{' ) // fn definition
  {
    sc_next();
    se_lvars = 0;
    while( pa_vardef() )
      /* define local var */ ;
    nv = st_count_at( se_level );
    assert( nv==se_args+se_lvars, "nv==se_args+se_lvars" );
    cg_fn_begin( id_table[id], nv*4 );
    while( sc_tkn!='}' ) if( !pa_stmt() ) return t_(F); // error
    sc_next();
    if( nv>0 )
    {
      if( ST_DUMP ) { p3("fn ",id_table[id],"\n"); st_dump_level( se_level ); }
      st_clean( se_level );
    }
    --se_level;
    cg_fn_end( 1 ); // flag = ret 0; depend on last stmt in fn body
    return t_(T);
  }
  return t_(F);
}

int pa_enumerator()
{
  int id;
  t1("pa_enumerator");
  if( sc_tkn != Id ) return t_(F);
  id = sc_num;
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
  if( sc_tkn==Kw+Void )
  {
    se_type=T_v;  se_stars = 0;
    sc_next();
    if( sc_tkn != Id ) return t_(F);
    sc_next();
    if( sc_tkn != '(' ) return t_(F);
    return t_(pa_fn_or_vars());
  }
  if( !pa_type() ) return t_(F);
  pa_stars();
  if( sc_tkn != Id ) return t_(F);
  sc_next();
  return t_(pa_fn_or_vars());
}

int pa_program( char* fn )
{
  int rc = T;
  t1("pa_program");
  rd_file = open( fn, O_RDONLY, 0 );
  if( rd_file<=0 ) return t_(F);
  sc_next(); // start parsing<-scanning<-reading
  while( sc_tkn!=Eof ) if( !pa_decl_or_def() ) { rc = F; break; }
  close( rd_file );
  return t_(rc);
}

void before_exit()
{
  if( cg_file>0 ) close(cg_file); cg_file=0;
}

// Main compiler function ------------------------------------------------------

int main( int ac, char** av )
{
  char* filename = 0;
  int i,rc;
  if( ac==1 || ac==2 && (strequ( av[1], "-h" ) || strequ( av[1], "--help" )) )
  {
    p1( "c2s.exe [options] file.c\n" );
    p1( "-T  show tokens\n" );
    p1( "-L  show line numbers\n" );
    p1( "-P  show parser trace\n" );
    p1( "-I  show id table trace\n" );
    p1( "-D  dump id table data\n" );
    p1( "-S  dump symbol table\n" );
    return 0;
  }
  for( i=1; i<ac; ++i )
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

  if( !filename ) { p1( "No file name provided\n" ); exit(1); }
  // init
  op_set_prec();
  cg_file = open( "a.s", O_CREAT|O_WRONLY, 511 ); // 0777 - allow all
  if( cg_file<0 ) { p1( "Can't create file 'a.s'\n" ); exit(1); }
  cg_begin( filename );
  rc = 0;
  if( !pa_program( filename ) )
  {
    err( "something's wrong" );
    rc = 2; // don't exit, print tables if requested
  }
  cg_end();
  if( cg_file>0 ) close( cg_file );
  if( IT_DUMP ) id_table_dump();
  if( ST_DUMP ) st_dump_level(0);
  if( SC_DEBUG ) p2( i2s( sc_n_tokens ), " tokens\n" );
  return rc;
}
