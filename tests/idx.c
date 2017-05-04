char cag[5]; // .comm _cag, 5, 2
char* cpg;   // .comm _cpg, 4, 2

int iag[10]; // .comm _iag, 40, 5
int* ipg;    // .comm _ipg, 4, 2

int main( int ac, char** av )
{
  char cal[5];
  char* cpl;

  int ial[10];
  int* ipl;

  char c;
  int i;
  int k = ac; // mov eax, DWORD PTR [ebp+8]
              // mov DWORD PTR [esp+76], eax

  cpl = cag;  // mov DWORD PTR [esp+72], OFFSET FLAT:_cag
  cpg = cal;  // lea eax, [esp+55] # cal
              // mov DWORD PTR _cpg, eax
  ipl = iag;  // mov DWORD PTR [esp+68], OFFSET FLAT:_iag
  ipg = ial;  // lea eax, [esp+12] # ial
              // mov DWORD PTR _ipg, eax

  c = cag[k]; // mov eax, DWORD PTR [esp+76]
              // add eax, OFFSET FLAT:_cag
              // {*BYTE} === movzx eax, BYTE PTR [eax]
              // mov BYTE PTR [esp+67], al
  c = cal[k]; // lea edx, [esp+55] # cal
              // mov eax, DWORD PTR [esp+76]
              // add eax, edx
              // {*BYTE}
              // mov BYTE PTR [esp+67], al

  i = iag[k]; // mov eax, DWORD PTR [esp+76]
              // mov eax, DWORD PTR _iag[0+eax*4]
              // mov DWORD PTR [esp+60], eax
  i = ial[k]; // mov eax, DWORD PTR [esp+76]
              // mov eax, DWORD PTR [esp+12+eax*4]
              // mov DWORD PTR [esp+60], eax

  c = *cpg;   // mov eax, DWORD PTR _cpg
              // {*BYTE}
              // mov BYTE PTR [esp+67], al
  i = *cpl;   // mov eax, DWORD PTR [esp+72]
              // {*BYTE}
              // movsx eax, al
              // mov DWORD PTR [esp+60], eax

  c = *ipg;   // mov eax, DWORD PTR _ipg
              // {*DWORD} === mov eax, DWORD PTR [eax]
              // mov BYTE PTR [esp+67], al
  i = *ipl;   // mov eax, DWORD PTR [esp+68]
              // {*DWORD}
              // mov DWORD PTR [esp+60], eax

  cag[k] = c; // mov eax, DWORD PTR [esp+76]
              // lea edx, _cag[eax]
              // movzx eax, BYTE PTR [esp+67]
              // mov BYTE PTR [edx], al
  cal[k] = i; // mov eax, DWORD PTR [esp+60]
              // mov ecx, eax
              // lea edx, [esp+55]
              // mov eax, DWORD PTR [esp+76]
              // add eax, edx
              // mov BYTE PTR [eax], cl

  iag[k] = c; // movsx edx, BYTE PTR [esp+67]
              // mov eax, DWORD PTR [esp+76]
              // mov DWORD PTR _iag[0+eax*4], edx
  ial[k] = i; // mov eax, DWORD PTR [esp+76]
              // mov edx, DWORD PTR [esp+60]
              // mov DWORD PTR [esp+12+eax*4], edx

  *cpg = c;   // mov eax, DWORD PTR _cpg
              // movzx edx, BYTE PTR [esp+67]
              // mov BYTE PTR [eax], dl
  *cpl = i;   // mov eax, DWORD PTR [esp+60]
              // mov edx, eax
              // mov eax, DWORD PTR [esp+72]
              // mov BYTE PTR [eax], dl

  *ipg = c;   // mov eax, DWORD PTR _ipg
              // movsx edx, BYTE PTR [esp+67]
              // mov DWORD PTR [eax], edx
  *ipl = i;   // mov eax, DWORD PTR [esp+68]
              // mov edx, DWORD PTR [esp+60]
              // mov DWORD PTR [eax], edx

  char** cpp;
  int** ipp;

  ++c;        // movzx eax, BYTE PTR [esp+67]
              // add eax, 1
              // mov BYTE PTR [esp+67], al
  ++i;        // add DWORD PTR [esp+60], 1

  ++cpl;      // add DWORD PTR [esp+72], 1
  ++ipl;      // add DWORD PTR [esp+68], 4

  ++cpp;      // add DWORD PTR [esp+56], 4
  ++ipp;      // add DWORD PTR [esp+52], 4

  ++*cpl;     // mov eax, DWORD PTR [esp+72]
              // movzx eax, BYTE PTR [eax]
              // add eax, 1
              // mov edx, eax
              // mov eax, DWORD PTR [esp+72]
              // mov BYTE PTR [eax], dl

  ++*ipl;     // mov eax, DWORD PTR [esp+68]
              // mov eax, DWORD PTR [eax]
              // lea edx, [eax+1]
              // mov eax, DWORD PTR [esp+68]
              // mov DWORD PTR [eax], edx

  ++*cpp;     // mov eax, DWORD PTR [esp+56]
              // mov eax, DWORD PTR [eax]
              // lea edx, [eax+1]
              // mov eax, DWORD PTR [esp+56]
              // mov DWORD PTR [eax], edx

  ++*ipp;     // mov eax, DWORD PTR [esp+52]
              // mov eax, DWORD PTR [eax]
              // lea edx, [eax+4]
              // mov eax, DWORD PTR [esp+52]
              // mov DWORD PTR [eax], edx

  --*ipl;     // mov eax, DWORD PTR [esp+68]
              // mov eax, DWORD PTR [eax]
              // lea edx, [eax-1]
              // mov eax, DWORD PTR [esp+68]
              // mov DWORD PTR [eax], edx
  return 0;
}

