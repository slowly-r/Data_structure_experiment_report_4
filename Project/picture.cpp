#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include "picture.h"

using namespace std;

Status LocateVex(AMGraph G, VerTexType u)
{
	int i;
	for (i = 0; i < G.vexnum; ++i)
	{
		if (G.vexs[i] == u)
			return i;				// 找到顶点值为u的位置，返回该位置在顶点表中的索引 i
	}
	return ERROR;					// 没找到，返回错误码
}

Status InsertVex(AMGraph& G, int v)	//在以邻接矩阵形式存储的无向图G上插入顶点v
{
	int k;
	if ((G.vexnum + 1) > MVNum)
		return ERROR;				//判断插入操作是否合法
	G.vexnum++;						//增加图的顶点数量
	G.vexs[G.vexnum] = v;			//将新顶点v存入顶点表
	for (k = 0; k < G.vexnum; k++)	//邻接矩阵相应位置的元素置为0
		G.arcs[G.vexnum][k] = G.arcs[k][G.vexnum] = 0;
	return OK;
}

Status DeleteVex(AMGraph& G, char v)	//在以邻接矩阵形式存储的无向图G上删除顶点v
{
	int n, m, i;
	n = G.vexnum;
	if ((m = LocateVex(G, v)) < 0)	//判断删除操作是否合法，即v是否在G中
		return ERROR;
	swap(G.vexs[m],G.vexs[n]);		//将待删除顶点交换到最后一个顶点
	for (i = 0; i < n; i++)			//将边的关系随之交换
	{
		swap(G.arcs[m][i], G.arcs[n][i]);
		swap(G.arcs[i][m], G.arcs[i][n]);
	}
	G.vexnum--;						//顶点总数减1
	return OK;
}

Status InsertArc(AMGraph& G, char v, char w)	//在以邻接矩阵形式存储的无向图G上插入边(v,w)
{
	int i, j;
	if ((i = LocateVex(G, v)) < 0)	return ERROR;	//判断插入位置是否合法
	if ((j = LocateVex(G, w)) < 0)	return ERROR;	//判断插入位置是否合法
	if (i == j)	return ERROR;
	G.arcs[i][j] = G.arcs[j][i] = 1;				//在邻接矩阵上增加对应的边
	G.arcnum++;										//边数加1
	return OK;
}

Status DeleteArc(AMGraph& G, char v, char w)	//在以邻接矩阵形式存储的无向图G上删除边(v,w)
{
	int i, j;
	if ((i = LocateVex(G, v)) < 0)	return ERROR;	//判断插入位置是否合法
	if ((j = LocateVex(G, w)) < 0)	return ERROR;	//判断插入位置是否合法
	G.arcs[i][j] = G.arcs[j][i] = 0;				//在邻接矩阵上删除边
	G.arcnum--;										//边数减1
	return OK;
}

Status CreateUDN(AMGraph& G)		//采用邻接矩阵表示法，创建无向网G
{
	int i, j, k, w;
	VerTexType v1, v2;				//v1、v2表示点的位置、w表示该点权值
	cout << "输入总顶点数：";
	cin >> G.vexnum;	//输入总顶点数、总边数
	cout << "输入总边数：";
	cin >> G.arcnum;

	cout << "依次输入顶点名称：";
	for (i = 0; i < G.vexnum; ++i)	//依次输入点的信息
		cin >> G.vexs[i];

	for (i = 0; i < G.vexnum; ++i)	//初始化邻接矩阵、边的权值	均置为极大值MaxInt
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;

	for (k = 0; k < G.arcnum; ++k)	//构建邻接矩阵
	{
		cout << "输入一条边依附的顶点及权值:";
		cin >> v1 >> v2 >> w;		//输入一条边依附的顶点及权值
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);		//确定v1、v2在G中的位置，即顶点数组下标
		if (i == ERROR || j == ERROR)
		{
			cout << "顶点不存在！" << endl;
			return ERROR;
		}
		G.arcs[i][j] = w;			//边<v1,v2>的权值置为w 对称边<v2,v1>的权值为w
		G.arcs[j][i] = G.arcs[i][j];//置<v1,v2>的对称边<v2,v1>的权值为w
	}
	return OK;
}

