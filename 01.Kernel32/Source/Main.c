/**
 *  file    Main.c
 *  date    2014/1/14
 *  author  paganinist
 *          Copyright(c)2014 All rights reserved by paganinist
 *  brief   C 언어로 작성된 커널의 엔트리 포인트 파일
 */

#include "Types.h"
#include "Page.h"
BOOL kIsMemoryAvailable(void);
void kPrintString( int iX, int iY, const char* pcString );
BOOL kInitialize64Area(void);
/**
 *  아래 함수는 C 언어 커널의 시작 부분임
 *      반드시 다른 함수들 보다 가장 앞쪽에 존재해야 함
 */
void Main( void )
{
    
    kPrintString(0, 3, "C Language Kernel Started...........[Pass]" );
  
    kPrintString(0, 4, "Minimum Memory Size Check...........[    ]");
    if(kIsMemoryAvailable() == FALSE)
    {
        kPrintString(37,4, "Fail");
        kPrintString(0, 5, "Minimum Memory not Available.....");
        while(1);
    }
    else
    {
        kPrintString(37,4, "Pass");
    }

    kPrintString(0, 5, "IA-32e Kernel Initialized...........[    ]");

    if(kInitialize64Area() == FALSE)
    {
        kPrintString(37,5, "Fail");
        kPrintString(0, 6, "IA-32E Kernel Initialized Failed.....");
        while(1);
    }
    else
    {
        kPrintString(37,5, "Pass");
    }
   
    while( 1 ) ;
}

/**
 *  문자열을 X, Y 위치에 출력
 */

BOOL kInitialize64Area(void)
{
    DWORD* KernelCounter;

    KernelCounter = (DWORD*)0x100000;

    while((DWORD)KernelCounter < 0x600000)
    {
        *KernelCounter = 0x00;

        if(*KernelCounter != 0)
        {
            return FALSE;
        }
        KernelCounter++;
    }
    

    return TRUE;
}

BOOL kIsMemoryAvailable(void)
{

    DWORD* KernelCounter;
    KernelCounter = (DWORD*)0x100000;

    while((DWORD)KernelCounter < 0x4000000)
    {
        *KernelCounter = 0x1234;
        if(*KernelCounter != 0x1234)
        {
            return FALSE;
        }
        KernelCounter += 0x100000;

    }

    return TRUE;
}

void kPrintString( int iX, int iY, const char* pcString )
{
    CHARACTER* pstScreen = ( CHARACTER* ) 0xB8000;
    int i;
    
    // X, Y 좌표를 이용해서 문자열을 출력할 어드레스를 계산
    pstScreen += ( iY * 80 ) + iX;
    
    // NULL이 나올 때까지 문자열 출력
    for( i = 0 ; pcString[ i ] != 0 ; i++ )
    {
        pstScreen[ i ].bCharactor = pcString[ i ];
    }
}

