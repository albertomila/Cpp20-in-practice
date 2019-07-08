#include "stdafx.h"
#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>


std::queue<int> products;
std::mutex m;
std::condition_variable cond_var;
bool done = false;
bool notified = false;

void PC_ThreadProducer()
{
	while(true)
	{
		sleep(200);
		std::unique_lock<std::mutex> lock(m);
		int productValue = rand() % 100;
		products.push(productValue);
		std::cout << "push productValue["<< products.size() <<"]: " << productValue << '\n';
	}
}

void PC_ThreadConsumer()
{
	while (true)
	{
		sleep(1000);
		std::unique_lock<std::mutex> lock(m);
		while (!products.empty())
		{
			int productValue = products.front();
			std::cout << "pop productValue[" << products.size() << "]: " << productValue << '\n';
			products.pop();
		}
	}
}

BEGIN_TEST(Ch8_ProducerConsumer)
	std::thread producer(PC_ThreadProducer);
	std::thread consumer(PC_ThreadConsumer);

	producer.join();
	consumer.join();
END_TEST()