# asm.py - shows what's not recognized
# o.lst - listing; converted to pretty-print o.pp
# o.bin - binary output

o = open( "o.lst", "wt" )
b = open( "o.bin", "wb" )

l_no = 0 # number of current line

prep = True # two passes - preparation and final

s_data_len = 0  # for prep. pass
s_data = b''    # for final pass
s_rdata_len = 0 # for prep. pass
s_rdata = b''   # for final pass
s_code_len = 0  # for prep. pass -- let's call it code instead of text
s_code = b''    # for final pass
s_bss_len = 0

c_sec = 'code' # current section: code, data, rdata, bss
c_code = 0  # current address in code
c_data = 0  # current address in data
c_rdata = 0 # current address in rdata
c_bss = 0   # current address in bss

data_labels = []
code_labels = [] # ('name',addr)
jt = [] # (addr,is_jmp:bool,is_short:bool,label_index,target_addr)
jt_proc_start = 0 # index of next (vacant place) jump in jump table at proc start
jt_proc_done = False

def find_code_label( s:str )->int: # return index in code_labels
  for i,c in enumerate(code_labels):
    if c[0]==s: return i
  return -1

def add_code_label( s:str, a:int )->int: # return index in code_labels
  code_labels.append( (s,a) )
  return len(code_labels)-1

def add_jump( addr:int, is_jmp:bool, label_name:str ):
  idx = find_code_label( label_name )
  if idx<0:
    idx = add_code_label( label_name, -1 )
  jt.append( (addr,is_jmp,True,idx) )

def find_jump( addr:int )->int:
  for i in range( jt_proc_start, len(jt) ):
    if jt[i][0]==addr: return i
  return -1

def start_proc_jt( start:int ):
  # prepare jumps/labels for new proc
  global jt_proc_start, jt_proc_done
  jt_proc_start = start
  jt_proc_done = False

def end_proc_jt():
  # resolve all jumps in the latest proc
  global c_code # can change code len!
  for i in range( jt_proc_start, len( jt ) ): # can't do that more then this times
    shifted = False
    for j in range( jt_proc_start, len( jt ) ):
      (a,is_jmp,is_short,lx) = jt[j]
      if not is_short: # already long
        continue
      (_,target_addr) = code_labels[lx]
      diff = target_addr - (a + 2)
      if -128<=diff<=127:
        continue # all ok, leave as is
      if is_jmp: # unconditional jmp
        sz = 5
      else: # jcc
        sz = 6
      jt[j] = (a,is_jmp,False,lx) # change is_short
      shift = sz-2 # insert 3 or 4 bytes
      assert prep
      c_code += shift
      # shift jumps with bigger addresses
      for j1 in range( j+1, len( jt ) ):
        (a1,is_jmp1,is_short1,lx1) = jt[j1] # change address only
        a1 += shift
        jt[j1] = (a1,is_jmp1,is_short1,lx1)
      # shift all labels with address > a
      for l1 in range(len(code_labels)):
        (nm1,adr1) = code_labels[l1]
        if adr1 > a:
          code_labels[l1] = (nm1, adr1 + shift)
      shifted = True
      break
    if not shifted: # all is resolved
      break
  proc_jt_done = True

def process_label( lbl:str ):
  if c_sec == 'code':
    if prep:
      ix = find_code_label( lbl )
      if ix<0:
        add_code_label( lbl, c_code )
      else:
        (_,addr) = code_labels[ix]
        if addr>=0: print( '%d: !!! '%l_no+lbl+' - label redefinition' )
        code_labels[ix] = ( lbl, c_code )
    else:
      print( '\n%08x <%s>:' % (c_code,lbl), end='', file=o )

def NL():
  if prep:
    pass
  else:
    if c_sec == 'code':
      print( "\n%4x:  " % c_code, end='', file=o ) # if listing
    else:
      print( "\n%4x:  " % 0, end='', file=o ) # if listing

def Y( b:int ):
  global c_code
  if prep:
    pass
  else:
    print( ' %02x' % b, end='', file=o )
  c_code += 1

