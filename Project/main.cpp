#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
#include <iomanip>
#include "picture.h"

using namespace std;

void show(AMGraph G, int* D, int* Path) 
{
	for (int i = 0; i < G.vexnum; ++i) 
	{
		if (D[i] == MaxInt) 
		{
			cout << "��v0�� " << G.vexs[i] << " ���·��������" << endl;
		}
		else 
		{
			cout << "��v0�� " << G.vexs[i] << " ������·��Ϊ��" << G.vexs[i];
			int pre = Path[i];
			while (pre != -1) 
			{
				cout << " <- " << G.vexs[pre];
				pre = Path[pre];
			}
			cout << "������Ϊ��" << D[i] << endl;
		}
	}
}

int main()
{
	int D[10];
	int Path[20];
	AMGraph G;
	CreateDN(G);
	cout << "v0����������·��(����v0)��";
	int v0;
	char v01;
	cin >> v01;
	for (v0 = 0; v0 < G.vexnum; ++v0)
	{
		if (G.vexs[v0] == v01)
			break;
	}
	ShortestPath_DIJ(G, v0, D, Path);
	show(G, D, Path);
	return 0;
}
