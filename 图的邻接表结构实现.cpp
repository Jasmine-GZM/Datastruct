#include <iostream>
#include <string>
#include <queue>
using namespace std;

// ����㶨��
struct ArcNode
{
	// TODO: ���ϵ���Ϣ����
	int adj;		// �ڽӵ�����
	ArcNode *nextarc;
};

// �����㶨�� 
struct VexNode
{
	// TODO: �����ϵ���Ϣ����
	ArcNode *firstarc;	// ����ͷָ��
};

// �ڽӱ�ṹ��ͼ�Ķ���
struct Graph
{
	VexNode *vexes;
	int vexnumber;
};

int InitGraph(Graph &G, int vexnumber)
{
	G.vexes = new VexNode[vexnumber];
	G.vexnumber = vexnumber;
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
int InsertArc(Graph &G, int i, int j)
{
	ArcNode *aArcNode = new ArcNode;
	aArcNode->adj = j;
	aArcNode->nextarc = G.vexes[i].firstarc;
	G.vexes[i].firstarc = aArcNode;
	return 0;
}
int DFS(Graph &G, int v0, int visited[])
{
	cout << v0 << ", "; // Visit v0
	visited[v0] = 1;
	for (ArcNode *p = G.vexes[v0].firstarc; p != NULL; p = p->nextarc)
	{
		if (!visited[p->adj]) 
			DFS(G, p->adj, visited);
	}
	return 0;
}
int DFSTraverse(Graph &G)
{
	int *visited = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) visited[i] = 0;
	for (int i = 0; i < G.vexnumber; i++)
	{
		if (!visited[i])
			DFS(G, i, visited);
	}
	delete[]visited;
	return 0;
}
int BFS(Graph &G, int v0, int visited[])
{
	queue<int> q;
	q.push(v0); 
	visited[v0] = 1;
	while (!q.empty())
	{
		int v = q.front();
		q.pop();
		cout << v << ", "; // Visit
		for (ArcNode *p = G.vexes[v].firstarc; p != NULL; p = p->nextarc)
		{
			if (!visited[p->adj])
			{
				q.push(p->adj);
				visited[p->adj] = 1;
			}
		}
	}
	return 0;
}
int BFSTraverse(Graph &G)
{
	int *visited = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) visited[i] = 0;
	for (int i = 0; i < G.vexnumber; i++)
	{
		if (!visited[i])
			BFS(G, i, visited);
	}
	delete[]visited;
	return 0;
}
int CreateDemoGraph(Graph &G)
{
	InitGraph(G, 10);
	int arcs[][2] = { {0, 1}, {0, 2}, {1, 4}, {1, 7}, {2, 1}, {2, 4}, {3, 0}, {3,8}, {5, 2}, {5, 9}, {6, 9}, {7, 4}, {7, 5}, {8, 0}, {9, 5}, {9, 7} };
	for (int i = 0; i < sizeof(arcs) / sizeof(*arcs); i++)
	{
		InsertArc(G, arcs[i][0], arcs[i][1]);
	}
	return 0;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);
	
	cout << "��ȱ�����";
	DFSTraverse(G);
	cout << endl;

	cout << "��ȱ�����";
	BFSTraverse(G);
	cout << endl;

	DestroyGraph(G);
	return 0;
}