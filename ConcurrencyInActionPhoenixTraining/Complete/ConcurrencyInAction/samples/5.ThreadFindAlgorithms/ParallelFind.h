#pragma once
#include "stdafx.h"
#include <vector>
#include <list>
#include <future>

namespace Ex27
{
	class join_threads
	{
	public:
		explicit join_threads(std::vector<std::thread>& threads_) :
			threads(threads_)
		{
		}

		~join_threads()
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

	template<typename Iterator, typename MatchType>
	Iterator parallel_find(Iterator first, Iterator last, MatchType match)
	{
		struct find_element
		{
			void operator() (Iterator begin
				, Iterator end
				, MatchType match
				, std::promise<Iterator>* result
				, std::atomic<bool>* done_flag)
			{
				try
				{
					for (; (begin != end) && !done_flag->load(); ++begin)
					{
						if (*begin == match)
						{
							result->set_value(begin);
							done_flag->store(true);
							return;
						}
					}
				}
				catch (...)
				{
					try
					{
						result->set_exception(std::current_exception());
						done_flag->store(true);
					}
					catch (...)
					{
					}
				}
			}
		};
		unsigned long const length = std::distance(first, last);
		if (!length)
		{
			return last;
		}
		unsigned long const min_per_thread = 25;
		unsigned long const max_threads = (length + min_per_thread - 1) / min_per_thread;
		unsigned long const hardware_threads = std::thread::hardware_concurrency();
		unsigned long const num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
		unsigned long const block_size = length / num_threads;

		std::promise<Iterator> result;
		std::atomic<bool> done_flag(false);
		std::vector<std::thread> threads(num_threads - 1);
		{
			join_threads joiner(threads);
			Iterator block_start = first;
			for (unsigned long i = 0; i < (num_threads - 1); ++i)
			{
				Iterator block_end = block_start;
				std::advance(block_end, block_size);
				threads[i] = std::thread(find_element()
					, block_start
					, block_end
					, match
					, &result
					, &done_flag);
				block_start = block_end;
			}
			find_element()(block_start
				, last
				, match
				, &result
				, &done_flag);
		}
		if (!done_flag.load())
		{
			return last;
		}
		return result.get_future().get();
	}


	//async version
	template<typename Iterator, typename MatchType>
	Iterator parallel_find_impl_async(Iterator first, Iterator last, MatchType match,
		std::atomic<bool>& done)
	{
		try
		{
			unsigned long const length = std::distance(first, last);
			unsigned long const min_per_thread = 25;
			if (length < (2 * min_per_thread))
			{
				for (; (first != last) && !done.load(); ++first)
				{
					if (*first == match)
					{
						done = true;
						return first;
					}
				}
				return last;
			}
			else
			{
				Iterator const mid_point = first + (length / 2);
				std::future<Iterator> async_result = std::async(
					&parallel_find_impl_async<Iterator, MatchType>
					, mid_point
					, last
					, match
					, std::ref(done));

				Iterator const direct_result = parallel_find_impl_async(first, mid_point, match, done);

				return (direct_result == mid_point)
					? async_result.get()
					: direct_result;
			}
		}
		catch (...)
		{
			done = true;
			throw;
		}
	}

	template<typename Iterator, typename MatchType>
	Iterator parallel_find_async(Iterator first, Iterator last, MatchType match)
	{
		std::atomic<bool> done(false);
		return parallel_find_impl_async(first, last, match, done);
	}

	BEGIN_TEST(Ex27_ParallelFind)
	END_TEST()
}