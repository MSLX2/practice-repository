#include<iostream>
#include<fstream>
#include"Identity.h"
#include<string>
#include"student.h"
#include"teacher.h"
#include"manager.h"
#include"globalFile.h"
using namespace std;

void LoginIn(string fileNAme, int type)
{
	Identity* person = NULL;
	ifstream ifs;
	ifs.open(fileNAme, ios::in);

	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		return;
	}

	int id = -1;
	string name = "";
	string pwd;

	if (type == 1)
	{
		cout << "������ѧ�Ż�������";
		cin >> id;
		if (!cin.good())
		{
			cin.clear();
			cin >> name;
		}
	}
	else if (type == 2)
	{
		cout << "������ְ����Ż�������";
		cin >> id;
		if (!cin.good())
		{
			cin.clear();
			cin >> name;
		}
	}
	else if (type == 3)
	{
		cout << "�������û�����";
		cin >> name;
	}
	cout << "���������룺";
	cin >> pwd;

	//��֤��¼
	int fId;
	string fName;
	string fPwd;
	bool lSign = 0;

	while (ifs >> fId && ifs >> fName && ifs >> fPwd)
	{
		/*cout << fId << endl;
		cout << fName << endl;
		cout << fPwd << endl;*/

		if (fId == id||fName == name)
		{
			if (fPwd == pwd)
			{
				cout << "��½�ɹ�" << endl;
				system("pause");
				system("cls");
				if (type == 1)
				{
					//cout << "id = " << fId << "\tname = " << fName << "\tpwd = " << fPwd << endl;
					person = new Student(fId, fName, fPwd);
					Student* stu = (Student*)person;
					//cout << "stu.id = " << stu->id << "\tstu.name = " << stu->name << "\tpwd = " << stu->pwd<<endl;
					stu->studentMenu(stu);
					return;
				}
				else if (type == 2)
				{
					person = new Teacher(fId, fName, fPwd);
					Teacher* tea = (Teacher*)person;
					
					tea->teacherMenu(tea);
					return;
				}
				else if (type == 3)
				{
					person = new Manager(fName, fPwd);
					Manager* man = (Manager*)person;

					man->managerMenu(man);
					return;
				}
			}
			else lSign = 1;
		}
	}

	if (lSign == 1)
	{
		cout << "�������" << endl;
	}
	else cout << "δ�ҵ����û���" << endl;
	return;
}

int main()
{
	int select = 0;
	while (true)
	{
		cout << "=================��ӭʹ��XX����ԤԼϵͳ================" << endl;
		cout << "\t-----------------------------------------\t\t" << endl;
		cout << "\t|\t      ��ѡ���������\t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t1.��Уѧ��  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t2.��ʦְ��  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t3.������Ա  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t0.�˳�ϵͳ  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t-----------------------------------------\t\t" << endl;
		cout << "����������ѡ��";
		select = Identity::cinChoice();

		switch (select)
		{
		case 1:
			LoginIn(STUDENT_FILE,select);
			break;
		case 2:
			LoginIn(TEACHER_FILE,select);
			break;
		case 3:
			LoginIn(ADMIN_FILE, select);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��" << endl;
			return 0;
			break;
		default:
			cout << "��������ȷ����ţ�" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	

	return 0;
}