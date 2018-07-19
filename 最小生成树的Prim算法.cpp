#include <iostream>
#include <string>
#include <climits>
using namespace std;

// ����㶨��
struct ArcNode
{
	int weight;		// ���ϵ���Ϣ����
	int adj;		// �ڽӵ�����
	ArcNode *nextarc;
};

// �����㶨�� 
struct VexNode
{
	string info;		// �����ϵ���Ϣ����
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
int InsertArc(Graph &G, int i, int j, int weight)
{
	ArcNode *aArcNode = new ArcNode;
	aArcNode->weight = weight;
	aArcNode->adj = j;
	aArcNode->nextarc = G.vexes[i].firstarc;
	G.vexes[i].firstarc = aArcNode;
	return 0;
}
int CreateDemoGraph(Graph &G)
{
	// ��ʼ��ͼ�洢�ṹ
	InitGraph(G, 7);
	
	// ��ʼ��������Ϣ
	string infos[] = { "�߼�ׯ", "��Һ���", "��Ƥ��", "�ܼұ�", "������", "��ɽ��", "���ʹ�" };
	for (int i = 0; i < G.vexnumber; i++)
		G.vexes[i].info = infos[i];
	
	// ��ʼ������Ϣ
	int arcs[][3] = { { 0, 1, 10 },{ 0, 2, 9 },{ 0, 3, 13 },{ 1, 3, 15 },{ 1, 4, 7 },{ 1, 6, 12 },{ 2, 3, 4 },{ 2, 5, 3 },{ 3, 5, 22 },{ 3, 6, 23 },{ 4, 6, 20 },{ 5, 6, 32 }, };
	for (int i = 0; i < sizeof(arcs) / sizeof(*arcs); i++)
	{
		// ����ͼ�ı��������ԳƵĻ���� 
		InsertArc(G, arcs[i][0], arcs[i][1], arcs[i][2]);
		InsertArc(G, arcs[i][1], arcs[i][0], arcs[i][2]);
	}
	return 0;
}

int Prim(Graph &G, int(*T)[2])
{
	// ��ʼ��U������U[i]��ʾVi�Ƿ���U���У�1��ʾ�ڣ�0��ʾ����
	int *U = new int[G.vexnumber];
	U[0] = 1;
	for (int i = 1; i < G.vexnumber; i++) U[i] = 0;

	// ��ʼ��cost������cost[i]��ʾVi��U������̱ߵ�Ȩֵ
	// ��ʼʱ��U��ֻ��V0�����cost[i]����<V0, Vi>��Ȩֵ
	int *cost = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) cost[i] = INT_MAX;
	for (ArcNode *p = G.vexes[0].firstarc; p != NULL; p = p->nextarc)
		cost[p->adj] = p->weight;

	// ��ʼ��adj������adj[i]��ʾVi��U������̱���U�е��ڽӵ�����
	// ��ʼʱ��U��ֻ��V0�����adj[i]Ϊ0
	int *adj = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++)
		adj[i] = 0;

	// ����MST������ѡn-1����
	for (int i = 0; i < G.vexnumber - 1; i++)
	{
		// ����V-U��cost��С�Ķ���k 
		int k = -1;
		for (int j = 0; j < G.vexnumber; j++)
		{
			if (!U[j] && (k == -1 || cost[j] < cost[k]))
				k = j;
		}

		// ������k����U��
		U[k] = 1;
		// �ռ�һ����<Vk, Vadj[k]>
		T[i][0] = k;
		T[i][1] = adj[k];

		// ����V-U��ʣ�ඥ���cost��adj��ֻ�ж���k���ڽӵ���Ҫ�������� 
		for (ArcNode *p = G.vexes[k].firstarc; p != NULL; p = p->nextarc)
		{
			// �Զ���Vj������³��ֵĿ�U��V-U�ı�<Vk, Vj>�Ƿ��ԭ���Ŀ�U��V-U����̱߸���
			int j = p->adj;
			if (!U[j] && p->weight < cost[j])
			{
				cost[j] = p->weight;
				adj[j] = k;
			}
		}
	}

	delete[]adj;
	delete[]cost;
	delete[]U;
	return 0;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);

	int(*T)[2] = new int[G.vexnumber - 1][2];
	Prim(G, T);
	for (int i = 0; i < G.vexnumber - 1; i++)
		cout << G.vexes[T[i][0]].info << " -- " << G.vexes[T[i][1]].info << endl;

	DestroyGraph(G);
	delete[]T;
	return 0;
}
