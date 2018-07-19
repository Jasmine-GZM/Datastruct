#include <iostream>
#include <string>
#include <climits>
#include <stack>
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
	InitGraph(G, 12);
	int arcs[][3] = { { 0, 1, 5 },{ 0, 2, 3 },{ 1, 3, 10 },{ 1, 6, 12 },{ 2, 3, 4 },{ 2, 4, 18 },{ 3, 5, 9 },{ 3, 6, 3 },{ 4, 10, 20 },{ 5, 7, 17 },{ 6, 8, 10 },{ 7, 9, 9 },{ 7, 11, 19 },{ 8, 9, 21 },{ 8, 10, 5 },{ 9, 11, 12 },{ 10, 11, 15 }, };
	for (int i = 0; i < sizeof(arcs) / sizeof(*arcs); i++)
	{
		InsertArc(G, arcs[i][0], arcs[i][1], arcs[i][2]);
	}
	return 0;
}

int CriticalPath(Graph &G, int(*aCriticalArcs)[2])
{
	// ͳ�Ƹ��������
	int *indegree = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) indegree[i] = 0;
	for (int i = 0; i < G.vexnumber; i++)
		for (ArcNode *p = G.vexes[i].firstarc; p != NULL; p = p->nextarc)
			indegree[p->adj]++;

	// ���Ϊ0�Ķ�����ջ
	stack<int> s;
	for (int i = 0; i < G.vexnumber; i++)
		if (indegree[i] == 0) s.push(i);

	// �������򣬲�����������㶥���ve
	int *ve = new int[G.vexnumber];
	for (int i = 0; i < G.vexnumber; i++) ve[i] = 0;
	stack<int> s2; // ������¼������
	while (!s.empty())
	{
		// ȡ��һ�������򶥵㣬����¼��s2ջ�У�����������������
		int i = s.top(); s.pop();
		s2.push(i);
		// ����Vi�������ڽӵ�
		for (ArcNode *p = G.vexes[i].firstarc; p != NULL; p = p->nextarc)
		{
			// ��Vi���ڽӵ�Vj��ȼ�1������0��Vj��ջ�ȴ���������
			int j = p->adj;
			indegree[j]--;
			if (indegree[j] == 0) s.push(p->adj);

			// ����Vj��veֵ
			if (ve[i] + p->weight > ve[j])
				ve[j] = ve[i] + p->weight;
		}
	}

	// ������������㶥���vl���յ��veֵ��Ϊvl�ĳ�ֵ
	int *vl = new int[G.vexnumber];
	int maxve = ve[s2.top()];
	for (int i = 0; i < G.vexnumber; i++) vl[i] = maxve;
	while (!s2.empty())
	{
		int i = s2.top(); s2.pop();
		// ��Vi���ڽӵ�������Vi��vlֵ
		for (ArcNode *p = G.vexes[i].firstarc; p != NULL; p = p->nextarc)
		{
			int j = p->adj;
			if (vl[j] - p->weight < vl[i])
				vl[i] = vl[j] - p->weight;
		}
	}

	// �������еĻ������㻡��e��lֵ����ѡ�ؼ�����e��l��ȵĻ���
	int count = 0;
	for (int i = 0; i < G.vexnumber; i++)
	{
		for (ArcNode *p = G.vexes[i].firstarc; p != NULL; p = p->nextarc)
		{
			int e = ve[i];
			int l = vl[p->adj] - p->weight;
			if (e == l)
			{
				aCriticalArcs[count][0] = i;
				aCriticalArcs[count][1] = p->adj;
				count++;
			}
		}
	}

	delete[]indegree;
	delete[]ve;
	delete[]vl;
	return count;
}

int main()
{
	Graph G;
	CreateDemoGraph(G);

	int(*Path)[2] = new int[G.arcnumber][2];
	int n = CriticalPath(G, Path);
	for (int i = 0; i < n; i++)
	{
		cout << Path[i][0] << " -> " << Path[i][1] << endl;
	}
	cout << endl;

	DestroyGraph(G);
	delete[]Path;
	system("pause");
	return 0;
}
