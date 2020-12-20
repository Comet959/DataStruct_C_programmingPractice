/*
 * fileName: Main.c
 * date: 2020/11/21
 * compiler: GCC 9.2.0
 * auther: JunyiYang-杨竣轶
 * number: 1810730229
 * codeFormat: UTF-8
 * compiler cmd: gcc Tree.c Main.c -o Main
 * description: 入口主函数，实现二叉树的四种遍历方式
*/

#include <stdio.h>
#include <stdlib.h>

// 二叉树的二叉链表示
#include "Tree.h"


int main(int argc,const char *argv[])
{
    BiTNode *T;
    printf("请输入第一个节点的值，两个空格表示没有孩子：\n");
    CreateBiTree(&T);

    printf("先序遍历二叉树：");
    PreOrderTraverse(T, OutElem);
    printf("\n");

    printf("中序遍历二叉树：");
    InOrderTraverse(T, OutElem);
    printf("\n");

    printf("后续遍历二叉树：");
    PostOrderTraverse(T, OutElem);
    printf("\n");

    printf("层次遍历二叉树：");
    LevelOrderTraverse(T, OutElem);
    printf("\n");
    return OK;
}

