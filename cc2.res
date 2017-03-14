pa_file cc.c
[1][//]
[2][//]
[3][//]
[4]
[5][//]
[6]
[7] 202 - kw int
pa_decl_or_def
pa_type
 5 - id open
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id path
 44 - op/sep ,
 202 - kw int
pa_argdef
pa_type
 5 - id oflag
pa_stars
 44 - op/sep ,
 202 - kw int
pa_argdef
pa_type
 5 - id cmode
pa_stars
 41 - op/sep )
 59 - op/sep ;
pa_fntail
[//]
[8] 202 - kw int
pa_decl_or_def
pa_type
 5 - id close
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id fd
pa_stars
 41 - op/sep )
 59 - op/sep ;
pa_fntail
[//]
[9] 202 - kw int
pa_decl_or_def
pa_type
 5 - id read
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id fd
pa_stars
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id buf
 44 - op/sep ,
 202 - kw int
pa_argdef
pa_type
 5 - id count
pa_stars
 41 - op/sep )
 59 - op/sep ;
pa_fntail
[//]
[10] 202 - kw int
pa_decl_or_def
pa_type
 5 - id write
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id fd
pa_stars
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id buf
 44 - op/sep ,
 202 - kw int
pa_argdef
pa_type
 5 - id count
pa_stars
 41 - op/sep )
 59 - op/sep ;
pa_fntail
[//]
[11] 201 - kw char
pa_decl_or_def
pa_type
 42 - op/sep *
pa_stars
 5 - id malloc
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id size
pa_stars
 41 - op/sep )
 59 - op/sep ;
pa_fntail

[12] 200 - kw void
pa_decl_or_def
pa_type
 5 - id free
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id ptr
 41 - op/sep )
 59 - op/sep ;
pa_fntail

[13] 200 - kw void
pa_decl_or_def
pa_type
 5 - id exit
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id status
pa_stars
 41 - op/sep )
 59 - op/sep ;
pa_fntail

[14]
[15] 203 - kw enum
pa_decl_or_def
 123 - op/sep {
pa_enumdef
 5 - id O_RDONLY
pa_enumerator
 44 - op/sep ,
 5 - id O_WRONLY
pa_enumerator
 44 - op/sep ,
 5 - id O_RDWR
pa_enumerator
 44 - op/sep ,
 5 - id O_APPEND
pa_enumerator
 61 - op/sep =
 2 - num 8
pa_intexpr
pa_number
 44 - op/sep ,
 5 - id O_CREAT
pa_enumerator
 61 - op/sep =
 2 - num 512
pa_intexpr
pa_number
 44 - op/sep ,
 5 - id O_TRUNC
pa_enumerator
 61 - op/sep =
 2 - num 1024
pa_intexpr
pa_number
 44 - op/sep ,
 5 - id O_EXCL
pa_enumerator
 61 - op/sep =
 2 - num 2048
pa_intexpr
pa_number
 125 - op/sep }
 59 - op/sep ;

[16][//]
[17]
[18] 202 - kw int
pa_decl_or_def
pa_type
 5 - id is_abc
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id c
pa_stars
 41 - op/sep )
 123 - op/sep {
pa_fntail
 208 - kw return
pa_block
pa_stmt
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 3 - chr 97
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id c
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 3 - chr 122
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id c
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 3 - chr 65
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id c
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 3 - chr 90
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id c
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 95
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[19]
[20] 202 - kw int
pa_decl_or_def
pa_type
 5 - id strlen
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 41 - op/sep )
 123 - op/sep {
pa_fntail
 202 - kw int
pa_block
pa_stmt
pa_type
 5 - id n
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 206 - kw while
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id s
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 105 - op/sep i
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id s
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id n
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }
 208 - kw return
pa_stmt
 5 - id n
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[21] 201 - kw char
pa_decl_or_def
pa_type
 42 - op/sep *
pa_stars
 5 - id strcpy
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id d
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 41 - op/sep )
 123 - op/sep {
pa_fntail
 201 - kw char
pa_block
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id r
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id d
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 206 - kw while
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id s
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 42 - op/sep *
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id d
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 42 - op/sep *
pa_term
pa_unexpr
 5 - id s
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id d
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id s
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }
 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id d
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id r
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[22] 201 - kw char
pa_decl_or_def
pa_type
 42 - op/sep *
pa_stars
 5 - id strcat
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id t
 41 - op/sep )
 123 - op/sep {
pa_fntail
 202 - kw int
pa_block
pa_stmt
pa_type
 5 - id n
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id strlen
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id strcpy
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id n
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id t
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[23]
[24] 201 - kw char
pa_decl_or_def
pa_type
 42 - op/sep *
pa_stars
 5 - id strrev
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 41 - op/sep )

[25] 123 - op/sep {
pa_fntail

[26] 202 - kw int
pa_block
pa_stmt
pa_type
 5 - id n
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id strlen
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id n
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[27] 201 - kw char
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id b
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 201 - kw char
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id e
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id n
pa_term
pa_unexpr
pa_postfix
pa_primary
 45 - op/sep -
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[28] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id b
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 60 - op/sep <
pa_call_or_index
pa_binop
 5 - id e
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 201 - kw char
pa_block
pa_stmt
pa_type
 5 - id t
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id e
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id e
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 42 - op/sep *
pa_term
pa_unexpr
 5 - id b
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id b
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id t
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id b
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 100 - op/sep d
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id e
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[29] 208 - kw return
pa_stmt
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[30] 125 - op/sep }

