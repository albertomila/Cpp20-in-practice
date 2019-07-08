#include "stdafx.h"
#include <atomic>
#include <queue>
#include <list>

namespace Ex15
{
	class Semaphore
	{
	public:
		Semaphore(int count_)
			: count(count_)
		{
		}

		void wait(int source)
		{
			std::unique_lock<std::mutex> lock(m);

			std::cout << "wait " << source << " count:" << count << '\n';
			if (count == 0)
			{
				std::cout << "push thread " << source << '\n';
				queueCV.push(new std::condition_variable());
				queueCV.back()->wait(lock);
			}
			count--;

			std::cout << "thread " << source << " execute" << '\n';
		}

		void notify(int source)
		{
			std::unique_lock<std::mutex> lock(m);
			count++;

			if (!queueCV.empty())
			{
				std::condition_variable* cv = queueCV.front();
				queueCV.pop();
				cv->notify_one();
				delete cv;
			}
		}

	private:
		std::mutex m;
		std::queue<std::condition_variable*> queueCV;
		int count;
	};

	const int Ex15_MAX_THREADS = 10;
	const int Ex15_MAX_THREADS_ALLOWED = 5;
	Semaphore sem(Ex15_MAX_THREADS_ALLOWED);

	void Thread(int i)
	{
		sem.wait(i);
		sleep(2000);
		sem.notify(i);
	}

	BEGIN_TEST(Ex15_Semaphore)
		std::list<std::thread*> threads;

		for (int i = 0; i < Ex15_MAX_THREADS; ++i)
		{
			std::thread* th = new std::thread(Thread, i);
			threads.push_back(th);
		}

		for (std::thread* th : threads)
		{
			th->join();
		}

		std::cout << "thread main" << std::endl;
	END_TEST()
}