#include "stdafx.h"
#include <future>

namespace Ex20
{
	struct Data
	{
		int x;
	};


	void ThreadA(std::promise<Data>& promiseData)
	{
		sleep(5000);

		Data data;
		data.x = 99;
		promiseData.set_value(data);
	}

	void ThreadB(std::promise<Data>& promiseData)
	{
		std::future<Data> futurePromise = promiseData.get_future();
		//futurePromise.wait();
		Data dataValue = futurePromise.get();
	}

	BEGIN_TEST(Ex20_Promise)
		std::promise<Data> promiseData;

		std::thread threadCheck(ThreadA, std::ref(promiseData));
		std::thread threadMain(ThreadB, std::ref(promiseData));

		threadMain.join();
		threadCheck.join();

	END_TEST()
}