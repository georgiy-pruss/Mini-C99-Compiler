// cc.c -- self-compiling C compiler - 2017 (C) G.Pruss
// gcc -fno-builtin-malloc -fno-builtin-strlen -O2 cc.c -o cc.exe
// -std=c99 is default in gcc

// TODO comments in code gen for statements
// TODO labels for return, loop beg/end, if/else/end, stack of labels (int)
// TODO labels for && and ||
// TODO jumps for statements
// TODO expressions; lvalue for = ++ --; initializers, strings and arrays as values

// Parameters ------------------------------------------------------------------

enum { INTSZ = 4,    // all this is for 32-bit architecture; int and int* is 4 bytes
  STR_MAX_SZ=260,    // max size of any string (line, name, etc.)
  ID_TABLE_DIM=1009, // for id freezing; should be prime number
  SL_TABLE_DIM=500,  // string literal table; let's assume 500
  ST_DIM=500,        // symbol table; max length is 500 (it's for all scopes at a moment)
  RD_BUF=8000,       // buffer for reading program text
  BF_WRT_SZ=4000,    // buffer for suspended output
  BSS_ORG=100000 };  // tag that data is in bss section (BSS_ORG+offset)

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
// enum { O_RDONLY, O_WRONLY, O_RDWR, O_APPEND=8, O_CREAT=256, O_TRUNC=512, O_EXCL=1024,
//   O_TEXT=16384, O_BINARY=32768 }; // Windows

int is_abc( int c ) { return c>='a' && c<='z' || c>='A' && c<='Z' || c=='_'; }

void memcopy( char* d, char* s, int n ) { for( ; n>0; ++d, ++s, --n ) *d = *s; }

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
    if( *s=='\n' ) { *d='\\'; ++d; *d='n'; }
    else if( *s==0 ) { *d='\\'; ++d; *d='0'; }
    else if( *s=='\b' ) { *d='\\'; ++d; *d='b'; }
    else if( *s=='\r' ) { *d='\\'; ++d; *d='r'; }
    else *d=*s;
  }
  *d = '"'; ++d; *d = '\0';
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
void p1n( char* s ) { write( 1, s, strlen(s) ); write( 1, "\n", 1 ); }
void p2n( char* s, char* s2 ) { p1( s ); p1( s2 ); write( 1, "\n", 1 ); }
void p3n( char* s, char* s2, char* s3 ) { p1( s ); p1( s2 ); p1( s3 ); write( 1, "\n", 1 ); }

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

int op_prec[128] = {0}; // operator precedence

void op_set_prec()
{
  char* o = "=oa|^&en<>lg+-*/%";
  char* p = "134567889999BBCCC";
  for( int i=0; o[i]; ++i ) op_prec[o[i]] = p[i]-'0';
}

int find_kw( char* s )
{
  for( int i=0; i<NKW; ++i ) if( strequ( s, KWDS[i] ) ) return i;
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
  int k = 0;
  for( int i=0; i<id_table_dim; ++i )
    if( id_table[i] ) { ++k; p3n( i2s(i), " ", id_table[i] ); }
  p1( "-------------------------------------\n" );
  p2( i2s(k), " ids, " );
  if( k!=id_count ) p3( " BUT MUST BE: ", i2s(id_count), ", " );
  p2( i2s(collisions), " collisions\n" );
}

// String Literal table --------------------------------------------------------

char** sl_table; // ptr to array of char (string) ptrs
int sl_count;

void sl_table_create( int n ) { sl_table = (char**)malloc( n*INTSZ ); sl_count = 0; }

int sl_add( char* s )
{
  if( sl_count==SL_TABLE_LEN ) err1( "Too many literal strings" );
  sl_table[ sl_count ] = strdup( s );
  ++sl_count;
  return sl_count - 1;
}

