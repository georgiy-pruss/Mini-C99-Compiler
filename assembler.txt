p proc nargs,nlocals
a arg offset?
v loc type,nwords,offset?
  endp
  end
e equ value|name
v glob type,nwords,initialvalue?

  binop res,arg1,op,arg2  #  + - * / % & | < > <= >= == !=
  unop  res,op,arg        #  - ! w b (extend to word; shrink to byte)
  move  res,arg
  push  arg
  pop   res

# registers: sp bp ax bx cx dx si di
# arg can be int,var,reg
# res can be var,reg
