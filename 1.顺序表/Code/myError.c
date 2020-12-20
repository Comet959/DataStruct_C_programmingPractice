/*
 * fileName: myError.c
 * date: 2020/9/28
 * compiler: GCC 9.2.0
 * author: JunyiYang—杨竣轶
 * number: 1810730229
 * codedFormat: UTF-8
 * description: 一些常见的错误处理方法
*/

#include <stdio.h>
#include "myError.h"


void errOverFlow()
{
    fprintf(stderr,"ERROR_CODE: -2 ERROR_MESSAGE: OVERFLOW!\n");
}

void errError()
{
    fprintf(stderr,"ERROR_CODE: 0 ERROR_MESSAGE: List is not exists!Please initialize list first!\n");
}

void errBound()
{
    fprintf(stderr, "ERROR_CODE: 0 ERROR_MESSAGE: The subscript crossing the line!\n");
}