#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>
#include <Windows.h>
#include "Hourly.h"
#include "Commission.h"
using namespace std;

#define WRONG_CHOICE cerr << "\n������ �������� �������. ���������� ��� ���\n";

vector<Company *> companyWorkers;

Company *DeserializeH(const string &data) //�������������� ���������� ���������
{
	Company *worker = nullptr;
	string fullName, gender;
	float salary, incSalary, norm;
	stringstream ss(data);
	for (string token; getline(ss, token, ';');)
	{
		size_t found = token.find('=');
		string tag = token.substr(0, found);
		string value = token.substr(found + 1, token.length());

		if (tag == "fullName") fullName = value;
		else if (tag == "gender") gender = value;
		else if (tag == "salary") salary = atof(value.c_str());
		else if (tag == "incSalary") incSalary = atof(value.c_str());
		else if (tag == "norm") norm = atof(value.c_str());
	}
	worker = new Hourly(fullName, gender, salary, incSalary, norm);
	return worker;
}

Company *DeserializeC(const string &data) //�������������� ������������� ���������
{
	Company *worker = nullptr;
	string fullname, gender;
	float salary, percent;
	stringstream ss(data);
	for (string token; getline(ss, token, ';');)
	{
		size_t found = token.find('=');
		string tag = token.substr(0, found);
		string value = token.substr(found + 1, token.length());

		if (tag == "fullName") fullname = value;
		else if (tag == "gender") gender = value;
		else if (tag == "salary") salary = atof(value.c_str());
		else if (tag == "percent") percent = atof(value.c_str());
	}
	worker = new Commission(fullname, gender, salary, percent);
	return worker;
}

void DeserializeVector() //������� �������������� �������
{
	fstream fs;
	fs.open("serialize.bin", ios::in | ios::binary);
	for (string temp; getline(fs, temp, '^');)
	{
		if (temp[temp.find('=') + 1] == 'h') companyWorkers.push_back(DeserializeH(temp));
		else if (temp[temp.find('=') + 1] == 'c') companyWorkers.push_back(DeserializeC(temp));
	}
	fs.close();
	cout << "�������������� ������� ���������\n";
}

void SerializeVector() //������� ������������ �������
{
	fstream fs("serialize.bin", ios::app | ios::binary);
	for (auto *it : companyWorkers) fs << it->Serialize() << "^\n";
	fs.close();
	cout << "������������ ������� ���������\n";
}

bool Check() //������� �������� ������� �� �������
{
	if (!companyWorkers.empty()) return true;
	cout << "\n�� ��������� �� ������ ���������. ������ ����\n";
	return false;
}

void Dismiss() //������� ����������
{
	int worker;
	while (true)
	{
		cout << "\n������� ����� ��������� ('0' - ��������� �����): ";
		cin >> worker;
		if (!worker) return;
		try
		{
			companyWorkers.at(worker - 1);
			companyWorkers.erase(companyWorkers.cbegin() + worker - 1);
		}
		catch (const out_of_range)
		{
			WRONG_CHOICE
				continue;
		}
		cout << "�������� ������� ������\n";
		break;
	}
}

void AddWorker() //������� ���������� ������ ���������
{
	string fullName, gender;
	float salary, incSalary, percent, norm;
	int group;
	Company *worker = nullptr;

	cout << "\n�������� ��� ���������:\n" <<
		"'1' - ���������\n'2' - ������������\n" <<
		"'������ �������' - ��������� �����\n����: ";
	cin >> group;
	if (group != 1 && group != 2) return;
	cout << "������� ��� ���������: ";
	cin.ignore(32767, '\n');
	/*���������� ������ ����� ������
	����� ���� ����������� ��������� �������
	����� �� ������ �����*/
	getline(cin, fullName);
	cout << "������� ��� ���������: ";
	cin >> gender;

	switch (group)
	{
	case 1:
		cout << "������� ������ �� ���: ";
		cin >> salary;
		cout << "������� ���������� ������ �� ���: ";
		cin >> incSalary;
		cout << "������� ����� �����: ";
		cin >> norm;
		worker = new Hourly(fullName, gender, salary, incSalary, norm);
		companyWorkers.push_back(worker);
		break;
	case 2:
		cout << "������� ������������� �����: ";
		cin >> salary;
		cout << "������� ������� �� ������ �������: ";
		cin >> percent;
		worker = new Commission(fullName, gender, salary, percent);
		companyWorkers.push_back(worker);
		break;
	}
}

void PutList() //������� ������ �������
{
	for (unsigned int i = 0; i < companyWorkers.size(); ++i)
		cout << i + 1 << ". " << *companyWorkers[i];
}

void SimulateWork() //������� ��������� ������
{
	int day;
	cout << "������� ���������� ����, ������� ������������ ������ ('0' - ��������� �����): ";
	cin >> day;
	if (!day) return;
	Company::SimulateWork(day, companyWorkers);
}

void Clear() //������� ������� �������
{
	for (auto pObj = companyWorkers.begin(); pObj != companyWorkers.end(); ++pObj)
		delete *pObj;
	companyWorkers.clear();
	cout << "������ ������� ������\n";
}

void Menu() //������� ��������� ����
{
	int ans;
	while (true)
	{
		cout << "\n������� ������� ��������\n\n" <<
			"�������:\n" <<
			"'1' - ����� �������� ���������\n" <<
			"'2' - ����� ������� ������ ����������\n" <<
			"'3' - ����� ������� ���������\n" <<
			"'4' - ����� ������������� ������\n" <<
			"'5' - ����� ������� ������������\n" <<
			"'6' - ����� ������� ��������������\n" <<
			"'7' - ����� �������� ������\n" <<
			"'0' - ����� ����� �� ���������\n" <<
			"����: ";

		cin >> ans;
		if ((ans != 0 && ans != 1 && ans != 6) && !Check()) continue;
		switch (ans)
		{
		case 1:
			AddWorker();
			break;
		case 2:
			PutList();
			break;
		case 3:
			Dismiss();
			break;
		case 4:
			SimulateWork();
			break;
		case 5:
			SerializeVector();
			break;
		case 6:
			DeserializeVector();
			break;
		case 7:
			Clear();
			break;
		case 0:
			Clear();
			exit(0);
		default:
			WRONG_CHOICE
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
	return 0;
}