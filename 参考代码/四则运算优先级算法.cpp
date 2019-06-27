#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// �����ʾ�ִ����͵�ö������
enum TokenType { Token_Operator, Token_Value };

// ��ʾһ���ִʵĽṹ�壬�ִʿ�����һ���������������һ����������
struct Token
{
	TokenType Type;   // �ִ�����
	union
	{
		int Operator; // ���������
		double Value; // ��������ֵ
	};
};

// ����������ı��룬����ǲ���ʶ��������������-1��
int GetOperator(char op)
{
	static char Operators[] = "+-*/()";
	if (op == '\0') return 0;
	for (int i = 0; Operators[i] != '\0'; i++)
		if (Operators[i] == op) return i + 1;   // ��ֹ���������Լ��Ϊ0��ʵ������������1��ʼ��
	return -1;
}

// �ӱ��ʽ������ȡ������һ���ʣ����޸�exp����ָ��ȡ��֮��Ĵ���
int GetToken(Token &aToken, char *&exp)
{
	char *p = exp;
	
	// �Թ��հ׷�
	while (isspace(*p)) p++;

	// ������ʽ���Ѿ�������������һ�����������
	if (*p == '\0')
	{
		aToken.Type = Token_Operator;
		aToken.Operator = 0;
		return 0;
	}

	// ����Ƿ�Ϊ���֣�����Լ����֧����С���㿪ʼ����ֵд��������֧����".13"�Ĳ�����д����
	if (isdigit(*p))
	{
		// ��ȡһ��������
		aToken.Type = Token_Value;
		double aValue = 0.0;
		// ���ַ���ȡ�������֣��������ֵ
		for (; *p != '\0' && isdigit(*p); p++)
		{
			aValue = aValue * 10 + (*p - '0');
		}
		// ��ȡС������
		if (*p == '.')
		{
			// ����С����
			p++;
			// ���ַ���ȡС�����֣��������ֵ
			double aDecimal = 0.1;
			for (; *p != '\0' && isdigit(*p); p++)
			{
				aValue += (*p - '0') * aDecimal;
				aDecimal /= 10.0;
			}
			if (*p == '.') return -1;
		}
		aToken.Value = aValue;
	}
	else
	{
		// ��ȡһ�������
		aToken.Type = Token_Operator;
		int aOperator = GetOperator(*p);
		if (aOperator < 0) return -2;
		aToken.Operator = aOperator;
		p++;
	}

	exp = p;
	return 0;
}

char *priorities[] = 
{
	//       #+-*/()
	/* # */ "E<<<<<X",
	/* + */ ">>><<<>",
	/* - */ ">>><<<>",
	/* * */ ">>>>><>",
	/* / */ ">>>>><>",
	/* ( */ "X<<<<<=",
	/* ) */ "XXXXXXX",
};

double calc(double aValue1, int aOperator, double aValue2)
{
	switch (aOperator)
	{
	case 1:
		return aValue1 + aValue2;
	case 2:
		return aValue1 - aValue2;
	case 3:
		return aValue1 * aValue2;
	case 4:
		return aValue1 / aValue2;
	default:
		throw "����ʶ��������";
	}
}

double calc(char exp[])
{
	char *p = exp;
	
	stack<int> sOp;   // �����ջ
	stack<double> sValue; // ������ջ
	sOp.push(0);  // ��ʼ�������ջ
	
	while (true)
	{
		Token aToken;
		// ��ȡһ���ִ�
		if (GetToken(aToken, p) != 0) throw "�������ʽ����(����ʶ��������)��";

		// ��������ķִ�
		switch (aToken.Type)
		{
		case Token_Operator:
			// ���������ʱ�����������ջ��ջ�����ȼ��ߵ������
			while (priorities[sOp.top()][aToken.Operator] == '>')
			{
				if (sValue.empty()) throw "�������ʽ����(û���㹻�Ĳ�����)��";
				double aValue2 = sValue.top(); sValue.pop();
				if (sValue.empty()) throw "�������ʽ����(û���㹻�Ĳ�����)��";
				double aValue1 = sValue.top(); sValue.pop();
				int aOperator = sOp.top(); sOp.pop();
				sValue.push(calc(aValue1, aOperator, aValue2));
			}
			switch (priorities[sOp.top()][aToken.Operator])
			{
			case '<':
				sOp.push(aToken.Operator);
				break;
			case '=':
				sOp.pop();
				break;
			case 'E':
			{
				if (sValue.empty()) throw "�������ʽ����(ȱ�ٽ��)��";
				double aResult = sValue.top(); sValue.pop();
				if (!sValue.empty()) throw "�������ʽ����(�ж���Ĳ�����)��";
				return aResult;
			}
			case 'X':
				throw "�������ʽ����(����������˳��)��";
			}
			break;
		case Token_Value:
			// ����������ʱ����������ջ����
			sValue.push(aToken.Value);
			break;
		}
	}
}

int main()
{
	char exp[1024];

	cout << "������ʽ��" << endl;
	while (cin.getline(exp, sizeof(exp) / sizeof(*exp)))
	{
		try
		{
			double result = calc(exp);
			cout << exp << " = " << result << endl;
		}
		catch (char *err)
		{
			cerr << err << endl;
		}
		catch (...)
		{
			cerr << "�������ʽʧ�ܣ�" << endl;
		}
	}
	return 0;
}