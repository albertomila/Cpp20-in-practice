#include "stdafx.h"
#include <deque>
#include <future>

std::mutex _mutex2;
std::deque<std::packaged_task<void()>> tasks;

void ThreadCheck()
{
	while (true)
	{
		std::packaged_task<void()> packageTask;
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

template<typename Function>
std::future<void> PostTaskForThreadCheck(Function f)
{
	std::packaged_task<void()> packageTask(f);
	std::future<void> futureTask = packageTask.get_future();
	std::lock_guard<mutex> lockGuard(_mutex2);
	tasks.push_back(std::move(packageTask));

	return futureTask;
}

void TaskForThreadCheck()
{

}

void ThreadMain()
{
	std::future<void> future = PostTaskForThreadCheck(TaskForThreadCheck);
	future.wait();
}

BEGIN_TEST(Ch4_PackageTask)
	std::thread threadCheck(ThreadCheck);
	std::thread threadMain(ThreadMain);

	threadMain.join();
	threadCheck.join();
	
END_TEST()
