/*
 * fileName: Main.c
 * date: 2020/10/10
 * compiler: GCC 9.2.0
 * auther: JunyiYang-杨竣轶
 * number: 1810730229
 * codeFormat: UTF-8
 * compiler cmd: gcc universal/myError.c myLinkList.c Main.c -o Main
 * description: 入口主函数
*/

#include <stdio.h>
#include <stdlib.h>
#include "universal/status.h"
#include "myLinkList.h" 

int main(int argc, char *argv[])
{
	LinkList LA = NULL;
    LinkList LB = NULL;
    LinkList LC = NULL;
	
    fprintf(stdout, "Create linklist head LA:\n");
	CreateList_head( &LA );
    ListTraverse(LA , outElem );
    
    printf("\n");
    fprintf(stdout, "Create linklist tail LB:\n");
    CreateList_tail( &LB );
    ListTraverse(LB , outElem );
    
    printf("\n");
    fprintf(stdout, "Mergerlist LA and LB to LC:\n");
    InitList_L( &LC) ;
    MergeList_L( LA , LB, LC);    
    ListTraverse(LC , outElem );

    printf("\n");
    fprintf(stdout, "Destroy LC...\n");
    DestroyList_L(&LC);
    fprintf(stdout, "Destroy LC Successfully!\n");

	return EXIT_SUCCESS;
}