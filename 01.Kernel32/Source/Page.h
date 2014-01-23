#ifdef  __PAGE_H__
#define __PAGE_H__

#define PAGE_FLAGS_P        0x00000001 //Present
#define PAGE_FLAGS_RW       0x00000002 //Read_Write
#define PAGE_FLAGS_US       0x00000004 //User_Supervisor
#define PAGE_FLAGS_PWT      0x00000008 //Page level Write-through
#define PAGE_FLAGS_PCD      0x00000010 //Page level Cache Disable
#define PAGE_FLAGS_A        0x00000020 //Accessed
#define PAGE_FLAGS_D        0x00000040 //Dirty
#define PAGE_FLAGS_PS       0x00000080 //Page Size
#define PAGE_FLAGS_G        0x00000100 //Global
#define PAGE_FLAGS_PAT      0x00001000 //Page Attribute Table Index
#define PAGE_FLAGS_EXB      0x80000000 //Execute Disable bit
#define PAGE_FLAGS_DEFAULT (PAGE_FLAGS_P | PAGE_FLAGS_RW)
#define PAGE_TABLESIZE      Ox1000
#define PAGE_MAXENTRYCOUNT  512

#pragma pack(push, 1)

typedef struct kPageTableEntryStruct{
    DWORD dwUpper;
    DWORD dwLower;
}PDTEntry, PDPTEntry, PML4Entry, PTEntry;

#pragma pack(pop)

void kInitializePageTable(void);
void kSetPageEntryData(PTENTRY* pstEntry, DWORD dwUpperBaseAddress, DWORD dwLowerBaseAddress, 
        DWORD dwLowerFlags, DWORD dwUpperFlags);

#endif  __PAGE_H__
