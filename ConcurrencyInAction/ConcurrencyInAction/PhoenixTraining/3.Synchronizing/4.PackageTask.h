#include "stdafx.h"
#include <deque>
#include <future>

namespace Ex19
{
	std::mutex _mutex2;
	std::deque<std::packaged_task<int()>> tasks;


	int TaskForThreadCheck()
	{
		return 0;
	}

	template<typename Function>
	std::future<int> PostTaskForThreadCheck(Function f)
	{
		std::packaged_task<int()> packageTask(f);
		std::future<int> futureTask = packageTask.get_future();

		std::lock_guard<mutex> lockGuard(_mutex2);
		tasks.push_back(std::move(packageTask));

		return futureTask;
	}

	void ThreadMain()
	{
		std::future<int> future = PostTaskForThreadCheck(TaskForThreadCheck);
		//future.wait();
		future.get();
	}

	void ThreadCheck()
	{
		while (true)
		{
			std::packaged_task<int()> packageTask;
			{
				std::lock_guard<mutex> lockGuard(_mutex2);
				if (tasks.empty())
				{
					continue;
				}

				packageTask = std::move(tasks.front());
				tasks.pop_front();
			}

			sleep(10000);
			packageTask();
		}
	}

	BEGIN_TEST(Ex19_PackageTask)
		std::thread threadCheck(ThreadCheck);
		std::thread threadMain(ThreadMain);

		threadMain.join();
		threadCheck.join();

	END_TEST()
}