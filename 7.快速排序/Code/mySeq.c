/*
 * fileName: mySeq.c
 * date: 2020/9/28
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 顺序表上操作的具体实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mySeq.h" // 线性表

Status initList(SqList *L) // 初始化表，测试通过！ 
{
    L->base = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); // 在堆上分配基址空间
    if( !existList(L) ) // 分配失败，异常处理
    {
        fprintf(stderr,"ERROR_CODE: -2 ERROR_MESSAGE: OVERFLOW!\n"); // 溢出
        return OVERFLOW;
    }
    memset(L->base, 0x00, LIST_INIT_SIZE * sizeof(ElemType)); // 把内存置0
    L->length = 0; // 当前线性表长度为0
    L->listSize = LIST_INIT_SIZE; // 初始储存容量为初始分配量

    return OK;
}
Status existList(const SqList *L) // 判断线性表是否存在，测试通过！ 
{
    if( !L->base ) // 不存在
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }  
}
Status destroyList(SqList *L) // 销毁线性表
{
    if( !existList(L) ) // 线性表不存在，返回错误
    {
        fprintf(stderr,"ERROR_CODE: 0 ERROR_MESSAGE: List is not exists!Please initialize list first!\n"); // 错误
        return ERROR;
    }
    
    free(L->base); // 释放堆内存
    L->base = NULL; // 置空
    L->length = 0;
    L->listSize = 0;
    
    return OK;
}

Status outElem(const ElemType *e) // 输出元素
{
    fprintf(stdout, "%d ", *e);
    return OK;
}

Status outSqList(const SqList *L) // 输出线性表
{
    if( !existList(L) )
    {
        fprintf(stderr,"ERROR_CODE: 0 ERROR_MESSAGE: List is not exists!Please initialize list first!\n");
        return ERROR;
    }

    int iter;
    for(iter = 0; iter != L->length; ++iter)
    {
        printf("%d ", *(L->base + iter));
    }
    return OK;
}
Status inputNode(SqList *L) // 输入插入节点
{
    char ch; // 判断字符标志
    ElemType *p = NULL;
    int iter = 0;
    ElemType input; // 输入的数字
    do
    {
        if (scanf("%d%c", &input, &ch) < 2) // 输入失败
        {
            fprintf(stderr, "INPUT_ERROR_MESSAGE: Please input a correct number.\n");
            fflush(stdin); // 清空输入缓冲区
            continue;
        }

        if( !L->length ) // 如果表空
        {
            listInsert(L, 1, &input);
            continue;
        }

        p = L->base;
        // for(iter = 0; iter < L->length; iter++) // 插入排序
        // {
        //     if(input <= *p)
        //     {
        //         break;
        //     }
        //     p++;
        // }
        listInsert(L, p - L->base + 1,&input);
    } while ((int)ch != 35);
    p = NULL;
    return OK;
}

int listLength(const SqList *L) // 返回线性表长度的接口，通过
{
    if( !existList(L) )
    {
        fprintf(stderr,"ERROR_CODE: 0 ERROR_MESSAGE: List is not exists!Please initialize list first!\n");
        return ERROR;
    }

    return L->length;
}

Status listInsert(SqList *L, int i, const ElemType *e) // 插入元素（在i前面插入元素）
{
    ElemType *newbase = NULL;
    ElemType *p = NULL, *q = NULL;

    if( !existList(L) )
    {
        fprintf(stderr,"ERROR_CODE: 0 ERROR_MESSAGE: List is not exists!Please initialize list first!\n");
        return ERROR;
    }

    if( i < 1 || i > listLength(L) + 1)
    {
        fprintf(stderr,"ERROR:Insert Failed!\t Note: No >= 1 and No < %d!\n", L->length + 1);
		return ERROR ;
    }

    if(L->length >= L->listSize)
    {
        newbase = (ElemType *)realloc(L->base, (L->listSize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase)
        {
            fprintf(stdout, "ERROR: Failed to assign space.\n");
            exit(OVERFLOW);
        }
        L->base = newbase;
        L->listSize += LISTINCREMENT;
    }

    q = L->base + i -1;
    for(p = L->base + L->length - 1; p >= q; p--)
    {
        *(p + 1) = *p;
    }

    *q = *e;
    ++L->length;

    return OK;
}

Status createList(SqList *L) // 创建线性表
{
    initList(L); // 初始化
    fprintf(stdout, "Please input integer data no more than %d end with the '#' key:\n", L->listSize);

    inputNode(L); // 输入节点
    return OK;
}