def YY( c:bool, b:int ): # conditional yield
  global c_code
  if c:
    if prep:
      pass
    else:
      print( ' %02x' % b, end='', file=o )
    c_code += 1

def Y1( b:str ): # yielding 1-byte immediate; will be for ints
  global c_code
  if prep:
    pass
  else:
    print( ' '+b, end='', file=o )
  c_code += 1

def Y4( b:str ): # yielding 4-byte immediate; will be for ints
  global c_code
  if prep:
    pass
  else:
    print( ' '+b, end='', file=o )
  c_code += 4

REGS = {'eax':0,'ecx':1,'edx':2,'ebx':3,'esp':4,'ebp':5,'esi':6,'edi':7}
SETOPS = {'sete':0x94,'setz':0x94,'setne':0x95,'setnz':0x95,
          'setl':0x9c,'setg':0x9f,'setle':0x9e,'setge':0x9d}
BINOPS = {'add':0x00,'or':0x08,'and':0x20,'sub':0x28,'xor':0x30,'cmp':0x38}
JMPS = {'je':0x74,'jz':0x74,'jne':0x75,'jnz':0x75,'js':0x78,'jns':0x79,
        'jl':0x7c,'jge':0x7d,'jle':0x7e,'jg':0x7f,'jmp':0xeb}

def immediate( s ):
  if s.startswith('0x'):    n = int(s[2:],16)
  elif s.startswith('-0x'): n = -int(s[3:],16)
  else:                     n = int(s)
  if 0<=n<=127:     imm = '%02x'%n
  elif -128<=n<=-1: imm = '%02x'%(256+n)
  elif n>0:               imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  else: n += 0x100000000; imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  return imm

def immediate4( s ):
  if s.startswith('0x'):    n = int(s[2:],16)
  elif s.startswith('-0x'): n = -int(s[3:],16)
  else:                     n = int(s)
  if n>=0:                imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  else: n += 0x100000000; imm = '%02x %02x %02x %02x' % ((n&255),((n>>8)&255),((n>>16)&255),(n>>24))
  return imm

def immediate1( s ): # accept -127..255
  if s.startswith('0x'):    n = int(s[2:],16)
  elif s.startswith('-0x'): n = -int(s[3:],16)
  else:                     n = int(s)
  if 0<=n<=255:   return '%02x'%n
  if -128<=n<=-1: return '%02x'%(256+n)
  print( '%d: *** '%l_no+s+' - const too big' )
  return '**'

def mod_reg_rm( mod, reg, rm ): # hmmm not used
  b = (mod<<6)|(reg<<3)|rm
  return '%02x' % b

