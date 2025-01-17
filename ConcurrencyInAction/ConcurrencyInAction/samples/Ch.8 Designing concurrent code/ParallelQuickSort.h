#include "stdafx.h"
#include <vector>
#include <list>
#include <future>
#include "../Ch.6 Lock-based data structures/ThreadSafeStack.h"

template<typename T>
struct parallel_sorter
{
private:
	struct chunk_to_sort
	{
		std::list<T> data;
		std::promise<std::list<T> > promise;
	};

public:
	parallel_sorter()
		: max_thread_count(std::thread::hardware_concurrency() - 1)
		, end_of_data(false)
	{
	}

	~parallel_sorter()
	{
		end_of_data = true;
		for (unsigned i = 0; i < threads.size(); ++i)
		{
			threads[i].join();
		}
	}

	void try_sort_chunk()
	{
		std::shared_ptr<chunk_to_sort > chunk = chunks.pop();
		if (chunk)
		{
				sort_chunk(chunk);
		}
	}

	std::list<T> do_sort(std::list<T>& chunk_data)
	{
		if (chunk_data.empty())
		{
			return chunk_data;
		}

		std::list<T> result;
		result.splice(result.begin(), chunk_data, chunk_data.begin());

		const T& partition_val = *result.begin();
		typename std::list<T>::iterator divide_point = std::partition
			( chunk_data.begin()
			, chunk_data.end()
			, [&](const T& val) {return val < partition_val; });

		chunk_to_sort new_lower_chunk;
		new_lower_chunk.data.splice (new_lower_chunk.data.end()
									, chunk_data
									, chunk_data.begin()
									, divide_point);

		std::future<std::list<T> > new_lower = new_lower_chunk.promise.get_future();

		chunks.push(std::move(new_lower_chunk));

		if (threads.size() < max_thread_count)
		{
			threads.push_back(std::thread(&parallel_sorter<T>::sort_thread, this));
		}

		std::list<T> new_higher(do_sort(chunk_data));

		result.splice(result.end(), new_higher);

		while (new_lower.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
		{
			try_sort_chunk();
		}

		result.splice(result.begin(), new_lower.get());
		return result;
	}

	void sort_chunk(std::shared_ptr<chunk_to_sort > const& chunk)
	{
		chunk_to_sort* cts = chunk.get();
		cts->promise.set_value(do_sort(chunk->data));
	}

	void sort_thread()
	{
		while (!end_of_data)
		{
			try_sort_chunk();
			std::this_thread::yield();
		}
	}

private:
	threadsafe_stack<chunk_to_sort> chunks;
	std::vector<std::thread> threads;
	unsigned const max_thread_count;
	std::atomic<bool> end_of_data;

};

template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
	if (input.empty())
	{
		return input;
	}
	parallel_sorter<T> s;
	return s.do_sort(input);
}
//

BEGIN_TEST(Ch8_ParallelQuickSort)
//{
//	std::list<int> randList;
//	for (int i = 0; i < 100; ++i)
//	{
//		randList.push_back(rand() % 1000);
//	}
//
//	std::list<int> sortedList = parallel_quick_sort<int>(randList);
END_TEST()
