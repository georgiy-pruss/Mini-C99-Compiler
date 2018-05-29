// cc.c -- self-compiling C compiler
// Copyright (C) 2017 Georgiy Pruss
// https://github.com/georgiy-pruss/Mini-C99-Compiler
// gcc -fno-builtin-malloc -fno-builtin-strlen -O2 cc.c -o cc.exe
// -std=c99 is default in gcc

// TODO number array initializers; local array initializers
// TODO exprs in vardef_of_expr to allow for( i=1,j=2; ... ) and ++i, f(i), a=b;

char* TITLE = "Georgiy Pruss C99C 0.26149";

// Parameters ------------------------------------------------------------------

enum { INTSZ = 4,    // all this is for 32-bit architecture; int and int* is 4 bytes
  STR_MAX_SZ=260,    // max size of any string (line, name, etc.)
  ID_TABLE_DIM=1009, // for id freezing; should be prime number
  SL_TABLE_DIM=500,  // string literal table; let's assume 500
  ST_DIM=500,        // symbol table; max length is 500 (it's for all scopes at a moment)
  RD_BUF=8000,       // buffer for reading program text
  BF_WRT_SZ=4000,    // buffer for suspended output
  MAX_INIT_DIM=600,  // max number of items in init array
  BSS_ORG=100000 };  // tag that data is in bss section (BSS_ORG+offset)

int SC_DEBUG=0; // -T - tokens trace, including lines
int PA_TRACE=0; // -P - parser trace
int IT_DEBUG=0; // -I - id table trace
int IT_DUMP=0;  // -D - id table dump
int ST_DUMP=0;  // -S - symbol table dump
int ET_TRACE=0; // -E - trace expressions
int CG_LINES=1; // -L - omit output of line numbers; -L => CG_LINES=0

// stdlib ----------------------------------------------------------------------

//int open( char* path, int oflag ); // >0 if ok; flags below - own flags!
int close( int fd );                          // 0 if ok
int read( int fd, char* buf, int count );     // fd=0 - stdin
int write( int fd, char* buf, int count );    // fd=1 - stdout, fd=2 - stderr
int lseek( int fd, int offset, int whence ); // if bad: -1, if std: 0
char* malloc( int size );
void free( char* ptr );
void exit( int status );
//enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=16, O_TRUNC=32, O_EXCL=64 };
enum { SEEK_SET, SEEK_CUR, SEEK_END };

enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=256, O_TRUNC=512, O_EXCL=1024,
   O_TEXT=16384, O_BINARY=32768 }; // Windows
int open( char* path, int oflag, int mode ); // Windows

// helper fns ------------------------------------------------------------------

int is_abc( int c ) { return c>='a' && c<='z' || c>='A' && c<='Z' || c=='_'; }

void memcopy( char* d, char* s, int n ) { for( ; n>0; ++d, ++s, --n ) *d = *s; }

char* memchr( char* s, int c, int n ) { for( ; n>0; --n, ++s ) if( *s==c ) return s; return 0; }

int strlen( char* s ) { char* b=s; while( *s ) ++s; return s-b; }

char* strdup( char* s )
{
  int n = strlen(s); char* d = malloc( n + 1 ); memcopy( d, s, n + 1 );
  return d;
}

char* strrev( char* s )
{
  int n = strlen(s); if( n<=1 ) return s;
  for( char* b = s, *e = s+n-1; b<e; ++b, --e ) { char t = *e; *e = *b; *b = t; }
  return s;
}

int strcmp( char* s, char* t )
{
  for( ; *t; ++s, ++t ) { if( *s==0 || *s<*t ) return -1; if( *s>*t ) return 1; }
  return *s!=0;
}

int strequ( char* s, char* t ) { return strcmp( s, t ) == 0; }

char* strrchr( char* s, int c )
{
  for( int n = strlen(s); n>0; --n ) if( s[n-1] == c ) return s + (n-1);
  return 0;
}

char str_repr_buf[STR_MAX_SZ];

char* str_repr( char* s )
{
  char* d = str_repr_buf; *d = '"';
  for( ++d; *s; ++d, ++s )
  {
    if( *s=='\n' ) { *d='\\'; *++d='n'; }
    else if( *s==0 ) { *d='\\'; *++d='0'; }
    else if( *s=='\b' ) { *d='\\'; *++d='b'; }
    else if( *s=='\r' ) { *d='\\'; *++d='r'; }
    else *d=*s;
  }
  *d = '"'; *++d = '\0';
  return str_repr_buf;
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

void p1( char* s ) { write( 1, s, strlen(s) ); } // p = print
void p2( char* s, char* s2 ) { p1( s ); p1( s2 ); }
void p3( char* s, char* s2, char* s3 ) { p1( s ); p1( s2 ); p1( s3 ); }
void p4( char* s, char* s2, char* s3, char* s4 ) { p1( s ); p1( s2 ); p1( s3 ); p1( s4 ); }
void p0n() { write( 1, "\n", 1 ); } // n = new line
void p1n( char* s ) { write( 1, s, strlen(s) ); p0n(); }
void p2n( char* s, char* s2 ) { p1( s ); p1( s2 ); p0n(); }
void p3n( char* s, char* s2, char* s3 ) { p1( s ); p1( s2 ); p1( s3 ); p0n(); }

void before_exit(); // to call if compilation fails, before calling exit()

void assert( int cond, char* msg )
{
  if( cond != 0 ) return;
  write( 2, "ASSERT FAILED: ", 15 ); write( 2, msg, strlen(msg) ); write( 2, "\n", 1 );
  before_exit();
  exit(1);
}

void p2wLN( char* k, char* m ); // print 2 args with special msg and line number

void warn( char* msg ) { p2wLN( "Warning", msg ); }
void err1( char* msg ) { p2wLN( "Error", msg ); before_exit(); exit(1); }
void err2( char* msg, char* m2 ) { p2wLN( "Error", msg );
                                   p2n( "*** ", m2 ); before_exit(); exit(1); }

// Compiler Definitions --------------------------------------------------------

enum { Err, Eof, Num, Chr, Str, Id, // tokens
       // Op: = i d e n (++ -- == !=) < > l g (<= >=) + - * / % & ^ | ~ ! a o (&& ||)
       // Sep: ( ) [ ] { } , ;
       Kw=128 }; // actual tokens for keywors: Kw+k, where k is from below:

enum { Void, Char, Int, Enum, If, Else, While, For, Break, Return, NKW }; // keywords

char* KWDS[NKW] = { "void","char","int","enum","if","else","while","for","break","return" };

int find_kw( char* s )
{
  for( int i=0; i<NKW; ++i ) if( strequ( s, KWDS[i] ) ) return i;
  return -1;
}

char* OPS = "=+-en*/%<>lgao&^|"; // binary ors in frequency order
char* PRC = "1BB88CCC999943765"; // precedence corresp. to OPS
enum { OPS_LEN = 17 };

int op_prec[128]; // operator precedence

void op_set_prec() { for( int i=0; OPS[i]; ++i ) op_prec[OPS[i]] = PRC[i]-'0'; }

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
  if( rd_char<0 ) rd_char = rd_char + 256; // transfer chars -128..-1 to 128..255
}

void p2wLN( char* sev, char* msg ) // we can define it when rd_line is defined
{
  p4( "\n*** ", sev, " at or before line ", i2s( rd_line ) ); p2n( "\n*** ", msg );
}

// Id Table --------------------------------------------------------------------

char** id_table = 0;
int id_table_dim = 0;
int id_count = 0;
int collisions = 0;

void id_table_create( int n )
{
  id_table = (char**)malloc( 4*n ); id_table_dim = n;
  for( --n; n>=0; --n ) id_table[n] = 0;
}

int id_hash( char* s )
{
  int h = 5381; for( ; *s; ++s ) h = (h*66 + *s) % 0100000000; return h;
}

int id_index( char* s ) // looks up in the table or adds there if needed
{
  if( IT_DEBUG ) p1( s );
  int h = id_hash( s ) % id_table_dim; int h0 = h;
  int collision = 0;
  while( id_table[h] )
  {
    if( strequ( id_table[h], s ) ) { if( IT_DEBUG ) p2n( " == ", i2s(h) ); return h; }
    h = (h+1) % id_table_dim;
    if( h == h0 ) err1( "Too many ids; id_table is full" );
    collision = 1;
  }
  if( collision ) ++collisions;
  if( IT_DEBUG ) p2n( " ++ ", i2s(h) );
  id_table[h] = strdup( s );
  ++id_count;
  return h;
}

void id_table_dump()
{
  int k = 0; // count ids for double-check
  for( int i=0; i<id_table_dim; ++i )
    if( id_table[i] ) { ++k; p3n( i2s(i), " ", id_table[i] ); }
  p1( "-------------------------------------\n" );
  p2( i2s(k), " ids, " );
  assert( k==id_count, "Errors in id_table (negative hash?)" );
  p2( i2s(collisions), " collisions\n" );
}

// String Literal table --------------------------------------------------------

char** sl_table; // ptr to array of char (string) ptrs
int sl_count;

void sl_table_create( int n ) { sl_table = (char**)malloc( n*INTSZ ); sl_count = 0; }

int sl_add( char* s )
{
  for( int i=0; i<sl_count; ++i ) if( strequ( s, sl_table[i] ) ) return i; // 237->199
  if( sl_count==SL_TABLE_DIM ) err1( "Too many literal strings" );
  sl_table[ sl_count ] = strdup( s );
  ++sl_count;
  return sl_count - 1;
}

void sl_table_dump()
{
  for( int i=0; i<sl_count; ++i ) p3n( i2s(i), " -> ", str_repr(sl_table[i]) );
}

// Scanner ---------------------------------------------------------------------

int  sc_tkn;              // current token
char sc_text[STR_MAX_SZ]; // for Id, Kw, Num, Str
int  sc_num;              // for Num and Chr, also id_number for Id

