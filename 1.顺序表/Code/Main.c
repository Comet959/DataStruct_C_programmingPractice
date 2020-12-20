/*
 * fileName: Main.c
 * date: 2020/9/28
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * compiler cmd: gcc myError.c mySeq.c Main.c -o Main
 * description: 入口主函数
*/
#include <stdio.h>
#include <stdlib.h>

#include "mySeq.h" // 线性表

/* 测试样例：（注意以#号键结束，#需紧跟数字的下一个输入）
 * Input: 3 5 8 11#
 *        2 6 8 9 11 15 20#
 * Output: 
 *        2 3 5 6 8 8 9 11 11 15 20
*/

int main(int argc, char *argv[])
{
    SqList LA, LB, LC;   

    // 创建与初始化线性表
    createList(&LA); 
    createList(&LB); 
    initList(&LC);

    // 合并线性表LA、LB到LC
    mergeList_2nd(&LA, &LB, &LC);

    printf("--------Boundary-------\n");
    // 输出LA、LB、LC
    printf("LA: \n");
    outSqList(&LA);
    printf("\nLB: \n");
    outSqList(&LB);
    printf("\nLC: \n");
    outSqList(&LC);

    // 释放内存
    destroyList(&LA);
    destroyList(&LB);
    destroyList(&LC);
    return 0;
}
