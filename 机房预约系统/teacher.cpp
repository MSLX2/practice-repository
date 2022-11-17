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
	cout << "===================��ӭ" << this->name << "��ʦ��½=================" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "\t|\t      ��ѡ�����Ĳ���\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t1.��ʾ����ԤԼ\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t2.���ԤԼ  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t3.�鿴ѧ���˺�\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t0.ע����¼  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "����������ѡ��";
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

void Teacher::valiOrder()
{
	while (true)
	{
		OrderFile of;
		if (of.orderSize == 0)
		{
			cout << "��ԤԼ��¼" << endl;
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
					cout << "��" << ++j << "����¼��";
					cout << "\tԤԼ���ڣ�" << "��" << of.orderDate[i]["date"];
					cout << "\tԤԼʱ�Σ�" << of.orderDate[i]["interval"];
					cout << "\tԤԼ������" << of.orderDate[i]["roomId"];
					cout << "\tԤԼ״̬��" << "�����" << endl;
				}
			}
			if (j == 0)
			{
				cout << "�޴����ԤԼ��¼��" << endl;
				return;
			}

			cout << "��������Ҫ��˵ı��(����0�˳�)��";
			select = cinChoice();


			if (select < 0 || select > preOrder.size())
			{
				cout << "�����뷶Χ�ڵı�ţ�" << endl;
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
					cout << "��˽��(2.ͨ����� -1.δͨ�����):";
					string choice;
					cin >> choice;
					if (choice == "2")
					{
						ofs << "\tstatus:" << "2" << endl;
						cout << "��ͨ����ԤԼ" << endl;
						continue;
					}
					else if (choice == "-1")
					{
						ofs << "\tstatus:" << "-1" << endl;
						cout << "�Ѿܾ���ԤԼ" << endl;
						continue;
					}
					else
					{
						cout << "��������ȷ�ı�ţ�" << endl;
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
		cout << "�ļ���ȡʧ�ܣ�" << endl;
		return;
	}
	else
	{
		Student s;
	
		cout << "ѧ����Ϣ���£�" << endl;
		while (ifs >> s.id && ifs >> s.name && ifs >> s.pwd)
		{
			vStudent.push_back(s);
			cout <<"��"<<vStudent.size() << "����¼" << "ѧ��ѧ�ţ�" << s.id << "\t����:" << s.name << endl;
			
		}
		ifs.close();
		cout << "��ǰѧ����Ϊ��" << vStudent.size() << endl;
	}
	return;
}
