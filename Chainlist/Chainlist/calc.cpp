#include "Stack.h"
#include <map>
using namespace std;
Stack* op;//运算符栈
Stackf* num;//数字栈
map<int, int> order;//运算符优先级定义
bool doing = false;//正在处理
bool opOnly = false;//当此标志为true时,只能输入运算符
bool isNum = false; //标识对数进行操作
bool isFloat = false;//标识对浮点数操作
int deci = 1;//小数位数，isFloat为true时每次pushNum时，deci*10,pushOp时重置为1
//判断当前运算符是否能入栈
bool can_push(int chr);
//初始化运算符栈、数字栈、运算符优先级、操作状态
void init(void);
//算数表达式结束时处理后事，err为true时表示计算遇到错误
void endExp(bool err);
//数字压栈，同时计算多位数与浮点数
void pushNum(float num);
//运算符压栈，同时计算，无异常返回true,异常返回false
bool pushOp(char op);
//运算符出栈并计算
bool calc();
int main()
{ 
	init();
	char chr = 0;
	while(true)
	{
		if (!doing)
		{
			cout << "请输入表达式(输入@退出程序):" << endl;
			doing = true;
		}
		chr = cin.get();
		if (chr == '\n')
			endExp(false);
		if (chr == '@')
			return 0;
		//遇到数字压栈,isNum设为true
		else if (chr >= '0' && chr <= '9' && !opOnly)
		{
			if (!isNum)cout << " ";
			cout << chr;//输出到后缀表达式
			pushNum(float(chr - '0'));
			isNum = true;
		}
		//遇到'.'且为数字状态、不是小数状态、可接受时
		//设置为小数操作
		//否则忽略
		else if (chr == '.'&& !opOnly && isNum && !isFloat)
		{
				isFloat = true;
				cout << chr;//输出到后缀表达式
		}
		//遇到左括号无条件压栈,并清除数字状态
		else if (chr == '('&& !opOnly)
		{
			pushOp(chr);
			isNum = false;
			isFloat = false;
		}
		//当数字状态或仅允许算符时压栈
		//并清除数字状态,清除opOnly，否则忽略
		else if (chr == '+' && (isNum || opOnly))
		{
			isNum = false;
			isFloat = false;
			opOnly = false;
			pushOp(chr);
		}
		//当数字状态或仅允许算符时压栈
		//否则先压入0，再压入'-'
		//清除数字状态
		else if (chr == '-')
		{
			if (isNum || opOnly)//为双目运算符
				pushOp(chr);
			else//为单目运算符
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
		//遇到不能作为单目运算符的字符时
		//数字状态、仅允许算符时压栈
		//否则作为新的输入，覆盖栈顶
		//清除数字状态
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
		//遇到右括号时状态变为仅接受算符
		//弹栈运算直至遇到左括号
		//其本身不压栈
		//清除数字状态
		else if (chr == ')')
		{
			opOnly = true;//当输入右括号之后，下个字符只能为双目运算符或右括号
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
		deci *= 10;//小数位向后推算
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
	deci = 1;//执行此函数说明一个数字读取完毕，将小数位重置
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
	//表达式结束，按算符计算栈中元素
	while (!op->empty())
		if (!calc())
		{
			error("error");
			return;
		}
	//最终结果保存在数字栈中，输出
	cout <<endl<< num->pop() << endl;
}
bool calc()
{
	float a = num->pop();
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