[31]
[32] 202 - kw int
pa_decl_or_def
pa_type
 5 - id strcmp
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id t
 41 - op/sep )

[33] 123 - op/sep {
pa_fntail

[34] 206 - kw while
pa_block
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id s
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[35] 123 - op/sep {
pa_stmt

[36] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id t
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 42 - op/sep *
pa_term
pa_unexpr
 5 - id s
pa_term
pa_unexpr
pa_postfix
pa_primary
 62 - op/sep >
pa_call_or_index
pa_binop
 42 - op/sep *
pa_term
pa_unexpr
 5 - id t
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[37] 204 - kw if
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id s
pa_term
pa_unexpr
pa_postfix
pa_primary
 60 - op/sep <
pa_call_or_index
pa_binop
 42 - op/sep *
pa_term
pa_unexpr
 5 - id t
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 45 - op/sep -
pa_expr
pa_term
pa_unexpr
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[38] 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id s
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id t
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[39] 125 - op/sep }

[40] 204 - kw if
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id t
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 45 - op/sep -
pa_expr
pa_term
pa_unexpr
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[41] 208 - kw return
pa_stmt
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[42] 125 - op/sep }

[43]
[44] 202 - kw int
pa_decl_or_def
pa_type
 5 - id strequ
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id t
 41 - op/sep )
 123 - op/sep {
pa_fntail
 208 - kw return
pa_block
pa_stmt
 5 - id strcmp
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id t
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 101 - op/sep e
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[45]
[46] 201 - kw char
pa_decl_or_def
pa_type
 42 - op/sep *
pa_stars
 5 - id strrchr
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 44 - op/sep ,
 202 - kw int
pa_argdef
pa_type
 5 - id c
pa_stars
 41 - op/sep )

