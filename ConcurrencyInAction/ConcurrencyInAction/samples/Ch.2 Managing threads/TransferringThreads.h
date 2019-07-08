#include "stdafx.h"
#include <iostream>
#include <thread>


void some_function()
{

}

void some_other_function()
{

}

std::thread ReturnThreadExample1()
{
	return std::thread(some_function);
}
std::thread ReturnThreadExample2()
{
	std::thread t(some_other_function);
	return t;
}

void ArgumentThreadExample1(std::thread t)
{

}

void ArgumentThreadExample4()
{
	ArgumentThreadExample1(std::thread(some_function));

	std::thread t(some_function);

	ArgumentThreadExample1(std::move(t));
}

BEGIN_TEST(Ch2_TransferingThreads)
	{
		std::thread t1(some_function);
		std::thread t2 = std::move(t1);

		t1 = std::thread(some_other_function);

		std::thread t3;
		t3 = std::move(t2);

		t1 = std::move(t3);
	}
END_TEST()

//int main(){MainExample(); return 0;}
