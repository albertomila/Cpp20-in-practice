// ConcurrencyInAction.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>
void Hello()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "1";
	}
}
void Hello2()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		std::cout << "2";
	}
}

BEGIN_TEST(Ch2_HelloWorld)
	std::thread threadTest(Hello);
	std::thread threadTest2(Hello2);

	//this point never reached 
	threadTest.join(); //wait until thread 1 is finished
	threadTest2.join(); //wait until thread 2 is finished

END_TEST()

//int main(){MainExample(); return 0;}
