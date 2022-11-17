#include "student.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
	this->id = id;
	this->name = name;
	this->pwd = pwd;

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.comId && ifs >> com.maxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
}

void Student::studentMenu(Student*& stu)
{
	while (true)
	{
		stu->operMenu();

		int select = 0;
		select = cinChoice();

		switch (select)
		{
			case 1:
			{
				stu->applyOrder();
				break;

			}
			case 2:
			{
				stu->showMyOrder();
				break;
			}
			case 3:
			{
				stu->showAllOrder();
				break;
			}
			case 4:
			{
				stu->cancelOrder();
				break;
			}
			case 0:
			{
				delete stu;
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

void Student::operMenu()
{
	cout << "=====================欢迎学生" << this->name << "登陆===================" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "\t|\t      请选择您的操作\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t1.预约机房  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t2.显示个人预约\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t3.显示所有预约\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t4.取消预约  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t0.注销登录  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "请输入您的选择：";
}

void Student::applyOrder()
{
	int date;
	int interval;
	int room;

	cout << "机房目前情况如下：" << endl;
	cout << "周一至周五，时段1至时段5" << endl;
	for_each(vCom.begin(), vCom.end(), [&](ComputerRoom& c)
		{
			cout << c.comId << "号机房容量为" << c.maxNum << endl;
		});
	
	do
	{
		cout << "请输入您要预约周几(1-5):";
		date = cinChoice();
	} while (date == -1 || date > 5 || date < 1);
	
	do
	{
		cout << "请输入您要预约的时段(1-5):";
		interval = cinChoice();
	} while (interval == -1 || interval > 5 || interval < 1);

	do
	{
		cout << "请输入您要预约的机房(1-3):";
		room = cinChoice();
	} while (room == -1 || room > 3 || room < 1);

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date;
	ofs << "\tinterval:" << interval;
	ofs << "\tstuId:" << this->id;
	ofs << "\tstuName:" << this->name;
	ofs << "\troomId:" << room;
	ofs << "\tstatus:" << 1 << endl;
	ofs.close();

	cout << "预约成功，等待审核" << endl;
	return;
}

vector<int> Student::showMyOrder()
{
	OrderFile of;

	int j = 0;
	vector<int> myOrder;
	for (int i = 0; i < of.orderSize; i++)
	{
		if (stoi(of.orderDate[i]["stuId"]) == id)
		{
			myOrder.push_back(i);
			cout << "第" << ++j << "条记录：" << endl;
			cout << "\t预约日期：" << "\t周" << of.orderDate[i]["date"] << endl;
			cout << "\t预约时段：" << "\t" << of.orderDate[i]["interval"] << endl;
			cout << "\t预约机房：" << "\t" << of.orderDate[i]["roomId"] << endl;
			cout << "\t预约状态：" << "\t";
			switch (stoi(of.orderDate[i]["status"]))
			{
			case 1:
				cout << "审核中" << endl;
				break;
			case 2:
				cout << "预约成功" << endl;
				break;
			case -1:
				cout << "预约失败" << endl;
				break;
			default:
				cout << "预约已取消" << endl;
				break;
			}
		}
	}
	if (j == 0)
	{
		cout << "无预约记录！" << endl;
	}
	return myOrder;                          
}

void Student::cancelOrder()
{
	OrderFile of;
	if (of.orderSize == 0)
	{
		cout << "无预约记录" << endl;
		return;
	}
	else
	{
		int select;
		vector<int> myOrder;
		myOrder = showMyOrder();
		if (myOrder.size() == 0)
		{
			return;
		}

		cout << "请输入您要删除的记录编号：";
		select = cinChoice();
		if (select < 1 || select > myOrder.size())
		{
			cout << "请输入范围内的编号！" << endl;
			return;
		}

		int i = 0;
		ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
		for (map<int, map<string, string>>::iterator it = of.orderDate.begin(); i < of.orderSize; it++)
		{
			if (select == ++i)
			{
				cout << "确认删除[Y/N]:";
				string choice;
				cin >> choice;
				if (choice == "Y")
				{
					it++;
					of.orderSize--;
					cout << "已删除第" << select << "条预约" << endl;
				}
				else
				{
					cout << "取消删除" << endl;
				}
			}
			ofs << "date:" << it->second["date"];
			ofs << "\tinterval:" << it->second["interval"];
			ofs << "\tstuId:" << it->second["stuId"];
			ofs << "\tstuName:" << it->second["stuName"];
			ofs << "\troomId:" << it->second["roomId"];
			ofs << "\tstatus:" << it->second["status"] << endl;
		}
		ofs.close();
		return;
	}
}
