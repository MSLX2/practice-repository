#include "teacher.h"
#include<string>
Teacher::Teacher()
{
}

Teacher::Teacher(int id, string name, string pwd)
{
	this->id = id;
	this->name = name;
	this->pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "===================欢迎" << this->name << "老师登陆=================" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "\t|\t      请选择您的操作\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t1.显示所有预约\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t2.审核预约  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t3.查看学生账号\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t0.注销登录  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "请输入您的选择：";
}

void Teacher::teacherMenu(Teacher*& tea)
{
	while (true)
	{
		tea->operMenu();

		int select = 0;
		select = cinChoice();

		switch (select)
		{
		case 1:
		{
			tea->showAllOrder();
			break;
		}
		case 2:
		{
			tea->valiOrder();
			break;
		}
		case 3:
		{
			tea->showStudents();
			break;
		}
		case 0:
		{
			delete tea;
			cout << "注销成功" << endl;
			return;
		}
		default:
		{
			cout << "请输入正确的序号！" << endl;
			break;
		}
		}
		system("pause");
		system("cls");
	}
}

void Teacher::valiOrder()
{
	while (true)
	{
		OrderFile of;
		if (of.orderSize == 0)
		{
			cout << "无预约记录" << endl;
			return;
		}
		else
		{
			int select = 0;
			int j = 0;
			vector<int> preOrder;

			for (int i = 0; i < of.orderSize; i++)
			{
				if (of.orderDate[i]["status"] == "1")
				{
					preOrder.push_back(i);
					cout << "第" << ++j << "条记录：";
					cout << "\t预约日期：" << "周" << of.orderDate[i]["date"];
					cout << "\t预约时段：" << of.orderDate[i]["interval"];
					cout << "\t预约机房：" << of.orderDate[i]["roomId"];
					cout << "\t预约状态：" << "审核中" << endl;
				}
			}
			if (j == 0)
			{
				cout << "无待审核预约记录！" << endl;
				return;
			}

			cout << "请输入您要审核的编号(输入0退出)：";
			select = cinChoice();


			if (select < 0 || select > preOrder.size())
			{
				cout << "请输入范围内的编号！" << endl;
				continue;
			}
			else if (select == 0) return;

			int i = 0;
			ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
			for (map<int, map<string, string>>::iterator it = of.orderDate.begin(); i < of.orderSize; it++)
			{
				ofs << "date:" << it->second["date"];
				ofs << "\tinterval:" << it->second["interval"];
				ofs << "\tstuId:" << it->second["stuId"];
				ofs << "\tstuName:" << it->second["stuName"];
				ofs << "\troomId:" << it->second["roomId"];

				if (preOrder[select - 1] == i++)
				{
					cout << "审核结果(2.通过审核 -1.未通过审核):";
					string choice;
					cin >> choice;
					if (choice == "2")
					{
						ofs << "\tstatus:" << "2" << endl;
						cout << "已通过该预约" << endl;
						continue;
					}
					else if (choice == "-1")
					{
						ofs << "\tstatus:" << "-1" << endl;
						cout << "已拒绝该预约" << endl;
						continue;
					}
					else
					{
						cout << "请输入正确的编号！" << endl;
					}
				}
				ofs << "\tstatus:" << it->second["status"] << endl;
			}
			ofs.close();
			system("pause");
			system("cls");
			operMenu();
			cout << "2" << endl;
		}
	}
}

void Teacher::showStudents()
{
	vStudent.clear();
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败！" << endl;
		return;
	}
	else
	{
		Student s;
	
		cout << "学生信息如下：" << endl;
		while (ifs >> s.id && ifs >> s.name && ifs >> s.pwd)
		{
			vStudent.push_back(s);
			cout <<"第"<<vStudent.size() << "条记录" << "学生学号：" << s.id << "\t姓名:" << s.name << endl;
			
		}
		ifs.close();
		cout << "当前学生数为：" << vStudent.size() << endl;
	}
	return;
}