void sl_table_dump()
{
  for( int i=0; i<sl_count; ++i )
    p3n( i2s(i), " -> ", str_repr(sl_table[i]) );
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
    if( v==0 ) // octal
      for( rd_next(); rd_char>='0' && rd_char<='7'; rd_next() ) v = 8*v + rd_char - '0';
      // hex also can be here, under 'x' etc
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
  if( rd_char=='#' ) // comment #...
  {
    rd_next();
    while( rd_char!='\n' && rd_char>0 )
      rd_next();
    if( rd_char=='\n' ) { ++rd_line; if(RD_LINES) p3( "[//]\n[", i2s(rd_line), "]" ); }
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

int sc_n_tokens = 0; // total count of tokens, JFYI

void sc_next() // read and put token into sc_tkn
{
  sc_tkn = sc_read_next();
  ++sc_n_tokens;
  if( SC_DEBUG )
  {
    p3( " ", i2s(sc_tkn), " - " );
    if (sc_tkn >= Kw)        p2( "kw ", KWDS[ sc_tkn - Kw ] );
    else if( sc_tkn == Id )  p4( "id ", id_table[sc_num], " #",i2s(sc_num) );
    else if( sc_tkn == Str ) p2( "str ", str_repr(sl_table[sc_num]) );
    else if( sc_tkn == Num ) p2( "num ", i2s(sc_num) );
    else if( sc_tkn == Chr ) p2( "chr ", i2s(sc_num) );
    else if( sc_tkn == Eof ) p1( "eof" );
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
enum { K_enum, K_var, K_array, K_arg, K_fn };

char* st_type_str[] = {"Void","Char","Char*","Char**","Int","Int*","Int**"};
char* st_kind_str[] = {"Enum","Var","Array","Arg","Fn"};

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
    int k = st_kind[i]; int kk = k; if( kk==K_array ) kk==K_var;
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

// Code generation -------------------------------------------------------------

int cg_file = 0;
int* cg_buffer = 0;
char* cg_section = ""; // current section

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
  cg_o( "  .file \"" ); cg_o( fn ); cg_n( "\"" );
  cg_n( "  .intel_syntax noprefix\n" );
}

void cg_end()
{
  cg_n( "  .ident  \"GCC: (GNU) 5.4.0\"\n" );
  // dump declarations of all undefined functions
  for( int i=0; i<st_count; ++i )
    if( st_kind[i]==K_fn && st_value[i]==0 )
      { cg_o( "  .def _" ); cg_o( id_table[st_id[i]] ); cg_n( "; .scl 2; .type 32; .endef" ); }
}

void cg_fn_begin( char* name )
{
  if( strequ( name, "main" ) ) cg_n( "  .def ___main; .scl 2; .type 32; .endef" );
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
}

void cg_fn_end( int ret0 )
{
  if( ret0 ) cg_n( "  mov eax, 0" );
  cg_n( "  leave" );
  cg_n( "  .cfi_restore 5" );
  cg_n( "  .cfi_def_cfa 4, 4" );
  cg_n( "  ret" );
  cg_n( "  .cfi_endproc\n" );
}

// Parser ----------------------------------------------------------------------

int  tL = 0; // indent level
void tI() { p1("            "); for( int i=0; i<tL; ++i ) p1( "." ); }
void t1( char* s ) { if( PA_TRACE ) { tI(); p1n( s ); ++tL; } }
void t2( char* s, char* s2 ) { if( PA_TRACE ) { tI(); p2n( s,s2 ); ++tL; } }
void t3( char* s, char* s2, char* s3 ) { if( PA_TRACE ) { tI(); p3n( s,s2,s3 ); ++tL; } }
int  t_( int r ) { if( PA_TRACE ) { --tL; tI(); p2n( "<< ", i2s(r) ); } return r; }

enum { F, T }; // Boolean result of pa_* functions: False, True

// Due to recursive nature and difficult syntax, some fns have to be pre-declared
int pa_expr(int min_prec); int pa_term();

int pa_primary()
{
  t1("pa_primary");
  if( sc_tkn==Num || sc_tkn==Chr || sc_tkn==Str || sc_tkn==Id )
  {
    if( sc_tkn==Num || sc_tkn==Chr )
      //{ cg_o( "  # primary - num "); cg_n(i2s(sc_num)); }
      ;
    else if( sc_tkn==Str )
      //{ cg_o( "  # primary - str "); cg_n(str_repr(sc_text)); }
      ;
    else if( sc_tkn==Id )
      //{ cg_o( "  # primary - id "); cg_n(sc_text); }
      ;
    sc_next(); return t_(T);
  }
  if( sc_tkn!='(' ) return t_(F);
  sc_next(); if( !pa_expr(0) ) return t_(F);
  if( sc_tkn!=')' ) return t_(F);
  sc_next();
  se_type = T_i; // TODO elaborate! calculate type
  return t_(T);
}

int pa_integer() // has value at compile time
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
    else /* '(' */
      { sc_next(); if( sc_tkn!=')' ) { if( !pa_exprs() || sc_tkn!=')' ) return t_(F); } }
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

int pa_term()
{
  t1("pa_term");
  if( sc_tkn=='(' )
  {
    sc_next();
    if( pa_type() ) // cast (T)E
    {
      pa_stars(); if( sc_tkn!=')' ) return t_(F);
      sc_next(); return t_(pa_term());
    }
    if( !pa_expr(0) || sc_tkn!=')' ) return t_(F); // (E)
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
  while( pa_binop_na() && min_prec < op_prec[sc_tkn] )
  {
    int p = op_prec[sc_tkn];
    if( sc_tkn=='=' ) --p; // correct precedence for right-to-left operator
    sc_next();
    if( !pa_expr( p ) ) return t_(F);
  }
  return t_(T);
}

int pa_arrayinit()
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
  if( sc_tkn!='{' ) return t_(F);
  sc_next();
  if( sc_tkn==Str )
  {
    sc_next();                              // TODO sc_tkn can be '0'
    while( sc_tkn==',' ) { sc_next(); ++se_items; if( sc_tkn!=Str ) return t_(F); sc_next(); }
  }
  else
  {
    if( !pa_integer() ) return t_(F);
    while( sc_tkn==',' ) { sc_next(); ++se_items; if( !pa_integer() ) return t_(F); }
  }
  if( sc_tkn!='}' ) return t_(F);
  sc_next(); ++se_items;
  return t_(T);
}

int se_add_var( int id, int t, int dim, char* init )
{
  int k = K_array;
  if( dim<0 ) { dim=1; k = K_var; }
  int itemsz=INTSZ; if( t==T_c ) itemsz=1;
  int varsz = (dim*itemsz + INTSZ-1) / INTSZ * INTSZ; // align up to INTSZ bound
  if( se_level>0 )
  {
    se_local_offset = se_local_offset - varsz; // negative!
    return st_add( id, t, K_var, se_local_offset, dim ); // local var
  }
  int n;
  if( init )
  {
    n = st_add( id, t, K_var, se_data_offset, dim ); // global var in data section
    se_data_offset = se_data_offset + varsz;
  }
  else
  {
    n = st_add( id, t, K_var, se_bss_offset+BSS_ORG, dim ); // global bss
    se_bss_offset = se_bss_offset + varsz;
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
    p2n( "dupl var ",id_table[id] );
  if( se_level>0 ) { ++se_lvars; } else { ++se_gvars; }
  if( sc_tkn=='=' )
  {
    se_add_var( id, t, -1, "..." );
    sc_next();
    return t_(pa_expr(0)); // must be calculable for globals
  }
  if( sc_tkn!='[' )
  {
    se_add_var( id, t, -1, 0 );
    return t_(T);
  }
  sc_next();
  if( sc_tkn==']' ) // take length from the initial value
  {
    sc_next();
    if( sc_tkn!='=' ) return t_(F);
    sc_next();
    if( !pa_arrayinit() ) return t_(F);
    se_add_var( id, t, se_items, "..." );
    return t_(T);
  }
  else // length is specified in [N]
  {
    if( !pa_integer() ) return t_(F); // value in se_value
    if( sc_tkn!=']' ) return t_(F);
    se_add_var( id, t, se_value, 0 );
    sc_next();
    if( sc_tkn!='=' ) return t_(T); // no initialization
    sc_next();
    return t_(pa_arrayinit());
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
  t1("pa_vardef_or_expr");
  if( sc_tkn!=Kw+Int && sc_tkn!=Kw+Char )
  {
    if( !pa_expr(0) || sc_tkn!=';' ) return t_(F); // expr ';'
    sc_next();
    return t_(T);
  }
  if( !pa_type() ) return t_(F);
  pa_stars();
  int t = se_type + se_stars;
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
  st_add( sc_num, t, K_arg, se_arg_count, 0 );
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
    sc_next(); if( sc_tkn!=';' ) return t_(F); sc_next(); return t_(T);
  }
  if( sc_tkn==Kw+Return )
  {
    se_last_stmt_ret = T;
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
    ++se_level; // 'for' makes a new scope
    int block_local_start = st_count;         // in ST
    int block_local_offset = se_local_offset; // on stack
    if( sc_tkn!=';' )
    {
      if( !pa_vardef_or_expr() ) return t_(F); // also clean?
    }
    else sc_next();
    if( sc_tkn!=';' ) if( !pa_expr(0) ) return t_(F); // also ....
    sc_next();
    if( sc_tkn!=')' ) if( !pa_exprs() ) return t_(F); // opt. post-expressions
    if( sc_tkn!=')' ) return t_(F); // also...
    sc_next();
    int rc = pa_stmt();
    if( se_local_offset<se_max_l_offset) se_max_l_offset=se_local_offset; // negative!
    if( st_count>block_local_start ) // vars were defined in block
    {
      if( ST_DUMP ) { p1n("for"); st_dump( block_local_start, -1 ); }
      st_count = block_local_start;         // remove block vars
      se_local_offset = block_local_offset;
    }
    --se_level;
    return t_(rc);
  }
  //was: if( !pa_vardef_or_expr(0) || sc_tkn != ';' ) return t_(F); // expr ';'
  //was: sc_next(); ret T
  return t_( pa_vardef_or_expr() ); // vardef | expr ';'
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
    cg_fn_begin( id_table[id] );
    cg_suspend(); // resume until we know local scope size on stack
    if( strequ( id_table[id], "main" ) ) cg_n( "  call ___main\n" );
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
      memcopy( cmd, "  sub esp, ", 11 );
      char* number = i2s(-se_max_l_offset); int nn = strlen(number);
      memcopy( cmd+11, number, nn );
      memcopy( cmd+11+nn, "\n", 2 ); // with ending '\0'
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

int pa_program( char* fn )
{
  t1("pa_program");
  rd_file = open( fn, O_RDONLY, 0 );
  if( rd_file<=0 ) return t_(F);
  int rc = T;
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
  if( ac==1 || ac==2 && (strequ( av[1], "-h" ) || strequ( av[1], "--help" )) )
  {
    p1( "c2s.exe [options] file.c\n" );
    p1( "-T  show tokens\n" );
    p1( "-L  show line numbers\n" );
    p1( "-P  show parser trace\n" );
    p1( "-I  show id table trace\n" );
    p1( "-D  dump id table data and string literal table\n" );
    p1( "-S  dump symbol table\n" );
    return 0;
  }
  for( int i=1; i<ac; ++i )
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

  if( !filename ) { p1( "No input file\n" ); exit(1); }
  // initialization
  op_set_prec();
  st_create( ST_DIM );
  id_table_create( ID_TABLE_DIM );
  sl_table_create( SL_TABLE_DIM );
  char OUTFN[] = "a.s";
  cg_file = open( OUTFN, O_CREAT|O_TRUNC|O_WRONLY, 0666 );
  if( cg_file<0 ) { p3( "Can't create file '", OUTFN, "'\n" ); exit(1); }
  cg_begin( filename );
  if( !pa_program( filename ) ) err1( "wrong syntax" );
  cg_end();
  if( cg_file>0 ) close( cg_file );
  if( IT_DUMP ) { id_table_dump(); sl_table_dump(); }
  if( ST_DUMP )
  {
    int n;
    p1("globals\nenums:\n"); n = st_dump(0,K_enum); p1n(i2s(n));
    p1("vars:\n"); n = st_dump(0,K_var); p1n(i2s(n)); // also dumps K_array
    p1("funcs:\n"); n = st_dump(0,K_fn); p1n(i2s(n));
    p2n( "data size: ", i2s(se_data_offset) );
    p2n( "bss size: ", i2s(se_bss_offset) );
  }
  if( SC_DEBUG ) p2( i2s( sc_n_tokens ), " tokens\n" );
  return 0;
}