def process_command( l:str ):
  global text_addr
  b = l.find(' ')
  if b<0:
    print( "\n####   ==-==------------------------ "+l, end='', file=o )
    NL()
    if l=='nop': Y( 0x90 )
    elif l=='cdq': Y( 0x99 )
    elif l=='cld': Y( 0xfc )
    elif l=='leave': Y( 0xc9 )
    elif l=='ret': Y( 0xc3 )
    else: print( '%d: !!! '%l_no+l+' - unknown cmd' )
    return
  k = b+1
  while k<len(l) and l[k]==' ': k+=1
  if k==len(l):
    print( 'word, then blanks' )
  w = l[:b]
  a = l[k:]
  print( "\n####   ==-==-==-==-==-==-==-==-==-== "+l, end='', file=o )
  NL()
  if w=='pop':
    if a in REGS: Y( 0x58 + REGS[a] )
    else: print( '%d: XXX '%l_no+w+' '+a )
  elif w=='push':
    if a in REGS: Y( 0x50 + REGS[a] )
    elif a[0] in '-+0123456789':
      imm = immediate(a)
      if len(imm)==2: Y( 0x6a ); Y1( imm )
      else:           Y( 0x68 ); Y4( imm )
    else: print( '%d: ??? '%l_no+w+' '+a+' - not reg or number' )
  elif w=='neg' or w=='not':
    if a in REGS: Y( 0xf7 ); Y( {'neg':0xd8,'not':0xd0}[w] + REGS[a] )
    else: print( '%d: ??? '%l_no+w+' '+a+' - not reg' )
  elif w=='repne' and a=='scasb':
    Y( 0xf2 ); Y( 0xae )
  elif w=='rep' and a=='movsb':
    Y( 0xf3 ); Y( 0xa4 )
  elif w in SETOPS and a=='al':
    Y( 0x0f ); Y( SETOPS[w] ); Y( 0xc0 )
  elif w=='idiv':
    if a in REGS: Y( 0xf7 ); Y( 0xf8+REGS[a] )
    else:
      print( '%d: /// '%l_no+w+' '+a )
      Y( 0x90 )
  elif w=='imul':
    if a.startswith( 'eax,eax,' ):
      imm = immediate( a[8:] )
      if len(imm)==2:  Y( 0x6b ); Y( 0xc0 ); Y1( imm )
      else:            Y( 0x69 ); Y( 0xc0 ); Y4( imm )
    elif a=='eax,ebx': Y( 0x0f ); Y( 0xaf ); Y( 0xc3 )
    elif a.startswith('eax,dword ptr [ebp') and a[-1]==']':
      reg = REGS['ebp']
      ofs = immediate(a[18:-1])
      if len(ofs)==2: Y( 0x0f ); Y( 0xaf ); Y( 0x40|reg ); Y1( ofs )
      else:           Y( 0x0f ); Y( 0xaf ); Y( 0x80|reg ); Y4( ofs )
    else: print( '%d: ??? '%l_no+w+' '+a )
  elif w=='movzx' and a=='eax,al':
    Y( 0x0f ); Y( 0xb6 ); Y( 0xc0 )
  elif w=='movsx' and a=='eax,byte ptr [eax]':
    Y( 0x0f ); Y( 0xbe ); Y( 0x00 )
  elif w=='test':
    if a=='eax,eax': Y( 0x85 ); Y( 0xc0 )
    elif a=='al,al': Y( 0x84 ); Y( 0xc0 )
    else: print( '%d: ??? '%l_no+w+' '+a )
  # binops
  elif w in BINOPS:
    if w=='cmp' and a.startswith('al,'):
      imm = immediate1(a[3:])
      Y( 0x3c ); Y1( imm )
    elif a[3]==',' and a[:3] in REGS and a[4] in '-+0123456789': # binop reg,imm
      reg = REGS[a[:3]]
      imm = immediate(a[4:])
      if len(imm)==2: Y( 0x83 ); Y( 0xc0|BINOPS[w]|reg ); Y1( imm )
      elif reg==0:    Y( BINOPS[w]+5 ); Y4( imm )
      else:           print( '%d: ??? '%l_no+w+' '+a+' - binop not impl' ) # probably 0x81 etc
    elif a[3]==',' and a[:3] in REGS and a[4:] in REGS: # binop reg,reg
      reg1 = REGS[a[:3]]
      reg2 = REGS[a[4:]]
      Y( BINOPS[w]+1 ); Y( 0xC0|(reg2<<3)|reg1 )
    elif a.startswith('eax,dword ptr [ebp') and a[-1]==']': # binop eax,dword ptr [ebp+ofs]
      reg = REGS['ebp'] # maybe add other regs here, but then need to check for esp...
      ofs = immediate(a[18:-1])
      if len(ofs)==2: Y( BINOPS[w]+3 ); Y( 0x40|reg ); Y1( ofs )
      else:           Y( BINOPS[w]+3 ); Y( 0x80|reg ); Y4( ofs )
    elif a.startswith('dword ptr [ebp'): # cmp dword ptr [ebp+ofs],imm
      reg = REGS['ebp']
      sep = a.find('],')
      ofs = immediate(a[14:sep])
      imm = immediate(a[sep+2:])
      if len(imm)==2:
        if len(ofs)==2: Y( 0x83 ); Y( BINOPS[w]|0x40|reg ); Y1( ofs ); Y1( imm )
        else:           Y( 0x83 ); Y( BINOPS[w]|0x80|reg ); Y4( ofs ); Y1( imm )
      else:
        if len(ofs)==2: Y( 0x81 ); Y( BINOPS[w]|0x40|reg ); Y1( ofs ); Y4( imm )
        else:           Y( 0x81 ); Y( BINOPS[w]|0x80|reg ); Y4( ofs ); Y4( imm )
    else:
      print( '%d: ??? '%l_no+w+' '+a+' - binop' ) # e.g. add var,eax or cmp eax,var
      Y( 0x90 )
  # mov
  elif w=='mov':
    if a[3]==',' and a[:3] in REGS and a[4:] in REGS: # mov reg,reg
      reg1 = REGS[a[:3]]
      reg2 = REGS[a[4:]]
      Y( 0x89 ); Y( 0xC0|(reg2<<3)|reg1 )
    elif a[3]==',' and a[:3] in REGS and a[4] in '-+0123456789': # mov reg,imm
      reg = REGS[a[:3]]
      imm = immediate4(a[4:])
      Y( 0xb8+reg ); Y4( imm )
    elif a.startswith('al,byte ptr [') and a[16]==']':
      reg = REGS[a[13:16]]
      if reg==4: Y( 0x8a ); Y( reg ); Y( 0x24 ) # esp -- different command
      elif reg==5: Y( 0x8a ); Y( 0x40|reg ); Y( 0x00 ) # ebp -- add disp8=0
      else: Y( 0x8a ); Y( reg )
    elif a[3:15]==',dword ptr [' and a[18]==']':
      # mov reg,dword ptr [reg]
      reg1 = REGS[a[:3]]
      reg2 = REGS[a[15:18]]
      if reg2==4: Y( 0x8b ); Y( (reg1<<3)|reg2 ); Y( 0x24 )
      elif reg2==5: Y( 0x8b ); Y( 0x40|(reg1<<3)|reg2 ); Y( 0x00 )
      else: Y( 0x8b ); Y( (reg1<<3)|reg2 )
    elif a[:11]=='dword ptr [' and a[14:16]=='],' and a[16:] in REGS:
      # mov dword ptr [reg],reg
      reg1 = REGS[a[11:14]]
      reg2 = REGS[a[16:]]
      if reg1==4: Y( 0x89 ); Y( (reg2<<3)|reg1 ); Y( 0x24 )
      elif reg1==5: Y( 0x89 ); Y( 0x40|(reg2<<3)|reg1 ); Y( 0x00 )
      else: Y( 0x89 ); Y( (reg2<<3)|reg1 )
    elif a[3:15]==',dword ptr [' and a[18] in '+-' and a[-1]==']':
      # mov reg,dword ptr [reg+ofs]
      reg1 = REGS[a[:3]]
      reg2 = REGS[a[15:18]]
      ofs = immediate(a[18:-1])
      if len(ofs)==2: Y( 0x8b ); Y( 0x40|(reg1<<3)|reg2 ); YY( reg2==4, 0x24 ); Y1( ofs )
      else:           Y( 0x8b ); Y( 0x80|(reg1<<3)|reg2 ); YY( reg2==4, 0x24 ); Y4( ofs )
    elif a[:11]=='dword ptr [' and a[14] in '+-' and a[a.find('],')+2:] in REGS:
      # mov dword ptr [reg+ofs],reg
      sep = a.find('],')
      reg1 = REGS[a[11:14]]
      reg2 = REGS[a[sep+2:]]
      ofs = immediate(a[14:sep])
      if len(ofs)==2: Y( 0x89 ); Y( 0x40|(reg2<<3)|reg1 ); YY( reg1==4, 0x24 ); Y1( ofs )
      else:           Y( 0x89 ); Y( 0x80|(reg2<<3)|reg1 ); YY( reg1==4, 0x24 ); Y4( ofs )
    elif a[:10]=='byte ptr [' and a[13:15]=='],' and a[15:]=='al':
      # mov byte ptr [reg],al -- but not esp
      reg = REGS[a[10:13]]
      if reg!=4: Y( 0x88 ); Y( reg )
      else: print( '%d: ... '%l_no+w+' '+a+' - not implemented' )
    elif a[:13]=='al,byte ptr [' and a[16] in '+-' and a[-1]==']':
      # mov al,byte ptr [reg+ofs]
      reg = REGS[a[13:16]]
      ofs = immediate(a[16:-1])
      if len(ofs)==2: Y( 0x8a ); Y( 0x40|reg ); YY( reg==4, 0x24 ); Y1( ofs )
      else:           Y( 0x8a ); Y( 0x80|reg ); YY( reg==4, 0x24 ); Y4( ofs )
    elif a[:10]=='byte ptr [' and a[13:15]=='],' and a[15] in '-+0123456789':
      # mov byte ptr [reg],immed
      reg = REGS[a[10:13]] # esp -- not implemented, never esp (4) here
      imm = immediate1(a[15:])
      Y( 0xc6 ); Y( reg ); Y1( imm )
    elif a[:11]=='dword ptr [' and a[14] in '+-' and a[a.find('],')+2:][0] in '-+0123456789':
      # mov dword ptr [reg+ofs],immed (immed is always 4 bytes)
      sep = a.find('],')
      reg = REGS[a[11:14]]
      ofs = immediate(a[14:sep])
      imm = immediate4(a[sep+2:])
      if len(ofs)==2: Y( 0xc7 ); Y( 0x40|reg ); YY( reg==4, 0x24 ); Y1( ofs ); Y4( imm )
      else:           Y( 0xc7 ); Y( 0x80|reg ); YY( reg==4, 0x24 ); Y4( ofs ); Y4( imm )
    else:
      print( '%d: ... '%l_no+w+' '+a+' - not implemented' )
      Y( 0x90 )
  elif w=='movsx' and a[:14]=='eax,byte ptr [' and a[17] in '+-' and a[-1]==']':
    # movsx eax,byte ptr [reg+ofs]
    reg = REGS[a[14:17]]
    ofs = immediate(a[17:-1])
    if len(ofs)==2: Y( 0x0f ); Y( 0xbe ); Y( 0x40|reg ); YY( reg==4, 0x24 ); Y1( ofs )
    else:           Y( 0x0f ); Y( 0xbe ); Y( 0x80|reg ); YY( reg==4, 0x24 ); Y4( ofs )
  elif w=='lea' and a=='eax,[eax+4*ebx]':
    Y( 0x8d ); Y( 0x04 ); Y( 0x98 )
  elif w=='lea' and a=='eax,[ebx+4*eax]':
    Y( 0x8d ); Y( 0x04 ); Y( 0x83 )
  elif w=='lea' and a.startswith('eax,['):
    if a[8]==']':
      reg = REGS[a[5:8]]
      if reg==4:   Y( 0x8d ); Y( reg ); Y( 0x24 )
      elif reg==5: Y( 0x8d ); Y( 0x40|reg ); Y( 0x00 )
      else:        Y( 0x8d ); Y( reg )
    else: # assert a[8] in '+-'
      reg = REGS[a[5:8]]
      ofs = immediate(a[8:-1])
      if len(ofs)==2: Y( 0x8d ); Y( 0x40|reg ); YY( reg==4, 0x24 ); Y1( ofs )
      else:           Y( 0x8d ); Y( 0x80|reg ); YY( reg==4, 0x24 ); Y4( ofs )
  elif w in JMPS:
    if prep:
      add_jump( c_code, w=='jmp', a )
      Y( 0x00 ); Y( 0x00 ) # fake values to advance c_code
    else: # second pass, all jumps are resolved
      op = JMPS[w]
      idx = find_jump( c_code )
      if idx<0: print('%d: !!! '%l_no+'cannot be',hex(c_code))
      (_,is_jmp,is_short,lblidx) = jt[idx] # jump properties
      (_,tgt) = code_labels[lblidx]
      if is_short:
        diff = tgt - (c_code+2)
        if diff<0: diff += 256
        Y( op ); Y( diff )
      elif is_jmp:
        diff = tgt - (c_code+5)
        if diff<0: diff += 0x100000000
        Y( 0xe9 ); Y( diff&255 ); Y( (diff>>8)&255 ); Y( (diff>>16)&255 ); Y( diff>>24 )
      else: # conditional
        diff = tgt - (c_code+6)
        if diff<0: diff += 0x100000000
        Y( 0x0f ); Y( 0x10+op ); Y( diff&255 ); Y( (diff>>8)&255 ); Y( (diff>>16)&255 ); Y( diff>>24 )

  # TODO

  elif w=='call':
    Y( 0xe8 ); Y4( '00 00 00 00' )

  # data refs!

  else: print( '%d: ... '%l_no+w+' '+a )

