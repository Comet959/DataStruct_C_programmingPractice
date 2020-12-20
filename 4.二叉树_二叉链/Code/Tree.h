/*
 * fileName: Tree.c
 * date: 2020/11/21
 * compiler: GCC 9.2.0
 * auther: JunyiYang-杨竣轶
 * number: 1810730229
 * codeFormat: UTF-8
 * description: 二叉链树的数据结构及操作接口，以及为实现层序遍历编写的相关队列的接口
*/

#ifndef _TREE_H_
#define _TREE_H_

typedef int Status;

#define OK 1
#define OVERFLOW -1
#define ERROR -1
#define QUEUE_INIT_SIZE 100 // 初始分配量
#define QUEUEINCREMENT 10 // 增量

typedef char TElemType;
typedef struct BTNode{
    TElemType data;
    struct BTNode *lChild;
    struct BTNode *rChild;
}BiTNode, *BiTree;

typedef BiTree ElemType;
typedef struct 
{
    ElemType *base; // 基地址
    ElemType *front; // 队首
    ElemType *rear; // 队尾指针
    int queueSize; // 队长
    int listSize; // 分配的空间长度
}Queue; // 队列


Status OutElem(TElemType e);// 输出元素

// 队列相关操作
Status InitQueue(Queue *Q); // 初始化队列
Status QueueEmpty(Queue *Q); // 队列为空
Status EnQueue(Queue *Q, ElemType e); // 进队
Status DeQueue(Queue *Q, ElemType *e); // 出队
// 二叉树相关操作

//先序创建二叉树
Status CreateBiTree(BiTree *T); // 线序创建二叉树
Status PreOrderTraverse(BiTree T, Status (* Visit)(TElemType e)); // 先序遍历二叉树
Status InOrderTraverse(BiTree T, Status (* Visit)(TElemType e)); // 中序遍历二叉树
Status PostOrderTraverse(BiTree T, Status (* Visit)(TElemType e)); // 后续遍历二叉树
Status LevelOrderTraverse(BiTree T, Status (* Visit)(TElemType e)); // 层次遍历二叉树
#endif