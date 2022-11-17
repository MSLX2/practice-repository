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
			cout << "非法输入！" << endl;
			return -1;
		}
		return select;
	}

	static void showAllOrder()
	{
		OrderFile of;
		if (of.orderSize == 0)
		{
			cout << "无预约记录！" << endl;
			return;
		}
		int j = 0;
		for (int i = 0; i < of.orderSize; i++)
		{
			cout << "第" << i + 1 << "条记录：";
			cout << "\t预约日期：" << "周" << of.orderDate[i]["date"];
			cout << "\t预约时段：" << of.orderDate[i]["interval"];
			cout << "\t预约者学号：" << of.orderDate[i]["stuId"];
			cout << "\t姓名：" << of.orderDate[i]["stuName"];
			cout << "\t预约机房：" << of.orderDate[i]["roomId"];
			cout << "\t预约状态：";
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
		return;
	}
};