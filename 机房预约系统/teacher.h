#pragma once
#define _CRT_SE
#include<iostream>
#include"Identity.h"
#include"orderFile.h"
#include<string>
#include"student.h"
using namespace std;

class Teacher :public Identity
{
public:
	Teacher();

	Teacher(int id, string name, string pwd);
	
	void operMenu();

	void teacherMenu(Teacher*& tea);

	void valiOrder();

	void showStudents();

	int id = 1;

	vector<Student> vStudent;
};