//用Dijkstra算法求图G中距离顶点v0的最短路径长度最大的一个顶点m
int ShortestPathMAX(AMGraph G, int v0)
{
	int n, v, i, min, w, max, m;
	int S[20], D[20], Path[20];
	n = G.vexnum;					//n为G中顶点的个数
	for (v = 0; v < n; ++v)			//n个顶点依次初始化
	{
		S[v] = false;				//S初始为空集
		D[v] = G.arcs[v0][v];		//将v0到各个终点的最短路径长度初始化为弧上的权值
		if (D[v] = 0)				//如果v0和v之间有弧，则将v的前驱置为v0
			D[v] = MaxInt;

		if (D[v] < MaxInt)			//如果v0和v之间有弧，则将v的前驱置为v0
			Path[v] = v0;
		else						//如果v0和v之间无弧，则将v的前驱置为-1
			Path[v] = -1;
	}
	S[v0] = true;					//将v0加入S
	D[v0] = 0;						//源点到源点的距离为0
	/*-----初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集-----*/
	for (i = 1; i < n; ++i)			//对其余n-1个顶点，依次进行计算
	{
		min = MaxInt;				
		for (w = 0; w < n; ++w)
			if(!S[w] && D[w]<min)
			{
				v = w;
				min = D[w];			//选择一条当前的最短路径，终点为v
			}
		S[v] = true;				//将v加入S
		for (w = 0; w < n; ++w)		//更新从v0出发到集合V-S上所有顶点的最短路径长度
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];		//更新D[w]
				Path[w] = v;					//更新w的前驱为v
			}
	}
	/*-----最短路径求解完毕，设距离顶点v0的最短路径长度最大的一个顶点为m-----*/
	max = D[0];
	m = 0;
	for (i = 1; i < n; i++)
		if (max < D[i])	
			m = i;
	return m;						//返回顶点下标
}

Status CreateDN(AMGraph& G)			//采用邻接矩阵表示法，创建有向网G
{
	int i, j, k, w;
	VerTexType v1, v2;				//v1、v2表示点的位置、w表示该点权值
	cout << "输入总顶点数：";
	cin >> G.vexnum;				//输入总顶点数、总边数
	cout << "输入总边数：";
	cin >> G.arcnum;

	cout << "依次输入顶点名称：";
	for (i = 0; i < G.vexnum; ++i)	//依次输入点的信息
		cin >> G.vexs[i];

	for (i = 0; i < G.vexnum; ++i)	//初始化邻接矩阵、边的权值	均置为极大值MaxInt
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;

	for (k = 0; k < G.arcnum; ++k)	//构建邻接矩阵
	{
		cout << "输入一条边的起点、终点及权值:";
		cin >> v1 >> v2 >> w;		//输入一条边依附的顶点及权值
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);		//确定v1、v2在G中的位置，即顶点数组下标
		if (i == ERROR || j == ERROR)
		{
			cout << "顶点不存在！" << endl;
			return ERROR;
		}
		G.arcs[i][j] = w;			//边<v1,v2>的权值置为w 对称边<v2,v1>的权值为w
	}
	return OK;
}
//用Dijkstra算法求有向网的v0顶点到其余顶点的最短路径
void ShortestPath_DIJ(AMGraph G, int v0, int *D, int *Path)
{
	int n, v, i, min, w, max, m;
	int S[20];
	n = G.vexnum;					//n为G中顶点的个数
	for (v = 0; v < n; ++v)			//n个顶点依次初始化
	{
		S[v] = false;				//S初始为空集
		D[v] = G.arcs[v0][v];		//将v0到各个终点的最短路径长度初始化为弧上的权值
		if (D[v] < MaxInt)			//如果v0和v之间有弧，则将v的前驱置为v0
			Path[v] = v0;
		else						//如果v0和v之间无弧，则将v的前驱置为-1
			Path[v] = -1;
	}
	S[v0] = true;					//将v0加入S
	D[v0] = 0;						//源点到源点的距离为0
	/*-----初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加到S集-----*/
	for (i = 1; i < n; ++i)			//对其余n-1个顶点，依次进行计算
	{
		min = MaxInt;
		for (w = 0; w < n; ++w)
			if (!S[w] && D[w] < min)
			{
				v = w;
				min = D[w];			//选择一条当前的最短路径，终点为v
			}
		S[v] = true;				//将v加入S
		for (w = 0; w < n; ++w)		//更新从v0出发到集合V-S上所有顶点的最短路径长度
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];		//更新D[w]
				Path[w] = v;					//更新w的前驱为v
			}
	}
}
