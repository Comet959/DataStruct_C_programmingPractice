/*
 * fileName: mySeq.c
 * date: 2020/9/28
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 线性表上操作的具体实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "mySeq.h" // 线性表
#include "status.h" // 状态宏
#include "myError.h" // 错误输出


Status initList(SqList *L) // 初始化表，测试通过！ 
{
    L->base = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType)); // 在堆上分配基址空间
    if( !existList(L) ) // 分配失败，异常处理
    {
        errOverFlow(); // 溢出
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
        errError(); // 错误
        return ERROR;
    }
    
    free(L->base); // 释放堆内存
    L->base = NULL; // 置空
    L->length = 0;
    L->listSize = 0;
    
    return OK;
}

Status clearList(SqList *L) // 清空线性表，通过
{
    if( !existList(L) ) // 线性表不存在
    {
        errError();
        return ERROR;
    }
    
    memset(L->base, 0x00, L->listSize * sizeof(ElemType));
    L->length = 0;

    return OK;
}

Status listEmpty(const SqList *L) // 判断线性表长度是否为0，通过
{
    if( !existList(L) ) // 线性表不存在
    {
        errError();
        return ERROR;
    }

    if(L->length == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }   
}

int listLength(const SqList *L) // 返回线性表长度的接口，通过
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }

    return L->length;
}

Status getElem(const SqList *L, int i, ElemType *e) // 获取元素，通过
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }

    if( i < 1 || i > L->length ) // 判断长度
    {
        errBound(); // 越界
        return ERROR;
    }
    *e = *(L->base + i - 1);

    return OK;
}

Status compareElem(const ElemType *e1, const ElemType *e2) // 比较两个元素，通过
{
    int flags = 0;
    if( *e1 == *e2 )
    {
        flags = 0;
    }
    if( *e1 > *e2 )
    {
        flags = 1;
    }
    if( *e1 < *e2 )
    {
        flags = -1;
    }
    return flags;   
}

int locateElem(const SqList *L, const ElemType *e, Status (*compareElem)(const ElemType *, const ElemType *)) // 定位元素，通过！
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }

    int iter = 0; // 迭代器
    int flags = 0;
    ElemType *p = L->base; // 指向基地址的指针

    for(iter = 0; iter != L->length ; ++iter)
    {
        if( !(*compareElem)(p++, e) )  //找到了
        {
            flags = 0;
            break;
        }
        else
        {
            flags = 1; // 没找到
        }
    }

    if(flags == 1)
    {
        return 0; // 未找到
    }
    else
    {
        return iter + 1; // 位置
    }
}

Status priorElem(const SqList *L, const ElemType *cure_e, ElemType *pre_e) // 访问前驱元素，通过
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }

    int i = -1;
    i = locateElem(L, cure_e, compareElem);
    if( i == 1 ) // 首元素
    {
        pre_e = NULL;
        fprintf(stderr, "ERROR_MESSAGE: The element %d is the first element, there is no precursor element!\n", *cure_e);
        return FALSE; //无前驱
    }
    else if(i == 0)
    {
        pre_e = NULL;
        fprintf(stderr, "ERROR_MESSAGE: The element %d does not exist in the table, please enter the correct elemtype!\n", *cure_e);
        return ERROR;
    }
    else
    {
        *pre_e = *(L->base + i - 2);
        return OK;
    }
}

Status nextElem(const SqList *L, const ElemType *cur_e, ElemType *next_e) // 访问后继元素，通过
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }

    int i = 0;
    i = locateElem(L, cur_e, compareElem);
    if(i == listLength(L))
    {
        next_e = NULL; // 无后继
        fprintf(stderr, "ERROR_MESSAGE: The element %d is the last element, there is no subsequent element!\n", *cur_e);
        return FALSE;
    }
    else if(i == 0)
    {
        next_e = NULL; // 元素不存在
        fprintf(stderr, "ERROR_MESSAGE: The element %d does not exist in the table, please enter the correct elemtype!\n", *cur_e);
        return ERROR;
    }
    else
    {
        *next_e = *(L->base + i);
        return OK;
    }
}
Status listInsert(SqList *L, int i, const ElemType *e) // 插入元素（在i前面插入元素），测试通过！
{
    ElemType *newbase = NULL;
    ElemType *p = NULL, *q = NULL;

    if( !existList(L) )
    {
        errError();
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

Status listDelete(SqList *L, int i, ElemType *e) // 删除元素，通过
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }

    int length = 0;
    ElemType *p = NULL ;
	ElemType *q = NULL ;

    if (!L->base || !L->length)
    {
        fprintf(stderr, "ERROR_MESSAGE: No elements can be deleted.\n");
        return ERROR;
    }

    if(i < 1 || i > L->length)
    {
        errBound();
        return ERROR;
    }

    p = L->base + i - 1;
    *e = *p;

    for(q = L->base + L->length - 1; p <= q; p++)
    {
        *p = *(p + 1);
    }
    --L->length;

    return OK;
}

Status outElem(const ElemType *e) // 输出元素，通过
{
    fprintf(stdout, "%d ", *e);
    return OK;
}

Status outSqList(const SqList *L) // 输出线性表，通过
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }

    int iter;
    for(iter = 0; iter != L->length; ++iter)
    {
        printf("%d ", *(L->base + iter));
    }
    return OK;
}

Status listTraverse(const SqList *L, Status (*pvisit)(const ElemType *)) // 遍历表，通过
{
    if( !existList(L) )
    {
        errError();
        return ERROR;
    }
    ElemType *p = NULL;
    ElemType *q = L->base + L->length;

    for(p = L->base; p < q; p++)
    {
        (*pvisit)( p );
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
        for(iter = 0; iter < L->length; iter++)
        {
            if(input <= *p)
            {
                break;
            }
            p++;
        }
        listInsert(L, p - L->base + 1,&input);
    } while ((int)ch != 35);
    p = NULL;
    return OK;
    
}

Status createList(SqList *L) // 创建线性表，通过
{
    initList(L); // 初始化
    fprintf(stdout, "Please input integer data no more than %d end with the '#' key:\n", L->listSize);

    inputNode(L); // 输入节点
    return OK;
}

Status mergeList(const SqList *La, const SqList *Lb, SqList *Lc) // 合并线性表
{
    if( !existList(Lc) )
    {
        errError();
        return ERROR;
    }

    int iter = 0;
    ElemType *pa = La->base;
    ElemType *pb = Lb->base;
    int flag = 0;

    while(pa < La->base + La->length && pb < Lb->base + Lb->length)
    {

        if(*pa <= *pb)
        {
            listInsert(Lc, ++iter, pa++);
        }
        else
        {
            listInsert(Lc, ++iter, pb++);
        }
    }

    while(pa < La->base + La->length)
    {
        listInsert(Lc, ++iter, pa++);
    }

    while(pb < Lb->base + Lb->length)
    {
        listInsert(Lc, ++iter, pb++);
    }

    pa = NULL;
    pb = NULL;
    return OK;
}

Status mergeList_2nd(const SqList *La, const SqList *Lb, SqList *Lc) // 合并线性表2
{
    ElemType * pa = La->base;
    ElemType * pb = Lb->base;
    Lc->listSize = Lc->length = La->length + Lb->length;
    ElemType * pc = Lc->base = (ElemType *)malloc(Lc->listSize *sizeof(ElemType));
    if( !Lc->base )
    {
        fprintf(stdout, "ERROR: Failed to assign space.\n");
        exit(OVERFLOW);
    }

    while(pa <= (La->base + La->length - 1) && pb <= (Lb->base + Lb->length - 1))
    {
        if(*pa <= *pb) 
        {
            *pc++ = *pa++;
        }
        else
        {
            *pc++=*pb++;
        }
    }
    while (pa <= (La->base + La->length - 1))
    {
        *pc++=*pa++;
    }
    while (pb <= (Lb->base + Lb->length - 1))
    {
        *pc++=*pb++;
    }
    return OK;
}