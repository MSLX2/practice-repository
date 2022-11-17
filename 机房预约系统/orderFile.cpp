#include "orderFile.h"

OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	orderSize = 0;
	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{	
		map<string, string> m;
		m.insert(separateRecord(date));
		m.insert(separateRecord(interval));
		m.insert(separateRecord(stuId));
		m.insert(separateRecord(stuName));
		m.insert(separateRecord(roomId));
		m.insert(separateRecord(status));

		orderDate.insert(make_pair(orderSize++, move(m)));
	}
	ifs.close();
	/*cout << orderSize << endl;
	for (map<int, map<string, string>>::iterator it = orderDate.begin(); it != orderDate.end(); it++)
	{
		cout << "µÚ" << it->first+1 << "Ìõ¼ÇÂ¼£º"<<endl;
		for (map<string, string> ::iterator mit = (*it).second.begin(); mit != it->second.end(); mit++)
		{
			cout << "\tkey = " << mit->first << "\tvalue = " << mit->second << endl;
		}
		cout << endl;
	}*/
}

void OrderFile::updateOrder()
{
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < orderSize; i++)
	{
		ofs << "date:" << orderDate[i]["date"];
		ofs << "\tinterval:" << orderDate[i]["interval"];
		ofs << "\tstuId:" << orderDate[i]["stuId"];
		ofs << "\tstuName:" << orderDate[i]["stuName"];
		ofs << "\troomId:" << orderDate[i]["roomId"];
		ofs << "\tstatus:" << orderDate[i]["status"] << endl;
	}
	ofs.close();
	return;
}

pair<string,string> OrderFile::separateRecord(string& record)
{
	int pos;
	pos = record.find(':');

	string key = record.substr(0, pos);
	string value = record.substr(pos + 1);

	
	return make_pair(key,value);
}
