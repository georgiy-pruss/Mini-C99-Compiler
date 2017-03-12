void proc_v_v() {}

int proc_i_c( char c ) { return c+1; }

char proc_c_i( int i ) { return (char)(i-1); }

void proc_ip_v( int i, int* p ) { *p = i; }

void proc_cs_v( char c, char* s ) { *s = c; }

void proc_ipx_v( int i, int* p, int** x ) { *x = p + i; }

