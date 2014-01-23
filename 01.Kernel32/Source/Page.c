#include "Page.h"

void kInitializePageTable(void);
void kSetPageEntryData(PTENTRY* pstEntry, DWORD dwUpperBaseAddress, DWORD dwLowerBaseAddress, 
        DWORD dwLowerFlags, DWORD dwUpperFlags);
