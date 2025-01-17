#include "stdafx.h"
#include <vector>
#include <list>
#include <future>

class join_threads_pfe
{
public:
	explicit join_threads_pfe(std::vector<std::thread>& threads_) :
		threads(threads_)
	{
	}

	~join_threads_pfe()
	{
		for (unsigned long i = 0; i < threads.size(); ++i)
		{
			if (threads[i].joinable())
			{
				threads[i].join();
			}
		}
	}

private:
	std::vector<std::thread>& threads;
};

template<typename Iterator, typename Func>
void parallel_for_each(Iterator first, Iterator last, Func f)
{
	unsigned long const length = std::distance(first, last);
	if (!length)
	{
		return;
	}
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
	unsigned long const hardware_threads = std::thread::hardware_concurrency();
	unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	unsigned long const block_size = length / num_threads;
	std::vector<std::future<void> > futures(num_threads - 1);
	std::vector<std::thread> threads(num_threads - 1);

	join_threads_pfe joiner(threads);
	Iterator block_start = first;
	for (unsigned long i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);
		std::packaged_task<void(void)> task(
			[=]()
		{
			std::for_each(block_start, block_end, f);
		});
		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task));
		block_start = block_end;
	}

	std::for_each(block_start, last, f);
	for (unsigned long i = 0; i < (num_threads - 1); ++i)
	{
		futures[i].get();
	}
}

template<typename Iterator, typename Func>
void parallel_for_each_using_async(Iterator first, Iterator last, Func f)
{
	unsigned long const length = std::distance(first, last);
	if (!length)
	{
		return;
	}

	unsigned long const min_per_thread = 25;
	if (length < (2 * min_per_thread))
	{
		std::for_each(first, last, f);
	}
	else
	{
		const Iterator mid_point = first + length / 2;
		std::future<void> first_half = std::async(&parallel_for_each<Iterator, Func>
												, first
												, mid_point
												, f);
		parallel_for_each(mid_point, last, f);
		first_half.get();
	}
}

BEGIN_TEST(Ch8_ParallelForEach)
END_TEST()