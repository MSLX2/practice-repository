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
			cout << "非法输入！" << endl;
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
			cout << "注销成功" << endl;
			return;
		}
		default:
			cout << "请输入正确的序号！" << endl;
			break;
		}
		system("pause");
		system("cls");
	}
}

void Manager::operMenu()
{
	cout << "===================欢迎"<<this->name<<"管理员登陆=================" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "\t|\t      请选择您的操作\t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t1.添加账号  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t2.查看账号  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t3.查看机房  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t4.清空预约  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t|\t\t0.注销登录  \t\t|\t\t" << endl;
	cout << "\t|\t\t\t   \t\t|\t\t" << endl;
	cout << "\t-----------------------------------------\t\t" << endl;
	cout << "请输入您的选择：";
}

void Manager::addPerson()
{
	string fileName;
	string tip;
	int id = -1;

	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;
	cout << "请输入添加账号类型：";
	int select = 0;
	select = cinChoice();

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		cout<<"请输入学号：";
	}
	else if (select == 2)
	{
		fileName = TEACHER_FILE;
		cout << "请输入职工编号：";
	}
	else
	{
		cout << "请输入正确的序号";
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
			cout << "编号重复，请重新输入!" << endl;
			cout << "请输入编号：";
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：";
	cin >> name;
	cout << "请输入密码：";
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

	cout << "添加成功" << endl;
	
}

void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有教师" << endl;
	int select = 0;
	select = cinChoice();

	if (select == 1)
	{
		cout << "学生信息如下：" << endl;
		//匿名函数指针
		for_each(vStu.begin(), vStu.end(), [&](Student& s)
			{
				cout << "学生学号：" << s.id << "\t姓名:" << s.name << "\t密码:" << s.pwd << endl;
			}
		);
	}
	else if (select == 2)
	{
		cout << "教师信息如下：" << endl;
		//匿名函数指针
		for_each(vTea.begin(), vTea.end(), [&](Teacher& t)
			{
				cout << "职工编号：" << t.id << "\t姓名:" << t.name << "\t密码:" << t.pwd << endl;
			}
		);
	}
	else
	{
		cout << "请输入正确的编号！" << endl;
	}
}

void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;
	for_each(vCom.begin(), vCom.end(), [&](ComputerRoom& c)
		{
			cout << "机房编号：" << c.comId << "\t最大容量：" << c.maxNum << endl;
		});

}

void Manager::cleanFile()
{
	string sel;
	cout << "确认清空？[Y/N] ";
	cin >> sel;
	if (sel == "Y")
	{
		ofstream ofs(ORDER_FILE, ios::trunc);
		ofs.close();
		cout << "已清空预约" << endl;
	}
	else cout << "取消清空" << endl;
}

void Manager::initVector()
{
	vStu.clear();
	vTea.clear();
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
		while (ifs >> s.id && ifs >> s.name && ifs >> s.pwd)
		{
			vStu.push_back(s);
		}
		//cout << "当前学生数为：" << vStu.size() << endl;
		ifs.close();

		ifs.open(TEACHER_FILE, ios::in);
		Teacher t;
		while (ifs>>t.id&&ifs>>t.name&&ifs>>t.pwd)
		{
			vTea.push_back(t);
		}
		//cout << "当前老师数量为：" << vTea.size() << endl;
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
	//cout << "机房的数量为：" << vCom.size() << endl;

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
