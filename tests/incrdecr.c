int** x;
int* y[6];

int main()
{
  int i;
  int* p;
  int** q;
  char* s;
  int* m[8];

  i;                   // mov eax,DWORD PTR [ebp-4] # i

  i = 1;               // mov eax,1
                       // mov DWORD PTR [ebp-4],eax # i

  ++i;                 // mov eax,DWORD PTR [ebp-4] # i
                       // add eax,1
                       // mov DWORD PTR [ebp-4],eax # i

  ++p;                 // mov eax,DWORD PTR [ebp-8] # p
                       // add eax,4
                       // mov DWORD PTR [ebp-8],eax # p

  --p;                 // mov eax,DWORD PTR [ebp-8] # p
                       // sub eax,4
                       // mov DWORD PTR [ebp-8],eax # p

  *p;                  // mov eax,DWORD PTR [ebp-8] # p
                       // mov eax,DWORD PTR [eax]
                       //
  *p = 2;              // mov eax,DWORD PTR [ebp-8] # p
                       // mov ebx,eax
                       // mov eax,2
                       // mov DWORD PTR [ebx],eax
  222;

  *p = *p + 1;         // mov eax,DWORD PTR [ebp-8] # p
                       // push eax
                       // mov eax,DWORD PTR [ebp-8] # p
                       // mov eax,DWORD PTR [eax]
                       // add eax,1
                       // pop ebx
                       // mov DWORD PTR [ebx],eax

  ++*p;                // mov eax,DWORD PTR [ebp-8] # p
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // add eax,1
                       // mov DWORD PTR [ebx],eax

  --*p;                // mov eax,DWORD PTR [ebp-8] # p
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // sub eax,1
                       // mov DWORD PTR [ebx],eax
  333;

  *(p+1) = *(p+1) + 1; // mov eax,DWORD PTR [ebp-8] # p
                       // add eax,4
                       // push eax
                       // mov eax,DWORD PTR [ebp-8] # p
                       // add eax,4
                       // mov eax,DWORD PTR [eax]
                       // add eax,4
                       // pop ebx
                       // mov DWORD PTR [ebx],eax


  ++*(p+1);            // mov eax,DWORD PTR [ebp-8] # p
                       // add eax,4
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // add eax,1
                       // mov DWORD PTR [ebx],eax

  --*(p+1);            // mov eax,DWORD PTR [ebp-8] # p
                       // add eax,4
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // sub eax,1
                       // mov DWORD PTR [ebx],eax
  444;

  q = q + 1;           // mov eax,DWORD PTR [ebp-12] # q
                       // add eax,4
                       // mov DWORD PTR [ebp-12],eax # q

  ++q;                 // mov eax,DWORD PTR [ebp-12] # q
                       // add eax,4
                       // mov DWORD PTR [ebp-12],eax # q

  *q = *q + 1;         // mov eax,DWORD PTR [ebp-12] # q
                       // push eax
                       // mov eax,DWORD PTR [ebp-12] # q
                       // mov eax,DWORD PTR [eax]
                       // add eax,4
                       // pop ebx
                       // mov DWORD PTR [ebx],eax

  ++*q;                // mov eax,DWORD PTR [ebp-12] # q
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // add eax,4
                       // mov DWORD PTR [ebx],eax

  --*q;                // mov eax,DWORD PTR [ebp-12] # q
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // sub eax,4
                       // mov DWORD PTR [ebx],eax

  q[10] = q[10] + 1;   // mov eax,DWORD PTR [ebp-12] # q
                       // add eax,40
                       // push eax
                       // mov eax,DWORD PTR [ebp-12] # q
                       // add eax,40
                       // mov eax,DWORD PTR [eax]
                       // add eax,4
                       // pop ebx
                       // mov DWORD PTR [ebx],eax

  ++q[10];             // mov eax,DWORD PTR [ebp-12] # q
                       // add eax,40
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // add eax,4
                       // mov DWORD PTR [ebx],eax

  --q[10];             // mov eax,DWORD PTR [ebp-12] # q
                       // add eax,40
                       // mov ebx,eax
                       // mov eax,DWORD PTR [ebx]
                       // sub eax,4
                       // mov DWORD PTR [ebx],eax
  555;

  ++s;          // mov eax,DWORD PTR [ebp-16] # s
                // add eax,1
                // mov DWORD PTR [ebp-16],eax # s

  --s;          // mov eax,DWORD PTR [ebp-16] # s
                // sub eax,1
                // mov DWORD PTR [ebp-16],eax # s

  ++*s;         // mov eax,DWORD PTR [ebp-16] # s
                // mov ebx,eax
                // movsx eax,BYTE PTR [ebx]
                // sub eax,1
                // mov BYTE PTR [ebx],al

  --*s;         // mov eax,DWORD PTR [ebp-16] # s
                // mov ebx,eax
                // movsx eax,BYTE PTR [ebx]
                // sub eax,1
                // mov BYTE PTR [ebx],al

  ++s[2];       // mov eax,DWORD PTR [ebp-16] # s
                // add eax,2
                // mov ebx,eax
                // movsx eax,BYTE PTR [ebx]
                // add eax,1
                // mov BYTE PTR [ebx],al

  --s[2];       // mov eax,DWORD PTR [ebp-16] # s
                // add eax,2
                // mov ebx,eax
                // movsx eax,BYTE PTR [ebx]
                // sub eax,1
                // mov BYTE PTR [ebx],al

  ++*(s+3);     // mov eax,DWORD PTR [ebp-16] # s
                // add eax,3
                // mov ebx,eax
                // movsx eax,BYTE PTR [ebx]
                // add eax,1
                // mov BYTE PTR [ebx],al

  --*(s+3);     // mov eax,DWORD PTR [ebp-16] # s
                // add eax,3
                // mov ebx,eax
                // movsx eax,BYTE PTR [ebx]
                // sub eax,1
                // mov BYTE PTR [ebx],al
  666;

  ++s[0];       // mov eax,DWORD PTR [ebp-16] # s
                // mov ebx,eax
                // movsx eax,BYTE PTR [ebx]
                // add eax,1
                // mov BYTE PTR [ebx],al

  ++p[0];       // mov eax,DWORD PTR [ebp-8] # p
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,1
                // mov DWORD PTR [ebx],eax

  ++q[0];       // mov eax,DWORD PTR [ebp-12] # q
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,4
                // mov DWORD PTR [ebx],eax

  --s[0];       // ... sub eax,1
  --p[0];       // ... sub eax,1
  --q[0];       // ... sub eax,4

  777;

  ++x;          // mov eax,DWORD PTR _x
                // add eax,4
                // mov DWORD PTR _x,eax

  ++*x;         // mov eax,DWORD PTR _x
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,4
                // mov DWORD PTR [ebx],eax

  ++**x;        // mov eax,DWORD PTR _x
                // mov eax,DWORD PTR [eax]
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,1
                // mov DWORD PTR [ebx],eax

  --x;          // ... sub eax,4
  --*x;         // ... sub eax,4
  --**x;        // ... sub eax,1

  ++*y;         // mov eax,OFFSET FLAT:_y
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,4
                // mov DWORD PTR [ebx],eax

  ++**y;        // mov eax,OFFSET FLAT:_y
                // mov eax,DWORD PTR [eax]
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,1
                // mov DWORD PTR [ebx],eax

  --*y;         // ... sub eax,4
  --**y;        // ... sub eax,1

  ++*m;         // lea eax,[ebp-48] # m
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,4
                // mov DWORD PTR [ebx],eax

  ++**m;        // lea eax,[ebp-48] # m
                // mov eax,DWORD PTR [eax]
                // mov ebx,eax
                // mov eax,DWORD PTR [ebx]
                // add eax,1
                // mov DWORD PTR [ebx],eax

  --*m;         // ... sub eax,4
  --**m;        // ... sub eax,1

  return 0;
}
