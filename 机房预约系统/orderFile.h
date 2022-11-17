#pragma once
#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include"globalFile.h"
using namespace std;

class OrderFile
{
public:
	OrderFile();

	void updateOrder();

	pair<string, string> separateRecord(string& record);

	map<int, map<string, string>> orderDate;

	int orderSize;
};
