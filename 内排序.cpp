#include <iostream>
#include <ctime>
using namespace std;

// ֱ�Ӳ������򷨣�Ԥ����L[0]λ�ã����ݴ�L[1]~L[n]
int InsertSort(int L[], int n)
{
	for (int i = 2; i <= n; i++)
	{
		L[0] = L[i];
		for (int j = i; L[j - 1] > L[j]; j--)
			swap(L[j - 1], L[j]);
	}
	return 0;
}

// ֱ�ӽ������򷨣�ð������
int SwapSort(int L[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		bool swapped = false;
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (L[j] > L[j + 1])
			{
				swap(L[j], L[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
	return 0;
}

// ��������Ļ��ֹ���
int Partition(int L[], int s, int t)
{
	int temp = L[s];
	int low = s, high = t;
	while (low <  high)
	{
		while (low < high && L[high] >= temp) high--;
		L[low] = L[high];
		while (low < high && L[low] <= temp) low++;
		L[high] = L[low];
	}
	L[low] = temp;
	return low;
}
// ��������ĵݹ����
int QSort(int L[], int s, int t)
{
	if (s >= t) return 0;
	int k = Partition(L, s, t);
	QSort(L, s, k - 1);
	QSort(L, k + 1, t);
	return 0;
}
// �������򷨵�������
int QuickSort(int L[], int n)
{
	return QSort(L, 0, n - 1);
}

// ��L[s]~L[n-1]���жѵ���
int HeapAdjust(int L[], int n, int s)
{
	int i = s;
	// ��ָ����������Ҷ��㣨û�����Ӽ�ΪҶ��㣩
	while (i + i + 1 < n)
	{
		// ȷ�����i������ӽ��j
		int j = i + i + 1;						// ��ȡ���i������Ϊj
		if (j + 1 < n && L[j] < L[j + 1]) j++;	// ������i�����������ӱ����Ӵ���ȡ����Ϊj
		if (L[j] <= L[i]) break;				// ������i������ӽ��j���Ƚ��i��������Ҫ�ٵ����ˡ�
		swap(L[j], L[i]);						// ������i������ӽ��j�Ƚ��i���򽻻����i��j
		i = j;									// �����������Ƶ����j
	}
	return 0;
}
// ��ָ�����������д���һ���󶥶�
int CreateHeap(int L[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		HeapAdjust(L, n, i);
	}
	return 0;
}
// ������
int HeapSort(int L[], int n)
{
	// �Ƚ����������д�����һ���󶥶�
	CreateHeap(L, n);
	// ��ʼ���򣬴�����Ĵ󶥶ѵĽ������n�ݼ���1
	for (int i = n; i > 1; i--)
	{
		// �����Ѷ������һƬҶ��
		swap(L[0], L[i - 1]);
		// ����
		HeapAdjust(L, i - 1, 0);
	}
	return 0;
}

// ����ȡֵ��Χ1~n��������У��Ŷ�����Ϊm
int CreateRandSequence(int L[], int n, int m)
{
	for (int i = 0; i < n; i++)
		L[i] = i + 1;
	for (int i = 0; i < m; i++)
		swap(L[rand() % n], L[rand() % n]);
	return 0;
}

// �������
int OutputSequence(const char *title, int L[], int n)
{
	cout << title;
	for (int i = 0; i < n; i++)
		cout << L[i] << ", ";
	cout << endl;
	return 0;
}

int main()
{
	srand((unsigned int)time(NULL));
	int *L0, *L;
	int n = 16, m = 20;
	L0 = new int[n];
	L = new int[n + 1];
	CreateRandSequence(L0, n, m);

	memcpy(L + 1, L0, n * sizeof(int));
	OutputSequence("ԭʼ���У�", L + 1, n);
	InsertSort(L, n);
	OutputSequence("ֱ�Ӳ�����������", L + 1, n);

	memcpy(L, L0, n * sizeof(int));
	OutputSequence("\nԭʼ���У�", L, n);
	SwapSort(L, n);
	OutputSequence("ֱ�ӽ�����������", L, n);

	memcpy(L, L0, n * sizeof(int));
	OutputSequence("\nԭʼ���У�", L, n);
	QuickSort(L, n);
	OutputSequence("������������", L, n);

	memcpy(L, L0, n * sizeof(int));
	OutputSequence("\nԭʼ���У�", L, n);
	HeapSort(L, n);
	OutputSequence("����������", L, n);

	delete[]L;
	delete[]L0;
	system("pause");
	return 0;
}