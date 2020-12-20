/*
 * fileName: Main.c
 * date: 2020/11/14
 * compiler: GCC 9.2.0
 * auther: JunyiYang-杨竣轶
 * number: 1810730229
 * codeFormat: UTF-8
 * compiler cmd: gcc Stack.c Queue.c Main.c -o Main
 * description: 入口主函数，实现用栈十进制转二进制，利用队列二进制转十进制，未使用模块化编程是由于题目要求元素出栈后立即进队列，我没有想到好的办法来实现3个功能分别实现。
*/

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "Queue.h"
#include <math.h>


char BtoH(const int s); // 将二进制的十进制数转换成字符A B C D E F

int main(void)
{

    Stack S;
    Queue Q1, Q2;
    InitStack(&S);
    InitQueue(&Q1);
    InitQueue(&Q2);

/*-----------------------Step1. 输入数据--------------------------------------------------*/
    int inputNum; // 输入的数据
    printf("请输入一个十进制数字：");
    scanf("%d", &inputNum);

/*-----------------------Step2.1. 利用栈实现十进制转二进制---------------------------------*/
    printf("利用栈转换成二进制为：\n");
    if( !inputNum ) printf("0");
    int r;
    while(inputNum)
    {
        r = inputNum % 2;
        Push(&S, r);
        inputNum = inputNum / 2;
    }
    while ( !StackEmpty(&S) )
    {
        Pop(&S, &r); // 出栈
        printf("%d", r);
        // 出栈同时进队
        EnQueue(&Q1, r); // 进队
        EnQueue(&Q2, r); // 进队
    }
    printf("\n");

/*-----------------------Step2.2. 利用队列实现二进制转八进制-------------------------------*/
    printf("利用队列二进制转八进制：\n");
    int num;
    num = QueueLength(&Q1) % 3; // 最前面几位0的个数
    int s = 0; // 转换的值
    for(int i = 0; i < num; i++)
    {
        DeQueue(&Q1, &inputNum);
        s += inputNum * pow(2, num-i-1);
    }
    if (s || QueueEmpty(&Q1)) printf("%d", s);
    while( !QueueEmpty(&Q1) )
    {
        s = 0;

        for (int i = 2; i >=0; i--)
        {   
            DeQueue(&Q1, &inputNum);
            s = s + inputNum * pow(2, i);
        }
        printf("%d", s);
    }
    printf("\n");

/*-----------------------Step2.3. 利用队列实现二进制转十六进制------------------------------*/
    printf("利用队列二进制转十六进制：\n");
    printf("0x");
    num = QueueLength(&Q2) % 4;  // 求前面非对齐的几位个数
    s = 0;
    for(int i = 0; i < num; i++)
    {
        DeQueue(&Q2, &inputNum);
        s += inputNum * pow(2, num - i -1);
    }
    if (s || QueueEmpty(&Q2)) printf("%d", s); // 前面几位永不大于10

    while( !QueueEmpty(&Q2) )
    {
        s = 0;

        for (int i = 3; i >= 0; i--)
        {
            DeQueue(&Q2, &inputNum);
            s = s + inputNum * pow(2,i);
        }
        printf("%c", BtoH(s));
    }

    printf("\n");

    return OK;

}

char BtoH(const int s) // 将二进制的十进制数转换成字符A B C D E F
{
    switch(s)
    {
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
    }
}
