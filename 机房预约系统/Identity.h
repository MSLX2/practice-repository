#pragma once
#include<iostream>
#include"globalFile.h"
#include<string>
#include<algorithm>
#include"orderFile.h"
using namespace std;

class Identity
{
public:
	virtual void operMenu() = 0;

	string name;
	string pwd;

	static int cinChoice()
	{
		int select = 0;
		cin >> select;
		if (!cin.good())
		{
			cin.clear();
			cin.sync();
			string wrong;
			cin >> wrong;
			cout << "�Ƿ����룡" << endl;
			return -1;
		}
		return select;
	}

	static void showAllOrder()
	{
		OrderFile of;
		if (of.orderSize == 0)
		{
			cout << "��ԤԼ��¼��" << endl;
			return;
		}
		int j = 0;
		for (int i = 0; i < of.orderSize; i++)
		{
			cout << "��" << i + 1 << "����¼��";
			cout << "\tԤԼ���ڣ�" << "��" << of.orderDate[i]["date"];
			cout << "\tԤԼʱ�Σ�" << of.orderDate[i]["interval"];
			cout << "\tԤԼ��ѧ�ţ�" << of.orderDate[i]["stuId"];
			cout << "\t������" << of.orderDate[i]["stuName"];
			cout << "\tԤԼ������" << of.orderDate[i]["roomId"];
			cout << "\tԤԼ״̬��";
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
		return;
	}
};