int aa[10]; int* pp; int* qq;

int main(int k)
{
  int a[10]; int* p; int* q; int n; char* d; char* s;

  // below is GCC code. mine must be the same, except it's based on EBP

  pp = aa;      // mov DWORD PTR _pp, OFFSET FLAT:_aa

  qq = pp+1;    // mov eax, DWORD PTR _pp
                // add eax, 4
                // mov DWORD PTR _qq, eax

  p = a;        // lea eax, [esp+4]
                // mov DWORD PTR [esp+60], eax

  q = p + 1;    // mov eax, DWORD PTR [esp+60]
                // add eax, 4
                // mov DWORD PTR [esp+56], eax

  ++p;          // add DWORD PTR [esp+60], 4

  n = a[k];     // mov eax, DWORD PTR [ebp+8]
                // mov eax, DWORD PTR [esp+4+eax*4]
                // mov DWORD PTR [esp+52], eax

  ++n;          // add DWORD PTR [esp+52], 1

  s = "ab";     // mov DWORD PTR [esp+48], OFFSET FLAT:LC0

  *d = *s;      // mov eax, DWORD PTR [esp+48]
                // movzx edx, BYTE PTR [eax]
                // mov eax, DWORD PTR [esp+44]
                // mov BYTE PTR [eax], dl

  *d = *s+5;    // mov eax, DWORD PTR [esp+48]
                // movzx eax, BYTE PTR [eax]
                // add eax, 5
                // mov edx, eax
                // mov eax, DWORD PTR [esp+44]
                // mov BYTE PTR [eax], dl

  ++*d;         // mov eax, DWORD PTR [esp+44]
                // movzx eax, BYTE PTR [eax]
                // add eax, 1
                // mov edx, eax
                // mov eax, DWORD PTR [esp+44]
                // mov BYTE PTR [eax], dl

  --*s;         // mov eax, DWORD PTR [esp+48]
                // movzx eax, BYTE PTR [eax]
                // sub eax, 1
                // mov edx, eax
                // mov eax, DWORD PTR [esp+48]
                // mov BYTE PTR [eax], dl

  ++a[k];       // mov eax, DWORD PTR [ebp+8]
                // mov eax, DWORD PTR [esp+4+eax*4]
                // lea edx, [eax+1] # increment
                // mov eax, DWORD PTR [ebp+8]
                // mov DWORD PTR [esp+4+eax*4], edx

  --d[k];       // mov edx, DWORD PTR [ebp+8]
                // mov eax, DWORD PTR [esp+44]
                // add eax, edx
                // movzx edx, BYTE PTR [eax]
                // sub edx, 1
                // mov BYTE PTR [eax], dl

  char e,f;

  return qq-q;  // mov eax, DWORD PTR _qq
                // mov edx, eax
                // mov eax, DWORD PTR [esp+56]
                // sub edx, eax
                // mov eax, edx
                // sar eax, 2
}
