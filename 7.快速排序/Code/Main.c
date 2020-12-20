/*
 * fileName: Main.c
 * date: 2020/11/30
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 入口主函数，实现快速排序
*/
#include <stdio.h>
#include <stdlib.h>

#include "mySeq.h" // 引入顺序表

int Partition(SqList *L, int low, int high); 
Status QSort(SqList *L, int low, int high); 
Status QuickSort(SqList *L);  // 快速排序
int i = 0; // 全局变量，记录排序的趟数
int main(int argc, char *argv[])
{
    SqList L;
    createList(&L); // 建表时逆序输入
    printf("输出表为：");
    outSqList(&L);
    printf("\n");
    QuickSort(&L);
    printf("经过快速排序后的有序序列为：");
    outSqList(&L);
    destroyList(&L);
    return 0;
}

int Partition(SqList *L, int low, int high) // 交换
{
    int pivotkey = *(L->base + low); // 枢轴
    while (low < high) // 扫描过程
    {
        while (low < high && *(L->base + high) >= pivotkey)
        {
            --high;
        }
        *(L->base + low) = *(L->base + high);
        while (low < high && *(L->base + low) <= pivotkey)
        {
            ++low;
        }
        *(L->base + high) = *(L->base + low);
    }
    *(L->base + low) = pivotkey;
    ++i;
    printf("第%d趟排序的结果为：", i);
    outSqList(L);
    printf("\n");
    return low;
}

Status QSort(SqList *L, int low, int high) // 快速排序
{
    if(low < high)
    {
        int pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);
    }
    return OK;
}

Status QuickSort(SqList *L)  // 快速排序
{
    QSort(L, 0, L->length - 1);
    return OK;
}