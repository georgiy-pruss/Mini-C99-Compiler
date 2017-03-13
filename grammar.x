// comments are //... and /*...*/ the later can be multi-line
// syntax: http://www.lysator.liu.se/c/ANSI-C-grammar-y.html
// parse: https://en.wikipedia.org/wiki/Recursive_descent_parser
// {...} can be 0 or more times  [...] can be 0 or 1 time   x|y alternative

pgm : decl_or_def { decl_or_def } @Eof          // definition/declaration

decl_or_def : type stars @Id fn_or_vars | "enum" enumdef

type : "int" | "char" | "void"

stars : [ '*' [ '*' ] ]

fn_or_vars : '(' args ')' fntail | varsº

fntail : ';' | '{' block      // '{' out of block for easy analysis

block : { stmt } '}'

varsⁿ : vartailⁿ { ',' stars @Id vartailⁿ } ';'

vartailº : [ '[' number ']' ] [ '=' constexpr ]
vartail¹ : [ '[' number ']' ] [ '=' expr ]

constexpr : intexpr                             // int n = -42;
          | @String                             // char* s = "abc";
          | @Id                                 // int* ptr = array;
          | '{' constexpr { ',' constexpr } '}' // int m[4] = { 1, 2 };

intexpr : [ '-' ] number

number : @Number | @Char

args : [ argdef { ',' argdef } ]

argdef : type stars @Id

enumdef : '{' enumerator { ',' enumerator } '}' ';'

enumerator : @Id [ '=' intexpr ]

stmt : ';'
     | '{' block
     | "break" ';'                              | "return" [ expr ] ';'
     | "if" '(' expr ')' stmt [ "else" stmt ]   | "while" '(' expr ')' stmt
     | "enum" enumdef
     | type stars @Id vars¹
     | expr ';'

expr : term { binop term }

term : { unop } base       // ????????????????
     | "sizeof" expr
     | '(' type stars ')' expr

base : "sizeof" '(' type stars ')'   // maybe omit this if too difficult
     | primary { call_or_index }

call_or_index : '(' [ exprs ] ')' | '[' expr ']' // on postfix ++ and --

exprs : expr { ',' expr }

primary : @Number | @Char | @String | @Id | '(' expr ')'

binop : '*' | '/' | '%'                         // pri. 3
      | '+' | '-'                               // pri. 4   5: << >>
      | '<' | '>' | '<''=' | '>''='             // pri. 6
      | '=''=' | '!''='                         // pri. 7
      | '&'                                     // pri. 8   9: ^
      | '|'                                     // pri. 10
      | '&''&'                                  // pri. 11
      | '|''|'                                  // pri. 12  13: ?:
      | '='                                     // pri. 14  and op=

unop : '-' | '!' | '*' | '+''+' | '-''-'        // no &x ~x


# vim: set syntax=ANTLR :
