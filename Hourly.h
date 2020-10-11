#pragma once

using namespace std;

class Hourly
{
	string fullName, gender; //���, ���
	float hour = 0, salary = 0, incSalary = 0, norm = 0, wage = 0;
	/*���������� ������������ �����, 
	�������� � ���, ���������� �������� � ���
	����� �����, ����� ��������*/
public:
	//����������� � �����������, ����������� ��-���������
	Hourly(string _fullName = "", 
		string _gender = "",
		float _salary = 0, 
		float _incSalary = 0, 
		float _norm = 0) :
		fullName{_fullName}, gender{_gender}, salary{_salary}, incSalary{_incSalary}, norm{_norm} {}

	void Work(float hour) //������� ���������� ���������� ������������ �����
	{
		this->hour += hour;
	}

	float GetWork() //������� �������� ���������� �����
	{
		return hour;
	}

	float GetWage() //������� �������� ����� ��������
	{
		return wage;
	}

	float CalculateSalary() //������� ������� � �������� ��������
	{
		wage += (hour <= norm ? hour * salary : norm * salary + (hour - norm) * incSalary);
		hour = 0;
		return wage;
	}

	string GetName() //������� �������� ���
	{
		return fullName;
	}

	string GetGender() //������� �������� ����
	{
		return gender;
	}
};