#include <iostream>
#include <list>
using namespace std;
int main()
{
	list<int> list1;

	// �������
	for (int i = 0; i < 10; i++) list1.push_back(i);

	// �������������
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) cout << *it << ", ";
	cout << endl;

	// ��ÿ������ǰ������10��
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) list1.insert(it, *it * 10);

	// �������������
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) cout << *it << ", ";
	cout << endl;

	// ������������ɾ������3�ı���
	list<int>::iterator it = list1.begin();
	while (it != list1.end())
	{
		if (*it % 3 == 0) it = list1.erase(it); else it++;
	}

	// �������������
	for (list<int>::iterator it = list1.begin(); it != list1.end(); it++) cout << *it << ", ";
	cout << endl;

	return 0;
}
