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
			return i;				// �ҵ�����ֵΪu��λ�ã����ظ�λ���ڶ�����е����� i
	}
	return ERROR;					// û�ҵ������ش�����
}

Status InsertVex(AMGraph& G, int v)	//�����ڽӾ�����ʽ�洢������ͼG�ϲ��붥��v
{
	int k;
	if ((G.vexnum + 1) > MVNum)
		return ERROR;				//�жϲ�������Ƿ�Ϸ�
	G.vexnum++;						//����ͼ�Ķ�������
	G.vexs[G.vexnum] = v;			//���¶���v���붥���
	for (k = 0; k < G.vexnum; k++)	//�ڽӾ�����Ӧλ�õ�Ԫ����Ϊ0
		G.arcs[G.vexnum][k] = G.arcs[k][G.vexnum] = 0;
	return OK;
}

Status DeleteVex(AMGraph& G, char v)	//�����ڽӾ�����ʽ�洢������ͼG��ɾ������v
{
	int n, m, i;
	n = G.vexnum;
	if ((m = LocateVex(G, v)) < 0)	//�ж�ɾ�������Ƿ�Ϸ�����v�Ƿ���G��
		return ERROR;
	swap(G.vexs[m],G.vexs[n]);		//����ɾ�����㽻�������һ������
	for (i = 0; i < n; i++)			//���ߵĹ�ϵ��֮����
	{
		swap(G.arcs[m][i], G.arcs[n][i]);
		swap(G.arcs[i][m], G.arcs[i][n]);
	}
	G.vexnum--;						//����������1
	return OK;
}

Status InsertArc(AMGraph& G, char v, char w)	//�����ڽӾ�����ʽ�洢������ͼG�ϲ����(v,w)
{
	int i, j;
	if ((i = LocateVex(G, v)) < 0)	return ERROR;	//�жϲ���λ���Ƿ�Ϸ�
	if ((j = LocateVex(G, w)) < 0)	return ERROR;	//�жϲ���λ���Ƿ�Ϸ�
	if (i == j)	return ERROR;
	G.arcs[i][j] = G.arcs[j][i] = 1;				//���ڽӾ��������Ӷ�Ӧ�ı�
	G.arcnum++;										//������1
	return OK;
}

Status DeleteArc(AMGraph& G, char v, char w)	//�����ڽӾ�����ʽ�洢������ͼG��ɾ����(v,w)
{
	int i, j;
	if ((i = LocateVex(G, v)) < 0)	return ERROR;	//�жϲ���λ���Ƿ�Ϸ�
	if ((j = LocateVex(G, w)) < 0)	return ERROR;	//�жϲ���λ���Ƿ�Ϸ�
	G.arcs[i][j] = G.arcs[j][i] = 0;				//���ڽӾ�����ɾ����
	G.arcnum--;										//������1
	return OK;
}

Status CreateUDN(AMGraph& G)		//�����ڽӾ����ʾ��������������G
{
	int i, j, k, w;
	VerTexType v1, v2;				//v1��v2��ʾ���λ�á�w��ʾ�õ�Ȩֵ
	cout << "�����ܶ�������";
	cin >> G.vexnum;	//�����ܶ��������ܱ���
	cout << "�����ܱ�����";
	cin >> G.arcnum;

	cout << "�������붥�����ƣ�";
	for (i = 0; i < G.vexnum; ++i)	//������������Ϣ
		cin >> G.vexs[i];

	for (i = 0; i < G.vexnum; ++i)	//��ʼ���ڽӾ��󡢱ߵ�Ȩֵ	����Ϊ����ֵMaxInt
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;

	for (k = 0; k < G.arcnum; ++k)	//�����ڽӾ���
	{
		cout << "����һ���������Ķ��㼰Ȩֵ:";
		cin >> v1 >> v2 >> w;		//����һ���������Ķ��㼰Ȩֵ
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);		//ȷ��v1��v2��G�е�λ�ã������������±�
		if (i == ERROR || j == ERROR)
		{
			cout << "���㲻���ڣ�" << endl;
			return ERROR;
		}
		G.arcs[i][j] = w;			//��<v1,v2>��Ȩֵ��Ϊw �ԳƱ�<v2,v1>��ȨֵΪw
		G.arcs[j][i] = G.arcs[i][j];//��<v1,v2>�ĶԳƱ�<v2,v1>��ȨֵΪw
	}
	return OK;
}

