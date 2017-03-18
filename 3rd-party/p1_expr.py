# see http://effbot.org/zone/simple-top-down-parsing.txt

import sys
import re

pa_prec = {"+":10,"-":10,"<":5,">":5,"=":5,"*":20,"/":30,"^":40,"E":0}

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
  if pos>=len(pgm_text): return 'E'
  c = pgm_text[pos]
  return c

def expr(rbp):
  global sc_tkn
  t = sc_tkn
  sc_tkn = next()

  left = int(t) # first term

  while rbp < pa_prec[sc_tkn]:

    t = sc_tkn
    sc_tkn = next()

    p = pa_prec[t]
    if t=="^": p -= 1 # right-assoc. operator
    e = expr(p)
    print(t,left,e)
    if t=="*": left *= e
    if t=="/": left /= e
    if t=="+": left += e
    if t=="-": left -= e
    if t=="<": left = left < e
    if t==">": left = left > e
    if t=="=": left = left == e
    if t=="^": left = left ** e

  return left

def parse(program):
  print( program, "..." )
  start(program)
  e = expr(0)
  print( "-->", e )
  print()

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
parse("1+2*3+4")
parse("1*2+3*4")

