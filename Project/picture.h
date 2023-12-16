#pragma once
#ifndef PICTURE_H
#define PICTURE_H

typedef int Status;
#define	OK		1
#define ERROR	-1

#define swap(a, b)	{a = a + b; b = a - b; a = a - b;}

//-------ͼ���ڽӾ���洢��ʾ--------//
#define MaxInt  32767       //��ʾ����ֵ������
#define MVNum   100         //��󶥵���     
typedef char VerTexType;	//���趥�����������Ϊ�ַ���
typedef int ArcType;		//����ߵ�Ȩֵ����Ϊ����
typedef struct
{
	VerTexType vexs[MVNum];		//�����
	ArcType arcs[MVNum][MVNum];	//�ڽӾ���
	int vexnum, arcnum;			//ͼ�ĵ�ǰ�����ͱ���
}AMGraph;

Status CreateUDN(AMGraph& G);		//�����ڽӾ����ʾ��������������G
Status CreateDN(AMGraph& G);			//�����ڽӾ����ʾ��������������G
Status LocateVex(AMGraph G, VerTexType u);
void ShortestPath_DIJ(AMGraph G, int v0, int* D, int* Path);
int ShortestPathMAX(AMGraph G, int v0);

#endif 