//��Dijkstra�㷨��ͼG�о��붥��v0�����·����������һ������m
int ShortestPathMAX(AMGraph G, int v0)
{
	int n, v, i, min, w, max, m;
	int S[20], D[20], Path[20];
	n = G.vexnum;					//nΪG�ж���ĸ���
	for (v = 0; v < n; ++v)			//n���������γ�ʼ��
	{
		S[v] = false;				//S��ʼΪ�ռ�
		D[v] = G.arcs[v0][v];		//��v0�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
		if (D[v] = 0)				//���v0��v֮���л�����v��ǰ����Ϊv0
			D[v] = MaxInt;

		if (D[v] < MaxInt)			//���v0��v֮���л�����v��ǰ����Ϊv0
			Path[v] = v0;
		else						//���v0��v֮���޻�����v��ǰ����Ϊ-1
			Path[v] = -1;
	}
	S[v0] = true;					//��v0����S
	D[v0] = 0;						//Դ�㵽Դ��ľ���Ϊ0
	/*-----��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v�ӵ�S��-----*/
	for (i = 1; i < n; ++i)			//������n-1�����㣬���ν��м���
	{
		min = MaxInt;				
		for (w = 0; w < n; ++w)
			if(!S[w] && D[w]<min)
			{
				v = w;
				min = D[w];			//ѡ��һ����ǰ�����·�����յ�Ϊv
			}
		S[v] = true;				//��v����S
		for (w = 0; w < n; ++w)		//���´�v0����������V-S�����ж�������·������
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];		//����D[w]
				Path[w] = v;					//����w��ǰ��Ϊv
			}
	}
	/*-----���·�������ϣ�����붥��v0�����·����������һ������Ϊm-----*/
	max = D[0];
	m = 0;
	for (i = 1; i < n; i++)
		if (max < D[i])	
			m = i;
	return m;						//���ض����±�
}

Status CreateDN(AMGraph& G)			//�����ڽӾ����ʾ��������������G
{
	int i, j, k, w;
	VerTexType v1, v2;				//v1��v2��ʾ���λ�á�w��ʾ�õ�Ȩֵ
	cout << "�����ܶ�������";
	cin >> G.vexnum;				//�����ܶ��������ܱ���
	cout << "�����ܱ�����";
	cin >> G.arcnum;

	cout << "�������붥�����ƣ�";
	for (i = 0; i < G.vexnum; ++i)	//������������Ϣ
		cin >> G.vexs[i];

	for (i = 0; i < G.vexnum; ++i)	//��ʼ���ڽӾ��󡢱ߵ�Ȩֵ	����Ϊ����ֵMaxInt
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MaxInt;

	for (k = 0; k < G.arcnum; ++k)	//�����ڽӾ���
	{
		cout << "����һ���ߵ���㡢�յ㼰Ȩֵ:";
		cin >> v1 >> v2 >> w;		//����һ���������Ķ��㼰Ȩֵ
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);		//ȷ��v1��v2��G�е�λ�ã������������±�
		if (i == ERROR || j == ERROR)
		{
			cout << "���㲻���ڣ�" << endl;
			return ERROR;
		}
		G.arcs[i][j] = w;			//��<v1,v2>��Ȩֵ��Ϊw �ԳƱ�<v2,v1>��ȨֵΪw
	}
	return OK;
}
//��Dijkstra�㷨����������v0���㵽���ඥ������·��
void ShortestPath_DIJ(AMGraph G, int v0, int *D, int *Path)
{
	int n, v, i, min, w, max, m;
	int S[20];
	n = G.vexnum;					//nΪG�ж���ĸ���
	for (v = 0; v < n; ++v)			//n���������γ�ʼ��
	{
		S[v] = false;				//S��ʼΪ�ռ�
		D[v] = G.arcs[v0][v];		//��v0�������յ�����·�����ȳ�ʼ��Ϊ���ϵ�Ȩֵ
		if (D[v] < MaxInt)			//���v0��v֮���л�����v��ǰ����Ϊv0
			Path[v] = v0;
		else						//���v0��v֮���޻�����v��ǰ����Ϊ-1
			Path[v] = -1;
	}
	S[v0] = true;					//��v0����S
	D[v0] = 0;						//Դ�㵽Դ��ľ���Ϊ0
	/*-----��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v�ӵ�S��-----*/
	for (i = 1; i < n; ++i)			//������n-1�����㣬���ν��м���
	{
		min = MaxInt;
		for (w = 0; w < n; ++w)
			if (!S[w] && D[w] < min)
			{
				v = w;
				min = D[w];			//ѡ��һ����ǰ�����·�����յ�Ϊv
			}
		S[v] = true;				//��v����S
		for (w = 0; w < n; ++w)		//���´�v0����������V-S�����ж�������·������
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];		//����D[w]
				Path[w] = v;					//����w��ǰ��Ϊv
			}
	}
}