[47] 123 - op/sep {
pa_fntail

[48] 202 - kw int
pa_block
pa_stmt
pa_type
 5 - id n
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id strlen
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[49] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id n
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 62 - op/sep >
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 5 - id n
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 45 - op/sep -
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 101 - op/sep e
pa_binop
 5 - id c
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 40 - op/sep (
pa_term
 5 - id n
pa_type
pa_exprtail
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 45 - op/sep -
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_call_or_index
pa_binop
 100 - op/sep d
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id n
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[50] 208 - kw return
pa_stmt
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[51] 125 - op/sep }

[52]
[53] 201 - kw char
pa_decl_or_def
pa_type
 5 - id i2s_buf
pa_stars
 91 - op/sep [
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 2 - num 16
pa_number
 93 - op/sep ]
 59 - op/sep ;
[//]
[54]
[55] 201 - kw char
pa_decl_or_def
pa_type
 42 - op/sep *
pa_stars
 5 - id i2s
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id value
pa_stars
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id str
 41 - op/sep )

[56] 123 - op/sep {
pa_fntail

[57] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id str
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id str
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id i2s_buf
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
[//]
[58] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id value
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 42 - op/sep *
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id str
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id str
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 61 - op/sep =
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id str
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[59] 201 - kw char
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id dst
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id str
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[60] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id value
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 60 - op/sep <
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[61] 123 - op/sep {
pa_stmt

[62] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id value
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 40 - op/sep (
pa_term
 45 - op/sep -
pa_type
pa_exprtail
pa_expr
pa_term
pa_unexpr
 2 - num 2147483647
pa_term
pa_unexpr
pa_postfix
pa_primary
 45 - op/sep -
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id strcpy
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id str
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str -2147483648
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id str
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[63] 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id dst
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 45
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id dst
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[64] 5 - id value
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 45 - op/sep -
pa_term
pa_unexpr
 5 - id value
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[65] 125 - op/sep }

[66] 201 - kw char
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id beg
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id dst
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[67] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id value
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 42 - op/sep *
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id dst
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 40 - op/sep (
pa_term
 201 - kw char
pa_type
 41 - op/sep )
pa_stars
 40 - op/sep (
pa_term
 5 - id value
pa_type
pa_exprtail
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 37 - op/sep %
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id dst
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id value
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id value
pa_term
pa_unexpr
pa_postfix
pa_primary
 47 - op/sep /
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[68] 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id dst
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[69] 5 - id strrev
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id beg
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[70] 208 - kw return
pa_stmt
 5 - id str
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[71] 125 - op/sep }

[72]
[73] 202 - kw int
pa_decl_or_def
pa_type
 5 - id s2i
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id str
 41 - op/sep )

[74] 123 - op/sep {
pa_fntail

[75] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id str
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 45
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 45 - op/sep -
pa_expr
pa_term
pa_unexpr
 5 - id s2i
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id str
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[76] 202 - kw int
pa_stmt
pa_type
 5 - id v
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[77] 206 - kw while
pa_stmt
 40 - op/sep (
 42 - op/sep *
pa_expr
pa_term
pa_unexpr
 5 - id str
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 42 - op/sep *
pa_term
pa_unexpr
 5 - id str
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 3 - chr 57
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id v
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 42 - op/sep *
pa_call_or_index
pa_binop
 5 - id v
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 42 - op/sep *
pa_term
pa_unexpr
 5 - id str
pa_term
pa_unexpr
pa_postfix
pa_primary
 45 - op/sep -
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id str
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[78] 208 - kw return
pa_stmt
 5 - id v
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[79] 125 - op/sep }

[80]
[81] 200 - kw void
pa_decl_or_def
pa_type
 5 - id assert
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id cond
pa_stars
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id msg
 41 - op/sep )

[82] 123 - op/sep {
pa_fntail

[83] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id cond
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 59 - op/sep ;

[84] 5 - id write
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 2 - num 2
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str ASSERT: 
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 8
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id write
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 2 - num 2
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id msg
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id strlen
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id msg
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 59 - op/sep ;
pa_binop
 5 - id write
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 2 - num 2
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str 

pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[85] 5 - id exit
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 2 - num 1
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[86] 125 - op/sep }

[87]
[88] 200 - kw void
pa_decl_or_def
pa_type
 5 - id p1
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 41 - op/sep )
 123 - op/sep {
pa_fntail
 5 - id write
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 2 - num 1
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id strlen
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[89] 200 - kw void
pa_decl_or_def
pa_type
 5 - id p2
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s2
 41 - op/sep )
 123 - op/sep {
pa_fntail
 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s2
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[90] 200 - kw void
pa_decl_or_def
pa_type
 5 - id p3
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s2
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s3
 41 - op/sep )
 123 - op/sep {
pa_fntail
 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s2
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s3
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[91] 200 - kw void
pa_decl_or_def
pa_type
 5 - id p4
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s2
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s3
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s4
 41 - op/sep )
 123 - op/sep {
pa_fntail
 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s2
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s3
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s4
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[92]
[93][//]
[94]
[95] 203 - kw enum
pa_decl_or_def
 123 - op/sep {
pa_enumdef
 5 - id Err
pa_enumerator
 44 - op/sep ,
 5 - id Eof
pa_enumerator
 44 - op/sep ,
 5 - id Num
pa_enumerator
 44 - op/sep ,
 5 - id Chr
pa_enumerator
 44 - op/sep ,
 5 - id Str
pa_enumerator
 44 - op/sep ,
 5 - id Id
pa_enumerator
 44 - op/sep ,
[//]
[96][//]
[97][//]
[98] 5 - id Kw
pa_enumerator
 61 - op/sep =
 2 - num 200
pa_intexpr
pa_number
 125 - op/sep }
 59 - op/sep ;
[//]
[99] 203 - kw enum
pa_decl_or_def
 123 - op/sep {
pa_enumdef
 5 - id Void
pa_enumerator
 44 - op/sep ,
 5 - id Char
pa_enumerator
 44 - op/sep ,
 5 - id Int
pa_enumerator
 44 - op/sep ,
 5 - id Enum
pa_enumerator
 44 - op/sep ,
 5 - id If
pa_enumerator
 44 - op/sep ,
 5 - id Else
pa_enumerator
 44 - op/sep ,
 5 - id While
pa_enumerator
 44 - op/sep ,
 5 - id Break
pa_enumerator
 44 - op/sep ,
 5 - id Return
pa_enumerator
 44 - op/sep ,
 5 - id Sizeof
pa_enumerator
 125 - op/sep }
 59 - op/sep ;
[//]
[100]
[101] 202 - kw int
pa_decl_or_def
pa_type
 5 - id find_kw
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id s
 41 - op/sep )

[102] 123 - op/sep {
pa_fntail

[103] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str int
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Int
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[104] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str void
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Void
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str enum
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Enum
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[105] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str if
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id If
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str else
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Else
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[106] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str while
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id While
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str break
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Break
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[107] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str return
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Return
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id strequ
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id s
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str sizeof
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id Sizeof
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[108] 208 - kw return
pa_stmt
 45 - op/sep -
pa_expr
pa_term
pa_unexpr
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[109] 125 - op/sep }

[110]
[111][//]
[112]
[113] 201 - kw char
pa_decl_or_def
pa_type
 5 - id rd_buf
pa_stars
 91 - op/sep [
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 2 - num 8000
pa_number
 93 - op/sep ]
 59 - op/sep ;

[114] 202 - kw int
pa_decl_or_def
pa_type
 5 - id rd_buf_len
pa_stars
 61 - op/sep =
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 45 - op/sep -
pa_constexpr
pa_intexpr
 2 - num 1
pa_number
 59 - op/sep ;
[//]
[115] 202 - kw int
pa_decl_or_def
pa_type
 5 - id rd_char_pos
pa_stars
 61 - op/sep =
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 2 - num 0
pa_constexpr
pa_intexpr
pa_number
 59 - op/sep ;
[//]
[116] 202 - kw int
pa_decl_or_def
pa_type
 5 - id rd_char
pa_stars
 61 - op/sep =
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 45 - op/sep -
pa_constexpr
pa_intexpr
 2 - num 1
pa_number
 59 - op/sep ;
[//]
[117] 202 - kw int
pa_decl_or_def
pa_type
 5 - id rd_file
pa_stars
 61 - op/sep =
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 45 - op/sep -
pa_constexpr
pa_intexpr
 2 - num 1
pa_number
 59 - op/sep ;
[//]
[118] 202 - kw int
pa_decl_or_def
pa_type
 5 - id rd_line
pa_stars
 61 - op/sep =
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 45 - op/sep -
pa_constexpr
pa_intexpr
 2 - num 1
pa_number
 59 - op/sep ;
[//]
[119]
[120] 200 - kw void
pa_decl_or_def
pa_type
 5 - id rd_next
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
[//]
[121] 123 - op/sep {
pa_fntail

[122] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id rd_char_pos
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 5 - id rd_buf_len
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[123] 123 - op/sep {
pa_stmt

[124] 5 - id rd_buf_len
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id read
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_file
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id rd_buf
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 209 - kw sizeof
pa_expr
pa_term
pa_unexpr
 40 - op/sep (
 5 - id rd_buf
pa_type
pa_exprtail
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 45 - op/sep -
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[125] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_buf_len
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id rd_char
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 45 - op/sep -
pa_term
pa_unexpr
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 59 - op/sep ;
 125 - op/sep }
[//]
[126] 5 - id rd_buf
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 5 - id rd_buf_len
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 61 - op/sep =
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[127] 5 - id rd_char_pos
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[128] 125 - op/sep }

[129] 5 - id rd_char
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id rd_buf
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 5 - id rd_char_pos
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id rd_char_pos
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[130] 125 - op/sep }

[131]
[132][//]
[133]
[134] 202 - kw int
pa_decl_or_def
pa_type
 5 - id sc_tkn
pa_stars
 59 - op/sep ;
pa_fn_or_vars
pa_vars:0
pa_vartail:0
[//]
[135] 201 - kw char
pa_decl_or_def
pa_type
 5 - id sc_text
pa_stars
 91 - op/sep [
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 2 - num 260
pa_number
 93 - op/sep ]
 59 - op/sep ;
[//]
[136] 202 - kw int
pa_decl_or_def
pa_type
 5 - id sc_num
pa_stars
 59 - op/sep ;
pa_fn_or_vars
pa_vars:0
pa_vartail:0
[//]
[137]
[138] 202 - kw int
pa_decl_or_def
pa_type
 5 - id sc_read_next
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
[//]
[139] 123 - op/sep {
pa_fntail

[140] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 60 - op/sep <
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 5 - id rd_line
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 1
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id p3
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str [
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_line
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str ]
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[141] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 32
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 13
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[142] 123 - op/sep {
pa_stmt

[143] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 105 - op/sep i
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id rd_line
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id p3
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str 
[
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_line
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str ]
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }
[//]
[144] 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[145] 125 - op/sep }

[146] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 60 - op/sep <
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id Eof
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[147] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 3 - chr 57
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[148] 123 - op/sep {
pa_stmt

[149] 201 - kw char
pa_block
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id p
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id sc_text
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[150] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 3 - chr 57
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 42 - op/sep *
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }

[151] 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[152] 5 - id sc_num
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id s2i
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id sc_text
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[153] 208 - kw return
pa_stmt
 5 - id Num
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[154] 125 - op/sep }

[155] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id is_abc
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_char
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
[//]
[156] 123 - op/sep {
pa_stmt

[157] 201 - kw char
pa_block
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id p
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id sc_text
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[158] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id is_abc
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_char
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 111 - op/sep o
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 3 - chr 57
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 42 - op/sep *
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }

[159] 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[160] 202 - kw int
pa_stmt
pa_type
 5 - id k
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id find_kw
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id sc_text
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[161] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id k
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id Kw
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id k
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[162] 208 - kw return
pa_stmt
 5 - id Id
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[163] 125 - op/sep }

[164] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 34
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[165] 123 - op/sep {
pa_stmt

[166] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[167] 201 - kw char
pa_stmt
pa_type
 42 - op/sep *
pa_stars
 5 - id p
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id sc_text
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[168] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 34
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[169] 123 - op/sep {
pa_stmt

[170] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 92
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[171] 123 - op/sep {
pa_stmt

[172] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[173] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 110
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id rd_char
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[174] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 114
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id rd_char
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 13
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[175] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 98
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id rd_char
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 8
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[176] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 48
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id rd_char
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[177] 125 - op/sep }

[178] 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 105 - op/sep i
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[179] 125 - op/sep }

[180] 42 - op/sep *
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id p
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[181] 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[182] 208 - kw return
pa_stmt
 5 - id Str
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[183] 125 - op/sep }

[184] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 39
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[185] 123 - op/sep {
pa_stmt

[186] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[187] 5 - id sc_num
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
[//]
[188] 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[189] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 2 - num 39
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id Err
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
[//]
[190] 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[191] 208 - kw return
pa_stmt
 5 - id Chr
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[192] 125 - op/sep }

[193] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 123
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 125
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop

[194] 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 91
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 93
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 44
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop

[195] 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 42
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 37
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[196] 123 - op/sep {
pa_stmt

[197] 202 - kw int
pa_block
pa_stmt
pa_type
 5 - id c
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[198] 125 - op/sep }

[199] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 61
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 60
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 62
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 33
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[200] 123 - op/sep {
pa_stmt

[201] 202 - kw int
pa_block
pa_stmt
pa_type
 5 - id c
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[202] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 61
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[203] 123 - op/sep {
pa_stmt

[204] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[205] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 61
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 101
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 60
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 108
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 62
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 103
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 205 - kw else
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 110
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[206] 125 - op/sep }

[207] 208 - kw return
pa_stmt
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[208] 125 - op/sep }

[209] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 43
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 45
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 38
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 124
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[210] 123 - op/sep {
pa_stmt

[211] 202 - kw int
pa_block
pa_stmt
pa_type
 5 - id c
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[212] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id c
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[213] 123 - op/sep {
pa_stmt

[214] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[215] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 43
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 105
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 45
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 100
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 38
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 97
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 205 - kw else
 5 - id c
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 3 - chr 111
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[216] 125 - op/sep }

[217] 208 - kw return
pa_stmt
 5 - id c
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[218] 125 - op/sep }

[219] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 47
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[220] 123 - op/sep {
pa_stmt

[221] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[222] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 47
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[223] 123 - op/sep {
pa_stmt

[224] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[225] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 62 - op/sep >
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[226] 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[227] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 105 - op/sep i
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id rd_line
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id p3
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str [//]
[
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_line
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str ]
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }
[//]
[228] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 62 - op/sep >
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[229] 208 - kw return
pa_stmt
 5 - id sc_read_next
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[230] 125 - op/sep }

[231] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 42
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[232] 123 - op/sep {
pa_stmt

[233] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[234] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 105 - op/sep i
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id rd_line
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id p3
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str [/*]
[
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_line
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str ]
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[235] 206 - kw while
pa_stmt
 40 - op/sep (
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[236] 123 - op/sep {
pa_stmt

[237] 206 - kw while
pa_block
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 42
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 62 - op/sep >
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[238] 123 - op/sep {
pa_stmt

[239] 5 - id rd_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[240] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 10
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 105 - op/sep i
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
 5 - id rd_line
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id p3
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str [**]
[
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_line
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str ]
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[241] 125 - op/sep }

[242] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 62 - op/sep >
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[243] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 47
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[244] 207 - kw break
pa_stmt
 59 - op/sep ;

[245] 125 - op/sep }

[246] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_char
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 62 - op/sep >
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[247] 208 - kw return
pa_stmt
 5 - id sc_read_next
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[248] 125 - op/sep }

[249] 205 - kw else

[250] 208 - kw return
pa_stmt
 3 - chr 47
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[251] 125 - op/sep }

[252] 205 - kw else

[253] 123 - op/sep {
pa_stmt

[254] 5 - id sc_text
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 61 - op/sep =
pa_binop
 5 - id rd_char
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id sc_text
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 61 - op/sep =
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[255] 5 - id rd_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[256] 208 - kw return
pa_stmt
 5 - id Err
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[257] 125 - op/sep }

[258] 125 - op/sep }

[259]
[260] 201 - kw char
pa_decl_or_def
pa_type
 42 - op/sep *
pa_stars
 5 - id KWDS
 91 - op/sep [
pa_fn_or_vars
pa_vars:0
pa_vartail:0
 2 - num 10
pa_number
 93 - op/sep ]
 61 - op/sep =
 123 - op/sep {
pa_constexpr
 4 - str void
pa_constexpr
 44 - op/sep ,
 4 - str char
pa_constexpr
 44 - op/sep ,
 4 - str int
pa_constexpr
 44 - op/sep ,
 4 - str enum
pa_constexpr
 44 - op/sep ,
 4 - str if
pa_constexpr
 44 - op/sep ,
 4 - str else
pa_constexpr
 44 - op/sep ,
 4 - str while
pa_constexpr
 44 - op/sep ,
 4 - str break
pa_constexpr
 44 - op/sep ,
 4 - str return
pa_constexpr
 44 - op/sep ,
 4 - str sizeof
pa_constexpr
 125 - op/sep }
 59 - op/sep ;

[261]
[262] 200 - kw void
pa_decl_or_def
pa_type
 5 - id sc_next
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
[//]
[263] 123 - op/sep {
pa_fntail

[264] 5 - id sc_tkn
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id sc_read_next
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[265] 204 - kw if
pa_stmt
 40 - op/sep (
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[266] 123 - op/sep {
pa_stmt

[267] 5 - id p3
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str  
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id sc_tkn
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str  - 
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[268] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 103 - op/sep g
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str kw 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id KWDS
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 45 - op/sep -
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 59 - op/sep ;
pa_binop

[269] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str id 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id sc_text
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[270] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Str
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str str 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id sc_text
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[271] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Num
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str num 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id sc_num
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 59 - op/sep ;
pa_binop

[272] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Chr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str chr 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id sc_num
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 59 - op/sep ;
pa_binop

[273] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Eof
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str eof
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[274] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Err
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str err
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id sc_text
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[275] 205 - kw else
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 60 - op/sep <
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 201 - kw char
pa_block
pa_stmt
pa_type
 5 - id o
pa_stars
 91 - op/sep [
pa_vars:1
pa_vartail:1
 2 - num 2
pa_number
 93 - op/sep ]
 61 - op/sep =
 4 - str .
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id o
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 61 - op/sep =
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str op/sep 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id o
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop
 125 - op/sep }

[276] 205 - kw else
 5 - id p2
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str ?
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id sc_text
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[277] 5 - id p1
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str 

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[278] 125 - op/sep }

[279] 125 - op/sep }

[280]
[281][//]
[282]
[283] 203 - kw enum
pa_decl_or_def
 123 - op/sep {
pa_enumdef
 5 - id F
pa_enumerator
 44 - op/sep ,
 5 - id T
pa_enumerator
 125 - op/sep }
 59 - op/sep ;
[//]
[284]
[285][//]
[286] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_expr
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail
 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_term
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail
 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_type
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail
 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_stars
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail
 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_exprtail
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail

[287] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_block
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail
 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_enumdef
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail
 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_vars
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id k
pa_stars
 41 - op/sep )
 59 - op/sep ;
pa_fntail
 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_intexpr
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
 59 - op/sep ;
pa_fntail

[288]
[289] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_primary
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[290] 123 - op/sep {
pa_fntail

[291] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_primary

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[292] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Num
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Chr
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Str
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[293] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[294] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[295] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[296] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[297] 125 - op/sep }

[298]
[299] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_exprs
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[300] 123 - op/sep {
pa_fntail

[301] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_exprs

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[302] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[303] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 44
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[304] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[305] 125 - op/sep }

[306]
[307] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_call_or_index
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[308] 123 - op/sep {
pa_fntail

[309] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_call_or_index

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[310] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 91
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[311] 123 - op/sep {
pa_stmt

[312] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 91
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 111 - op/sep o
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 93
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[313] 205 - kw else
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_exprs
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 111 - op/sep o
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }
 125 - op/sep }

[314] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[315] 125 - op/sep }

[316] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[317] 125 - op/sep }

[318]
[319] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_postfix
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[320] 123 - op/sep {
pa_fntail

[321] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_postfix

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[322] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_primary
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[323] 208 - kw return
pa_stmt
 5 - id pa_call_or_index
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[324] 125 - op/sep }

[325]
[326] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_unexpr
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[327] 123 - op/sep {
pa_fntail

[328] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_unexpr

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[329] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 105
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 100
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_unexpr
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }

[330] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 45
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 33
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 42
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_term
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }

[331] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Sizeof
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[332] 123 - op/sep {
pa_stmt

[333] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[334] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[335] 123 - op/sep {
pa_stmt

[336] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[337] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id pa_type
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop

[338] 123 - op/sep {
pa_stmt

[339] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_stars
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[340] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[341] 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[342] 125 - op/sep }

[343] 208 - kw return
pa_stmt
 5 - id pa_exprtail
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[344] 125 - op/sep }

[345] 208 - kw return
pa_stmt
 5 - id pa_unexpr
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[346] 125 - op/sep }

[347] 208 - kw return
pa_stmt
 5 - id pa_postfix
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[348] 125 - op/sep }

[349]
[350] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_exprtail
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[351] 123 - op/sep {
pa_fntail

[352] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_exprtail

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[353] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[354] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[355] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[356] 208 - kw return
pa_stmt
 5 - id pa_call_or_index
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[357] 125 - op/sep }

[358]
[359] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_term
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[360] 123 - op/sep {
pa_fntail

[361] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_term

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[362] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[363] 123 - op/sep {
pa_stmt

[364] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[365] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id pa_type
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop

[366] 123 - op/sep {
pa_stmt

[367] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_stars
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[368] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[369] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[370] 208 - kw return
pa_stmt
 5 - id pa_term
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[371] 125 - op/sep }

[372] 208 - kw return
pa_stmt
 5 - id pa_exprtail
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[373] 125 - op/sep }

[374] 208 - kw return
pa_stmt
 5 - id pa_unexpr
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[375] 125 - op/sep }

[376]
[377] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_binop
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[378] 123 - op/sep {
pa_fntail

[379] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_binop

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[380] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 42
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 47
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 37
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
[//]
[381] 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 43
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 45
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
[//]
[382] 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 60
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 62
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 108
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 103
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
[//]
[383] 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 101
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 110
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
[//]
[384] 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 38
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 124
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
[//]
[385] 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 97
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 111
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 61
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
[//]
[386] 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[387] 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[388] 125 - op/sep }

[389]
[390] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_expr
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[391] 123 - op/sep {
pa_fntail

[392] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_expr

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[393] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_term
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[394] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id pa_binop
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_term
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[395] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[396] 125 - op/sep }

[397]
[398] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_stmt
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[399] 123 - op/sep {
pa_fntail

[400] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_stmt

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[401] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }
[//]
[402] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 123
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_block
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }

[403] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Break
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[404] 123 - op/sep {
pa_stmt

[405] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[406] 125 - op/sep }

[407] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Return
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[408] 123 - op/sep {
pa_stmt

[409] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[410] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[411] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[412] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[413] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[414] 125 - op/sep }

[415] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id While
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[416] 123 - op/sep {
pa_stmt

[417] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[418] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[419] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[420] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[421] 208 - kw return
pa_stmt
 5 - id pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[422] 125 - op/sep }

[423] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id If
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[424] 123 - op/sep {
pa_stmt

[425] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[426] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[427] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[428] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[429] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_stmt
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[430] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Else
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[431] 123 - op/sep {
pa_stmt

[432] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[433] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_stmt
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[434] 125 - op/sep }

[435] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[436] 125 - op/sep }

[437] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Enum
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[438] 123 - op/sep {
pa_stmt

[439] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[440] 208 - kw return
pa_stmt
 5 - id pa_enumdef
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[441] 125 - op/sep }

[442] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Int
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Char
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Void
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[443] 123 - op/sep {
pa_stmt

[444] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_type
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 111 - op/sep o
pa_binop
 33 - op/sep !
pa_term
pa_unexpr
 5 - id pa_stars
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[445] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[446] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[447] 208 - kw return
pa_stmt
 5 - id pa_vars
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 2 - num 1
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[448] 125 - op/sep }

[449][//]
[450] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[451] 125 - op/sep }

[452]
[453] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_enumerator
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[454] 123 - op/sep {
pa_fntail

[455] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_enumerator

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[456] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[457] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[458] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 61
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[459] 123 - op/sep {
pa_stmt

[460] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[461] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_intexpr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[462] 125 - op/sep }

[463] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[464] 125 - op/sep }

[465]
[466] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_enumdef
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[467] 123 - op/sep {
pa_fntail

[468] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_enumdef

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[469] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 123
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[470] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[471] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_enumerator
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[472] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 44
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[473] 123 - op/sep {
pa_stmt

[474] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[475] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_enumerator
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[476] 125 - op/sep }

[477] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 125
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[478] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[479] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[480] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[481] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[482] 125 - op/sep }

[483]
[484] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_argdef
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[485] 123 - op/sep {
pa_fntail

[486] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_argdef

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[487] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_type
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 111 - op/sep o
pa_binop
 33 - op/sep !
pa_term
pa_unexpr
 5 - id pa_stars
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[488] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[489] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[490] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[491] 125 - op/sep }

[492]
[493] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_args
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[494] 123 - op/sep {
pa_fntail

[495] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_args

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[496] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_argdef
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[497] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 44
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[498] 123 - op/sep {
pa_stmt

[499] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[500] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_argdef
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[501] 125 - op/sep }

[502] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[503] 125 - op/sep }

[504]
[505] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_number
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[506] 123 - op/sep {
pa_fntail

[507] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_number

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[508] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Num
pa_term
pa_unexpr
pa_postfix
pa_primary
 97 - op/sep a
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Chr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[509][//]
[510] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[511] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[512] 125 - op/sep }

[513]
[514] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_intexpr
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[515] 123 - op/sep {
pa_fntail

[516] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_intexpr

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[517] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 45
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[518] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[519] 208 - kw return
pa_stmt
 5 - id pa_number
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[520] 125 - op/sep }

[521]
[522] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_constexpr
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[523] 123 - op/sep {
pa_fntail

[524] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_constexpr

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[525] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }
[//]
[526] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Str
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }
[//]
[527] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 123
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_intexpr
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[528] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[529] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_constexpr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[530] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 44
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[531] 123 - op/sep {
pa_stmt

[532] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[533] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_constexpr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[534] 125 - op/sep }

[535] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 125
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[536] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[537] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[538] 125 - op/sep }

[539]
[540] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_vartail
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id k
pa_stars
 41 - op/sep )

[541] 123 - op/sep {
pa_fntail

[542] 5 - id p3
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_vartail:
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id k
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str 

pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[543] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 91
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[544] 123 - op/sep {
pa_stmt

[545] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[546] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_number
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[547] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 93
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[548] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[549] 125 - op/sep }

[550] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 61
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[551] 123 - op/sep {
pa_stmt

[552] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[553] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id k
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_constexpr
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 205 - kw else
 208 - kw return
pa_stmt
 5 - id pa_expr
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[554] 125 - op/sep }

[555] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[556] 125 - op/sep }

[557]
[558] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_vars
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id k
pa_stars
 41 - op/sep )

[559] 123 - op/sep {
pa_fntail

[560] 5 - id p3
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_vars:
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id i2s
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id k
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 44 - op/sep ,
pa_binop
 4 - str 

pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[561] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_vartail
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id k
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[562] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 44
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[563] 123 - op/sep {
pa_stmt

[564] 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[565] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_stars
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[566] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[567] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[568] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_vartail
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id k
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[569] 125 - op/sep }

[570] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[571] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[572] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[573] 125 - op/sep }

[574]
[575] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_block
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type
[//]
[576] 123 - op/sep {
pa_fntail

[577] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_block

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[578] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 125
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[579] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_stmt
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
[//]
[580] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[581] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[582] 125 - op/sep }

[583]
[584] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_fntail
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[585] 123 - op/sep {
pa_fntail

[586] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_fntail

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[587] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 59
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }
[//]
[588] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 123
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_block
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }
[//]
[589] 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[590] 125 - op/sep }

[591]
[592] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_fn_or_vars
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[593] 123 - op/sep {
pa_fntail

[594] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_fn_or_vars

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[595] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 40
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_vars
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 2 - num 0
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[596] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[597] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_args
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[598] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 3 - chr 41
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[599] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[600] 208 - kw return
pa_stmt
 5 - id pa_fntail
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[601] 125 - op/sep }

[602]
[603] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_stars
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[604] 123 - op/sep {
pa_fntail

[605] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_stars

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[606] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 42
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 3 - chr 42
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }

[607] 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[608] 125 - op/sep }

[609]
[610] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_type
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[611] 123 - op/sep {
pa_fntail

[612] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_type

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[613] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Int
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Char
pa_term
pa_unexpr
pa_postfix
pa_primary
 111 - op/sep o
pa_call_or_index
pa_binop
 5 - id sc_tkn
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Void
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[614] 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[615] 125 - op/sep }

[616]
[617] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_decl_or_def
pa_stars
 40 - op/sep (
pa_fn_or_vars
 41 - op/sep )
pa_args
pa_argdef
pa_type

[618] 123 - op/sep {
pa_fntail

[619] 5 - id p1
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_decl_or_def

pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[620] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 101 - op/sep e
pa_call_or_index
pa_binop
 5 - id Kw
pa_term
pa_unexpr
pa_postfix
pa_primary
 43 - op/sep +
pa_call_or_index
pa_binop
 5 - id Enum
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 123 - op/sep {
pa_stmt
 5 - id sc_next
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 5 - id pa_enumdef
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop
 125 - op/sep }

[621] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_type
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 111 - op/sep o
pa_binop
 33 - op/sep !
pa_term
pa_unexpr
 5 - id pa_stars
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[622] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Id
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id F
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[623] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[624] 208 - kw return
pa_stmt
 5 - id pa_fn_or_vars
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[625] 125 - op/sep }

[626]
[627] 202 - kw int
pa_decl_or_def
pa_type
 5 - id pa_file
pa_stars
 40 - op/sep (
pa_fn_or_vars
 201 - kw char
pa_args
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 5 - id fn
 41 - op/sep )

[628] 123 - op/sep {
pa_fntail

[629] 5 - id p3
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str pa_file 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id fn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 4 - str 

pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[630] 5 - id rd_file
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id open
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id fn
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id O_RDONLY
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[631] 204 - kw if
pa_stmt
 40 - op/sep (
 5 - id rd_file
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 108 - op/sep l
pa_call_or_index
pa_binop
 2 - num 0
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 208 - kw return
pa_stmt
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[632]
[633] 202 - kw int
pa_stmt
pa_type
 5 - id rc
pa_stars
 61 - op/sep =
pa_vars:1
pa_vartail:1
 5 - id T
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[634] 5 - id sc_next
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 59 - op/sep ;
pa_binop

[635] 206 - kw while
pa_stmt
 40 - op/sep (
 5 - id sc_tkn
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 110 - op/sep n
pa_call_or_index
pa_binop
 5 - id Eof
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop

[636] 204 - kw if
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_decl_or_def
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 41 - op/sep )
 41 - op/sep )
pa_binop

[637] 123 - op/sep {
pa_stmt
 5 - id rc
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 61 - op/sep =
pa_call_or_index
pa_binop
 5 - id F
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 207 - kw break
pa_stmt
 59 - op/sep ;
 125 - op/sep }

[638]
[639] 5 - id close
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id rd_file
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 41 - op/sep )
pa_call_or_index
pa_binop
 59 - op/sep ;
pa_binop

[640] 208 - kw return
pa_stmt
 5 - id rc
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[641] 125 - op/sep }

[642]
[643][//]
[644]
[645] 202 - kw int
pa_decl_or_def
pa_type
 5 - id main
pa_stars
 40 - op/sep (
pa_fn_or_vars
 202 - kw int
pa_args
pa_argdef
pa_type
 5 - id ac
pa_stars
 44 - op/sep ,
 201 - kw char
pa_argdef
pa_type
 42 - op/sep *
pa_stars
 42 - op/sep *
 5 - id av
 41 - op/sep )

[646] 123 - op/sep {
pa_fntail

[647] 204 - kw if
pa_block
pa_stmt
 40 - op/sep (
 33 - op/sep !
pa_expr
pa_term
pa_unexpr
 5 - id pa_file
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 5 - id av
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 41 - op/sep )
pa_binop
 123 - op/sep {
pa_stmt
 5 - id p2
pa_block
pa_stmt
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 40 - op/sep (
pa_call_or_index
 4 - str Error in 
pa_exprs
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 44 - op/sep ,
pa_call_or_index
pa_binop
 5 - id av
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 91 - op/sep [
pa_call_or_index
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 93 - op/sep ]
pa_call_or_index
pa_binop
 41 - op/sep )
pa_binop
 59 - op/sep ;
pa_binop
 208 - kw return
pa_stmt
 2 - num 1
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop
 125 - op/sep }

[648] 208 - kw return
pa_stmt
 2 - num 0
pa_expr
pa_term
pa_unexpr
pa_postfix
pa_primary
 59 - op/sep ;
pa_call_or_index
pa_binop

[649] 125 - op/sep }

[650] 1 - eof
