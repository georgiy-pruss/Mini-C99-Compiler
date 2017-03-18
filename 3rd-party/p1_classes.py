# see http://effbot.org/zone/simple-top-down-parsing.txt

import sys
import re

class literal_token:
  def __init__(self, value):
    self.value = value
  def nud(self):
    return self.value

class operator_add_token:
  lbp = 10
  def nud(self):
    e = expression(100)
    print("[+]",e)
    return e
  def led(self, left):
    e = expression(10)
    print("+",left,e)
    return left + e

class operator_sub_token:
  lbp = 10
  def nud(self):
    e = expression(100)
    print("[-]",e)
    return -e
  def led(self, left):
    e = expression(10)
    print("-",left,e)
    return left - e

class operator_less_token:
  lbp = 5
  def led(self, left):
    e = expression(5)
    print("<",left,e)
    return left < e

class operator_grtr_token:
  lbp = 5
  def led(self, left):
    e = expression(5)
    print(">",left,e)
    return left > e

class operator_equ_token:
  lbp = 5
  def led(self, left):
    e = expression(5)
    print("=",left,e)
    return left == e

class operator_mul_token:
  lbp = 20
  def led(self, left):
    e = expression(20)
    print("*",left,e)
    return left * e

class operator_div_token:
  lbp = 20
  def led(self, left):
    e = expression(20)
    print("/",left,e)
    return left / e

class operator_pow_token:
  lbp = 30
  def led(self, left):
    e = expression(30-1)
    print("^",left,e)
    return left ** e

class end_token:
  lbp = 0

program = ""
pos = -1
token = None

def next():
  global pos
  pos += 1
  if pos>=len(program): return end_token()
  c = program[pos]
  if c == "<": return operator_less_token()
  if c == ">": return operator_grtr_token()
  if c == "=": return operator_equ_token()
  if c == "+": return operator_add_token()
  if c == "-": return operator_sub_token()
  if c == "*": return operator_mul_token()
  if c == "/": return operator_div_token()
  if c == "^": return operator_pow_token()
  return literal_token(int(c))

def expression(rbp=0):
  global token
  t = token
  token = next()
  left = t.nud()
  while rbp < token.lbp:
    t = token
    token = next()
    left = t.led(left)
  return left

def parse(this_program):
  global token,program,pos
  program = this_program
  pos = -1
  print( program, "..." )
  token = next()
  print( "-->", expression() )
  print()

parse("+1")
parse("-1")
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
parse("2--1")

