/*
 * fileName: myLinkList.c
 * date: 2020/11/14
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 栈上的操作的具体实现
*/

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Status InitStack(Stack *S)
{
    S->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !S->base ) {
        fprintf(stderr, "Assign memory failed!Please try again!\n");
        exit(ERROR);
    }
    S->top = S->base;
    S->stackSize = STACK_INIT_SIZE;
    return OK;
}

Status DestroyStack(Stack *S)
{
    free(S->base);
    S->base = NULL;
    S->top = NULL;
    S->stackSize = 0;
    return OK;
}

Status ClearStack(Stack *S)
{
    if( StackEmpty(S) ) // 若栈已空
    {
        return OK;
    }
    S->top = S->base;
    return OK;
}

Status StackEmpty(Stack *S)
{
    return S->top == S->base;    
}

int StackLength(Stack *S)
{
    return S->top - S->base;
}

Status GetTop(Stack *S, ElemType *e)
{
    if(StackEmpty(S))
    {
        fprintf(stderr, "The stack is empty, exit!\n");
        exit(ERROR);
    } 

    *e = *(S->top - 1);
    return OK;
}

Status Push(Stack *S, ElemType e) 
{
    if(S->top - S->base >= S->stackSize) // 栈满
    {
        S->base = (ElemType *)realloc(S->base, (S->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !S->base )
        {
            fprintf(stderr, "Reassign memory failed!Please try again!\n");
            exit(ERROR);
        }
        S->top = S->base + S->stackSize;
        S->stackSize += STACKINCREMENT;
    }

    *S->top++ = e;
    return OK;
}

Status Pop(Stack *S, ElemType *e)
{
    if(StackEmpty(S))
    {
        fprintf(stderr, "The stack is empty, exit!\n");
        exit(ERROR);
    }

    *e = *--S->top;
    return OK;
}

Status OutElem(ElemType *e)
{
    printf("%d ", *e);
    return OK;
}


Status StackTraverse(Stack *S, Status (*visit)(ElemType *e)) // 从栈底到栈顶遍历
{
    ElemType *p = NULL;
    printf("从栈底到栈顶遍历：\n");
    for (p = S->base; p != S->top; p++)
    {
        if( !visit(p) )
        {
            fprintf(stderr, "Visit failed!\n");
            exit(ERROR);
        }
    }
    return OK;
}

