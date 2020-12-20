/* 
 * fileName: Main.c 
 * date: 2020/11/30
 * compiler: GCC 9.2.0 
 * auther: JunyiYang-杨竣轶 
 * number: 1810730229 
 * codeFormat: UTF-8 
 * compiler cmd: gcc UDNGraph.c Main. Main 
 * description: 入口主函数，创建无向图并进行DFS遍历
*/ 


#include <stdio.h>
#include <stdlib.h>
#include "UDNGraph.h"

int main(int argc, char* argv[])
{

    MGraph G;
    CreateUDNGraph(&G);
    printf("结点数为：%d, 弧数为：%d\n", G.vexnum, G.arcnum);
    printf("结点信息为：\n");
    for(int i = 0; i < MAX_VERTEX_NUM; ++i)
    {
        printf("%s ", G.vexs[i]);
    }
    printf("\n");
    printf("邻接矩阵为：\n");
    for(int i = 0; i < MAX_VERTEX_NUM; ++i)
    {
        for(int j = 0; j < MAX_VERTEX_NUM; ++j)
        {
            if(j == MAX_VERTEX_NUM - 1)
                printf("%2d\n", G.arcs[i][j]);
            else
            {
                printf("%2d ", G.arcs[i][j]);
            }
            
        }
    }
    printf("请输入编号，指定从哪一个结点开始深度遍历DFS：\n");
    VertexNum v;
    scanf("%d", &v);
    printf("从结点%s开始深度遍历结果为：\n", G.vexs[v-1]);
    DFS(&G, v-1);

    return 0;
}

