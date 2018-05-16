#!/usr/bin/python
import sys
for s in sys.argv[1:]:
  o = b""
  k = False
  with open(s,"rb") as f:
    for t in f:
      while b"\r\n" in t: k = True; t = t.replace(b"\r\n",b"\n")
      o += t
  if k:
    with open(s,"wb") as f: f.write( o )