def process_pseudocommand( l:str ): # TODO
  global c_sec
  if l=='.text':
    c_sec = 'code'
  elif l=='.bss':
    c_sec = 'bss'
  elif l=='.data':
    c_sec = 'data'
  elif l=='.section .rdata,"dr"':
    c_sec = 'rdata';
  elif l=='.cfi_startproc':
    # prepare code labels and jump table; also do this at the very code start
    start_proc_jt( c_code )
  elif l=='.cfi_endproc':
    # resolve jumps in the proc; also do this at the very end if no such command
    end_proc_jt()
  elif l.startswith('.align '): # + immed value
    pass
    #nops = (4-c_code%4)%4
    #if nops>0:
    #  print( "\n####   - - - - - - - - - - - - - - - "+'nop', end='', file=o )
    #  for i in range(nops):
    #    NL(); Y( 0x90 )
  elif l.startswith('.include '): # + filename in ""
    pass
  elif l.startswith('.long '): # + immed value or data label
    pass
  elif l.startswith('.ascii '): # + string in "". maybe strings and ints by ','
    pass
  elif l.startswith('.space '): # + immed value
    pass
  elif l.startswith('.globl '): # + label
    pass
  elif l.startswith('.def '): # + label; ...etc - always '.scl 2; type 32; .endef'
    pass
  elif l.startswith('.file ') or l.startswith('.intel_syntax ') or l.startswith('.ident '):
    pass
  else:
    if prep: print( '%d: ps: '%l_no+l )

