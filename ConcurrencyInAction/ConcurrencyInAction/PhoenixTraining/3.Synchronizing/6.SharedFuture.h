#include "stdafx.h"
#include <future>

namespace Ex21
{
	struct DataFuture
	{
		int x;
	};


	void ThreadListener1(std::shared_future<DataFuture>& sharedFuturePromise)
	{
		DataFuture dataValue = sharedFuturePromise.get();
	}
	void ThreadListener2(std::shared_future<DataFuture>& sharedFuturePromise)
	{
		DataFuture dataValue = sharedFuturePromise.get();
	}
	void ThreadListener3(std::shared_future<DataFuture>& sharedFuturePromise)
	{
		DataFuture dataValue = sharedFuturePromise.get();
	}

	void ThreadB(std::promise<DataFuture>& promiseData)
	{
		sleep(4000);
		DataFuture data;
		data.x = 99;

		//Notify all other threads.
		promiseData.set_value(data);
	}

	BEGIN_TEST(Ex21_SharedFuture)
		std::promise<DataFuture> promiseData;
		std::shared_future<DataFuture> sharedFuturePromise = promiseData.get_future().share();

		std::thread threadMain(ThreadB, std::ref(promiseData));

		std::vector<std::thread> threads;
		threads.push_back(std::thread(ThreadListener1, sharedFuturePromise));
		threads.push_back(std::thread(ThreadListener2, sharedFuturePromise));
		for (int i = 0; i < 5; ++i)
		{
			threads.push_back(std::thread(ThreadListener3, sharedFuturePromise));
		}

		threadMain.join();
		for (std::thread& thread : threads)
		{
			thread.join();
		}

	END_TEST()
}