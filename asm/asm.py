# asm.py >t
# o.o - result, some missing, watch it
# t - what's not recognized

o = open( "o.o", "wt" )

def process_label( l:str ):
  # print( l+': '+str(text_addr) )
  pass

REGS = {'eax':0,'ecx':1,'edx':2,'ebx':3,'esp':4,'ebp':5,'esi':6,'edi':7}
SETOPS = {'sete':0x94,'setz':0x94,'setne':0x95,'setnz':0x95,
          'setl':0x9c,'setg':0x9f,'setle':0x9e,'setge':0x9d}
BINOPS = {'add':0x00,'or':0x08,'and':0x20,'sub':0x28,'xor':0x30,'cmp':0x38}
BINOPS2 = {'add':0xc0,'or':0xc8,'and':0xe0,'sub':0xe8,'xor':0xf0,'cmp':0xf8}

def immediate4( s ):
  if s.startswith('0x'):    n = int(s[2:],16)
  elif s.startswith('-0x'): n = -int(s[3:],16)
  else:                     n = int(s)
  if n>0:                 imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  else: n += 0x100000000; imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  return imm

def immediate( s ):
  if s.startswith('0x'):    n = int(s[2:],16)
  elif s.startswith('-0x'): n = -int(s[3:],16)
  else:                     n = int(s)
  if 0<=n<=127:     imm = '%02x'%n
  elif -128<=n<=-1: imm = '%02x'%(256+n)
  elif n>0:               imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  else: n += 0x100000000; imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  return imm

def mod_reg_rm( mod, reg, rm ):
  b = (mod<<6)|(reg<<3)|rm
  return '%02x' % b

