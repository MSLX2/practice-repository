#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"globalFile.h"
#include"Identity.h"
#include"student.h"
#include"teacher.h"
#include"computerRoom.h"

using namespace std;

class Manager :public Identity
{
public:
	Manager();

	Manager(string name, string pwd);

	void managerMenu(Manager*& man);

	virtual void operMenu();

	void addPerson();

	void showPerson();

	void showComputer();

	void cleanFile();

	void initVector();

	void initComputer();

	bool checkRepeat(int id, int type);

	vector<Student> vStu;

	vector<Teacher> vTea;

	vector<ComputerRoom> vCom;

	int id = 0;
};