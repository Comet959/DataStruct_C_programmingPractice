/*
 * fileName: myLinkList.c
 * date: 2020/11/14
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 队列上的操作的具体实现
*/

#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"


Status InitQueue(Queue *Q)
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

Status DestroyQueue(Queue *Q)
{
    free(Q->base);
    Q->base = NULL;
    Q->front = NULL;
    Q->listSize = 0;
    Q->rear = NULL;
    Q->queueSize = 0;
    return OK;
}

Status ClearQueue(Queue *Q) // 清空队列
{
    Q->front = Q->rear = Q->base; // 清空队列，并将队首放到基址
    Q->queueSize = Q->rear-Q->front;
    return OK;
}

Status QueueEmpty(Queue *Q)
{
    return Q->front == Q->rear;
}

int QueueLength(Queue *Q)
{
    return Q->rear - Q->front;
}

Status GetHead(Queue *Q, ElemType *e)
{
    if( QueueEmpty(Q) )
    {
        fprintf(stderr, "The queue is empty, exit!\n");
        exit(ERROR);
    }

    *e = *Q->front;
    return OK;
}

Status EnQueue(Queue *Q, ElemType e)
{
    if(Q->rear - Q->base >= Q->queueSize) // 队满，但是不一定空间满
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

Status DeQueue(Queue *Q, ElemType *e)
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

Status QueueTraverse(Queue *Q, Status (*visit)(ElemType *e)) // 从队首到队尾遍历
{
    ElemType *p = NULL;
    printf("从队首到队尾遍历：\n");
    for (p = Q->front; p != Q->rear; p++)
    {
        if( !visit(p) )
        {
            fprintf(stderr, "Visit failed\n");
            exit(ERROR);
        }
    }
    return OK;
}
