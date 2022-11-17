#include "manager.h"
#include<string>

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	this->name = name;
	this->pwd = pwd;
	this->initVector();
	this->initComputer();
}

void Manager::managerMenu(Manager*& man)
{
	while (true)
	{
		man->operMenu();
		
		int select = 0;
		cin >> select;
		if (!cin.good())
		{
			cin.clear();
			cin.sync();
			string wrong;
			cin >> wrong;
			cout << "�Ƿ����룡" << endl;
			continue;
		}

		switch (select)
		{
		case 1:
		{
			man->addPerson();
			break;
		}
		case 2:
		{
			man->showPerson();
			break;
		}
		case 3:
		{
			man->showComputer();
			break;
		}
		case 4:
		{
			man->cleanFile();
			break;
		}
		case 0:
		{
			delete man;
			cout << "ע���ɹ�" << endl;
			return;
		}
		default:
			cout << "��������ȷ����ţ�" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

void Manager::operMenu()
{
	cout << "===================��ӭ"<<this->name<<"����Ա��½=================" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "\t|\t      ��ѡ�����Ĳ���\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t1.����˺�  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t2.�鿴�˺�  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t3.�鿴����  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t4.���ԤԼ  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t0.ע����¼  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "����������ѡ��";
}

void Manager::addPerson()
{
	string fileName;
	string tip;
	int id = -1;

	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;
	cout << "����������˺����ͣ�";
	int select = 0;
	select = cinChoice();

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		cout<<"������ѧ�ţ�";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		cout << "������ְ����ţ�";
	}
	else
	{
		cout << "��������ȷ�����";
		return;
	}

	ofstream ofs;
	ofs.open(fileName, ios::out | ios::app);
	string name;
	string pwd;
	
	while (true)
	{
		cin >> id;
		if (checkRepeat(id, select))
		{
			cout << "����ظ�������������!" << endl;
			cout << "�������ţ�";
		}
		else
		{
			break;
		}
	}

	cout << "������������";
	cin >> name;
	cout << "���������룺";
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	if (select == 1)
	{
		Student s(id, name, pwd);
		vStu.push_back(s);
	}
	else if (select == 2)
	{
		Teacher tea(id, name, pwd);
		vTea.push_back(tea);
	}

	cout << "��ӳɹ�" << endl;
	
}

void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴���н�ʦ" << endl;
	int select = 0;
	select = cinChoice();

	if (select == 1)
	{
		cout << "ѧ����Ϣ���£�" << endl;
		//��������ָ��
		for_each(vStu.begin(), vStu.end(), [&](Student& s)
			{
				cout << "ѧ��ѧ�ţ�" << s.id << "\t����:" << s.name << "\t����:" << s.pwd << endl;
			}
		);
	}
	else if (select == 2)
	{
		cout << "��ʦ��Ϣ���£�" << endl;
		//��������ָ��
		for_each(vTea.begin(), vTea.end(), [&](Teacher& t)
			{
				cout << "ְ����ţ�" << t.id << "\t����:" << t.name << "\t����:" << t.pwd << endl;
			}
		);
	}
	else
	{
		cout << "��������ȷ�ı�ţ�" << endl;
	}
}

void Manager::showComputer()
{
	cout << "������Ϣ���£�" << endl;
	for_each(vCom.begin(), vCom.end(), [&](ComputerRoom& c)
		{
			cout << "������ţ�" << c.comId << "\t���������" << c.maxNum << endl;
		});

}

void Manager::cleanFile()
{
	string sel;
	cout << "ȷ����գ�[Y/N] ";
	cin >> sel;
	if (sel == "Y")
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "�����ԤԼ" << endl;
	}
	else cout << "ȡ�����" << endl;
}

void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
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
		while (ifs >> s.id && ifs >> s.name && ifs >> s.pwd)
		{
			vStu.push_back(s);
		}
		//cout << "��ǰѧ����Ϊ��" << vStu.size() << endl;
		ifs.close();

		ifs.open(TEACHER_FILE, ios::in);
		Teacher t;
		while (ifs>>t.id&&ifs>>t.name&&ifs>>t.pwd)
		{
			vTea.push_back(t);
		}
		//cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
		ifs.close();
	}

}

void Manager::initComputer()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs>>com.comId&&ifs>>com.maxNum)
	{
		vCom.push_back(com);
	}
	ifs.close();
	//cout << "����������Ϊ��" << vCom.size() << endl;

}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->id)
			{
				return true;
			}
		}
	}
	else if(type == 2)
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it ++ )
		{
			if (id == it->id)
			{
				return true;
			}
		}
	}
	return false;
}
