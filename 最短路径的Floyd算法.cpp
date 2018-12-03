﻿#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <stack>
using namespace std;

// 弧结点定义
struct ArcNode
{
	int weight;		// 弧上的信息部分
	int adj;		// 邻接点的序号
	ArcNode *nextarc;
};

// 顶点结点定义 
struct VexNode
{
	string info;		// 顶点上的信息部分
	ArcNode *firstarc;	// 弧链头指针
};

// 邻接表结构的图的定义
struct Graph
{
	VexNode *vexes;
	int vexnumber, arcnumber;
};

int InitGraph(Graph &G, int vexnumber)
{
	G.vexes = new VexNode[vexnumber];
	G.vexnumber = vexnumber;
	G.arcnumber = 0;
	for (int i = 0; i < vexnumber; i++)
		G.vexes[i].firstarc = NULL;
	return 0;
}
int DestroyGraph(Graph &G)
{
	for (int i = 0; i < G.vexnumber; i++)
	{
		while (G.vexes[i].firstarc != NULL)
		{
			ArcNode *p = G.vexes[i].firstarc;
			G.vexes[i].firstarc = p->nextarc;
			delete p;
		}
	}
	delete[]G.vexes;
	G.vexes = NULL;
	G.vexnumber = 0;
	return 0;
}
int InsertArc(Graph &G, int i, int j, int weight)
{
	ArcNode *aArcNode = new ArcNode;
	aArcNode->weight = weight;
	aArcNode->adj = j;
	aArcNode->nextarc = G.vexes[i].firstarc;
	G.vexes[i].firstarc = aArcNode;
	G.arcnumber++;
	return 0;
}
int CreateDemoGraph(Graph &G)
{
	InitGraph(G, 6);
	int arcs[][3] = { { 0, 1, 17 },{ 0, 2, 21 },{ 0, 3, 12 },{ 0, 4, 5 },{ 1, 0, 6 },{ 1, 5, 4 },{ 2, 0, 10 },{ 2, 3, 14 },{ 3, 1, 11 },{ 3, 5, 4 },{ 4, 1, 4 },{ 4, 2, 13 },{ 5, 0, 9 },{ 5, 4, 20 }, };
	for (int i = 0; i < sizeof(arcs) / sizeof(*arcs); i++)
	{
		InsertArc(G, arcs[i][0], arcs[i][1], arcs[i][2]);
	}
	return 0;
}

vector<vector<int>> Floyd(Graph &G)
{
    // 创建Path矩阵
    vector<vector<int>> aPaths(G.vexnumber);
    for (auto &r : aPaths)
        r.resize(G.vexnumber);

	// 创建shortest矩阵
    vector<vector<int>> shortest(G.vexnumber);
    for (auto &r : shortest)
        r.resize(G.vexnumber);
	
	// 初始化shortest和Path，即P(i, j, -)
	for (int i = 0; i < G.vexnumber; i++)
		for (int j = 0; j < G.vexnumber; j++)
		{
			shortest[i][j] = INT_MAX;
			aPaths[i][j] = -1;
		}
	for (int i = 0; i < G.vexnumber; i++)
		for (ArcNode *p = G.vexes[i].firstarc; p != NULL; p = p->nextarc)
		{
			shortest[i][p->adj] = p->weight;
			aPaths[i][p->adj] = i;
		}

	// 迭代计算P(i, j, k)
	for (int k = 0; k < G.vexnumber; k++)
		for (int i = 0; i < G.vexnumber; i++)
			for (int j = 0; j < G.vexnumber; j++)
			{
				if (shortest[i][k] < INT_MAX && shortest[k][j] < INT_MAX && shortest[i][k] + shortest[k][j] < shortest[i][j])
				{
					shortest[i][j] = shortest[i][k] + shortest[k][j];
					aPaths[i][j] = aPaths[k][j];
				}
			}

	return aPaths;
}

int OutputPath(vector<vector<int>> &Path, int aStart, int aEnd)
{
	if (aStart == aEnd)
		cout << aStart;
	else
	{
		OutputPath(Path, aStart, Path[aStart][aEnd]);
		cout << " -> " << aEnd;
	}
	return 0;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);

	vector<vector<int>> Path = Floyd(G);

	for (int i = 0; i < G.vexnumber; i++)
		for (int j = 0; j < G.vexnumber; j++)
		{
			if (i == j || Path[i][j] < 0) continue;
			OutputPath(Path, i, j);
			cout << endl;
		}

	DestroyGraph(G);
	system("pause");
	return 0;
}
