#include "Stack.h"
#include <map>
using namespace std;
Stack* op;//�����ջ
Stackf* num;//����ջ
map<int, int> order;//��������ȼ�����
bool doing = false;//���ڴ���
bool opOnly = false;//���˱�־Ϊtrueʱ,ֻ�����������
bool isNum = false; //��ʶ�������в���
bool isFloat = false;//��ʶ�Ը���������
int deci = 1;//С��λ����isFloatΪtrueʱÿ��pushNumʱ��deci*10,pushOpʱ����Ϊ1
//�жϵ�ǰ������Ƿ�����ջ
bool can_push(int chr);
//��ʼ�������ջ������ջ����������ȼ�������״̬
void init(void);
//�������ʽ����ʱ������£�errΪtrueʱ��ʾ������������
void endExp(bool err);
//����ѹջ��ͬʱ�����λ���븡����
void pushNum(float num);
//�����ѹջ��ͬʱ���㣬���쳣����true,�쳣����false
bool pushOp(char op);
//�������ջ������
bool calc();
int main()
{ 
	init();
	char chr = 0;
	while(true)
	{
		if (!doing)
		{
			cout << "��������ʽ(����@�˳�����):" << endl;
			doing = true;
		}
		chr = cin.get();
		if (chr == '\n')
			endExp(false);
		if (chr == '@')
			return 0;
		//��������ѹջ,isNum��Ϊtrue
		else if (chr >= '0' && chr <= '9' && !opOnly)
		{
			if (!isNum)cout << " ";
			cout << chr;//�������׺���ʽ
			pushNum(float(chr - '0'));
			isNum = true;
		}
		//����'.'��Ϊ����״̬������С��״̬���ɽ���ʱ
		//����ΪС������
		//�������
		else if (chr == '.'&& !opOnly && isNum && !isFloat)
		{
				isFloat = true;
				cout << chr;//�������׺���ʽ
		}
		//����������������ѹջ,���������״̬
		else if (chr == '('&& !opOnly)
		{
			pushOp(chr);
			isNum = false;
			isFloat = false;
		}
		//������״̬����������ʱѹջ
		//���������״̬,���opOnly���������
		else if (chr == '+' && (isNum || opOnly))
		{
			isNum = false;
			isFloat = false;
			opOnly = false;
			pushOp(chr);
		}
		//������״̬����������ʱѹջ
		//������ѹ��0����ѹ��'-'
		//�������״̬
		else if (chr == '-')
		{
			if (isNum || opOnly)//Ϊ˫Ŀ�����
				pushOp(chr);
			else//Ϊ��Ŀ�����
			{
				cout << " 0";
				pushNum(0);
				if (!pushOp(chr))
					endExp(true);
			}
			isNum = false;
			isFloat = false;
			opOnly = false;
		}
		//����������Ϊ��Ŀ��������ַ�ʱ
		//����״̬�����������ʱѹջ
		//������Ϊ�µ����룬����ջ��
		//�������״̬
		else if (chr == '*' || chr == '/' || chr == '%')
		{
			if (isNum || opOnly)
				pushOp(chr);
			else
				op->top->val = chr;
			isNum = false;
			isFloat = false;
			opOnly = false;
		}
		//����������ʱ״̬��Ϊ���������
		//��ջ����ֱ������������
		//�䱾��ѹջ
		//�������״̬
		else if (chr == ')')
		{
			opOnly = true;//������������֮���¸��ַ�ֻ��Ϊ˫Ŀ�������������
			while (true)
			{
				if (op->top->val == '(')
				{
					op->pop();
					break;
				}
				else if (!calc())
					endExp(true);
			}
		}
	}
}
void init(void)
{
	op = new Stack;
	num = new Stackf;
	order['-'] = 1;
	order['+'] = 1;
	order['*'] = 2;
	order['/'] = 2;
	order['%'] = 3;
}
bool can_push(int chr)
{
	if (op->top == NULL)return true;
	if (chr == '(')return true;
	return order[chr] > order[op->top-> val] ? true : false;
}
void pushNum(float x)
{
	if (!isNum)
	{
		num->push(x);
		return;
	}
	if (isFloat)
	{
		deci *= 10;//С��λ�������
		x = x/ deci;
		num->top->val += x;
	}
	else {
		num->top->val *= 10;
		num->top->val += x;
	}
}
bool pushOp(char chr)
{
	while (!can_push(chr))
	{
		if (!calc())
			return false;
	}
	op->push(chr);
	deci = 1;//ִ�д˺���˵��һ�����ֶ�ȡ��ϣ���С��λ����
	return true;
}
void endExp(bool err)
{
	doing = false;
	isNum = false;
	isFloat = false;
	opOnly = false;
	if (err)
	{
		error("error");
		return;
	}
	//���ʽ���������������ջ��Ԫ��
	while (!op->empty())
		if (!calc())
		{
			error("error");
			return;
		}
	//���ս������������ջ�У����
	cout <<endl<< num->pop() << endl;
}
bool calc()
{
	float a = num->pop();
	float b = num->pop();
	char  cur = op->pop();
	cout << cur;//�������׺���ʽ
	switch (cur)
	{
	case '+':
		num->push(b + a);
		break;
	case '-':
		num->push(b - a);
		break;
	case '*':
		num->push(b * a);
		break;
	case '/':
		if (0 == a)
			return false;
		else num->push(b / a);
		break;
	case '%':
		num->push((int)b % (int)a);
		break;
	default:
		return false;
	}
	return true;
}