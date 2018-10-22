#include <iostream>	
#include <vector>
#include <cstring>
using namespace std;

// ͼ����Ϣ
struct Book
{
	char name[1024];
	char author[50];
	char code[20];
};
typedef vector<Book> Books;

// ��ӡͼ��Ŀ¼
int PrintBooks(Books &aLib)
{
	for (int i = 0; i < aLib.size(); i++)
	{
		cout << aLib.data[i].name << "\t"
			<< aLib.data[i].author << "\t"
			<< aLib.data[i].code << endl;
	}
	return 0;
}

// ����������ͼ���¼������ҵ���������ţ��±꣩�����û���ҵ���Լ������-1��
int FindBook(Books &aLib, char aName[])
{
	// ˳���������
	for (int i = 0; i < aLib.size(); i++)
	{
		if (strcmp(aLib.data[i].name, aName) == 0)
			return i;
	}
	return -1;
}

int ShowMenu()
{
	cout << "1. ���ͼ��" << endl;
	cout << "2. ������ɾ��ͼ��" << endl;
	cout << "3. ����������ͼ��" << endl;
	cout << "4. ��ӡͼ��Ŀ¼" << endl;
	cout << "0. �˳�" << endl;
	cout << "��ѡ��";

	int op;
	cin >> op;
	return op;
}

int main()
{
	Books lib;

	int op;
	while ((op = ShowMenu()) != 0)
	{
		switch (op)
		{
		case 1:
		{
			// ���ͼ�飨���ñ�׼���룬�������������ͱ����в��ܺ��пհ׷���
			Book aBook;
			int aIndex;
			cout << "���������� ���� ���� ���� ����λ�ã�";
			cin >> aBook.name >> aBook.author >> aBook.code >> aIndex;
			if (lib.insert(lib.begin() + aIndex, aBook) != lib.end())
				cout << "�����¼�ɹ���" << endl;
			else
				cout << "�����¼ʧ�ܣ�" << endl;
			break;
		}
		case 2:
		{
			// ������ɾ��ͼ��
			char aName[1024];
			cout << "������Ҫɾ��ͼ���������";
			cin >> aName;
			
			int aIndex = FindBook(lib, aName);
			if (aIndex < 0)
				cout << "û���ҵ���ͬ�����ļ�¼��" << endl;
			else 
            {
                lib.erase(lib.begin() + aIndex);
				cout << "ɾ��ͼ��ɹ���" << endl;
            }
			break;
		}
		case 3:
		{
			// ����������ͼ��
			char aName[1024];
			cout << "������Ҫ���ҵ�ͼ���������";
			cin >> aName;
			int aIndex = FindBook(lib, aName);
			if (aIndex < 0)
				cout << "û���ҵ���ͬ�����ļ�¼��" << endl;
			else
				cout << aIndex << ".\t"
				<< lib.data[aIndex].name << "\t"
				<< lib.data[aIndex].author << "\t"
				<< lib.data[aIndex].code << endl;
			break;
		}
		case 4:
		{
			// ��ӡͼ��Ŀ¼
			PrintBooks(lib);
			break;
		}
		}
	}

	return 0;
}
