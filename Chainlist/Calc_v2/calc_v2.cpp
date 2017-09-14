#include "Stack_v2.h"
#include <map>
using namespace std;
Stack* op;//运算符栈
Stackf* num;//数字栈
map<int, int> order;//运算符优先级定义
//定义程序状态
//各状态的关系在报告中有图解
enum S
{
	START,
	INTEGER,
	FLOAT,
	OPERATOR,
	RIGHT_BRACE,
	LEFT_BRACE
}State;
int deci = 1;//小数位数，isFloat为true时每次pushNum时，deci*10,pushOp时重置为1
//判断当前运算符是否能入栈
bool can_push(int chr);
//初始化运算符栈、数字栈、运算符优先级、操作状态
void init(void);
//算数表达式结束时的处理
void endExp();
//数字压栈，同时计算多位数与浮点数
void pushNum(float num);
//运算符压栈，同时计算，无异常返回true,异常返回false
bool pushOp(char op);
//运算符出栈并计算
//同时判断表达式是否有错，出错则返回false, 无错返回true
bool calc();
int main()
{ 
	init();
	char chr = 0;
	while(true)
	{
		if (State == START)
			cout << "请输入表达式(输入@退出程序):" << endl;
		chr = cin.get();
		if (chr == '\n')
			endExp();
		if (chr == '@')
			return 0;
		//遇到数字时
		else if (chr >= '0' && chr <= '9')
		{
			if (State == INTEGER || State == FLOAT)
			{
				pushNum(float(chr - '0'));
				cout << chr;//输出到后缀表达式
			}
			else if (State == OPERATOR || State == LEFT_BRACE || State == START)
			{
				pushNum(float(chr - '0'));
				cout << " " << chr;
				State = INTEGER;
			}
		}
		//遇到'.'且为整数状态时进入浮点数状态
		//否则忽略
		else if (chr == '.'&& State == INTEGER)
		{
			cout << chr;//输出到后缀表达式
			State = FLOAT;
		}
		//遇到左括号无条件压栈,进入左括号状态
		else if (chr == '(' && (State == OPERATOR || State == START || State == LEFT_BRACE))
		{
			pushOp(chr);
			State = LEFT_BRACE;
		}
		//单目或双目运算符时的处理
		else if (chr == '-')
		{
			if (State == START || State == LEFT_BRACE)//该运算符为单目运算符
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
		//处理双目运算符
		else if (chr == '+' || chr == '*' || chr == '/' || chr == '%')
		{
			if (State == INTEGER || State == FLOAT || State == RIGHT_BRACE)
			{
				pushOp(chr);
				State = OPERATOR;
			}
		}
		//遇到右括号弹栈计算，状态变为RIGHT_BRACE
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
				//如果出错，则重置op和num及State,准备处理新的表达式
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
		deci *= 10;//小数位向后推算
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
	deci = 1;//执行此函数说明一个数字读取完毕，将小数位重置
	return true;
}
void endExp()
{
	State = START;
	//表达式结束，按算符计算栈中元素
	while (!op->empty())
		if (!calc())
		{
			cout << endl;
			error("error");
			op->makenull();
			num->makenull();
			return;
		}
	//最终结果保存在数字栈中，输出
	cout <<endl<< num->pop() << endl;
}
bool calc()
{
	if (num->empty())return false;
	float a = num->pop();
	if (num->empty())return false;
	float b = num->pop();
	char  cur = op->pop();
	cout << cur;//输出到后缀表达式
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