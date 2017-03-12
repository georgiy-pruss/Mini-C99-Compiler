// comments are //... and /*...*/ the later can be multi-line
// syntax: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html
// parse: https://en.wikipedia.org/wiki/Recursive_descent_parser
// {...} can be 0 or more times  [...] can be 0 or 1 time   x|y alternative

pgm : declordef { declordef } @Eof                 // definition/declaration

declordef : type stars @Name fnorvars | enumdef

type : "int" | "void" | "char"

stars : [ '*' [ '*' ] ]

fnorvars : '(' args ')' fntail | vars

fntail : ';' | '{' { stmt } '}'

vars : vartail { ',' stars @Name vartail } ';'

vartail : [ '[' number ']' ] [ '=' constexpr ]

constexpr : intexpr                                // int n = -42;
          | @String                                // char* s = "abc";
          | @Name                                  // int* ptr = array;
          | '{' constexpr { ',' constexpr } '}'    // int m[4] = { 1, 2 };

intexpr : [ '-' ] number

number : @Number | @Char

args : [ argdef { ',' argdef } ]

argdef : type stars Name

enumdef : "enum" '{' enumname { ',' enumname } '}' ';'

enumname : @Name [ '=' intexpr ]

stmt : ';'                      | expr ';'       | '{' { stmt } '}'
     | "break" ';'                               | "return" [ expr ] ';'
     | "if" '(' expr ')' stmt [ "else" stmt ]    | "while" '(' expr ')' stmt
     | enumdef                                   | type stars @Name vars

expr : lvar '=' expr             | expr binop expr
     | '+''+' lvar               | "sizeof" expr
     | '-''-' lvar               | "sizeof" '(' type stars ')'
     | unop expr                 | '(' type stars ')' expr
     | expr '(' [ exprs ] ')'    | '(' expr ')'
     | expr '[' expr ']'
     | @Number | @Char | @String | @Name

lvar : expr         // well, it's hard to tell that the value should be assignable

exprs : expr { ',' expr }

binop : '+' | '-' | '*' | '/' | '%' | '<' | '>' | '&''&' | '|''|' | '=''=' | '!''='| '<''=' | '>''='

unop : '-' | '!' | '*'

// priorities:  2: x(...) x[x]                       6: + -         13: &&
//              3: ++x --x -x !x *x (cast)x sizeof   8: < <= > >=   14: ||
//              5: * / %                             9: == !=       16: =

# vim: set syntax=ANTLR :
