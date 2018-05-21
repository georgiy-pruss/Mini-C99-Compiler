import sys
for l in sys.stdin:
  l = l.rstrip()
  t = l.find('\t')
  while t>=0:
    if t==41: s = 3 # to mimic exact format of o.pp
    else: s = 8 - t % 8
    l = l[:t] + ' '*s + l[t+1:]
    t = l.find('\t')
  print(l.replace('DWORD PTR','dword ptr').replace('BYTE PTR','byte ptr'))
