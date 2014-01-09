#include "Types.h"

void main(void)
{


    while(1);
}

void sPrintString(int iX, int iY, const char *pString)
{
    CHARACTER* pstScreen = (CHARACTER*) 0xB8000;
    pstScreen += (iY * 80) + iX;

    int i = 0;
    for(i = 0; pString[i] != 0; i++)
    {
        pstScreen[i].sChar = pString[i];
    }

}

