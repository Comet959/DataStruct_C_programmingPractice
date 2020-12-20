/*
 * fileName: myLinkList.h
 * date: 2020/10/10
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 链表的结构定义与其上的操作的接口声明
*/

#ifndef _MYLINKLIST_H_
#define _MYLINKLIST_H_

#include "universal/status.h"

typedef int Status;
typedef int ElemType;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

Status InitList_L( LinkList *L) ;
Status DestroyList_L( LinkList *L ) ;
Status ClearList_L( LinkList *L ) ;
Status ListEmpty_L( const LinkList L ) ;
int ListLength_L( const LinkList L ) ;
Status GetElem_L( const LinkList L , int i , ElemType *e );

Status compare_e( const ElemType * e1 ,const ElemType  * e2 ) ; 

int LocateElem_L( const LinkList L ,const ElemType  *e , Status (*compare)());
Status PriorElem_L(const LinkList L ,const  ElemType  *cur_e, ElemType *pre_e  );
Status NextElem_L(const LinkList L , const ElemType  *cur_e, ElemType *next_e  );	
Status ListInsert_L( LinkList L , int i , const ElemType *e) ;
Status ListDelete_L( LinkList L , int i , ElemType *e) ;

Status outElem(const ElemType  *e) ; /* 根据实际情况编写 */

Status ListTraverse(const LinkList L , Status (*visit)(const ElemType  * ) );

Status CreateList_opt(LinkList *L, Status (*LinsInsert_opt_increasing)(LinkList L, const ElemType *e));// 可选的创建链表的方式，输入链表头指针的指针与函数指针，其中函数指针为可选的头插或尾插。

Status CreateList_head(LinkList *L ); // 头部插入法
Status ListInsert_head_increasing(LinkList L, const ElemType *e); // 实现

Status CreateList_tail(LinkList *L); // 尾部插入法
Status ListInsert_tail_increasing(LinkList L, const ElemType *e); // 实现

Status MergeList_L( const LinkList  La , const LinkList Lb, LinkList Lc); // 归并

#endif