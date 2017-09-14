#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
#define MIN numeric_limits<int>::min()
#define MAX numeric_limits<int>::max()
#define MAXSCORE 100
using namespace std;
extern int n, m, w;
map<string, int> Enametoid;
enum err
{
	FINISHED,
	NOT_ENOUGH_RAM,
	FILE_LADING_ERROR,
	FILE_SAVING_ERROR,
};
class Event
{
public:
	Event();
	int id;
	string name;
};
Event::Event()
{
	id = 0;
	name = "";
}
class Academy
{
public:
	Academy();
	Academy(Academy&);
	~Academy();
	inline Academy* SetName(const string name) { this->name = name;return this; }
	inline string GetName() { return this->name; }
	inline Academy* SetId(const int id) { this->id = id; return this; }
	inline int GetId() { return this->id; }
	Academy* SetScore(const string Event_name, const int score);
	Academy* SetScore(const int Event_id, const int score);
	int GetScore(const string Event_name);
	int GetScore(const int Event_id);
	int calc_tot_score();
	int GetTotScore() { return male_tot_score + female_tot_score; }
	int GetMaleScore() { return male_tot_score; }
	int GetFemaleScore() { return female_tot_score; }
private:
	int id;
	string name;
	int* score;
	int male_tot_score;
	int female_tot_score;
};
Academy::Academy()
{
	id = 0;
	name = "";
	score = new int[m + w + 1];
	memset(score, -1, (m + w + 1) * sizeof(int));
	male_tot_score = 0;
	female_tot_score = 0;
}
Academy::Academy(Academy& x)
{
	this->id = x.id;
	this->name = x.name;
	for (int i = 0; i <= m + w; i++)
		this->score[i] = x.score[i];
	this->male_tot_score = x.male_tot_score;
	this->female_tot_score = x.female_tot_score;
}
Academy::~Academy()
{
	delete[] score;
}
Academy* Academy::SetScore(const int id, const int score)
{
	this->score[id] = score;
	return this;
}
Academy* Academy::SetScore(const string name, const int score)
{
	return SetScore(Enametoid[name], score);
}
int Academy::GetScore(const int id)
{
	return score[id];
}
int Academy::GetScore(const string name)
{
	return GetScore(Enametoid[name]);
}
int Academy::calc_tot_score()
{
	male_tot_score = 0;
	female_tot_score = 0;
	for (int i = 1; i <= m; i++)
		male_tot_score += GetScore(i);
	for (int i = m + 1; i < w; i++)
		female_tot_score += GetScore(i);
	return male_tot_score + female_tot_score;
}

class Match
{
public:
	Match();
	Match(ifstream &is);
	~Match();
	Match* Academy_sort(int op);
	Academy* GetAcademy(const string name);
	Academy* GetAcademy(const int id);
	Match* SetAcademy(const int id, const string name);
	Match* SetEvent(const int id, const string name);
	bool tellA(const string name) { return Anametoid[name]; }
	bool tellE(const string name) { return Enametoid[name]; }
	int* GetRank(const int id);
	err save(string filename);

private:
	Academy* academy;
	Event*	 event;
	int*     event_rank;
	map<string, int>Anametoid;
	void sort(bool (*cmp)(Academy*, Academy*));
	static bool cmp_id(Academy *a, Academy *b) { return a->GetId() < b->GetId(); }
	static bool cmp_name(Academy *a, Academy *b) { return a->GetName() < b->GetName(); }
	static bool cmp_tot(Academy *a, Academy *b) { return a->GetTotScore() < b->GetTotScore(); }
	static bool cmp_m_tot(Academy *a, Academy *b) { return a->GetMaleScore() < b->GetMaleScore(); }
	static bool cmp_f_tot(Academy *a, Academy *b) { return a->GetFemaleScore() < b->GetFemaleScore(); }
};
Match::Match()
{
	academy = new Academy[n + 1];
	event = new Event[m + w + 1];
	event_rank = new int[5];
}
Match::Match(ifstream &is)
{
	string name;
	int score;
	is >> n >> m >> w;
	academy = new Academy[n + 1];
	event = new Event[m + w + 1];
	event_rank = new int[5];

	for (int i = 0; i < m + w; i++)
	{
		is >> name;
		this->SetEvent(i + 1, name);
	}
	for (int i = 0; i < n; i++)
	{
		is >> name;
		this->SetAcademy(i + 1, name);
		for (int j = 0; j < m + w; j++)
		{
			is >> score;
			this->academy[i + 1].SetScore(j + 1, score);
		}
	}
}
Match::~Match()
{
	delete[] academy;
	delete[] event;
	delete[] event_rank;
}
Academy* Match::GetAcademy(const int id)
{
	return (this->academy) + id;
}
Academy* Match::GetAcademy(const string name)
{
	return GetAcademy(Anametoid[name]);
}
Match* Match::SetAcademy(const int id, const string name)
{
	Anametoid[name] = id;
	academy[id].SetName(name);
	academy[id].SetId(id);
	return this;
}
Match* Match::SetEvent(const int id, const string name)
{
	Enametoid[name] = id;
	event[id].id = id;
	event[id].name = name;
	return this;
}
int* Match::GetRank(const int id)
{
	int* vis = new int[n];
	memset(vis, 0, n*sizeof(int));
	int num = id > m + 1 ? 5 : 3;
	int max = MIN, pos = 0;
	for (int i = 0; i < num; i++)
	{
		max = MIN;
		for (int j = 1; j <= n; j++)
			if (academy[j].GetScore(id) > max && !vis[j])
			{
				max = academy[j].GetScore(id);
				pos = j;
			}
		event_rank[i] = pos;
	}
	return event_rank;
}
Match* Match::Academy_sort(int op)
{
	for (int i = 0; i < m; i++)
		GetAcademy(i + 1)->calc_tot_score();
	switch (op)
	{
	case 1:
		sort(cmp_id);
		break;
	case 2:
		sort(cmp_name);
		break;
	case 3:
		sort(cmp_tot);
		break;
	case 4:
		sort(cmp_m_tot);
		break;
	case 5:
		sort(cmp_f_tot);
		break;
	}
	return this;
}
err Match::save(string filename)
{
	ofstream os;
	os.open(filename);
	os << n <<" "<< m << " "<< w <<endl;
	for (int i = 0; i < m + w; i++)
		os << setw(24) << event[i+1].name << " ";
		os << endl;
	for (int i = 0; i < n; i++)
	{
		os << setw(24) << academy[i + 1].GetName() << " ";
		for (int j = 0; j < m + w; j++)
			os << setw(25) << academy[i + 1].GetScore(j + 1);
		os << endl;
	}
	return FINISHED;
}
void Match::sort(bool (*cmp)(Academy*, Academy*))
{
	Academy tmp;
	Academy* arr = GetAcademy(0);
	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j <= n - i - 1; j ++)
			if (cmp(arr+j, arr+j+1))
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
				/*memcpy(tmp, arr + j, sizeof(Academy));
				memcpy(arr + j, arr + j + 1, sizeof(Academy));
				memcpy(arr + j + 1, tmp, sizeof(Academy));*/
			}
	}
}