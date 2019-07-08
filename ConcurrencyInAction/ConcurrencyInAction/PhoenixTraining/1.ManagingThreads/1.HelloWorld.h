#include "stdafx.h"
#include <iostream>
#include <thread> //main include
#include <chrono>

namespace Ex1
{ 
	inline void Thread()
	{
		for(int i = 0; i<3; ++i)
		{
			sleep(1000);
			std::cout << "Thread 1" << std::endl;
		}
	}

	BEGIN_TEST(Ex1_HelloWorld)
		std::thread threadTest(Thread);
		std::cout << "Thread Main" << std::endl;

		//wait until thread 1 is finished
		//cleans up the thread. 
		//property "joinable()" returns false from now on
		threadTest.join(); 
	
		std::cout << "Thread Main finish" << std::endl;
	END_TEST()
}