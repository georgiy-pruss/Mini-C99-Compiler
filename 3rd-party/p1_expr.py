# see http://effbot.org/zone/simple-top-down-parsing.txt

pa_prec = {"<":5,">":5,"=":5,"+":10,"-":10,"*":20,"/":30,"^":40}

pgm_text = ""
pos = -1
sc_tkn = None

def start(program):
  global sc_tkn,pgm_text,pos
  pgm_text = program
  pos = -1
  sc_tkn = next()

def next():
  global pos
  pos += 1
  if pos>=len(pgm_text):
    print( "*** next() returns <E>" )
    return 'E'
  c = pgm_text[pos]
  print( "*** next() returns "+c )
  return c

def expr(rbp):
  global sc_tkn

  print( ">>> entered expr with rbp",rbp )
  print( "tkn "+sc_tkn+" saved to t" )
  t = sc_tkn
  print( "<-> left is int("+t+")" )
  left = int(t) # first term

  sc_tkn = next()
  print( "tkn becomes "+sc_tkn+" before loop" )

  while sc_tkn in pa_prec and rbp < pa_prec[sc_tkn]:

    print( "in loop start, rbp was",str(rbp)+", sc_tkn was",sc_tkn+", its prec was "+
        str(pa_prec[sc_tkn]) )
    t = sc_tkn
    print( "in loop, tkn "+sc_tkn+" saved to t" )
    sc_tkn = next()
    print( "in loop, sc_tkn =",sc_tkn )

    p = pa_prec[t]
    print( "in loop, prec of t is",p )
    if t=="^": p -= 1 # right-assoc. operator
    print( "in loop, calling expr with p",p )
    e = expr(p)
    print( "in loop, expr returned",e )
    print( "in loop, now performing",t,left,e)
    if t=="*": left *= e
    if t=="/": left /= e
    if t=="+": left += e
    if t=="-": left -= e
    if t=="<": left = left < e
    if t==">": left = left > e
    if t=="=": left = left == e
    if t=="^": left = left ** e

  print( "<<< out of loop, returning",left,"from expr")
  return left

def parse(program):
  print( program, "..." )
  start(program)
  e = expr(0)
  print( "-->", e )
  print()

'''
parse("6")
parse("2^3^1")
parse("1+2")
parse("1+2+3")
parse("1+2*3")
parse("1*2+3")
parse("1*2/3")
parse("1+4>1+5")
parse("1+2*2=1+5")
parse("1+2*2<1^4+5")
parse("1*2+3*4")
'''
parse("1+2*3+4")

