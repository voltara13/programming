#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <ctime>
#include "Hourly.h"
#include "Commission.h"
using namespace std;

#define wrongChoice cerr << "\n������ �������� �������. ���������� ��� ���\n";

vector<Company*> companyWorkers;

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
			wrongChoice;
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
	Company* worker = nullptr;

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

void Menu() //������� ��������� ����
{
	int ans;
	while (true)
	{
		cout << "\n������� ���ר�� ��������\n\n" <<
			"�������:\n" <<
			"'1' - ����� �������� ���������\n" <<
			"'2' - ����� ������� ������ ����������\n" <<
			"'3' - ����� ������� ���������\n" <<
			"'4' - ����� ������������� ������\n" <<
			"'0' - ����� ����� �� ���������\n" <<
			"����: ";

		cin >> ans;
		if ((ans != 0 && ans != 1) && !Check()) continue;
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
		case 0:
			exit(0);
		default:
			wrongChoice;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Menu();
	for (auto pObj = companyWorkers.begin(); pObj != companyWorkers.end(); ++pObj)
		delete *pObj;
	companyWorkers.clear();
	return 0;
}
