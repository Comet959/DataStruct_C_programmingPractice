/*
 * fileName: Tree.c
 * date: 2020/11/21
 * compiler: GCC 9.2.0
 * auther: JunyiYang-杨竣轶
 * number: 1810730229
 * codeFormat: UTF-8
 * description: 二叉链树的操作实现以及实现层序遍历的相关队列的操作
*/

#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>

Status InitQueue(Queue *Q) // 初始化队列
{
    Q->base = (ElemType *)malloc(QUEUE_INIT_SIZE * sizeof(ElemType));
    if( !Q->base ) {
        fprintf(stderr, "Assign memory failed!Please try again!\n");
        exit(ERROR);
    }
    Q->front = Q->rear = Q->base; // 队空
    Q->queueSize = 0; // 队长为0
    Q->listSize = QUEUE_INIT_SIZE; // 队的空间
    return OK;
}

Status QueueEmpty(Queue *Q) // 队列空
{
    return Q->front == Q->rear;
}

Status EnQueue(Queue *Q, ElemType e) // 进队
{
    if(Q->rear - Q->base >= Q->listSize) // 队满，但是不一定空间满
    {
        Q->base = (ElemType *)realloc(Q->base, (Q->queueSize + QUEUEINCREMENT) * sizeof(ElemType));
        if( !Q->base )
        {
            fprintf(stderr, "Reassign memory failed!Please try again!\n");
            exit(ERROR);
        }
        Q->rear = Q->base + Q->queueSize;
        Q->listSize += QUEUEINCREMENT;
    }

    *Q->rear++ = e;
    Q->queueSize++;
    return OK;
}

Status DeQueue(Queue *Q, ElemType *e) // 出队
{
    if( QueueEmpty(Q) )
    {
        fprintf(stderr, "The queue is empty, exit!\n");
        exit(ERROR);
    }

    *e = *Q->front++;
    Q->queueSize--;
    return OK;
}



Status OutElem(TElemType e) // 输出元素
{
	printf("%c", e);
	return OK;
}

Status CreateBiTree(BiTree *T) // 创建二叉树
{
    TElemType ch;
    // ch = getchar();
    scanf("%c", &ch);
    if (ch == ' ')
    {
        *T = NULL;
        return OK;
    }
    else
    {
        if (!(*T = (BiTNode *)malloc(sizeof(BiTNode))))
        {
            exit(OVERFLOW);
			fprintf(stderr, "Memory assigned failed!\n"); 
        }
        (*T)->data = ch;
        // fflush(stdin);
        // printf("输入%c左孩子:",ch);
        CreateBiTree(&((*T)->lChild));
        // fflush(stdin);
        // printf("输入%c右孩子:",ch);
        CreateBiTree((&(*T)->rChild));
    }

    return OK;
}

Status PreOrderTraverse(BiTree T, Status (* Visit)(TElemType e)) // 先序遍历
{
    if(T)
	{
		if(Visit(T->data))
			if(PreOrderTraverse(T->lChild, Visit))
				if(PreOrderTraverse(T->rChild, Visit))
					return OK;
		return ERROR;
	}
	else
	{
		return OK;
	}
}

Status InOrderTraverse(BiTree T, Status (* Visit)(TElemType e)) // 中序遍历二叉树
{
    if(T)
    {
        if (InOrderTraverse(T->lChild, Visit))
            if(Visit(T->data))
                if (InOrderTraverse(T->rChild, Visit))
                    return OK;                
        return ERROR;
    }
    else
    {
        return OK;
    }
    
}

Status PostOrderTraverse(BiTree T, Status (* Visit)(TElemType e)) // 后续遍历二叉树
{
    if(T)
    {
        if(PostOrderTraverse(T->lChild, Visit))
            if(PostOrderTraverse(T->rChild, Visit))
                if(Visit(T->data))
                    return OK;
        return ERROR;
    }
    else
    {
        return OK;
    }
    
	return OK;
}

Status LevelOrderTraverse(BiTree T, Status (* Visit)(TElemType e)) // 层次遍历
{
    Queue Q;
    InitQueue(&Q);
    BiTree p = T;
    if( p )
    {
        EnQueue(&Q, p);
        while (!QueueEmpty(&Q))
        { 
            DeQueue(&Q, &p);
            Visit(p->data);
            if(p->lChild)
            {
				EnQueue(&Q, p->lChild);
            }
            if(p->rChild)
            {
                EnQueue(&Q, p->rChild);
            }   
        }
    }
	return OK;
}