if "todo"=="print canonical form":
  def process_label( l:str ): print( l+':' )
  def process_command( l:str ): print( ' '+l )
  def process_pseudocommand( l:str ): print( ' '+l )

def asm( t:str ):
  global l_no
  lines = t.replace('\r','').replace('\t',' ').split('\n')
  for l in lines:
    l_no += 1
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
    comment = t.find(' # ')    # comment: ' # '
    if comment>=0:
      t = t[:comment].rstrip()
    if t[0]=='.':
      process_pseudocommand( t )
    else:
      process_command( t )

# two passes
prep = True
c_code = 0
start_proc_jt( c_code )
with open( "all.s", "rt" ) as f:
  l_no = 0
  t = f.read()
  asm(t)
s_code_len = c_code

if not jt_proc_done:
  end_proc_jt()

prep = False
c_code = 0
start_proc_jt( c_code )
with open( "all.s", "rt" ) as f:
  l_no = 0
  t = f.read()
  asm(t)

o.close()

# reformat closer to objdump -d
with open( "o.pp", "wt" ) as o:
  with open( "o.lst", "rt" ) as f:
    c = ''
    for l in f:
      if l.startswith('####   '):
        c = l[37:].rstrip()
      elif c:
        if l.startswith('0000'): # label
          print( l.rstrip(), file=o )
        else:
          print( "%-44s%s" % (l.rstrip(),c), file=o )

print('--')
mn = 0
for n,_ in code_labels:
  if len(n)>mn: mn=len(n)
for n,a in code_labels:
  print( ('%-'+('%d'%(mn+1))+'s 0x%03x') % (n+':',a) )
print('--')
#for j in jt:
#  (a,jmp,sht,l) = j
#  (nm,tgt) = code_labels[l]
#  print("%3x: %s %s #%d: %3x %s" % (a,'-j'[jmp],'-s'[sht],l,tgt,nm) )
