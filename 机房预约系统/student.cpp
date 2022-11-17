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
				cout << "ע���ɹ�" << endl;
				return;
			}
			default:
			{
				cout << "��������ȷ����ţ�" << endl;
				break;
			}
		}
	
		system("pause");
		system("cls");
	}
}

void Student::operMenu()
{
	cout << "=====================��ӭѧ��" << this->name << "��½===================" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "\t|\t      ��ѡ�����Ĳ���\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t1.ԤԼ����  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t2.��ʾ����ԤԼ\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t3.��ʾ����ԤԼ\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t4.ȡ��ԤԼ  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t0.ע����¼  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "����������ѡ��";
}

void Student::applyOrder()
{
	int date;
	int interval;
	int room;

	cout << "����Ŀǰ������£�" << endl;
	cout << "��һ�����壬ʱ��1��ʱ��5" << endl;
	for_each(vCom.begin(), vCom.end(), [&](ComputerRoom& c)
		{
			cout << c.comId << "�Ż�������Ϊ" << c.maxNum << endl;
		});
	
	do
	{
		cout << "��������ҪԤԼ�ܼ�(1-5):";
		date = cinChoice();
	} while (date == -1 || date > 5 || date < 1);
	
	do
	{
		cout << "��������ҪԤԼ��ʱ��(1-5):";
		interval = cinChoice();
	} while (interval == -1 || interval > 5 || interval < 1);

	do
	{
		cout << "��������ҪԤԼ�Ļ���(1-3):";
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

	cout << "ԤԼ�ɹ����ȴ����" << endl;
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
			cout << "��" << ++j << "����¼��" << endl;
			cout << "\tԤԼ���ڣ�" << "\t��" << of.orderDate[i]["date"] << endl;
			cout << "\tԤԼʱ�Σ�" << "\t" << of.orderDate[i]["interval"] << endl;
			cout << "\tԤԼ������" << "\t" << of.orderDate[i]["roomId"] << endl;
			cout << "\tԤԼ״̬��" << "\t";
			switch (stoi(of.orderDate[i]["status"]))
			{
			case 1:
				cout << "�����" << endl;
				break;
			case 2:
				cout << "ԤԼ�ɹ�" << endl;
				break;
			case -1:
				cout << "ԤԼʧ��" << endl;
				break;
			default:
				cout << "ԤԼ��ȡ��" << endl;
				break;
			}
		}
	}
	if (j == 0)
	{
		cout << "��ԤԼ��¼��" << endl;
	}
	return myOrder;                          
}

void Student::cancelOrder()
{
	OrderFile of;
	if (of.orderSize == 0)
	{
		cout << "��ԤԼ��¼" << endl;
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

		cout << "��������Ҫɾ���ļ�¼��ţ�";
		select = cinChoice();
		if (select < 1 || select > myOrder.size())
		{
			cout << "�����뷶Χ�ڵı�ţ�" << endl;
			return;
		}

		int i = 0;
		ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
		for (map<int, map<string, string>>::iterator it = of.orderDate.begin(); i < of.orderSize; it++)
		{
			if (select == ++i)
			{
				cout << "ȷ��ɾ��[Y/N]:";
				string choice;
				cin >> choice;
				if (choice == "Y")
				{
					it++;
					of.orderSize--;
					cout << "��ɾ����" << select << "��ԤԼ" << endl;
				}
				else
				{
					cout << "ȡ��ɾ��" << endl;
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
