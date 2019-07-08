#include "stdafx.h"
#include <mutex>
#include <list>


std::list<int> _list;
std::mutex _mutex;

void AddToList(int value)
{
	std::lock_guard<std::mutex> guard(_mutex);
	_list.push_back(value);
}


bool Contains(int valueToFind)
{
	std::lock_guard<std::mutex> guard(_mutex);
	return std::find(_list.begin(), _list.end(), valueToFind) != _list.end();
}

BEGIN_TEST(Ch3_Mutex)
	AddToList(0);
	AddToList(1);
	AddToList(2);
	AddToList(3);
	AddToList(4);
	bool has = Contains(3);

END_TEST()

//int main(){MainExample(); return 0;}
