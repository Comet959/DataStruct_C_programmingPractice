/* 
 * fileName: UDNGraph.c 
 * date: 2020/11/30
 * compiler: GCC 9.2.0 
 * auther: JunyiYang-杨竣轶 
 * number: 1810730229 
 * codeFormat: UTF-8 
 * compiler cmd: gcc UDNGraph.c Main.c -o Main 
 * description: 图相关数据结构及其操作函数的声明接口
*/ 

#ifndef _UDNGraph_H_
#define _UDNGraph_H_

#define INFINITY -1 // 最大值
#define VRData 3
#define MAX_VERTEX_NUM 8 // 最大顶点个数
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define ADJ 1 // 相邻表示1
#define UNADJ -1 // 不相邻表示-1

typedef int Status;
typedef int VRType; // 顶点之间连通性
typedef char VertexType; // 顶点元素
typedef int VertexNum; // 顶点编号


// 默认为无向图
typedef struct ArcCell
{
    VRType adj; // 顶点的关系  1或0表示
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct Graph
{
    VertexType vexs[MAX_VERTEX_NUM][VRData]; // 顶点向量
    AdjMatrix arcs; // 邻接矩阵
    int vexnum, arcnum; // 当前顶点数与弧数
}MGraph;


Status CreateUDNGraph( MGraph *G ); // 创建图
int LocateVex( MGraph *G, char *v); // 寻找V在G中的位置
Status DFS( MGraph *G, VertexNum v); // 深度遍历
Status VisitFunc(MGraph *G, VertexNum v); // 图元素的访问

#endif