void cg_line(); // put line nr (rd_line) in assembler output

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
  if( rd_char < 0 ) { rd_next(); rd_line = 1; cg_line(); }
  while( rd_char==' ' || rd_char=='\n' || rd_char=='\r' )
  {
    if( rd_char=='\n' ) { ++rd_line; cg_line(); }
    rd_next();
  }
  if( rd_char<0 ) return Eof;
  if( rd_char>='0' && rd_char<='9' ) // Number
  {
    int v = rd_char - '0';
    if( v==0 ) // octal
      for( rd_next(); rd_char>='0' && rd_char<='7'; rd_next() ) v = 8*v + rd_char - '0';
      // hex also can be here, under 'x' etc..... in future
    else // decimal
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
    sc_num = sl_add( sc_text );
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
  if( memchr( "(){}[],;*%^~", rd_char, 12 ) )
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
  if( rd_char=='#' ) // comment #...
  {
    rd_next();
    while( rd_char!='\n' && rd_char>0 )
      rd_next();
    if( rd_char=='\n' ) { ++rd_line; cg_line(); }
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
      if( rd_char=='\n' ) { ++rd_line; cg_line(); }
      if(rd_char>0) rd_next();
      return sc_read_next();
    }
    if( rd_char == '*' ) // /*...*/
    {
      rd_next();
      if( rd_char=='\n' ) { ++rd_line; cg_line(); }
      while(1)
      {
        while( rd_char!='*' && rd_char>0 )
        {
          rd_next();
          if( rd_char=='\n' ) { ++rd_line; cg_line(); }
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

int sc_n_tokens = 0; // total count of tokens, JFYI
int sc_prev_line;

void sc_next() // read and put token into sc_tkn
{
  sc_tkn = sc_read_next();
  ++sc_n_tokens;
  if( SC_DEBUG )
  {
    if( rd_line != sc_prev_line ) { p0n(); sc_prev_line = rd_line; }
    p2( i2s(rd_line), "| " ); p2( i2s(sc_tkn), " - " );
    if (sc_tkn >= Kw)        p2( "kw ", KWDS[ sc_tkn - Kw ] );
    else if( sc_tkn == Id )  p4( "id ", id_table[sc_num], " #",i2s(sc_num) );
    else if( sc_tkn == Str ) p2( "str ", str_repr(sl_table[sc_num]) );
    else if( sc_tkn == Num ) p2( "num ", i2s(sc_num) );
    else if( sc_tkn == Chr ) p2( "chr ", i2s(sc_num) );
    else if( sc_tkn == Eof ) p1( "eof\n" );
    else if( sc_tkn == Err ) p2( "err", sc_text );
    else if( sc_tkn < Kw ) { char o[2]; o[0]=sc_tkn; o[1]='\0'; p2( "op/sep ", o ); }
    else p2( "???", sc_text );
    p0n();
  }
}

// Symbol table ----------------------------------------------------------------

int   st_dim = 0; // symbol table length; no ST initially, create dynamically
int*  st_id;      // ref to id_table
char* st_type;    // 0 void 1 2 3 char^ 4 5 6 int^
char* st_kind;    // Enum    Var    Array  Arg    Func
int*  st_value;   // --value --offs --offs --offs --0|offs
int*  st_prop;    //                --dim         --args
int   st_count;   // number of symbols in ST; the last is at st_count-1
int   st_local;   // start of local part of symbol table

enum { T_v, T_c, T_cp, T_cpp, T_i, T_ip, T_ipp }; // st_type
  // T_cp==T_c+1, T_cpp==T_cp+1, T_ip==T_i+1, T_ipp==T_ip+1 -- must be so!
enum { K_enum, K_var, K_array, K_arg, K_fn };

char* st_type_str[] = {"Void","Char","Char*","Char**","Int","Int*","Int**"};
char* st_kind_str[] = {"Enum","Var","Array","Arg","Fn"};

int se_is_int( int t ) { return t==T_c || t==T_i; }
int se_is_ptr( int t ) { return t==T_cp || t==T_cpp || t==T_ip || t==T_ipp; }
int se_is_ptr4( int t ) { return t==T_cpp || t==T_ip || t==T_ipp; }

void st_create( int n )
{
  // array of struct is split into set of arrays. b/c no struct in the language
  st_id = (int*)malloc( INTSZ*n );
  st_type = malloc( n );
  st_kind = malloc( n );
  st_value = (int*)malloc( INTSZ*n );
  st_prop = (int*)malloc( INTSZ*n );
  st_dim = n;
  st_count = 0;
}

char* st_copy_args( int start, int nargs )
{
  char* args = malloc( nargs+1 );
  for( int i=0; i<nargs; ++i )
  {
    assert( start<st_count && st_kind[start+i]==K_arg, "st_copy" );
    args[i] = st_type[start+i];
  }
  args[nargs]=0; // all types except Void >0; arg can't be Void
  return args;
}

int st_find( int id )
{
  for( int i=st_count-1; i>=0; --i ) if( st_id[i]==id ) return i;
  return -1;
}

int st_add( int id, int type, int kind, int value, int aux )
{
  int k = st_count;
  if( k >= st_dim ) err1( "too many identifiers" );
  st_id[k]=id; st_type[k]=type; st_kind[k]=kind; st_value[k]=value; st_prop[k]=aux;
  ++st_count;
  return k;
}

int st_count_local_sz()
{
  int s=0, words;
  for( int i=st_local; i<st_count; ++i )
  {
    if( st_kind[i]==K_var )
      words = 1;
    else if( st_kind[i]==K_array )
    {
      if( st_type[i]==T_c ) words = (st_prop[i] + 3) / INTSZ;
      else words = st_prop[i];
    }
    else
    {
      assert(st_kind[i]==K_arg,"K_arg");
      words = 0;
    }
    s = s + INTSZ * words;
  }
  return s;
}

void print_args( char* a )
{
  if( *a==0 ) p1( " ()" ); else for( ; *a; ++a ) p2( " ", st_type_str[*a] );
}

int st_dump( int start, int kind ) // kind == -1 -- all, if K_var, K_array too
{
  int cnt=0;
  for( int i=start; i<st_count; ++i )
  {
    int k = st_kind[i]; int kk = k; if( kk==K_array ) kk=K_var;
    if( kind==-1 || kind==kk )
    {
      ++cnt;
      p3( i2s(i), " - ", id_table[st_id[i]] );
      p3( " (", i2s( st_id[i] ), ") " );
      p3( st_type_str[st_type[i]], " ", st_kind_str[k] );
      p2( " v=", i2s(st_value[i]) );
      if( k==K_array )
        p2( " dim: ", i2s(st_prop[i]));
      if( k==K_fn )
        { p1( " args:" ); print_args( (char*)st_prop[i] ); }
      p0n();
    }
  }
  return cnt;
}

// Semantic variables ----------------------------------------------------------

int se_type;  // pa_type sets type here (Char or Int; Void is done separately)
int se_stars; // 0, 1, 2 - number of stars in "type stars"
int se_value; // value of constant expr, e.g. "integer"
int se_level = 0; // 0 is global; 1+ is in function; 2+ in for/blocks
int se_enum; // value of enumerator in enum
int se_arg_count; // number of arguments in fn
int se_lvars = 0; // local vars -- JFYI
int se_gvars = 0; // global vars -- JFYI
int se_items; // items in initialization array
int* se_array_items; // the items
int se_last_stmt_ret; // last statement was return -- for cg_fn_end
int se_local_offset; // offset for local vars (negative! for [EBP-...])
int se_max_l_offset; // max value of local offset == stack size to allocate
                     // but locals grow down, so it's 'max negative' = 'min'
int se_data_offset; // initialized data segment
int se_bss_offset;  // zero data segment -- bss section, in var: +BSS_ORG

// Buffer for writing ----------------------------------------------------------

enum { BF_LAST, BF_NEXT, BF_DIM, BF_COUNT, BF_HEADSZ };

int* bf_alloc_min( int n )
{
  // buffer (each part) starts with: last, next, maxn, curn
  int* a = (int*)malloc( (BF_HEADSZ + (n+INTSZ-1)/INTSZ) * INTSZ );
  a[BF_LAST] = (int)a; // pointer to the last part (only in first!)
  a[BF_DIM] = n; // allocated for n chars (used only in first)
  a[BF_NEXT] = 0; // next; 0 means it's the last one
  a[BF_COUNT] = 0; // current length (== n in all but the last one)
  return a;
}

void bf_append( int* bf, char* s, int n )
{
  int* last = (int*)bf[BF_LAST];
  int left = bf[BF_DIM]-last[BF_COUNT];
  while( left < n )
  {
    memcopy( (char*)(last+BF_HEADSZ) + last[BF_COUNT], s, left );
    last[BF_COUNT] = last[BF_COUNT] + left; // assert last[BF_COUNT]==bf[BF_DIM]
    // then allocate and put it at the end, it will be the new last
    int* new_bf = bf_alloc_min( bf[BF_DIM] );
    bf[BF_LAST] = (int)new_bf;
    last[BF_NEXT] = (int)new_bf;
    s = s + left;
    n = n - left;
    last = new_bf;
    left = bf[BF_DIM];
  }
  memcopy( (char*)(last+BF_HEADSZ) + last[BF_COUNT], s, n );
  last[BF_COUNT] = last[BF_COUNT] + n;
}

void bf_write( int* bf, int fd )
{
  while( bf ) { write( fd, (char*)(bf + BF_HEADSZ), bf[BF_COUNT] ); bf = (int*)bf[BF_NEXT]; }
}

void bf_free( int* bf )
{
  int* next = (int*)bf[BF_NEXT]; free( (char*)bf );
  while( next!=0 ) { bf = next; next = (int*)bf[BF_NEXT]; free( (char*)bf ); }
}

// Expression tree -------------------------------------------------------------

enum { ET_none, // not used actually; may be in tx(ET_NULL)... like that
  ET_num,   // + int; enum also gives ET_num, char literal too
  ET_str,   // + sl-id
  ET_var,   // + id (id checked and it's var or array or arg)
  ET_fn,    // + id (id checked and it's fn)
  ET_call,  // + fn-expr 0 | expr ptr-to-list
  ET_cast,  // + expr (type is from st_type enum, i.e. 1..3 char, 4..6 int; it's in tag!)
  ET_star,  // + expr  (*E)
  ET_neg }; // + expr  (-E)
  // other nodes are marked with these chars (from tokens enum):
  // 'i' 'd'    // + expr  -- incr, decr
  // '~' '!'    // + expr  -- not-bin, not-log
  // '*' '/' '%' '+' '-' '<' '>' 'l' 'g' 'e' 'n' '&' '^' '|' 'a' 'o' '=' // + expr1 expr2

// low 8 bits - expression kind/tag (ET_xxx)
// high 24 bits - expression type (T_xxx) actually 3 bits only
enum { ET_MASK=0377, ET_T=0400 }; // to get type - /ET_T, to add type - *ET_T

int* ET_1( int tag, int* expr, int type )
{
  int* r = (int*)malloc( 2*INTSZ ); r[0] = tag + type*ET_T; r[1] = (int)expr; return r;
}

int* ET_2( int tag, int* expr1, int* expr2, int type )
{
  int* r = (int*)malloc( 3*INTSZ ); r[0] = tag + type*ET_T; r[1] = (int)expr1; r[2] = (int)expr2;
  return r;
}

int* ET_I( int tag, int value, int type ) { return ET_1( tag, (int*)value, type ); }

int* ET_P( int* e ) { return ET_1( (int)e, 0, 0 ); } // just a pair for exprs (list)


char* ET_TAG[] = {"","Num","Str","Var","Fn","Call","Cast","@","Neg"};

void et_print( int* e )
{
  int e0 = e[0] & ET_MASK;
  int e0type = e[0] / ET_T;
  if( e0<' ' ) p3("(",ET_TAG[e0]," ");
  else if( e0=='i' ) p1( "(++ " ); else if( e0=='d' ) p1( "(-- " );
  else if( e0=='a' ) p1( "(&& " ); else if( e0=='o' ) p1( "(|| " );
  else if( e0=='e' ) p1( "(== " ); else if( e0=='n' ) p1( "(!= " );
  else if( e0=='l' ) p1( "(<= " ); else if( e0=='g' ) p1( "(>= " );
  else { char s[2]; s[0]=(char)e0; s[1]='\0'; p3("(",s," "); }
  // TODO INIT: else { char s[2] = {(char)e0,'\0'}; p3("(",s," "); }
  if( e0==ET_num ) { p1(i2s(e[1])); }
  else if( e0==ET_str ) p1(str_repr(sl_table[e[1]]));
  else if( e0==ET_fn ) p1(id_table[st_id[e[1]]]);
  else if( e0==ET_var ) p1(id_table[st_id[e[1]]]);
  else if( e0==ET_call ) { et_print( (int*)e[1] ); p1( " [" );
    for( int n=0, x=e[2]; x; ++n, x=((int*)x)[1] ) // = et_print_exprs
      { if(n>0)p1(" "); et_print( (int*)((int*)x)[0] ); }
    p1("]"); }
  else if( e0==ET_cast ) { p1( st_type_str[e0type] ); p1( " " ); et_print( (int*)e[1] ); }
  else if( e0==ET_star ) et_print( (int*)e[1] );
  else if( e0==ET_neg ) et_print( (int*)e[1] );
  else if( e0=='i'||e0=='d'||e0=='~'||e0=='!' ) et_print( (int*)e[1] );
  else { et_print( (int*)e[1] ); p1( " " ); et_print( (int*)e[2] ); }
  p3(" |",st_type_str[e0type],")"); // type:
}

void et_print_exprs( int** x )
{
  for( int n=0; x; ++n, x = (int**)x[1] ) { if(n>0)p1(" "); et_print( x[0] ); } p1n("]");
}

// Code generation -------------------------------------------------------------

enum { S_NONE, S_CODE, S_DATA, S_BSS }; // sections; bss = zero-init data

int cg_file = 0;
int* cg_buffer = 0;
int cg_section = S_NONE; // current section
int cg_data_align = 0; // current data align 0 to 3 (we don't alignt to 32)
int cg_bss_align = 0; // current bss align

int cg_label;    // general label number, for fns, if/then, etc
int cg_fn_label; // current function exit label

int cg_loop_label[20]; // stack of labels for loops/breaks
int cg_loop_level;     // stack "pointer"

int cg_new_label() { return ++cg_label; }

int cg_new_loop_label()
{
  cg_loop_label[cg_loop_level] = ++cg_label; ++cg_loop_level;
  return cg_label;
}

int cg_current_loop_label()
{
  if( cg_loop_level<=0 ) return -1;
  return cg_loop_label[cg_loop_level-1];
}

void cg_pop_loop_label() { --cg_loop_level; }

void cg_o( char* s )
{
  int n = strlen(s);
  if( cg_buffer == 0 ) write( cg_file, s, n ); else bf_append( cg_buffer, s, n );
}

void cg_n( char* s )
{
  int n = strlen(s);
  if( cg_buffer == 0 ) { write( cg_file, s, n ); write( cg_file, "\n", 1 ); }
  else { bf_append( cg_buffer, s, n ); bf_append( cg_buffer, "\n", 1 ); }
}

void cg_2( char* s, char* t ) { cg_o(s); cg_o(t); }
void cg_2n( char* s, char* t ) { cg_o(s); cg_n(t); }
void cg_3( char* s, char* t, char* u ) { cg_o(s); cg_o(t); cg_o(u); }
void cg_3n( char* s, char* t, char* u ) { cg_o(s); cg_o(t); cg_n(u); }

void cg_line() { if( CG_LINES ) cg_2n( "  # ", i2s(rd_line) ); }

void cg_suspend() // after this, write to buffer
{
  assert( cg_buffer==0, "int error: already suspended!" );
  cg_buffer = bf_alloc_min( BF_WRT_SZ );
}

void cg_resume( char* s ) // output string, then unload buffer to the file
{
  assert( cg_buffer!=0, "int error: was not suspended!" );
  write( cg_file, s, strlen(s) );
  bf_write( cg_buffer, cg_file ); bf_free( cg_buffer ); cg_buffer = 0;
}

void cg_begin( char* fn )
{
  cg_3n( "  .file \"", fn, "\"" );
  cg_n( "  .intel_syntax noprefix\n" );
  cg_n( "  .include \"startup.s\"\n" );
}

void cg_end()
{
  // http://www.trilithium.com/johan/2004/12/gcc-ident-strings/
  cg_3n( "\n  .ident  \"", TITLE, "\"\n" );
  /*
  // dump declarations of all undefined functions
  for( int i=0; i<st_count; ++i )
    if( st_kind[i]==K_fn && st_value[i]==0 )
      cg_3n( "  .def _", id_table[st_id[i]], "; .scl 2; .type 32; .endef" );
  */
}

void cg_fn_begin( char* name )
{
  // if( strequ( name, "main" ) ) cg_n( "  .def ___main; .scl 2; .type 32; .endef" );
  if( cg_section != S_CODE ) { cg_section = S_CODE; cg_n( "  .text" ); }
  cg_2n( "  .globl _", name );
  cg_3n( "  .def _", name, "; .scl 2; .type 32; .endef" );
  cg_3n( "_", name, ":" );
  cg_n( "  .cfi_startproc" );
  cg_n( "  push ebp" );
  cg_n( "  .cfi_def_cfa_offset 8\n  .cfi_offset 5,-8" );
  cg_n( "  mov ebp,esp" );
  cg_n( "  .cfi_def_cfa_register 5" );
}

void cg_fn_end( int ret0 )
{
  if( ret0 ) cg_n( "  xor eax,eax" );
  cg_3n( "R", i2s( cg_fn_label ), ":" );
  cg_n( "  leave" );
  cg_n( "  .cfi_restore 5\n  .cfi_def_cfa 4,4" );
  cg_n( "  ret" );
  cg_n( "  .cfi_endproc\n" );
}

void cg_spec_and_nl( char* str, int next )
{
  cg_o( str ); if( next>='0' && next<='9' ) cg_o( "\"\n  .ascii \"" );
}

void cg_sl_str( int i ) // write string def w/o align; w/o label
{
  char c[2]; c[1]='\0';
  // TODO INIT: char c[2] = ".";
  cg_o( "  .ascii \"" );
  for( char* s = sl_table[i]; *s; ++s )
  {
    if( *s=='\n' ) cg_spec_and_nl( "\\12", s[1] );
    else if( *s=='\\' ) cg_spec_and_nl( "\\134", s[1] );
    else if( *s=='\r' ) cg_spec_and_nl( "\\15", s[1] );
    else if( *s=='\b' ) cg_spec_and_nl( "\\10", s[1] );
    else if( *s=='\"' ) cg_spec_and_nl( "\\42", s[1] );
    else { c[0] = *s; cg_o( c ); }
  }
  cg_n( "\\0\"" );
}

void cg_sl_table()
{
  cg_n( "  .section .rdata,\"dr\"" );
  for( int i=0; i<sl_count; ++i )
  {
    cg_3n( "S", i2s(i), ":" );
    cg_sl_str( i );
  }
}

char* cg_var( int e1 ) // generate fragment, return name
{
  if( st_type[e1]==T_c ) cg_o( "BYTE PTR " ); else cg_o( "DWORD PTR " );
  if( e1<st_local ) { cg_2( "_", id_table[st_id[e1]] ); return 0; }
  int v = st_value[e1]; // local var
  cg_o( "[ebp" ); if( v>0 ) cg_o( "+" ); cg_2( i2s(v), "]" );
  return id_table[st_id[e1]];
}

void cg_var_n( int e )
{
  char* name = cg_var( e ); if( name ) cg_2n( " # ", name ); else cg_o( "\n" );
}

int cg_exprs_backwards_with_push( int** e );

void cg_expr( int* e )
{
  int e0 = e[0] & ET_MASK;
  if( e0==ET_num )
  {
    int n = e[1];
    if( n==0 ) cg_n( "  xor eax,eax" ); else cg_2n( "  mov eax,", i2s(n) );
  }
  else if( e0==ET_str )
  {
    cg_2n( "  mov eax,OFFSET FLAT:S", i2s(e[1]) );
  }
  else if( e0==ET_var )
  {
    int k = st_kind[e[1]];
    if( k==K_var || k==K_arg )
    {
      assert( e[0] / ET_T == st_type[e[1]], "ET_var is wrong" );
      if( st_type[e[1]]==T_c ) cg_o( "  movsx eax," ); else cg_o( "  mov eax," );
      cg_var_n( e[1] );
    }
    else // ET_var K_array
    {
      assert( k==K_array, "Must be var | arg | array" );
      int id = st_id[e[1]];
      if( e[1]<st_local ) // global array
        cg_o( "  mov eax,OFFSET FLAT:_" );
      else // local array
      {
        cg_o( "  lea eax,[ebp" ); int v = st_value[e[1]]; if( v>0 ) cg_o( "+" );
        cg_2( i2s(v), "] # " );
      }
      cg_n( id_table[id] );
    }
  }
  else if( e0==ET_call )
  {
    // TODO check arg types and number! TODO ... = n_args == VAR_ARGS
    if( (*(int*)e[1]&ET_MASK)!=ET_fn ) err1( "A call must have fn name on the left" );
    int n_args = cg_exprs_backwards_with_push( (int**)e[2] );
    cg_2n( "  call _", id_table[st_id[((int*)e[1])[1]]] );
    if( n_args>0 ) cg_2n( "  add esp,", i2s( INTSZ*n_args ) );
  }
  else if( e0=='=' )
  {
    int* e1 = (int*)e[1];
    int* e2 = (int*)e[2];
    int e1tag = e1[0] & ET_MASK;
    if( se_is_ptr(e1[0]/ET_T) && se_is_int(e2[0]/ET_T) ) // allow ptr = 0
    {
      if( !((e2[0] & ET_MASK) == ET_num && e2[1] == 0) )
        err1( "Can't assign integer to pointer" );
    }
    if( e1tag==ET_var )
    {
      if( st_kind[e1[1]]==K_array )
        err2( "Can't assign to array: ", id_table[st_id[e1[1]]] );
      cg_expr( (int*)e[2] );
      cg_o( "  mov " );
      char* name = cg_var( e1[1] );
      if( *e1 / ET_T == T_c ) cg_o( ",al" ); else cg_o( ",eax" );
      if( name ) cg_2n( " # ", name ); else cg_o( "\n" );
    }
    else if( e1tag==ET_star )
    {
      int e2et = *(int*)e[2] & ET_MASK;
      int n = ((int*)e[2])[1];
      if( e2et == ET_num || (e2et == ET_var && st_kind[n]!=K_array) )
      {
        cg_expr( (int*)e1[1] );
        cg_n( "  mov ebx,eax" );
        if( e2et == ET_num )
        {
          if( n==0 ) cg_n( "  xor eax,eax" );
          else       cg_2n( "  mov eax,", i2s(n) );
        }
        else // e2et == ET_var
        {
          if( *(int*)e[2] / ET_T == T_c ) cg_o( "  movsx eax," );
          else                            cg_o( "  mov eax," );
          cg_var_n( n );
        }
      }
      else
      {
        cg_expr( (int*)e1[1] ); cg_n( "  push eax" );
        cg_expr( (int*)e[2] );  cg_n( "  pop ebx" );
      }
      if( e1[0] / ET_T == T_c ) cg_n( "  mov BYTE PTR [ebx],al" );
      else                      cg_n( "  mov DWORD PTR [ebx],eax" );
    }
    else
      err1( "Wrong expression on left of '='" );
  }
  else if( e0=='i' || e0=='d' )
  {
    int* e1 = (int*)e[1];
    int e1et = e1[0] & ET_MASK;
    if( e1et == ET_var )
    {
      int k = st_kind[e1[1]];
      if( k==K_array )
        err2( "Can't be array name: ", id_table[st_id[e1[1]]] );
      if( st_type[e1[1]]==T_c ) cg_o( "  movsx eax," ); else cg_o( "  mov eax," );
      cg_var_n( e1[1] );
      if( e0=='i' ) cg_o( "  add eax," ); else cg_o( "  sub eax," );
      if( se_is_ptr4(st_type[e1[1]]) ) cg_n( "4" ); else cg_n( "1" ); // var type
      cg_o( "  mov " );
      char* name = cg_var( e1[1] );
      if( *e1 / ET_T == T_c ) cg_o( ",al" ); else cg_o( ",eax" );
      if( name ) cg_2n( " # ", name ); else cg_o( "\n" );
    }
    else if( e1et == ET_star )
    {
      int t = e[0] / ET_T; // expr type
      cg_expr( (int*)e1[1] );
      cg_n( "  mov ebx,eax" );
      if( t==T_c ) cg_n( "  movsx eax,BYTE PTR [ebx]" );
      else         cg_n( "  mov eax,DWORD PTR [ebx]" );
      if( e0=='i' ) cg_o( "  add eax," ); else cg_o( "  sub eax," );
      if( se_is_ptr4(t) ) cg_n( "4" ); else cg_n( "1" );
      if( t==T_c ) cg_n( "  mov BYTE PTR [ebx],al" );
      else         cg_n( "  mov DWORD PTR [ebx],eax" );
    }
    else
      err1( "Wrong expr for increment/decrement" );
  }
  else if( e0==ET_star )
  {
    int e0type = e[0] / ET_T; // dereferenced type!
    cg_expr( (int*)e[1] );
    if( e[0] / ET_T == T_c ) cg_n( "  movsx eax,BYTE PTR [eax]" );
    else                     cg_n( "  mov eax,DWORD PTR [eax]" );
  }
  else if( e0==ET_cast )
  {
    cg_expr( (int*)e[1] ); // no action at run-time
  }
  else if( e0==ET_neg )
  {
    cg_expr( (int*)e[1] ); cg_n( "  neg eax" );
  }
  else if( e0=='~' )
  {
    cg_expr( (int*)e[1] ); cg_n( "  not eax" );
  }
  else if( e0=='!' )
  {
    cg_expr( (int*)e[1] );
    cg_n( "  test eax,eax\n  setz al\n  movzx eax,al" );
  }
  else if( e0=='e' || e0=='n' )
  {
    int e2et = *(int*)e[2] & ET_MASK;
    int n = ((int*)e[2])[1];
    int zero = e2et == ET_num && n == 0;
    if( se_is_ptr( *(int*)e[1] / ET_T ) && se_is_int( *(int*)e[2] / ET_T ) )
    {
      if( !zero ) err1( "Can't compare poiner and number" );
    }
    char* cmp = "e";
    if( e2et == ET_num || (e2et == ET_var && st_kind[n]!=K_array) )
    {
      cg_expr( (int*)e[1] );
      if( zero )
      {
        cg_n( "  test eax,eax" ); cmp = "z";
      }
      else if( e2et == ET_var && *(int*)e[2] / ET_T == T_c )
      {
        cg_o( "  movsx ebx," ); cg_var_n( n ); cg_n( "  cmp eax,ebx" );
      }
      else
      {
        cg_o( "  cmp eax," ); if( e2et == ET_var ) cg_var_n( n ); else cg_n( i2s( n ) );
      }
    }
    else // some complex expression
    {
      cg_expr( (int*)e[2] ); cg_n( "  push eax" );
      cg_expr( (int*)e[1] ); cg_n( "  pop ebx\n  cmp eax,ebx" );
    }
    cg_o( "  set" ); if( e0=='n' ) cg_o( "n" ); cg_2n( cmp, " al\n  movzx eax,al" );
  }
  else if( memchr( "<>lg", e0, 4 ) )
  {
    int e2et = *(int*)e[2] & ET_MASK;
    int n = ((int*)e[2])[1];
    if( e2et == ET_num || (e2et == ET_var && st_kind[n]!=K_array) )
    {
      cg_expr( (int*)e[1] );
      if( e2et == ET_var && *(int*)e[2] / ET_T == T_c )
      {
        cg_o( "  movsx ebx," ); cg_var_n( n ); cg_n( "  cmp eax,ebx" );
      }
      else
      {
        cg_o( "  cmp eax," ); if( e2et == ET_var ) cg_var_n( n ); else cg_n( i2s( n ) );
      }
    }
    else // some complex expression
    {
      cg_expr( (int*)e[2] ); cg_n( "  push eax" );
      cg_expr( (int*)e[1] ); cg_n( "  pop ebx\n  cmp eax,ebx" );
    }
    char* o="l"; if( e0=='>' ) o="g"; else if( e0=='l' ) o="le"; else if( e0=='g' ) o="ge";
    cg_3n( "  set", o, " al\n  movzx eax,al" );
  }
  else if( memchr( "+-&|^*/%", e0, 8 ) )
  {
    int e1t = *(int*)e[1] / ET_T;
    int e2t = *(int*)e[2] / ET_T;
    int e2et = *(int*)e[2] & ET_MASK;
    int mixed = 0; // pointer cases: Tp + i (1) or i + Tp (2) or Tp - i (3)
    if( e0=='+' )
    {
      if( se_is_ptr4(e1t) && se_is_int(e2t) ) mixed = 1;
      else if( se_is_int(e1t) && se_is_ptr4(e2t) ) mixed = 2;
    }
    else if( e0=='-' && se_is_ptr4(e1t) && se_is_int(e2t) )
      mixed = 3;
    if( e2et == ET_num )
    {
      cg_expr( (int*)e[1] );
      int n = ((int*)e[2])[1];
      if( e0!='+' && e0!='-' && e0!='|' && e0!='^' || n!=0 )
      {
        if( e0=='+' )
        {
          if( mixed==2 ) cg_n( "  sal eax,2" );
          cg_o( "  add eax," ); // add eax,N
        }
        else if( e0=='-' ) cg_o( "  sub eax," );
        else if( e0=='*' ) cg_o( "  imul eax,eax," );
        else if( e0=='&' ) cg_o( "  and eax," );
        else if( e0=='|' ) cg_o( "  or eax," );
        else if( e0=='^' ) cg_o( "  xor eax," );
        else cg_o( "  cdq\n  mov ebx," ); // / % -- no 'idiv NUM'
        if( e0=='+' && mixed==1 || e0=='-' && mixed==3 ) n = n*4; // Tp + i or Tp - i
        cg_n( i2s( n ) );
        if( e0=='/' || e0=='%' ) cg_n( "  idiv ebx" );
      }
    }
    else if( e2et == ET_var && e2t != T_c && st_kind[((int*)e[2])[1]]!=K_array )
    {
      cg_expr( (int*)e[1] );
      if( e0=='+' ) { if( mixed==0 ) cg_o( "  add eax," ); else cg_o( "  mov ebx," ); }
      else if( e0=='-' ) { if( mixed==0 ) cg_o( "  sub eax," ); else cg_o( "  mov ebx," ); }
      else if( e0=='*' ) cg_o( "  imul eax," );
      else if( e0=='&' ) cg_o( "  and eax," );
      else if( e0=='|' ) cg_o( "  or eax," );
      else if( e0=='^' ) cg_o( "  xor eax," );
      else { cg_n( "  cdq" ); cg_o( "  idiv " ); }
      cg_var_n( ((int*)e[2])[1] );
      if( e0=='+' )
      {
        if( mixed==1 )      cg_n( "  lea eax,[eax+4*ebx]" ); // Tp + i
        else if( mixed==2 ) cg_n( "  lea eax,[4*eax+ebx]" ); // i + Tp
      }
      else if( e0=='-' && mixed==3 )
      {
        cg_n( "  sal ebx,2\n  sub eax,ebx" ); // Tp - i
      }
    }
    else // some complex expression
    {
      cg_expr( (int*)e[2] ); cg_n( "  push eax" );
      cg_expr( (int*)e[1] ); cg_n( "  pop ebx" );
      if( e0=='+' )
      {
        if( mixed==1 )      cg_n( "  lea eax,[eax+4*ebx]" ); // Tp + i
        else if( mixed==2 ) cg_n( "  lea eax,[4*eax+ebx]" ); // i + Tp
        else                cg_n( "  add eax,ebx" );
      }
      else if( e0=='-' )
      {
        if( mixed==3 ) cg_n( "  sal ebx,2" ); // Tp - i
        cg_n( "  sub eax,ebx" );
      }
      else if( e0=='*' ) cg_n( "  imul eax,ebx" );
      else if( e0=='&' ) cg_n( "  and eax,ebx" );
      else if( e0=='|' ) cg_n( "  or eax,ebx" );
      else if( e0=='^' ) cg_n( "  xor eax,ebx" );
      else /* / % */   { cg_n( "  cdq" ); cg_n( "  idiv ebx" ); }
    }
    if( e0=='-' && se_is_ptr4( *(int*)e[2] / ET_T ) ) cg_n( "  sar eax,2" );
    if( e0=='%' ) cg_n( "  mov eax,edx" );
  }
  else if( e0=='a' ) // &&
  {
    int and_label = cg_new_label();
    cg_expr( (int*)e[1] );
    cg_n( "  test eax,eax\n  setnz al\n  movzx eax,al" ); // need 0 or 1 for result
    cg_n( "  test eax,eax" );
    cg_o( "  jz A" ); cg_n( i2s( and_label ) );
    cg_expr( (int*)e[2] );
    cg_n( "  test eax,eax\n  setnz al\n  movzx eax,al" ); // need 0 or 1 for result
    cg_3n( "A", i2s( and_label ), ":" );
  }
  else if( e0=='o' ) // ||
  {
    int or_label = cg_new_label();
    cg_expr( (int*)e[1] );
    cg_n( "  test eax,eax\n  setnz al\n  movzx eax,al" ); // need 0 or 1 for result
    cg_n( "  test eax,eax" );
    cg_2n( "  jnz O", i2s( or_label ) );
    cg_expr( (int*)e[2] );
    cg_n( "  test eax,eax\n  setnz al\n  movzx eax,al" ); // need 0 or 1 for result
    cg_3n( "O", i2s( or_label ), ":" );
  }
  else if( e0==ET_fn )
    err1( "Just fn name? Must be fn(...)" );
  else
    assert( 0, "What expr?" ); // ET_TAG[e0]
}

int cg_exprs_backwards_with_push( int** x  ) // return number of exprs
{
  if( !x ) return 0;
  int n = cg_exprs_backwards_with_push( (int**)x[1] ); // first tail, then head
  cg_expr( x[0] );
  cg_n( "  push eax" );
  return n + 1;
}

void cg_exprs( int** x ) { for( ; x; x = (int**)x[1] ) cg_expr( x[0] ); }

// Parser ----------------------------------------------------------------------

int  tL = 0; // indent level
void tI() { p1("            "); for( int i=0; i<tL; ++i ) p1( "." ); }
void t1( char* s ) { if( PA_TRACE ) { tI(); p1n( s ); ++tL; } }
void t2( char* s, char* s2 ) { if( PA_TRACE ) { tI(); p2n( s,s2 ); ++tL; } }
void t3( char* s, char* s2, char* s3 ) { if( PA_TRACE ) { tI(); p3n( s,s2,s3 ); ++tL; } }
int  t_( int r ) { if( PA_TRACE ) { --tL; tI(); p2n( "<< ", i2s(r) ); } return r; }
int* tx( int* r ) { if( PA_TRACE ) { --tL; tI(); p2n( "<<* ", i2s((int)r) ); } return r; }

enum { F, T }; // Boolean result of pa_* functions: False, True

// Due to recursive nature and difficult syntax, some fns have to be pre-declared
// parser fns returning false/true - pa_...; returning expressions - px_...

int* px_expr(int min_prec); int* px_term();

int* px_primary()
{
  t1("px_primary");
  int* r;
  if( sc_tkn==Num || sc_tkn==Chr || sc_tkn==Str )
  {
    int t = T_i, k = ET_num;
    if( sc_tkn==Str ) { k = ET_str; t = T_cp; } else if( sc_tkn==Chr ) t = T_c;
    r = ET_I( k, sc_num, t );
    sc_next(); return tx(r);
  }
  if( sc_tkn==Id )
  {
    int varid = st_find(sc_num);
    if( varid < 0 ) err2( "Name is not defined: ", id_table[sc_num] );
    if( st_kind[varid]==K_enum ) r = ET_I( ET_num, st_value[varid], T_i );
    else if( st_kind[varid]==K_fn ) r = ET_I( ET_fn, varid, st_type[varid] );
    else if( st_kind[varid]==K_array ) r = ET_I( ET_var, varid, st_type[varid]+1 );
    else r = ET_I( ET_var, varid, st_type[varid] ); // var arg
    sc_next(); return tx(r);
  }
  if( sc_tkn!='(' ) return tx(0);
  sc_next(); if( !(r = px_expr(0)) ) return tx(0);
  if( sc_tkn!=')' ) return tx(0);
  sc_next();
  return tx(r);
}

int pa_integer() // has value at compile time; return in se_value
{
  int neg=F;
  t1("pa_integer");
  if( sc_tkn=='-' ) { neg=T; sc_next(); }
  if( sc_tkn!=Num && sc_tkn!=Chr && sc_tkn!=Id ) return t_(F);
  se_type = T_i;
  if( sc_tkn==Id ) // Id must be enum
  {
    int i = st_find( sc_num );
    if( i<0 || st_kind[i] != K_enum )
      err2( "Can't find enum Id in const expression", id_table[sc_num] );
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

int* px_exprs()
{
  t1("px_exprs");
  int* r = px_expr(0); if( !r ) return tx(0);
  int* first = ET_P( r ); // use it just as a pair - an item of a list of exprs
  int* last = first;
  while( sc_tkn==',' )
  {
    sc_next();
    if( !(r = px_expr(0)) ) return tx(0);
    last[1] = (int)ET_P( r );
    last = (int*)last[1];
  }
  return tx(first);
}

int* px_call_or_index(int* e)
{
  t1("px_call_or_index");
  int* r;
  while( sc_tkn=='(' || sc_tkn=='[' )
  {
    if( sc_tkn=='[' )
    {
      sc_next();
      if( !(r = px_expr(0)) || sc_tkn!=']' ) return tx(0);
      int et = *e / ET_T;
      int rt = *r / ET_T;
      if( !(et==T_cp || et==T_cpp || et==T_ip || et==T_ipp) )
        err1( "Indexed expr. must be pointer" );
      if( !(rt==T_i || rt==T_c) ) err1( "Index must be integer" ); // char too!
      // we don't implement 5[a] although *(5+a) works
      e = ET_1( ET_star, ET_2( '+', e, r, et ), et-1 );
    }
    else /* '(' */
    {
      sc_next();
      if( sc_tkn==')' )
      {
        e = ET_2( ET_call, e, 0, *e / ET_T ); // call with no args
      }
      else
      {
        if( !(r = px_exprs()) || sc_tkn!=')' ) return tx(0);
        e = ET_2( ET_call, e, r, *e / ET_T ); // r is list of args
      }
    }
    sc_next();
  }
  return tx(e);
}

int* px_postfix()
{
  t1("px_postfix");
  int* r = px_primary();
  if( !r ) return tx(0);
  return tx( px_call_or_index(r) );
}

int* px_unexpr()
{
  t1("px_unexpr");
  if( sc_tkn=='i' || sc_tkn=='d' )
  {
    int t = sc_tkn;
    sc_next();
    int* e = px_unexpr();
    return tx( ET_1( t, e, *e / ET_T ) ); // the same type
  }
  if( sc_tkn=='-' || sc_tkn=='!' || sc_tkn=='*' || sc_tkn=='~')
  {
    int t = sc_tkn;
    if( t=='-' ) t = ET_neg; else if( t=='*' ) t = ET_star;
    sc_next();
    int* e = px_term();
    int type = T_i;
    if( t==ET_star )
    {
      int et = *e / ET_T;
      if( !(et==T_cp || et==T_cpp || et==T_ip || et==T_ipp) )
        err1( "Dereferenced expr. must be pointer" );
      type = et-1;
    }
    return tx( ET_1( t, e, type ) );
  }
  return tx( px_postfix() );
}

int pa_type() // sets se_type
{
  t1("pa_type");
  if( sc_tkn==Kw+Int || sc_tkn==Kw+Char )
  {
    if( sc_tkn==Kw+Int ) se_type = T_i; else se_type = T_c;
    sc_next();
    return t_(T);
  }
  return t_(F);
}

int pa_stars() // sets se_stars
{
  t1("pa_stars");
  se_stars = 0;
  if( sc_tkn=='*' ) { sc_next(); se_stars = 1; if( sc_tkn=='*' ) { sc_next(); se_stars = 2; } }
  return t_(T);
}

int* px_term()
{
  t1("px_term");
  if( sc_tkn=='(' )
  {
    sc_next();
    if( pa_type() ) // cast (T)E
    {
      pa_stars(); if( sc_tkn!=')' ) return tx(0);
      int t = se_type + se_stars;
      sc_next();
      return tx( ET_1( ET_cast, px_term(), t ) );
    }
    int* r = px_expr(0);
    if( !r || sc_tkn!=')' ) return tx(0); // (E)
    sc_next();
    return tx( px_call_or_index( r ) );
  }
  return tx( px_unexpr() );
}

int se_calc_binop_type( int op, int* left, int* right )
{
  // calculate new type based on token op, left expr, right expr types
  if( op=='a' || op=='o' ) return T_i;
  int lt = *left / ET_T;
  int rt = *right / ET_T;
  if( op=='=' && lt==T_c && rt==T_c ) return T_c; // don't promote to int
  if( se_is_int(lt) && se_is_int(rt) ) return T_i; // enough for '&^|*/%'
  if( op=='=' )
  {
    if( se_is_ptr(lt) && lt==rt ) return lt; // Tp = Tp -> Tp
    if( se_is_ptr(lt) && (rt==T_c || rt==T_i) ) return lt; // Tp = 0
  }
  else if( op=='+' )
  {
    if( se_is_ptr(lt) && (rt==T_c || rt==T_i) ) return lt; // Tp + i|c -> Tp
    if( (lt==T_c || lt==T_i) && se_is_ptr(rt) ) return rt; // i|c + Tp -> Tp
  }
  else if( op=='-' )
  {
    if( se_is_ptr(lt) && (rt==T_c || rt==T_i) ) return lt; // Tp - i|c -> Tp
    if( se_is_ptr(lt) && lt==rt ) return T_i;              // Tp - Tp -> i
  }
  else if( op=='e' || op=='n' )
  {
    if( se_is_ptr(lt) && lt==rt ) return T_i; // Tp == Tp -> i
    if( se_is_ptr(lt) && (rt==T_c || rt==T_i) ) return T_i; // Tp == 0
  }
  else if( op=='<' || op=='>' || op=='l' || op=='g' )
  {
    if( se_is_ptr(lt) && lt==rt ) return T_i; // Tp == Tp -> i
  }
  // error: show msg with operator
  char op_s[2]; op_s[0] = (char)op; op_s[1]='\0';
  char* op_r = op_s;
  if( op=='e' ) op_r = "=="; else if( op=='n' ) op_r = "!=";
  else if( op=='l' ) op_r = "<="; else if( op=='g' ) op_r = ">=";
  err2( "Wrong operand types in operator: ", op_r );
  return T_v;
}

int* px_expr( int min_prec ) // precedence climbing
{
  t2("px_expr ",i2s(min_prec));
  int* r = px_term();
  if( !r ) return tx(0);
  while( memchr( OPS, sc_tkn, OPS_LEN ) != 0 && min_prec < op_prec[sc_tkn] )
  {
    int p = op_prec[sc_tkn];
    if( sc_tkn=='=' ) --p; // correct precedence for right-to-left operator
    int t = sc_tkn;
    sc_next();
    int* q = px_expr( p );
    if( !q ) return tx(0);
    r = ET_2( t, r, q, se_calc_binop_type( t, r, q ) );
  }
  return tx( r );
}

int pa_arrayinit()        // TODO can be any expression?
{
  t1("pa_arrayinit");
  if( sc_tkn==Str ) // string as array of char
  {
    if( se_type!=T_c ) return t_(F);
    se_items = strlen( sc_text ) + 1;
    sc_next();
    return t_(T);
  }
  se_items = 0;
  se_array_items = 0;
  if( sc_tkn!='{' ) return t_(F);
  sc_next();
  if( sc_tkn==Str )
  {
    int* array_items = (int*)malloc( INTSZ*MAX_INIT_DIM );
    array_items[se_items] = sc_num;
    sc_next();
    while( sc_tkn==',' )
    {
      sc_next(); ++se_items;
      if( sc_tkn!=Str ) return t_(F);   // TODO sc_tkn can be '0', 1st too
      array_items[se_items] = sc_num;
      sc_next();
    }
    se_array_items = array_items;
  }
  else
  {
    if( !pa_integer() ) return t_(F);
    while( sc_tkn==',' )
    {
      sc_next(); ++se_items;
      if( !pa_integer() ) return t_(F);
    }
  }
  if( sc_tkn!='}' ) return t_(F);
  sc_next(); ++se_items;
  return t_(T);
}

int se_add_var( int id, int t, int dim, int init, int* init_exprs )
{
  // init == 0 -- no init, Num/Str -- integer ([-]Int/Chr) or String,
  // init == Id -- variable... we'll see if it's used
  int k = K_array;
  if( dim<0 ) { dim=1; k = K_var; }
  int itemsz=INTSZ; if( t==T_c ) itemsz=1;
  int idealsz = dim*itemsz;
  int varsz = (idealsz + INTSZ-1) / INTSZ * INTSZ; // align up to INTSZ bound
  // local var
  if( se_level>0 )
  {
    se_local_offset = se_local_offset - varsz; // negative!
    if( init )
    {
      if( k==K_var )
      {
        cg_expr( init_exprs );
        // TODO check type
        cg_o( "  mov DWORD PTR [ebp" ); cg_o( i2s( se_local_offset ) );
        cg_o( ",eax # init " ); cg_n( id_table[id] );
      }
      else // array
      {
        int n=0;
        for( int* x=init_exprs; x && n<dim; ++n, x = (int*)x[1] )
        {
          cg_expr( (int*)x[0] );
          cg_o( "  mov DWORD PTR [ebp" ); cg_o( i2s( se_local_offset+n*INTSZ ) ); // TODO char
          if( n!=0 ) cg_n( ",eax" ); else { cg_o( ",eax # init " ); cg_n( id_table[id] ); }
        }
        for( ; n<dim; ++n )
        {
          cg_o( "  mov DWORD PTR [ebp" ); cg_o( i2s( se_local_offset+n*INTSZ ) ); // TODO char
          cg_n( ",0" );
        }
      }
    }
    return st_add( id, t, k, se_local_offset, dim ); // local var
  }
  // global var
  if( init==0 || init==Num && init_exprs==0 )
  {
    int n = st_add( id, t, k, se_bss_offset+BSS_ORG, dim ); // global bss
    se_bss_offset = se_bss_offset + varsz;
    cg_o( "  .globl _" ); cg_n( id_table[id] );
    if( cg_section != S_BSS ) { cg_section = S_BSS; cg_n( "  .bss" ); }
    if( idealsz>=4 && cg_bss_align!=0 ) { cg_n( "  .align 4" ); cg_bss_align=0; }
    cg_bss_align = (cg_bss_align+idealsz) % 4;
    cg_o( "_" ); cg_o( id_table[id] ); cg_n( ":" );
    cg_o( "  .space " ); cg_n( i2s(idealsz) );
    return n;
  }
  int n = st_add( id, t, k, se_data_offset, dim ); // global var in data section
  se_data_offset = se_data_offset + varsz;
  cg_o( "  .globl _" ); cg_n( id_table[id] );
  if( cg_section != S_DATA ) { cg_section = S_DATA; cg_n( "  .data" ); }
  if( idealsz>=4 && cg_data_align!=0 ) { cg_n( "  .align 4" ); cg_data_align=0; }
  cg_data_align = (cg_data_align+idealsz) % 4;
  cg_o( "_" ); cg_o( id_table[id] ); cg_n( ":" );
  if( init==Str && t==T_c && k==K_array )
  {
    cg_sl_str( (int)init_exprs ); // .ascii "...."
    int tail = dim - (strlen( sl_table[(int)init_exprs] )+1);
    if( tail > 0 ) { cg_o( "  .space " ); cg_n( i2s( tail ) ); }
  }
  else if( init==Str && t==T_cp && k==K_array )
  {
    int items = dim;
    if( items>se_items ) items = se_items;
    int i=0;
    for( ; i<items; ++i )
      cg_2n( "  .long S", i2s(init_exprs[i]) );
    if( i<dim )
      cg_2n( "  .space ", i2s(4*(dim-items) ) );
  }
  else
  {
    cg_o( "  .long " );
    if( t==T_cp ) // then init_exprs is string index
      cg_2n( "S", i2s( (int)init_exprs ) );
    else
      cg_n( i2s( (int)init_exprs ) );
    // TODO value; cg_data_   if chars; etc
    // maybe .space ...
  }
  return n;
}

int pa_vartail()
{
  assert(sc_tkn=='='||sc_tkn=='['||sc_tkn==','||sc_tkn==';',"var"); // right after Id
  t1("pa_vartail");
  int t = se_type + se_stars;
  int id = sc_num;
  int k = st_find( id );
  if( se_level>0 && k>=st_local || se_level==0 && k>=0 )
    p2n( "duplicate var ",id_table[id] );
  if( se_level>0 ) ++se_lvars; else ++se_gvars;
  if( sc_tkn=='=' ) // simple var with '='
  {
    sc_next();
    if( se_level==0 ) // must be calculable for globals
    {
      if( sc_tkn==Str )
      {
        se_add_var( id, t, -1, Str, (int*)sc_num );
        sc_next();
      }
      else
      {
        if( !pa_integer() ) return t_(F);
        se_add_var( id, t, -1, Num, (int*)se_value );
      }
    }
    else
    {
      int* e = px_expr(0);
      if( !e ) return t_(F);
      if( ET_TRACE && e ) { p1("E:var "); et_print( e ); p0n(); }
      int idx = se_add_var( id, t, -1, 0, 0 ); // TODO
      cg_expr( e );
      cg_o( "  mov DWORD PTR [ebp" ); cg_o( i2s(st_value[idx]) ); cg_o( "],eax # " );
      cg_n( id_table[id] );
    }
    return t_(T);
  }
  if( sc_tkn!='[' ) // simple var w/o '='
  {
    se_add_var( id, t, -1, 0, 0 );
    return t_(T);
  }
  sc_next();
  // array
  if( sc_tkn==']' ) // take length from the initial value
  {
    sc_next();
    if( sc_tkn!='=' ) return t_(F);
    sc_next();
    if( !pa_arrayinit() ) return t_(F);
    se_add_var( id, t, se_items, Str, se_array_items ); // TODO init ints...
    free( (char*)se_array_items );
    return t_(T);
  }
  else // length is specified in [N]
  {
    if( !pa_integer() ) return t_(F); // value in se_value
    if( sc_tkn!=']' ) return t_(F);
    int dim = se_value;
    sc_next();
    if( sc_tkn!='=' ) // no initialization
    {
      se_add_var( id, t, dim, 0, 0 );
      return t_(T);
    }
    sc_next();
    if( !pa_arrayinit() ) return t_(F);
    se_add_var( id, t, dim, Str, se_array_items ); // only {Str,Str,...} implemented
    free( (char*)se_array_items );
    return t_(T);
  }
}

int pa_morevars()
{
  t1("pa_morevars");
  // disallow array of double-pointers, like T** V[N];
  if( !pa_vartail() ) return t_(F);
  while( sc_tkn==',' )
  {
    sc_next(); pa_stars();
    int t = se_type + se_stars;
    if( sc_tkn != Id ) return t_(F);
    sc_next();
    if( !pa_vartail() ) return t_(F);
  }
  if( sc_tkn!=';' ) return t_(F);
  sc_next();
  return t_(T);
}

int pa_vardef_or_expr()
{
  // TODO if it's expr, return expr AST
  // TODO if it's vardef, perform var definitions, return exprs (list!)
  // TODO e.g. int* a,b=c,*d=o+2; === int* a,b,*d; { b=c; d=o+2; }

  // TODO all e must be one type. either int or int*

  t1("pa_vardef_or_expr");
  if( sc_tkn!=Kw+Int && sc_tkn!=Kw+Char )
  {
    int* e = px_expr(0);
    if( !e || sc_tkn!=';' ) return t_(F); // expr ';'
    if( ET_TRACE && e ) { p1("E:exp "); et_print( e ); p0n(); }
    sc_next();
    cg_expr( (int*)e );
    return t_(T);
  }
  if( !pa_type() ) return t_(F);
  pa_stars();
  if( sc_tkn!=Id ) return t_(F);
  sc_next();
  return t_(pa_morevars());
}

int pa_argdef()
{
  t1("pa_argdef");
  if( !pa_type() ) return t_(F);
  pa_stars();
  int t = se_type + se_stars;
  if( sc_tkn!=Id ) return t_(F);
  ++se_arg_count;
  st_add( sc_num, t, K_arg, se_arg_count*INTSZ+INTSZ, 0 );
  sc_next();
  return t_(T);
}

int pa_args()
{
  t1("pa_args");
  se_arg_count = 0;
  if( !pa_argdef() ) return t_(T);
  while( sc_tkn==',' )
  {
    sc_next();
    if( !pa_argdef() ) return t_(F);
  }
  return t_(T);
}

int pa_stmt()
{
  t1("pa_stmt");
  assert( se_level>0, "stmt in fns only" );
  se_last_stmt_ret = F;
  if( sc_tkn==';' ) { sc_next(); return t_(T); } // empty stmt ';'
  if( sc_tkn=='{' )
  {
    sc_next();
    ++se_level;
    int block_local_start = st_count;         // in ST
    int block_local_offset = se_local_offset; // on stack
    while( sc_tkn!='}' ) if( !pa_stmt() ) return t_(F); // error
    sc_next();
    if( se_local_offset<se_max_l_offset) se_max_l_offset=se_local_offset; // negative!
    if( st_count>block_local_start ) // vars were defined in block
    {
      if( ST_DUMP ) { p1n("block"); st_dump( block_local_start, -1 ); }
      st_count = block_local_start;         // remove block vars
      se_local_offset = block_local_offset;
    }
    --se_level;
    return t_(T);
  }
  if( sc_tkn==Kw+Break )
  {
    int loop_label = cg_current_loop_label();
    if( loop_label < 0 ) err1( "break outside loop" );
    sc_next(); if( sc_tkn!=';' ) return t_(F); sc_next();
    cg_o( "  jmp E" ); cg_n( i2s(loop_label) );
    return t_(T);
  }
  if( sc_tkn==Kw+Return )
  {
    se_last_stmt_ret = T;
    sc_next();
    if( sc_tkn==';' )
    {
      cg_o( "  jmp R" ); cg_n( i2s(cg_fn_label) );
      sc_next(); return t_(T);
    }
    int* e = px_expr(0);
    if( ET_TRACE && e ) { p1("E:ret "); et_print( e ); p0n(); }
    if( !e || sc_tkn!=';' ) return t_(F);
    if( e ) cg_expr( e );
    cg_o( "  jmp R" ); cg_n( i2s(cg_fn_label) );
    sc_next(); return t_(T);
  }
  if( sc_tkn==Kw+While )
  {
    int* c; // condition
    int loop_label = cg_new_loop_label();
    sc_next(); if( sc_tkn!='(' ) return t_(F);
    cg_o( "L" ); cg_o( i2s( loop_label ) ); cg_n( ":" );
    sc_next(); if( !(c = px_expr(0)) || sc_tkn!=')' ) return t_(F);
    // TODO cg_cond( c, "E", loop_label );
    cg_expr( c );
    cg_n( "  test eax,eax" );
    cg_o( "  jz E" ); cg_n( i2s( loop_label ) );
    if( ET_TRACE && c ) { p1( "E:whl " ); et_print( (int*)c ); p0n(); }
    sc_next();
    int r = pa_stmt();
    cg_o( "  jmp L" ); cg_n( i2s( loop_label ) );
    cg_o( "E" ); cg_o( i2s( loop_label ) ); cg_n( ":" );
    cg_pop_loop_label();
    return t_(r);
  }
  if( sc_tkn==Kw+If )
  {
    int* c; // condition
    int if_label = cg_new_label();
    sc_next(); if( sc_tkn!='(' ) return t_(F);
    sc_next(); if( !(c = px_expr(0)) || sc_tkn!=')' ) return t_(F);
    // TODO cg_cond( c, "J", if_label );
    cg_expr( c );
    cg_n( "  test eax,eax" );
    cg_o( "  jz J" ); cg_n( i2s( if_label ) ); // jump if false
    if( ET_TRACE && c ) { p1( "E:iff " ); et_print( (int*)c ); p0n(); }
    sc_next(); if( !pa_stmt() ) return t_(F);
    if( sc_tkn==Kw+Else )
    {
      cg_o( "  jmp Z" ); cg_n( i2s( if_label ) );
      cg_o( "J" ); cg_o( i2s( if_label ) ); cg_n( ":" );
      sc_next();
      if( !pa_stmt() ) return t_(F);
      cg_o( "Z" ); cg_o( i2s( if_label ) ); cg_n( ":" );
    }
    else // no else part
    {
      cg_o( "J" ); cg_o( i2s( if_label ) ); cg_n( ":" );
    }
    return t_(T);
  }
  if( sc_tkn==Kw+For )
  {
    int loop_label = cg_new_loop_label();
    sc_next(); if( sc_tkn != '(' ) return t_(F);
    sc_next();
    ++se_level; // 'for' makes a new scope
    int block_local_start = st_count;         // in ST
    int block_local_offset = se_local_offset; // on stack
    if( sc_tkn!=';' )
    {
      if( !pa_vardef_or_expr() ) return t_(F); // also clean?
      // it calls cg_... as well
    }
    else
      sc_next(); // no init part
    int* e2 = 0; // the default means no condition expr provided
    if( sc_tkn!=';' )
    {
      if( !(e2 = px_expr(0)) ) return t_(F); // also ....
    }
    if( ET_TRACE && e2 ) { p1( "E:fr2 " ); et_print( (int*)e2 ); p0n(); }
    int* e3 = 0; // e3 is exprs (list); the defualt means no post exprs
    sc_next();
    if( sc_tkn!=')' )
    {
      if( !(e3 = px_exprs()) ) return t_(F); // opt. post-expressions
    }
    if( ET_TRACE && e3 ) { p1( "E:fr3 [" ); et_print_exprs( (int**)e3 ); }
    if( sc_tkn!=')' ) return t_(F); // also...
    sc_next();
    if( e3 ) { cg_o( "  jmp C" ); cg_n( i2s( loop_label ) ); }
    cg_o( "P" ); cg_o( i2s( loop_label ) ); cg_n( ":" );
    if( e3 ) cg_exprs( (int**)e3 ); // e3 - post expressions
    cg_o( "C" ); cg_o( i2s( loop_label ) ); cg_n( ":" );
    if( e2 )
    {
      cg_expr( e2 ); // e2 - condition
      cg_n( "  test eax,eax" );
      cg_o( "  jz E" ); cg_n( i2s( loop_label ) );
    }
    int rc = pa_stmt();
    if( se_local_offset<se_max_l_offset) se_max_l_offset=se_local_offset; // negative!
    if( st_count>block_local_start ) // vars were defined in block
    {
      if( ST_DUMP ) { p1n("for"); st_dump( block_local_start, -1 ); }
      st_count = block_local_start;         // remove block vars
      se_local_offset = block_local_offset;
    }
    --se_level;
    cg_o( "  jmp P" ); cg_n( i2s( loop_label ) );
    cg_o( "E" ); cg_o( i2s( loop_label ) ); cg_n( ":" );
    cg_pop_loop_label();
    return t_(rc);
  }
  int e = pa_vardef_or_expr(); // can be definition!!! ufffff <-- generates code
  return t_( e ); // vardef | expr ';'
}

int pa_func()
{
  assert( sc_tkn=='(', "pa_func not at '('" );
  assert( se_level==0, "pa_func lvl!=0" );
  t1("pa_func");
  int redefined=F, ret0=F;
  int id=sc_num;
  int t=se_type+se_stars;
  int k2 = st_find( id ); // find duplicate if any
  if( k2>=0 && st_kind[k2]!=K_fn )
    err2( "This was defined as not function before", id_table[id] );
  int k = st_add( id, t, K_fn, 0, 0 ); // add this for now; may be gone later
  sc_next();
  se_level = 1; // actually it's argument level
  st_local = st_count; // start local scope in ST -- maybe can be local var here
  if( !pa_args() || sc_tkn != ')' ) return t_(F);            // <--- args
  char* args = st_copy_args( st_local, se_arg_count );
  sc_next();
  if( sc_tkn == ';' ) // fn declaration
  {
    sc_next();
    if( k2>=0 ) // duplicate definitions -- may be the same or different
    {
      if( t!=st_type[k2] || strcmp( (char*)st_prop[k2], args ) )
        err2( "duplicate function declaration (not matching)", id_table[id] );
    }
    else // first declaration
    {
      st_prop[k] = (int)args;
      st_count = st_local; // clean local scope, actually only args
      se_level = 0;
    }
    return t_(T);
  }
  if( sc_tkn == '{' ) // fn definition
  {
    sc_next();
    se_lvars = 0;
    if( k2>=0 )
    {
      if( st_value[k2]!=0 )
        err2( "function re-definition", id_table[id] );
      if( t!=st_type[k2] || strcmp( (char*)st_prop[k2], args ) )
        err2( "not matching function definition", id_table[id] );
      st_value[k2] = 1; // will be address? now it's a flag
      st_prop[k2] = (int)args;
      redefined = T; // was declared, now it's time to define
    }
    else
    {
      st_value[k] = 1; st_prop[k] = (int)args;
    }
    cg_fn_label = cg_new_label();
    cg_fn_begin( id_table[id] );
    cg_suspend(); // resume until we know local scope size on stack
    //if( strequ( id_table[id], "main" ) ) cg_n( "  call ___main\n" );
    se_local_offset = 0;
    se_max_l_offset = 0;
    int block_local_start = st_count;         // in ST
    int block_local_offset = se_local_offset; // on stack
    while( sc_tkn!='}' ) if( !pa_stmt() ) return t_(F);      // <--- stmts
    sc_next();
    if( se_local_offset<se_max_l_offset) se_max_l_offset=se_local_offset; // negative!
    if( ST_DUMP ) { p2n("fn ",id_table[id]); st_dump( st_local, -1 );
                    p2n("stk ",i2s(se_max_l_offset)); p0n(); }
    if( redefined ) --st_local; // remove new fn itself -- we used old one
    st_count = st_local; // clean local scope
    se_level = 0;
    if( !se_last_stmt_ret && t!=T_v ) { warn( "last stmt was not return!" ); ret0 = T; }
    // that doesn't catch all cases but it's ok for now
    if( se_max_l_offset < 0 ) // it's negative!
    {
      char cmd[32];
      memcopy( cmd, "  sub esp,", 10 );
      char* number = i2s(-se_max_l_offset); int nn = strlen(number);
      memcopy( cmd+10, number, nn );
      memcopy( cmd+10+nn, "\n", 2 ); // with ending '\0'
      cg_resume( cmd );
    }
    else
      cg_resume( "  # no local variables\n" );
    cg_fn_end( ret0 );
    return t_(T);
  }
  return t_(F); // i.e. not ';' and not '{' ==> syntax error
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
  st_add( id, T_i, K_enum, se_enum, 0 );
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
    return t_(pa_func());
  }
  if( !pa_type() ) return t_(F);
  pa_stars();
  if( sc_tkn != Id ) return t_(F);
  sc_next();
  if( sc_tkn != '(' ) return t_(pa_morevars());
  return t_(pa_func());
}

int pa_program()
{
  t1("pa_program");
  int rc = T;
  sc_next(); // start parsing<-scanning<-reading
  while( sc_tkn!=Eof ) if( !pa_decl_or_def() ) { rc = F; break; }
  return t_(rc);
}

void before_exit()
{
  if( cg_file>0 ) close(cg_file); cg_file=0;
  if( rd_file>0 ) close(rd_file); rd_file=0;
}

// Main compiler function ------------------------------------------------------

int main( int ac, char** av )
{
  char* filename = 0;
  char* outputfn = 0;
  if( ac==1 || ac==2 && (strequ( av[1], "-h" ) || strequ( av[1], "--help" )) )
  {
    p1( "cc.exe [options] file.c [options]\n" );
    p1( "-T  show tokens\n" );
    p1( "-P  show parser trace\n" );
    p1( "-I  show id table trace\n" );
    p1( "-D  dump id table data and string literal table\n" );
    p1( "-S  dump symbol table\n" );
    p1( "-E  trace expressions\n" );
    p1( "-L  omit output of line numbers in assembler\n" );
    p1( "-o FILE  specify output file name\n" );
    return 0;
  }
  for( int i=1; i<ac; ++i )
    if( *av[i] != '-' )
      filename = av[i];
    else
    {
      if( av[i][1] == 'T' ) SC_DEBUG=1;
      if( av[i][1] == 'P' ) PA_TRACE=1;
      if( av[i][1] == 'I' ) IT_DEBUG=1;
      if( av[i][1] == 'D' ) IT_DUMP=1;
      if( av[i][1] == 'S' ) ST_DUMP=1;
      if( av[i][1] == 'E' ) ET_TRACE=1;
      if( av[i][1] == 'L' ) CG_LINES=0;
      if( av[i][1] == 'o' ) { outputfn = av[++i]; }
    }

  if( !filename ) { p1( "No input file\n" ); exit(1); }
  rd_file = open( filename, O_RDONLY, 0666 );
  if( rd_file<=0 ) { p3( "Can't open input file '", filename, "'\n" ); exit(1); }
  // initialization
  op_set_prec();
  st_create( ST_DIM );
  id_table_create( ID_TABLE_DIM );
  sl_table_create( SL_TABLE_DIM );
  if( !outputfn ) outputfn = "a.s";
  cg_file = open( outputfn, O_CREAT|O_TRUNC|O_WRONLY, 0666 );
  if( cg_file<0 ) { p3( "Can't create file '", outputfn, "'\n" ); exit(1); }
  cg_begin( filename );
  if( !pa_program( filename ) ) err1( "wrong syntax" );
  cg_sl_table();
  cg_end();
  before_exit(); // close files
  if( IT_DUMP ) { id_table_dump(); sl_table_dump(); }
  if( ST_DUMP )
  {
    int n;
    p1("** globals **\nenums:\n"); n = st_dump(0,K_enum); p1n(i2s(n));
    p1("vars:\n"); n = st_dump(0,K_var); p1n(i2s(n)); // also dumps K_array
    p1("funcs:\n"); n = st_dump(0,K_fn); p1n(i2s(n));
    p2n("data size: ", i2s(se_data_offset));
    p2n("bss size: ", i2s(se_bss_offset));
  }
  if( SC_DEBUG ) p2( i2s( sc_n_tokens ), " tokens\n" );
  return 0;
}

/*

// stdlib

#define DWORD                    int
#define HANDLE                   int
#define GENERIC_READ             0x80000000
#define GENERIC_WRITE            0x40000000
#define FILE_APPEND_DATA         0x00000004
#define FILE_ATTRIBUTE_NORMAL    0x00000080
#define CREATE_NEW               1
#define CREATE_ALWAYS            2
#define OPEN_EXISTING            3
#define OPEN_ALWAYS              4
#define TRUNCATE_EXISTING        5
#define STD_INPUT_HANDLE         (DWORD)(0xfffffff6)
#define STD_OUTPUT_HANDLE        (DWORD)(0xfffffff5)
#define STD_ERROR_HANDLE         (DWORD)(0xfffffff4)
#define INVALID_HANDLE_VALUE     (HANDLE)(-1)
#define FILE_BEGIN               0
#define FILE_CURRENT             1
#define FILE_END                 2
#define INVALID_SET_FILE_POINTER ((DWORD)(-1))

// kernel32 imports:
int __stdcall GetStdHandle( int nStdHandle );
int __stdcall CreateFileA( char* filename, int mode, int share, int security,
                                          int extmode, int attr, int template);
int __stdcall ReadFile( int h, void* b, int n, int* w, int o );
int __stdcall WriteFile( int h, void* b, int n, int* w, int o );
int __stdcall SetFilePointer( int hFile, int lDistanceToMove, int lDH, int mode );
int __stdcall CloseHandle( int h );
char* __stdcall GetCommandLineA();
int __stdcall GetProcessHeap();
char* __stdcall HeapAlloc( int heap, int o, int size );
int __stdcall HeapFree( int heap, int o, char* addr );
void __stdcall ExitProcess( int status );

int hHeap;
int STDFD[3]; // initialized with GetStdHandler

int open( char *path, int oflag )
{
  int f,x;
  if( oflag & O_WRONLY ) { f = GENERIC_WRITE; x = OPEN_ALWAYS; }
  else if( oflag & O_RDWR ) f = GENERIC_READ | GENERIC_WRITE;
  else / * O_RDONLY * / { f = GENERIC_READ; x = OPEN_EXISTING; / *assert f==O_RDONLY;* / }

  if( f & (O_CREAT|O_EXCL) ) x = OPEN_ALWAYS;
  if( oflag & O_APPEND )
  {
    //assert f & GENERIC_WRITE;
    f = FILE_APPEND_DATA; // instead of GENERIC_WRITE
  }
  //...
  int hFile = CreateFileA(path,f,0,0,x,FILE_ATTRIBUTE_NORMAL,0);
  if( hFile == INVALID_HANDLE_VALUE ) return 0;
  //assert hFile>=0;
  return hFile + 3;
}

int read( int fd, char* buf, int count )
{
  if( fd < 3 ) fd = STDFD[fd]; else fd -= 3;
  int read = 0;
  int b = ReadFile(fd, buf, count, &read, 0);
  return b ? read : -1; // 0 means EOF
}
int write( int fd, char* buf, int count )
{
  if( fd < 3 ) fd = STDFD[fd]; else fd -= 3;
  int written = 0;
  int b = WriteFile(fd, buf, count, &written, 0);
  return b? written : -1;
}
int close( int fd )
{
  if( fd < 3 ) return -1;
  fd -= 3;
  return CloseHandle( fd ) ? 0 : -1;
}
int lseek( int fd, int offset, int whence ) // if bad: -1, if std: 0
{
  if( fd < 3 ) return 0;
  fd -= 3;
  int md = whence==SEEK_END ? FILE_END : (whence==SEEK_CUR ? FILE_CURRENT : FILE_BEGIN );
  int r = SetFilePointer( fd, offset, 0, md );
  return r == INVALID_SET_FILE_POINTER ? -1 : r;
}

int init()
{
  hHeap = GetProcessHeap();
  STDFD[0] = GetStdHandle(-10);
  STDFD[1] = GetStdHandle(-11);
  STDFD[2] = GetStdHandle(-12);
  // also args...
}

char* malloc( int size ) { return HeapAlloc( hHeap, 0, size ); }
void free( char* ptr ) { HeapFree( hHeap, 0, ptr ); }
void exit( int status ) { ExitProcess( status ); }

*/
