#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<int> list1;

	// �������
	for (int i = 0; i < 10; i++)
		list1.push_back(i);

	// �±귽ʽ�������
	for (int i = 0; i < list1.size(); i++)
		cout << list1[i] << ", ";
	cout << endl;

	// ��������
	list1.insert(list1.begin(), 10); // ��10���뵽�±�0λ��
	list1.insert(list1.begin() + 2, 20); // ��20���뵽�±�2λ��

	// �±귽ʽ�������
	for (int i = 0; i < list1.size(); i++)
		cout << list1[i] << ", ";
	cout << endl;

	// ɾ���±�Ϊ5������
	list1.erase(list1.begin() + 5); 

	// �±귽ʽ�������
	for (int i = 0; i < list1.size(); i++)
		cout << list1[i] << ", ";
	cout << endl;

	// �±귽ʽ�������
	for (int i = 0; i < list1.size(); i++) 
		cout << list1[i] << ", ";
	cout << endl;

	// �������������
	for (vector<int>::iterator it = list1.begin(); it != list1.end(); it++)
		cout << *it << ", ";
	cout << endl;

	return 0;
}
