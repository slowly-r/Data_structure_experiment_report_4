#pragma once
#ifndef PICTURE_H
#define PICTURE_H

typedef int Status;
#define	OK		1
#define ERROR	-1

#define swap(a, b)	{a = a + b; b = a - b; a = a - b;}

//-------图的邻接矩阵存储表示--------//
#define MaxInt  32767       //表示极大值，即∞
#define MVNum   100         //最大顶点数     
typedef char VerTexType;	//假设顶点的数据类型为字符型
typedef int ArcType;		//假设边的权值类型为整型
typedef struct
{
	VerTexType vexs[MVNum];		//顶点表
	ArcType arcs[MVNum][MVNum];	//邻接矩阵
	int vexnum, arcnum;			//图的当前点数和边数
}AMGraph;

Status CreateUDN(AMGraph& G);		//采用邻接矩阵表示法，创建无向网G
Status CreateDN(AMGraph& G);			//采用邻接矩阵表示法，创建有向网G
Status LocateVex(AMGraph G, VerTexType u);
void ShortestPath_DIJ(AMGraph G, int v0, int* D, int* Path);
int ShortestPathMAX(AMGraph G, int v0);

#endif 
