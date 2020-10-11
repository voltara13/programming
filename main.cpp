#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include "Hourly.h"
#include "Commission.h"
using namespace std;

/*������ ��� ���������� ������� � ����������� 
���� ������ �������: ��������� ������� �����
� � �������������*/

vector<Hourly> hourlyWorkers;
vector<Commission> commissionWorkers;

bool Check() //������� �������� ������� �� �������
{
	if (hourlyWorkers.size() || commissionWorkers.size()) return true;

	else
	{
		cout << "�� ��������� �� ������ ���������. ������ �����\n";
		return false;
	}
}

void PutList() //������� ������ ����� �������
{
	if (!Check()) return;

	if (hourlyWorkers.size())
	{
		cout << "\n��������� ���������:\n";
		for (int i = 0; i < hourlyWorkers.size(); ++i)
			cout << i + 1 << ". " << hourlyWorkers[i].GetName() <<
			", ����: " << hourlyWorkers[i].GetWork() <<
			", ��������: " << hourlyWorkers[i].GetWage() <<
			", ���: " << hourlyWorkers[i].GetGender() << endl;
	}

	if (commissionWorkers.size())
	{
		cout << "\n������������� ���������:\n";
		for (int i = 0; i < commissionWorkers.size(); ++i)
			cout << i + 1 << ". " << commissionWorkers[i].GetName() <<
			", �������: " << commissionWorkers[i].GetWork() <<
			", ��������: " << commissionWorkers[i].GetWage() << 
			", ���: " << commissionWorkers[i].GetGender() << endl;
	}

	cout << endl;
}

void Change() //������� ���������� �����/������ ����������
{
	if (!Check()) return;
	PutList();
	int ans;
	float work;

	cout << "�������� ��� ���������:\n" <<
		"1 - ���������\n" <<
		"2 - ������������\n" <<
		"����: ";

	cin >> ans;

	switch (ans)
	{
	case 1:
		cout << "\n������� ����� ���������: ";
		cin >> ans;
		cout << "������� ���������� ����������� �����: ";
		cin >> work;
		hourlyWorkers[ans - 1].Work(work);
		break;

	case 2:
		cout << "\n������� ����� ���������: ";
		cin >> ans;
		cout << "������� ���������� ����������� ������: ";
		cin >> work;
		commissionWorkers[ans - 1].Sell(work);
		break;

	default:
		cout << "������ �������� �������. ���������� ��� ���.\n";
	}
}

void CalculateWage() //������� ������� ��������
{
	if (!Check()) return;
	PutList();
	int ans;

	cout << "�������� ��� ���������:\n" <<
		"1 - ���������\n" <<
		"2 - ������������\n" <<
		"����: ";

	while (true)
	{
		cin >> ans;
		switch (ans)
		{
		case 1:
			cout << "\n������� ����� ���������: ";
			cin >> ans;
			hourlyWorkers[ans - 1].CalculateSalary();
			return;

		case 2:
			cout << "\n������� ����� ���������: ";
			cin >> ans;
			commissionWorkers[ans - 1].CalculateSalary();
			return;

		default:
			cout << "������ �������� �������. ���������� ��� ���.\n";
		}
	}
}

void AddWorker() //������� ���������� ������ ���������
{
	string fullName, gender;
	float salary, incSalary, percent, norm;
	cout << "������� ��� ���������: ";
	/*���������� ������ ����� ������
	����� ���� ����������� ��������� �������
	����� �� ������ �����*/
	cin.ignore(32767, '\n');
	getline(cin, fullName);
	cout << "������� ��� ���������: ";
	cin >> gender;
	int ans;

	cout << "�������� ��� ���������:\n" <<
		"1 - ���������\n" <<
		"2 - ������������\n" <<
		"����: ";

	while (true)
	{
		cin >> ans;
		switch (ans)
		{
		case 1:
			cout << "������� ������ �� ���: ";
			cin >> salary;
			cout << "������� ���������� ������ �� ���: ";
			cin >> incSalary;
			cout << "������� ����� �����: ";
			cin >> norm;
			hourlyWorkers.push_back(Hourly(fullName, gender, salary, incSalary, norm));
			return;

		case 2:
			cout << "������� ������������� �����: ";
			cin >> salary;
			cout << "������� ������� �� ������ �������: ";
			cin >> percent;
			commissionWorkers.push_back(Commission(fullName, gender, salary, percent));
			return;

		default:
			cout << "������ �������� �������. ���������� ��� ���.\n";
		}
	}
}

void Menu() //������� ��������� ����
{
	int ans;
	while (true)
	{
		cout << "\n������� ���ר�� ��������\n\n" <<
			"�������:\n" <<
			"1 - ����� �������� ���������\n" <<
			"2 - ����� ������� ������ ����������\n" <<
			"3 - ����� �������� ��������� ����/�������\n" <<
			"4 - ����� ��������� �������� ���������\n" <<
			"0 - ����� ����� �� ���������\n" <<
			"����: ";

		cin >> ans;

		switch (ans)
		{
		case 1:
			AddWorker();
			break;
		case 2:
			PutList();
			break;
		case 3:
			Change();
			break;
		case 4:
			CalculateWage();
			break;
		case 0:
			exit(0);
		default:
			cout << "������ �������� �������. ���������� ��� ���";
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
