/*
 * fileName: myLinkList.c
 * date: 2020/11/14
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 栈的数据结构定义与操作的接口
*/

#ifndef _STACK_H_
#define _STACK_H_

#define STACK_INIT_SIZE 100 // 初始分配量
#define STACKINCREMENT 10 // 增量

#include "Status.h"

typedef struct
{
    ElemType *base; // 栈底指针
    ElemType *top; // 栈顶指针
    int stackSize; // 已分配的储存空间，以元素为单位
}Stack;

Status InitStack(Stack *S);
Status DestroyStack(Stack *S);
Status ClearStack(Stack *S);
Status StackEmpty(Stack *S);
int StackLength(Stack *S);
Status GetTop(Stack *S, ElemType *e);
Status Push(Stack *S, ElemType e);
Status Pop(Stack *S, ElemType *e);
Status OutElem(ElemType *e);
Status StackTraverse(Stack *S, Status (*visit)(ElemType *e));

#endif