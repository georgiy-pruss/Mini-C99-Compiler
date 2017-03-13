// comments are //... and /*...*/ the later can be multi-line
// syntax: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html
// parse: https://en.wikipedia.org/wiki/Recursive_descent_parser
// {...} can be 0 or more times  [...] can be 0 or 1 time   x|y alternative

pgm : decl_or_def { decl_or_def } @Eof             // definition/declaration

decl_or_def : type stars @Name fn_or_vars | "enum" enumdef

type : "int" | "char" | "void"

stars : [ '*' [ '*' ] ]

fn_or_vars : '(' args ')' fntail | vars

fntail : ';' | block // can do check '{' here

block : '{' { stmt } '}' // checks for '{' done before

vars : vartail { ',' stars @Name vartail } ';'

vartail : [ '[' number ']' ] [ '=' constexpr ]

constexpr : intexpr                                // int n = -42;
          | @String                                // char* s = "abc";
          | @Name                                  // int* ptr = array;
          | '{' constexpr { ',' constexpr } '}'    // int m[4] = { 1, 2 };

intexpr : [ '-' ] number

number : @Number | @Char

args : [ argdef { ',' argdef } ]

argdef : type stars @Name

enumdef : '{' enumerator { ',' enumerator } '}' ';'

enumerator : @Name [ '=' intexpr ]

stmt : ';'                      | expr ';'       | block // check '{' before
     | "break" ';'                               | "return" [ expr ] ';'
     | "if" '(' expr ')' stmt [ "else" stmt ]    | "while" '(' expr ')' stmt
     | "enum" enumdef                            | type stars @Name vars

expr : term { binop term }

binop : '*' | '/' | '%'                       // pri. 5
      | '+' | '-'                             // pri. 6
      | '<' | '>' | '<''=' | '>''='           // pri. 8
      | '=''=' | '!''='                       // pri. 9
      | '&''&'                                // pri. 13
      | '|''|'                                // pri. 14
      | '='                                   // pri. 16

term : { unop } base

unop : '-' | '!' | '*' | '+''+' | '-''-' | "sizeof" | '(' type stars ')'

base : "sizeof" '(' type stars ')'   // maybe omit this if too difficult
     | primary { call_or_index }

call_or_index : '(' [ exprs ] ')' | '[' expr ']'

exprs : expr { ',' expr }

primary : @Number | @Char | @String | @Name | '(' expr ')'


# vim: set syntax=ANTLR :
