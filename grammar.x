// comments are //... and /*...*/ the later can be multi-line
// syntax: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html
// parse: https://en.wikipedia.org/wiki/Recursive_descent_parser
// {...} can be 0 or more times  [...] can be 0 or 1 time   x|y alternative

primary : @Number | @Char | @String | @Id | '(' expr ')'

exprs : expr { ',' expr }

call_or_index : { '[' expr ']' | '(' [ exprs ] ')' }

postfix : primary call_or_index          // no: postfix ++|--

type : "int" | "char" | "void"           // only these types

stars : [ '*' [ '*' ] ]                  // up to two stars for int and char

sizeofexpr : '(' type stars ')'
           | '(' @Id [ '[' @Number ']' ] ')'  // no: sizof expr

unexpr : '+''+' unexpr | '-''-' unexpr
       | '-' term | '!' term | '*' term  // no: &x ~x
       | "sizeof" sizeofexpr
       | postfix

term : '(' type stars ')' term
     | '(' expr ')' call_or_index
     | unexpr

binop : '*' | '/' | '%'                  // pri. 3     no:
      | '+' | '-'                        // pri. 4     5: << >>
      | '<' | '>' | '<''=' | '>''='      // pri. 6
      | '=''=' | '!''='                  // pri. 7     8 9 10: & ^ |
      | '&''&'                           // pri. 11
      | '|''|'                           // pri. 12    13: ?:
      | '='                              // pri. 14    14: += -= <<= ...

expr : term { binop term }

stmt : ';'
     | '{' block
     | "break" ';'                | "return" [ expr ] ';'
     | "while" '(' expr ')' stmt  | "if" '(' expr ')' stmt [ "else" stmt ]
     | type stars @Id vars__1
     | expr ';'

number : @Number | @Char

intexpr : number | '-' number | '!' number
        | "sizeof" sizeofexpr

constexpr : intexpr                             // int n = -42;
          | @String                             // char* s = "abc";
          | @Id                                 // int* ptr = array;
          | '{' constexpr { ',' constexpr } '}' // int m[4] = { 1, 2 };

vartail__0 : [ '[' number ']' ] [ '=' constexpr ]
vartail__1 : [ '[' number ']' ] [ '=' expr ]

vars__n : vartail__n { ',' stars @Id vartail__n } ';'

enumerator : @Id [ '=' intexpr ]

enumdef : '{' enumerator { ',' enumerator } '}' ';'

block : { stmt } '}'

fntail : ';' | '{' block      // '{' out of block for easy analysis

argdef : type stars @Id

args : [ argdef { ',' argdef } ]

fn_or_vars : '(' args ')' fntail | vars__0

decl_or_def : type stars @Id fn_or_vars | "enum" enumdef

program : decl_or_def { decl_or_def } @Eof      // definition/declaration


# vim: set syntax=ANTLR :
