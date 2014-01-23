/**
 *  file    Main.c
 *  date    2014/1/14
 *  author  paganinist
 *          Copyright(c)2014 All rights reserved by paganinist
 *  brief   C ���� �ۼ��� Ŀ���� ��Ʈ�� ����Ʈ ����
 */

#include "Types.h"
#include "Page.h"
BOOL kIsMemoryAvailable(void);
void kPrintString( int iX, int iY, const char* pcString );
BOOL kInitialize64Area(void);
/**
 *  �Ʒ� �Լ��� C ��� Ŀ���� ���� �κ���
 *      �ݵ�� �ٸ� �Լ��� ���� ���� ���ʿ� �����ؾ� ��
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
 *  ���ڿ��� X, Y ��ġ�� ���
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
    
    // X, Y ��ǥ�� �̿��ؼ� ���ڿ��� ����� ��巹���� ���
    pstScreen += ( iY * 80 ) + iX;
    
    // NULL�� ���� ������ ���ڿ� ���
    for( i = 0 ; pcString[ i ] != 0 ; i++ )
    {
        pstScreen[ i ].bCharactor = pcString[ i ];
    }
}

