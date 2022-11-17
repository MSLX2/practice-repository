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
		cout << "文件不存在" << endl;
		return;
	}

	int id = -1;
	string name = "";
	string pwd;

	if (type == 1)
	{
		cout << "请输入学号或姓名：";
		cin >> id;
		if (!cin.good())
		{
			cin.clear();
			cin >> name;
		}
	}
	else if (type == 2)
	{
		cout << "请输入职工编号或姓名：";
		cin >> id;
		if (!cin.good())
		{
			cin.clear();
			cin >> name;
		}
	}
	else if (type == 3)
	{
		cout << "请输入用户名：";
		cin >> name;
	}
	cout << "请输入密码：";
	cin >> pwd;

	//验证登录
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
				cout << "登陆成功" << endl;
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
		cout << "密码错误！" << endl;
	}
	else cout << "未找到该用户！" << endl;
	return;
}

int main()
{
	int select = 0;
	while (true)
	{
		cout << "=================欢迎使用XX机房预约系统================" << endl;
		cout << "\t-----------------------------------------\t\t" << endl;
		cout << "\t|\t      请选择您的身份\t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t1.本校学生  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t2.教师职工  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t3.管理人员  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t|\t\t0.退出系统  \t\t|\t\t" << endl;
		cout << "\t|\t\t\t   \t\t|\t\t" << endl;
		cout << "\t-----------------------------------------\t\t" << endl;
		cout << "请输入您的选择：";
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
			cout << "欢迎下次使用" << endl;
			return 0;
			break;
		default:
			cout << "请输入正确的序号！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
	

	return 0;
}