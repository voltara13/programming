#pragma once

using namespace std;

class Commission
{
	string fullName, gender; //���, ���
	int sales = 0; //���������� ������
	float salary = 0, percent = 0, wage = 0;
	/*���������� ������, ������� � ������,
	����� ��������*/
public:
	//����������� � �����������, ����������� ��-���������
	Commission(string _fullName = "", 
		string _gender = "",
		float _salary = 0, 
		float _percent = 0) : 
		fullName{_fullName}, gender{_gender }, salary{_salary}, percent{_percent / 100} {}

	void Sell(int sales) //������� ���������� ������
	{
		this->sales += sales;
	}

	int GetWork() //������� �������� ���������� ������
	{
		return sales;
	}

	float CalculateSalary() //������� ������� � �������� ��������
	{
		wage += salary + sales * salary * percent;
		sales = 0;
		return wage;
	}

	float GetWage() //������� �������� ����� ��������
	{
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