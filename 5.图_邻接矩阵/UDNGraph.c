/* 
 * fileName: UDNGraph.c
 * date: 2020/11/30
 * compiler: GCC 9.2.0 
 * auther: JunyiYang-杨竣轶 
 * number: 1810730229 
 * codeFormat: UTF-8 
 * compiler cmd: gcc UDNGraph.c Main.c -o Main 
 * description: 图相关数据结构及其操作函数的实现
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "UDNGraph.h"

int visited[MAX_VERTEX_NUM] = {FALSE}; // 全局变量 访问标志

Status CreateUDNGraph( MGraph *G ) // 创建无向图
{
    int i = 0;
    int j = 0;
    int k = 0;
    printf("请输入图的顶点数与弧数：\n");
    scanf("%d%d", &G->vexnum, &G->arcnum); // 输入图的顶点数与弧数
    while(G->vexnum > MAX_VERTEX_NUM || G->vexnum <= 0 || G->arcnum >= MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) / 2 || G->arcnum < 0)
    {
        fflush(stdin);
        printf("输入有误，顶点数必须在(0, %d]之间，弧数必须在[0, %d]之间，请重新输入\n", MAX_VERTEX_NUM, MAX_VERTEX_NUM * (MAX_VERTEX_NUM - 1) / 2);
        printf("请输入图的顶点数与弧数：\n");
        scanf("%d%d", &G->vexnum, &G->arcnum); // 输入图的顶点数与弧数
    }
    fflush(stdin);
    printf("输入顶点信息：\n");
    for(i = 0; i < G->vexnum; ++i)
    {
        scanf("%s", G->vexs[i]);
    }
    fflush(stdin);
    for(i = 0; i < G->vexnum; ++i)
    {
        for(j = 0; j < G->vexnum; ++j)
        {
            G->arcs[i][j].adj = UNADJ; // 初始化邻接矩阵为无穷大
        }

    }
    printf("输入结点之间的相邻关系，格式：vi vj 即表示vi与vj相邻：\n");
    for(k = 0; k < G->arcnum; ++k)
    {
        char v1[VRData], v2[VRData];
        // int w = UNADJ;
        scanf("%s %s", v1, v2);
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        if(i == ERROR || j == ERROR) 
        {
            fflush(stdin);
            printf("输入失败，请重新输入！\n");
            scanf("%s %s", v1, v2);
            i = LocateVex(G, v1);
            j = LocateVex(G, v2);
        }
        fflush(stdin);
        G->arcs[i][j].adj = ADJ;
        G->arcs[j][i].adj = G->arcs[i][j].adj;
    }
    fflush(stdin);
    return OK;
}

int LocateVex( MGraph *G, char *v) // 寻找V在G中的位置 在vex中对比v
{
    for(int i = 0; i < G->vexnum; ++i)
    {
        if ( !strcmp(v, G->vexs[i]) )
        {
            return i;
        }
    }
    return ERROR;
}

Status VisitFunc(MGraph *G, VertexNum v)
{
    return printf("%s ", G->vexs[v]);
}

Status DFS( MGraph *G, VertexNum v) // 深度遍历 从第v个节点开始
{
    VisitFunc(G, v);
    visited[v] = TRUE;
    for (VertexNum w = 0; w < MAX_VERTEX_NUM; ++w)
    {
        if( !visited[w] && G->arcs[v][w].adj == ADJ ) DFS(G,w);
    }
}