def process_command( l:str ):
  global text_addr
  b = l.find(' ')
  if b<0:
    print( "==-==------------------------ "+l, file=o )
    if l=='nop': print( '90', file=o )
    elif l=='cdq': print( '99', file=o )
    elif l=='cld': print( 'fc', file=o )
    elif l=='leave': print( 'c9', file=o )
    elif l=='ret':
      print( 'c3', file=o )
      nops = (4-text_addr%4)%4
      if nops>0:
        for i in range(nops): print( '90', file=o )
    else: print( 'ukn1 '+l )
    return
  k = b+1
  while k<len(l) and l[k]==' ': k+=1
  if k==len(l):
    print( 'word, then blanks' )
  w = l[:b]
  a = l[k:]
  print( "==-==-==-==-==-==-==-==-==-== "+l, file=o )
  if w=='pop':
    if a in REGS:
      reg = REGS[a]
      print( '%02x' % (0x58 + reg), file=o )
    else: print( 'ukn '+w+' '+a )
  elif w=='push':
    if a in REGS:
      reg = REGS[a]
      print( '%02x' % (0x50 + reg), file=o )
    elif a[0] in '-0123456789':
      imm = immediate(a)
      if len(imm)==2:
        print( '6a '+imm, file=o )
      else:
        print( '68 '+imm, file=o )
    else: print( 'ukn '+w+' '+a )
  elif w=='neg' or w=='not':
    op = {'neg':0xd8,'not':0xd0}[w]
    if a in REGS:
      print( 'f7 %02x' % (op+REGS[a]), file=o )
    else: print( 'ukn '+w+' '+a+' - not reg' )
  elif w=='repne' and a=='scasb':
    print( 'f2 ae', file=o )
  elif w=='rep' and a=='movsb':
    print( 'f3 a4', file=o )
  elif w in SETOPS:
    op = SETOPS[w]
    if a=='al': print( '0f %02x c0' % op, file=o )
    else: print( 'ukn '+w+' '+a )
  elif w=='idiv':
    if a in REGS:
      reg = REGS[a]
      print( 'f7 %02x' % (0xf8+reg), file=o )
    else: print( 'ukn '+w+' '+a )
  elif w=='imul':
    if a.startswith( 'eax,eax,' ):
      imm = immediate( a[8:] )
      if len(imm)==2:  print( '6b c0 ' + imm, file=o )
      else:            print( '69 c0 ' + imm, file=o )
    elif a=='eax,ebx': print( '0f af c3', file=o )
    else: print( 'ukn '+w+' '+a )
  elif w=='movzx' and a=='eax,al':
    print( '0f b6 c0', file=o )
  elif w=='test':
    if a=='eax,eax': print( '85 c0', file=o )
    elif a=='al,al': print( '84 c0', file=o )
    else: print( 'ukn '+w+' '+a )
  elif w in BINOPS2 and a[3]==',' and a[:3] in REGS and a[4] in '-0123456789': # binop reg,imm
    reg = REGS[a[:3]]
    imm = immediate(a[4:])
    if len(imm)==2: print( '83 %02x %s' % (BINOPS2[w]|reg,imm), file=o )
    elif reg==0:    print( '%02x %s' % (BINOPS[w]+5,imm), file=o )
    else:           print( 'ukn '+w+' '+a+' - not impl' )
  elif w in BINOPS and a[3]==',' and a[:3] in REGS and a[4:] in REGS: # binop reg,reg
    reg1 = REGS[a[:3]]
    reg2 = REGS[a[4:]]
    print( '%02x %02x' % (BINOPS[w]+1,0xC0|(reg2<<3)|reg1), file=o )
  elif w=='mov' and a[3]==',' and a[:3] in REGS and a[4:] in REGS: # mov reg,reg
    reg1 = REGS[a[:3]]
    reg2 = REGS[a[4:]]
    print( '89 %02x' % (0xC0|(reg2<<3)|reg1), file=o )
  elif w=='mov' and a[3]==',' and a[:3] in REGS and a[4] in '-0123456789': # mov reg,imm
    reg = REGS[a[:3]]
    imm = immediate4(a[4:])
    print( '%02x %s' % (0xb8+reg,imm), file=o )
  elif w=='cmp' and a.startswith('al,'):
    imm = immediate(a[3:])
    if len(imm)==2: print( '3c '+imm, file=o )
    else:           print( '*** '+w+' '+a+' - const too big' )
  elif w=='movsx' and a=='eax,byte ptr [eax]':
    print( '0f be 00', file=o )
  # mov
  elif w=='mov' and a.startswith('al,byte ptr [') and a[16]==']':
    reg = REGS[a[13:16]]
    if reg==4: # esp -- different command
      print( '8a %02x 24' % reg, file=o )
    elif reg==5: # ebp -- add disp8=0
      print( '8a %02x 00' % (0x40|reg), file=o )
    else:
      print( '8a %02x' % reg, file=o )
  elif w=='mov' and a[3:15]==',dword ptr [' and a[18]==']':
    # mov reg,dword ptr [reg]
    reg1 = REGS[a[:3]]
    reg2 = REGS[a[15:18]]
    if reg2==4: # esp -- different command
      print( '8b %02x 24' % ((reg1<<3)|reg2), file=o )
    elif reg2==5: # ebp -- add disp8=0
      print( '8b %02x 00' % (0x40|(reg1<<3)|reg2), file=o )
    else:
      print( '8b %02x' % ((reg1<<3)|reg2), file=o )
  elif w=='mov' and a[:11]=='dword ptr [' and a[14:16]=='],' and a[16:] in REGS:
    # mov dword ptr [reg],reg
    reg1 = REGS[a[11:14]]
    reg2 = REGS[a[16:]]
    if reg1==4: # esp -- different command
      print( '89 %02x 24' % ((reg2<<3)|reg1), file=o )
    elif reg1==5: # ebp -- add disp8=0
      print( '89 %02x 00' % (0x40|(reg2<<3)|reg1), file=o )
    else:
      print( '89 %02x' % ((reg2<<3)|reg1), file=o )

  elif w=='mov' and a[3:15]==',dword ptr [' and a[18] in '+-' and a[-1]==']':
    # mov reg,dword ptr [reg+ofs]
    reg1 = REGS[a[:3]]
    reg2 = REGS[a[15:18]]
    ofs = immediate(a[18:-1])
    if reg2==4: ins = '24 '
    else: ins = ''
    if len(ofs)==2:
      print( '8b %02x %s%s' % (0x40|(reg1<<3)|reg2,ins,ofs), file=o )
    else:
      print( '8b %02x %s%s' % (0x80|(reg1<<3)|reg2,ins,ofs), file=o )

  elif w=='mov' and a[:11]=='dword ptr [' and a[14] in '+-' and a[a.find('],')+2:] in REGS:
    # mov dword ptr [reg+ofs],reg
    sep = a.find('],')
    reg1 = REGS[a[11:14]]
    reg2 = REGS[a[sep+2:]]
    ofs = immediate(a[14:sep])
    if reg1==4: ins = '24 '
    else: ins = ''
    if len(ofs)==2:
      print( '8b %02x %s%s' % (0x40|(reg2<<3)|reg1,ins,ofs), file=o )
    else:
      print( '8b %02x %s%s' % (0x80|(reg2<<3)|reg1,ins,ofs), file=o )

  # TODO

  elif w in BINOPS:
    pass
    # print( '... '+w+' '+a+' ---- ops..' )

  elif w=='mov':
    pass
  elif w=='lea':
    pass
  elif w=='jmp':
    pass
  elif w=='call':
    pass
  elif w in ('je','jz','jne','jnz','jl','jle','jg','jge','js'):
    pass

  else: print( '... '+w+' '+a )
  text_addr += 1

def process_pseudocommand( l:str ):
  global text_addr
  text_addr += 1

if "todo"=="print canonical form":
  def process_label( l:str ): print( l+':' )
  def process_command( l:str ): print( ' '+l )
  def process_pseudocommand( l:str ): print( ' '+l )

text_addr = 0
data_addr = 0
rdata_addr = 0
bss_addr = 0

def asm( t:str ):
  lines = t.replace('\r','').replace('\t',' ').split('\n')
  for l in lines:
    if len(l)==0 or l[0]=='#': continue
    if l[0]!=' ': # label
      c = l.index(':')
      process_label( l[:c] )
      r = l[c+1:]
      if len(r)==0: continue
      l = ' '+r
    k = 0
    while k<len(l) and l[k]==' ': k+=1
    if k==len(l) or l[k]=='#': continue
    t = l[k:] # lstrip
    comment = t.find(' # ')               # comment: ' # '
    if comment>=0:
      t = t[:comment].rstrip()
    if t[0]=='.':
      process_pseudocommand( t )
    else:
      process_command( t )

with open( "all.s", "rt" ) as f:
  t = f.read()
  asm(t)

o.close()

