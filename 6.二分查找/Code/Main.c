/*
 * fileName: Main.c
 * date: 2020/11/30
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 入口主函数，实现二分查找
*/
#include <stdio.h>
#include <stdlib.h>

#include "mySeq.h" // 顺序表
typedef SqList SSTable;
typedef ElemType KeyType;
#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))

LOC SearchBin(SSTable *ST, KeyType key); // 二分查找

int main(int argc, char *argv[])
{
    SSTable ST;

    createList(&ST);
    KeyType key;
    printf("请输入待查找的数字：\n");
    scanf("%d", &key);
    printf("%d的位置是：%d\n", key, SearchBin(&ST, key));
    printf("打印查找表为：\n");
    outSqList(&ST);
    destroyList(&ST);

    return OK;
}

LOC SearchBin(SSTable *ST, KeyType key) // 二分查找
{
    int low = 0, high = ST->length-1; // 区间初值
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if(EQ(key, *(ST->base + mid)))
        {
            return mid + 1;
        }
        else if(LT(key, *(ST->base + mid)))
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }    
    }
    return OK;
}