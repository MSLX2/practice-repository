#pragma once
#include"Identity.h"
#include<iostream>
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>
#include"computerRoom.h"
#include"orderFile.h"
using namespace std;

class Student :public Identity
{
public:

	Student();

	Student(int id, string name, string pwd);

	void studentMenu(Student*& stu);
	
	virtual void operMenu();

	void applyOrder();

	vector<int> showMyOrder();

	void cancelOrder();

	int id = 1;

	vector<ComputerRoom> vCom;
};