#include <iostream>
#include <algorithm>
using namespace std;

struct HuffmanNode
{
	char info;
	int weight;
	int parent, lchild, rchild;
};
// ��������������sort�㷨��Ҫʹ��������ص������
bool operator<(const HuffmanNode &node1, const HuffmanNode &node2)
{
	return node1.weight < node2.weight;
}

struct HuffmanTree
{
	HuffmanNode *nodes;
	int leafnumber;
};

int CreateHuffmanTree(HuffmanTree &T, int leafnumber, int *weights)
{
	// ������������洢�ռ�
	T.nodes = new HuffmanNode[leafnumber + leafnumber - 1];
	T.leafnumber = leafnumber;

	// ��ʼ��Ҷ���
	for (int i = 0; i < leafnumber; i++)
	{
		T.nodes[i].info = 'a' + i;
		T.nodes[i].weight = weights[i];
		T.nodes[i].parent = T.nodes[i].lchild = T.nodes[i].rchild = -1;
	}
	
	// ��Ҷ��㰴Ȩֵ����
	sort(T.nodes, T.nodes + leafnumber);
	
	// ��ʼ�����������
	int s = 0, t = leafnumber; // �ֱ���������Ҷ���ͷ�Ҷ���
	for (int i = 0; i < leafnumber - 1; i++)
	{
		// ѡ���һ��Ȩֵ��С�ĸ����
		int k1;
		if (s < leafnumber && (t >= leafnumber + i || T.nodes[s].weight < T.nodes[t].weight))
			k1 = s++;
		else
			k1 = t++;
		
		// ѡ��ڶ���Ȩֵ��С�ĸ����
		int k2;
		if (s < leafnumber && (t >= leafnumber + i || T.nodes[s].weight < T.nodes[t].weight))
			k2 = s++;
		else
			k2 = t++;

		// �������k1, �����k2�ϲ������������i + leafnumber��
		T.nodes[i + leafnumber].weight = T.nodes[k1].weight + T.nodes[k2].weight;
		T.nodes[i + leafnumber].parent = -1;
		T.nodes[i + leafnumber].lchild = k1;
		T.nodes[i + leafnumber].rchild = k2;
		T.nodes[k1].parent = i + leafnumber;
		T.nodes[k2].parent = i + leafnumber;
	}

	return 0;
}

int main()
{
	HuffmanTree T;
	int weights[] = { 3, 7, 8, 6, 21 };
	CreateHuffmanTree(T, 5, weights);

	for (int i = 0; i < T.leafnumber + T.leafnumber - 1; i++)
	{
		cout << i << ":" << T.nodes[i].weight << ", " << T.nodes[i].parent << ", " << T.nodes[i].lchild << ", " << T.nodes[i].rchild << endl;
	}

	system("pause");
	return 0;
}