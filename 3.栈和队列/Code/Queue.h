/*
 * fileName: myLinkList.c
 * date: 2020/11/14
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 队列的数据结构定义与操作的接口
*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_INIT_SIZE 100 // 初始分配量
#define QUEUEINCREMENT 10 // 增量

#include "Status.h"

typedef struct 
{
    ElemType *base; // 基地址
    ElemType *front; // 队首
    ElemType *rear; // 队尾指针
    int queueSize; // 队长
    int listSize; // 分配的空间长度
}Queue;

Status InitQueue(Queue *Q);
Status DestroyQueue(Queue *Q);
Status ClearQueue(Queue *Q);
Status QueueEmpty(Queue *Q);
int QueueLength(Queue *Q);
Status GetHead(Queue *Q, ElemType *e);
Status EnQueue(Queue *Q, ElemType e);
Status DeQueue(Queue *Q, ElemType *e);
Status OutElem(ElemType *e);
Status QueueTraverse(Queue *Q, Status (*visit)(ElemType *e));

#endif