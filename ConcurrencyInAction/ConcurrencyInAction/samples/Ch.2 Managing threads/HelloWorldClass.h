#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>

class background_task
{
public:
	void operator()() const
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << "1";
		}
	}
};

class background_task_test
{
public:
	void operator()() const
	{
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			std::cout << "1";
		}
	}
};

std::thread background_task_test_function()
{
	background_task f;
	std::thread my_thread(f);
	return my_thread;
}

void do_something()
{
}
void do_something_else()
{
}

BEGIN_TEST(Ch2_HelloWorldClass)
	//initializes with a new object
	std::thread my_thread1{ background_task_test() };
	my_thread1.join(); //wait for the thread to finish, can only be called once, related: "IsJoinable()"
	my_thread1.detach(); //not to wait for thread to finish

						 //initializes with a thread returned by function
	std::thread my_thread2(background_task_test_function());
	my_thread1.join();

	//initializes with a local object
	background_task f;
	std::thread my_thread3(f);
	my_thread3.join();

	//initializes with a lambda
	std::thread my_thread([] 
	{
		do_something();
		do_something_else();
	});
END_TEST()

//int main(){MainExample(); return 0;}
