#include "stdafx.h"
#include <future>

struct DataFuture
{
	int x;
};


void Future_ThreadCheck(std::shared_future<DataFuture>& sharedFuturePromise)
{
	sharedFuturePromise.wait();
	DataFuture dataValue = sharedFuturePromise.get();
}

void Future_ThreadMain(std::promise<DataFuture>& promiseData)
{
	sleep(4000);
	DataFuture data;
	data.x = 99;

	//Notify all other threads.
	promiseData.set_value(data);
}

BEGIN_TEST(Ch4_SharedFuture)
	std::atomic<int> atomicInt;
	atomicInt = 4;

	std::promise<DataFuture> promiseData;
	std::shared_future<DataFuture> sharedFuturePromise = promiseData.get_future().share();

	std::thread threadMain(Future_ThreadMain, std::ref(promiseData));

	std::vector<std::thread> threads;
	for (int i = 0; i < 5; ++i)
	{
		threads.push_back(std::thread(Future_ThreadCheck, sharedFuturePromise));
	}

	threadMain.join();
	for (int i = 0; i < 5; ++i)
	{
		threads[i].join();
	}
	
END_TEST()