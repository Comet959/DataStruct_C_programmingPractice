/*
 * fileName: myLinkList.c
 * date: 2020/10/10
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 链表上操作的具体实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>

#include <malloc.h>

#include "myLinkList.h"
#include "universal/status.h"
#include "universal/myError.h"



Status InitList_L( LinkList *L) // 二级指针, 测试通过
{
	LNode *head = NULL ; // 头结点指针
	head = (LNode *)malloc(sizeof(LNode)); // 堆分配头节点
	if( !head )
	{
		exit(OVERFLOW);
	}
	
	head->next = NULL ;
	*L = head ; // 返回
	
	return OK;
}

Status DestroyList_L(LinkList *L) 
{
	LNode *p = NULL;
	LNode *q = NULL;
	
	if(!*L) // 头节点不存在
	{
		fprintf(stderr, "LinkList not exist!\n");
		exit(ERROR);
	}

	for( p = (*L)->next ; p != NULL ; )
	{
		q = p ;
		p = q->next ;
		free(q);
	}
	
	free(*L) ;
	
	return OK;
}

Status ClearList_L(LinkList *L) 
{
	if(!*L) // 头节点不存在
	{
		fprintf(stderr, "LinkList not exist!\n");
		exit(ERROR);
	}
	DestroyList_L(L);
	return OK;
}

Status ListEmpty_L(const LinkList L)
{
	if( L->next == NULL)
	{
		return TRUE;
	}	
	else
	{
		return FALSE ;
	}	
}

int ListLength_L(const LinkList L) // 1
{
	LNode *p = NULL;
	int length = 0  ;
	
	for( p = L->next ; p != NULL ;	 p = p->next  )
	{
		length++;
	}
	return length ;
}

Status GetElem_L(const LinkList L, int i , ElemType *e )
{
	LNode *p = NULL;
	int j = 1  ;
	
	if( i < 1 || i > ListLength_L(L) )
	{
		return ERROR ;
	}	
		
	for( p = L->next  ;  j < i ; p = p->next )
	{
		j++;
	}	
	
	*e = p->data ;
	
	return OK; 
}

Status compare_e( const ElemType * e1 ,const ElemType  * e2 )
{
	int flags = 0 ;
	if( *e1 == *e2)
		{
			flags = 0 ;
		}
	if( *e1 > *e2 )
		{
			flags = 1 ;
		}
	if( *e1 < *e2 )
		{
			flags = -1 ;
		}
	return flags ;
}

int LocateElem_L(const LinkList L ,const ElemType  *e , Status (*compare)( const ElemType  *, const ElemType  *))
{
	int i = 0 ;
	int flags = 0 ;
	int length = 0 ;	
	LNode *p = NULL ;	
	
	length = ListLength_L(L) ;	
	
	for( i = 1 , p = L->next ; p && i <= length ; p = p -> next , i++ )
	{
			if( !(*compare)(&p->data , e) )
			{
				flags = 0 ;
				break;
			}
			else
			{
				flags = 1 ;
			}	
	}
			
	if( flags == 1 )
	{
		return 0 ;
	}	
	else
    {
		return i ;	
	}	

}

Status PriorElem_L(const LinkList L ,const ElemType  *cur_e, ElemType *pre_e  )
{
		LNode *p = NULL ;
		LNode *q = NULL ;
		int flags = 0 ;
		int i = 1 ;		
		
		for( p = L->next , i = 1 ; p != NULL ; p = p->next , i++ )
		{
			if( !(*compare_e)(&p->data,cur_e ) )
			{
				if( i == 1 )
				{
						flags = 1 ;						
				}
				else 
				{
						flags = 0 ;
				}
				break;	
			}
			else
			{
				q = p ;
			}		
		}
		
		if( flags )
		{
			pre_e = NULL ;
			return FALSE;
		}	
		else
		{
			*pre_e = q->data;		
			return OK;
		}		
}

Status NextElem_L(const LinkList L, const  ElemType  *cur_e, ElemType *next_e  )
{
		LNode *p = NULL ;
		int flags = 1 ;
		
		for( p = L->next ; p->next ; p = p->next )
		{
			if( !(*compare_e)(&p->data,cur_e ) )
			{
				flags = 0 ;
				break;	
			}				
		}
	  if( flags == 0 )
	  {
	  	*next_e = p->next->data ;
	  	return TRUE ;
	  }
	  else
	  {
	  	next_e = NULL ;
	  	return FALSE ;
	  }		
}
	
Status ListInsert_L( LinkList L , int i , const ElemType *e) // 插入节点
{
	LNode *p = NULL ;	
	LNode *q = NULL ;
	int length = 0 ;
	int j = 0 ;
	
	length = ListLength_L(L) ;		
	if( i < 1 || i > length + 1 ) // 越界
	{
		errBound(); // 异常处理
		return ERROR ;
	}
	q = (LNode*)malloc(sizeof(LNode));
	if( !q )
	{
		fprintf(stderr, "Assign memory failed!");
		exit(OVERFLOW);
	}
	q->data = *e ;

	for( p = L , j = 0 ; p->next && j < i - 1  ; j++ )
	{
		p = p->next; // 指针移动
	}
	q->next = p->next;
	p->next = q ;
	
	return OK;
}

Status ListDelete_L( LinkList L , int i , ElemType *e)
{
	LNode *p = NULL ;	
	LNode *q = NULL ;

	int length = 0 ;
	int j = 0 ;
	
	length = ListLength_L(L) ;		
	if( i < 1 || i > length )
	{
		return ERROR ;
    }
	for(p = L ,j = 0 ; p->next && j < i - 1 ; j++ )
	{
		 p = p->next ;
	}		
	
	if(!(p->next) || j > i - 1 )
	{
		return ERROR ;
	}
	
	q = p->next ;
	p->next = q->next ;
	*e = q->data ;
	
	free(q);
			
	return OK;
}

Status outElem(const ElemType  *e) // 输出元素
{
	printf("%d ",*e);
	return OK ;
}

Status ListTraverse(const LinkList L ,Status (*visit)(const ElemType  *) ) // 链表遍历
{
	LNode *p = NULL ;	
	
	printf("Display List:\n");
	
	for(p = L->next ; p  ; p = p->next )
	{
		( *visit)( &p->data );
	}

	printf("\n");
	
	return OK;
}



// --------------------------分界线---------------------------------


Status CreateList_opt(LinkList *L, Status (*LinsInsert_opt_increasing)(LinkList L, const ElemType *e))// 可选的创建链表的方式，输入链表头指针的指针与函数指针，其中函数指针为可选的头插或尾插。
{
	InitList_L(L);
	fprintf(stdout, "Please input integer end with the '#' key!\n");

	ElemType input;
	char ch; // 结束符判断
	do{
		if(scanf("%d%c", &input, &ch) < 2) // 输入失败
		{
			fprintf(stderr, "INPUT_ERROR_MESSAGE: Please input a correct number.\n");
			fflush(stdin); // 清空缓冲区
			continue;
		}
		(*LinsInsert_opt_increasing)(*L, &input);
		// 可选的头插法或尾插法插入节点并按非递减排列
	}while((int)ch != 35);
	return OK;
}


// 头插法的具体实现
Status ListInsert_head_increasing(LinkList L, const ElemType *e) 
{

	LNode *p = (LNode *)malloc(sizeof(LNode)); // 创建节点
	if(!p)
	{
		fprintf(stderr, "Assign memory failed!\n");
		exit(ERROR);
	}
	LNode *q = NULL;
	p->next = NULL; // 赋初值
	p->data = *e; // 赋初值
	if(!L->next) // 如果是空，直接插入
	{
		L->next = p;
		return OK;
	}

	q = L;
	p->next = q->next;
	q->next = p;

	// // 如果输入顺序错乱，则进行选择插入
	// for(q = L; q->next != NULL && q->data < p->data; q = q->next) // 移动q，找到插入位置
	// {
	// // 待插入的节点数据如果最小（只需要小于第一个节点）则直接头插法插在第一个。否则寻找第一个比待插元素大的节点，在它前面插入
	// }

	// // 头插法移动指针
	// p->next = q->next;
	// q->next = p;

	return OK;
}



// 尾插法的具体实现
Status ListInsert_tail_increasing(LinkList L, const ElemType *e)
{ 
	LNode *p = (LNode *)malloc(sizeof(LNode)); // 创建节点
	if(!p)
	{
		fprintf(stderr, "Assign memory failed!\n");
		exit(ERROR);
	}
	LNode *q = L;
	p->next = NULL; // 赋初值
	p->data = *e; // 赋初值

	for (q = L; q->next!=NULL; q = q->next)
	{
	}

	q->next = p;

	// // 如果输入顺序错乱，则选择正确位置利用尾插法插入
	// for(q = L; q->next != NULL && q->next->data <p->data; q = q->next) // 移动q，找到插入位置
	// {
	// // 待插入的节点数据如果最小（只需要小于第一个节点）则直接尾插法插在后面
	// }

	// // 移动指针
	// p->next = q->next;
	// q->next = p;

	return OK;
}

Status CreateList_head(LinkList *L  ) // 头插法创建链表
{
    CreateList_opt(L, ListInsert_head_increasing);
	return OK;
}

Status CreateList_tail(LinkList *L  ) // 尾插法创建链表
{
	CreateList_opt(L, ListInsert_tail_increasing);
	return OK;
}


// 归并
Status MergeList_L( const LinkList La , const LinkList Lb, LinkList Lc)
{
	if(!(La && Lb && Lc))
	{
		fprintf(stderr, "LinkList not exists!\n");
		exit(ERROR);
	}
	LinkList pa = NULL;
	LinkList pb = NULL;
	LinkList pc = NULL;

	// 接管头节点
	pa = La->next;
	pb = Lb->next;
	pc = Lc;
	
	
	while(pa && pb) { // 修改指针
		if(pa->data == pb->data) {
			LinkList temp = pa; // 释放掉跳过的节点
			pa = pa->next;
			free(temp);
		}

		else if(pa->data < pb->data) {
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}

		else {
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}

	// 合并剩余节点
	pc->next = pa ? pa : pb;

	 // 注意：在这里需要释放La与Lb两个指针，因为它们的原始链表的指向已经更改了因此这两个指针没有实际作用，应该删除。同时在主函数中不能再使用DestroyList来销毁链表，因为指向改变了，会引起错误。
	free(La);
	free(Lb);
	return OK;
}
