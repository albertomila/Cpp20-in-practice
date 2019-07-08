#include "stdafx.h"
#include <future>

struct Data
{
	int x;
};


void ThreadCheck_(std::promise<Data>& promiseData)
{
	sleep(5000);

	Data data;
	data.x = 99;
	promiseData.set_value(data);
}

void ThreadMain_(std::promise<Data>& promiseData)
{
	std::future<Data> futurePromise = promiseData.get_future();
	futurePromise.wait();
	Data dataValue = futurePromise.get();
}

BEGIN_TEST(Ch4_Promise)
	std::promise<Data> promiseData;

	std::thread threadCheck(ThreadCheck_, std::ref(promiseData));
	std::thread threadMain(ThreadMain_, std::ref(promiseData));

	threadMain.join();
	threadCheck.join();
	
END_TEST()
