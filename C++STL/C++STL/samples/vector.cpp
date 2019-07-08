
#include "stdafx.h"
#include "samples/vector.h"
#include <fstream> 

void Vector::Example1()
{
	vector<int> myvector;
	for (int i = 1; i <= 5; i++) myvector.push_back(i);

	vector<int> v(100);
	cout << "size: " << (int)v.size() << "\n";
	cout << "capacity: " << (int)v.capacity() << "\n";
	cout << "max_size: " << (int)v.max_size() << "\n";

	cout << "myvector contains:";
	vector<int>::reverse_iterator rit;
	for (rit = myvector.rbegin(); rit < myvector.rend(); ++rit)
		cout << " " << *rit;

}

void Vector::Example2()
{
	vector<int> content;
	size_t filesize = 1024;

	content.reserve(filesize);
	cout << "size: " << (int)content.size() << "\n";
	cout << "capacity: " << (int)content.capacity() << "\n";
	cout << "max_size: " << (int)content.max_size() << "\n";

	ifstream file("Vector_Data.bin", ios::in | ios::ate | ios::binary);
	if (file.is_open())
	{
		filesize = static_cast<size_t>(file.tellg());

		content.reserve(filesize);

		file.seekg(0);
		while (!file.eof())
		{
			content.push_back(file.get());
		}

		// print out content:
		vector<int>::iterator it;
		for (it = content.begin(); it < content.end(); it++)
			cout << hex << *it;
	}
}

void Vector::Example3()
{
	vector<int> myvector(10);   // 10 zero-initialized ints
	unsigned int i;

	// assign some values:
	for (i = 0; i < myvector.size(); i++)
		myvector.at(i) = i;

	cout << "myvector contains:";
	for (i = 0; i < myvector.size(); i++)
		cout << " " << myvector.at(i);

	cout << endl;

	try
	{
		int value = myvector.at(100);
	}
	catch (out_of_range e)
	{
		string reason = e.what();
	}
}

void Vector::Example4()
{
	vector<int> myvector;

	myvector.push_back(10);

	while (myvector.back() != 0)
	{
		myvector.push_back(myvector.back() - 1);
	}

	cout << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		cout << " " << myvector[i];

	cout << endl;
}

void Vector::Example5()
{
	vector<int> first;
	vector<int> second;
	vector<int> third;

	first.assign(7, 100);             // a repetition 7 times of value 100

	vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1); // the 5 central values of first

	int myints[] = { 1776,7,4 };
	third.assign(myints, myints + 3);   // assigning from array.
	third.assign(it, first.end() - 1);
	cout << "Size of first: " << int(first.size()) << endl;
	cout << "Size of second: " << int(second.size()) << endl;
	cout << "Size of third: " << int(third.size()) << endl;
}

void Vector::Example6()
{
	vector<int> myvector(3, 100);
	vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert(it, 200);

	myvector.insert(it, 2, 300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	vector<int> anothervector(2, 400);
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());

	int myarray[] = { 501,502,503 };
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	cout << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		cout << " " << *it;
	cout << endl;
}

void Vector::Example7()
{
	string s7a(10, 42);
	vector<Vector_Data> myvector;
	myvector.push_back(Vector_Data());
	myvector.erase(myvector.begin());
}

void Vector::Example8()
{
	size_t found = -1;
	string str("aaaaaaaaaaaaaaaaaaaaaaaa");

	do
	{
		found++;
		found = str.find("a", found);
	} while (found != string::npos);
}