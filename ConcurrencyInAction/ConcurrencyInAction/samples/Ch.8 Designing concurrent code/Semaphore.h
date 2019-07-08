#include "stdafx.h"
#include <atomic>
#include <queue>
#include <list>

class semaphore
{
public:
	semaphore(int count_)
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

		std::cout << "thread "<< source <<" execute" << '\n';
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

const int Ch8_MAX_THREADS = 10;
const int Ch8_MAX_THREADS_ALLOWED = 2;
semaphore sem(Ch8_MAX_THREADS_ALLOWED);

void FncThread(int i)
{
	sem.wait(i);
	sleep(2000);
	sem.notify(i);
}

BEGIN_TEST(Ch8_Semaphore)
	std::list<std::thread*> threads;

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		std::thread* th = new std::thread(FncThread, i);
		threads.push_back(th);
	}

	for(std::thread* th : threads)
	{
		th->join();
	}

	std::cout << "thread main" << std::endl;
END_TEST()