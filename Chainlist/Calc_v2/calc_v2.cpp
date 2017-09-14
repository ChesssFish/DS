#include "Stack_v2.h"
#include <map>
using namespace std;
Stack* op;//�����ջ
Stackf* num;//����ջ
map<int, int> order;//��������ȼ�����
//�������״̬
//��״̬�Ĺ�ϵ�ڱ�������ͼ��
enum S
{
	START,
	INTEGER,
	FLOAT,
	OPERATOR,
	RIGHT_BRACE,
	LEFT_BRACE
}State;
int deci = 1;//С��λ����isFloatΪtrueʱÿ��pushNumʱ��deci*10,pushOpʱ����Ϊ1
//�жϵ�ǰ������Ƿ�����ջ
bool can_push(int chr);
//��ʼ�������ջ������ջ����������ȼ�������״̬
void init(void);
//�������ʽ����ʱ�Ĵ���
void endExp();
//����ѹջ��ͬʱ�����λ���븡����
void pushNum(float num);
//�����ѹջ��ͬʱ���㣬���쳣����true,�쳣����false
bool pushOp(char op);
//�������ջ������
//ͬʱ�жϱ��ʽ�Ƿ��д������򷵻�false, �޴���true
bool calc();
int main()
{ 
	init();
	char chr = 0;
	while(true)
	{
		if (State == START)
			cout << "��������ʽ(����@�˳�����):" << endl;
		chr = cin.get();
		if (chr == '\n')
			endExp();
		if (chr == '@')
			return 0;
		//��������ʱ
		else if (chr >= '0' && chr <= '9')
		{
			if (State == INTEGER || State == FLOAT)
			{
				pushNum(float(chr - '0'));
				cout << chr;//�������׺���ʽ
			}
			else if (State == OPERATOR || State == LEFT_BRACE || State == START)
			{
				pushNum(float(chr - '0'));
				cout << " " << chr;
				State = INTEGER;
			}
		}
		//����'.'��Ϊ����״̬ʱ���븡����״̬
		//�������
		else if (chr == '.'&& State == INTEGER)
		{
			cout << chr;//�������׺���ʽ
			State = FLOAT;
		}
		//����������������ѹջ,����������״̬
		else if (chr == '(' && (State == OPERATOR || State == START || State == LEFT_BRACE))
		{
			pushOp(chr);
			State = LEFT_BRACE;
		}
		//��Ŀ��˫Ŀ�����ʱ�Ĵ���
		else if (chr == '-')
		{
			if (State == START || State == LEFT_BRACE)//�������Ϊ��Ŀ�����
			{
				cout << 0;
				pushNum(0.0);
				pushOp(chr);
				State = OPERATOR;
			}
			else if (State == INTEGER || State == FLOAT || State == RIGHT_BRACE)
			{
				pushOp(chr);
				State = OPERATOR;
			}
		}
		//����˫Ŀ�����
		else if (chr == '+' || chr == '*' || chr == '/' || chr == '%')
		{
			if (State == INTEGER || State == FLOAT || State == RIGHT_BRACE)
			{
				pushOp(chr);
				State = OPERATOR;
			}
		}
		//���������ŵ�ջ���㣬״̬��ΪRIGHT_BRACE
		else if (chr == ')'&&(State == INTEGER || State == FLOAT))
		{
			State = RIGHT_BRACE;
			while (true)
			{
				if (op->top->val == '(')
				{
					op->pop();
					break;
				}
				//�������������op��num��State,׼�������µı��ʽ
				else if (!calc())
				{
					cout << endl;
					error("error");
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					num->makenull();
					op->makenull();
					State = START;
				}
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
	State = START;
}
bool can_push(int chr)
{
	if (op->top == NULL)return true;
	if (chr == '(')return true;
	return order[chr] > order[op->top-> val] ? true : false;
}
void pushNum(float x)
{
	if (State == INTEGER)
	{
		num->top->val *= 10;
		num->top->val += x;
	}
	else if (State == FLOAT)
	{
		deci *= 10;//С��λ�������
		x = x/ deci;
		num->top->val += x;
	}
	else {
		num->push(x);
		return;
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
void endExp()
{
	State = START;
	//���ʽ���������������ջ��Ԫ��
	while (!op->empty())
		if (!calc())
		{
			cout << endl;
			error("error");
			op->makenull();
			num->makenull();
			return;
		}
	//���ս������������ջ�У����
	cout <<endl<< num->pop() << endl;
}
bool calc()
{
	if (num->empty())return false;
	float a = num->pop();
	if (num->empty())return false;
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