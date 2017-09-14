#include "work4.h"

Match* match;
int n = -1, m = -1, w = -1;

err Initialize();
//检查整型输入是否合法
void cin_s(int &obj, 
    int min = MIN, 
    int max = MAX);
//打印主菜单，不执行输入或控制
bool confirm(string hint);
void main_menu();
void sub_exit(string filename);
void sub_input();
void sub_sort();
void sub_query();
//文件加载、主菜单控制、退出保存
//其余子程序一律不退出程序，仅返回状态
int main()
{
	string filename = "Match.d";
	ifstream is;
	is.open(filename);
	err state;

	if (is.good() && confirm("已找到" + filename + ",是否加载? <Y|N>:"))
	{
		match = new Match(is);
		cout << "成功加载" + filename << endl;
	}
	else
	{
		cout << "创建新的比赛......" << endl;
		state = Initialize();
		if (state == FINISHED)
			cout << "比赛创建成功！" << endl;
		else
			exit(state);
	}
	is.close();
	int option = 1;
	while (option)
	{
		main_menu();
		cin_s(option);
		switch (option)
		{
		case 0:
			sub_exit(filename);
			exit(0);
		case 1:
			match->save(filename);
			break;
		case 2:
			sub_input();
			break;
		case 3:
			sub_sort();
			break;
		case 4:
			sub_query();
			break;
		default:
			cout << "输入无效,请重新输入" << endl;
		}
	}
}
err Initialize()
{
	cout << "请输入学院个数(1~20): " << endl;
	cin_s(n, 0, 20);
	cout << "请输入男子项目个数(1~20): " << endl;
	cin_s(m, 0, 20);
	cout << "请输入女子项目个数(1~20): " << endl;
	cin_s(w, 0, 20);
	match = new Match();
	if (match == NULL)
		return NOT_ENOUGH_RAM;
	cout << "---输入学院名称---" << endl;
	string name;
	//输入学院
	for (int i = 0; i < n; i++)
	{
		cout << "请输入 " << i+1 << " 号学院的名称:";
		cin >> name;
		match->SetAcademy(i+1, name);
		cout << "学院 " << i+1 << " 输入成功" << endl;
	}
	cout << "---输入项目名称---" << endl;
	//输入项目
	for (int i = 0; i < m + w; i ++)
	{
		cout << "请输入 " << i + 1 << " 号项目的名称:";
		cin >> name;
		match->SetEvent(i+1, name);
		cout << "项目 " << i+1 << " 输入成功" << endl;
	}
	return FINISHED;
}
void cin_s(int &obj, int min, int max)
{
	cin >> obj;
	while (cin.fail() || obj < min || obj > max)
	{
		cout << "输入无效，请重新输入" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> obj;
	}
}
bool confirm(string hint)
{
	cout << hint;
	string op;
	while (true)
	{
		cin >> op;
		if (op == "y" || op == "Y")
			return true;
		if (op == "n" || op == "N")
			return false;
		cout << "输入无效，请重新输入" << endl;
	}
}
void main_menu()
{
	cout << "-----------------主菜单------------------" << endl;
	cout << "0: 退出" << endl;
	cout << "1: 保存" << endl;
	cout << "2: 输入成绩" << endl;
	cout << "3: 学院排序" << endl;
	cout << "4: 查询" << endl;
}
void sub_exit(string filename)
{
	cout << "-----------------退出--------------------" << endl;
	if(confirm("是否保存? <Y|N>:"))
		match->save(filename);
}
void sub_input()
{
	int option;
	while (true)
	{
		cout << "----------------输入成绩-----------------" << endl;
		cout << "0: 返回" << endl;
		cout << "1: 按名称输入" << endl;
		cout << "2: 按编号输入" << endl;
		cin_s(option);
		switch (option)
		{
		case 0:return;
		case 1:
		{
			string Academy_name, Event_name;
			int score;
			cout << "-----------------按名称输入成绩-------------" << endl;
			cout << "输入均为0结束输入" << endl;
			while (true)
			{
				cout << "请输入学院名称:";
				cin >> Academy_name;
				cout << "请输入项目名称:";
				cin >> Event_name;
				cout << "请输入项目成绩:";
				cin_s(score, 0, MAXSCORE);
				if (Academy_name == "0" && Event_name == "0" && score == 0)
					break;
				if (!match->tellA(Academy_name) || !match->tellE(Event_name))
				{
					cout << "学院或项目不存在！" << endl;
					continue;
				}
				match->GetAcademy(Academy_name)->SetScore(Event_name, score);
				cout << "添加成功" << endl;
			}
			break;
		}
		case 2:
		{
			int Academy_id, Event_id;
			int score;
			cout << "-----------------按编号输入成绩-------------" << endl;
			cout << "输入均为0结束输入" << endl;
			while (true)
			{
				cout << "请输入学院编号: ";
				cin_s(Academy_id, 0, n + 1);
				cout << "请输入项目编号: ";
				cin_s(Event_id, 0, m + w + 1);
				cout << "请输入成绩: ";
				cin_s(score, 0, MAXSCORE);
				if (Academy_id == 0 && Event_id == 0 && score == 0)
					break;
				match->GetAcademy(Academy_id)->SetScore(Event_id, score);
				cout << "---添加成功---" << endl;
			}
		}
		}
	}
}
void sub_sort()
{
	cout << "---------------学院排序----------------" << endl;
	cout << "0: 返回" << endl;
	cout << "1: 按学院编号排序" << endl;
	cout << "2: 按学院名称排序" << endl;
	cout << "3: 按学院总分排序" << endl;
	cout << "4: 按男子团体总分排序" << endl;
	cout << "5: 按女子团体总分排序" << endl;
	int option;
	while (true)
	{
		cin_s(option);
		if (!option)
			return;
		match->Academy_sort(option);
		cout << "排序完成！" << endl;
	}
}
void sub_query()
{
	int option;
	int Academy_id;
	int Event_id;
	while (true)
	{
		cout << "---------------查询---------------" << endl;
		cout << "0: 返回" << endl;
		cout << "1: 按学院编号查询项目成绩" << endl;
		cout << "2: 按项目编号查询学院排名" << endl;
		cin_s(option, 0, 2);
		if (!option)
			return;
		if (option == 1)
		{
			int score;
			cout << "请输入要查询的学院编号" << endl;
			cin_s(Academy_id, 1, n);
			cout << "请输入要查询的项目编号" << endl;
			cin_s(Event_id, 1, m+w);
			score = match->GetAcademy(Academy_id)->GetScore(Event_id);
			cout << Academy_id << "学院" << Event_id << "项目的成绩为: " << score << endl;
		}
		else
		{
			int* rank;
			int num;
			cout << "请输入要查询的项目编号" << endl;
			cin_s(Event_id, 1, m + w);
			rank = match->GetRank(Event_id);
			num = Event_id < m + 1 ? 5 : 3;
			for (int i = 0; i < 5; i++)
				cout << "第" << i + 1 << "名:" << match->GetAcademy(rank[i])->GetName() << endl;
		}
	}
}