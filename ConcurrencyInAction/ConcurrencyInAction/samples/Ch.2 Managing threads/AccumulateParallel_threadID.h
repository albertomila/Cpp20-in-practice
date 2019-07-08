#pragma once
#include "stdafx.h"
//#include <iostream>
//#include <thread>
//
//#include <numeric>
//#include <vector>
//#include <algorithm>
//
//template<typename Iterator, typename T>
//struct accumulate_block
//{
//	void operator() (Iterator first, Iterator last, T& result)
//	{
//		std::cout << "[" << std::this_thread::get_id() << "]\n" << std::endl;
//		result = std::accumulate(first, last, result);
//	}
//};
//
//template<typename Iterator, typename T>
//T parallel_accumulate(Iterator first, Iterator last, T init)
//{
//	const unsigned int length = std::distance(first, last);
//	if (!length)
//	{
//		return init;
//	}
//
//	static const unsigned int MIN_PER_THREADS = 25;
//	const unsigned int max_threads = (length + MIN_PER_THREADS - 1) / MIN_PER_THREADS;
//	const unsigned int hardware_threads = std::thread::hardware_concurrency();
//	      unsigned int num_threads =	  hardware_threads != 0
//									? hardware_threads
//									: 2;
//	num_threads = std::min(num_threads, max_threads);
//	const unsigned int block_size = length / num_threads;
//
//	std::vector<T> results(num_threads + 1);
//	std::vector<std::thread> threads(num_threads+1);
//
//	Iterator block_start = first;
//	for (unsigned int i = 0; i < (num_threads); ++i)
//	{
//		Iterator block_end = block_start;
//		std::advance(block_end, block_size);
//		threads[i] = std::thread(	  accumulate_block<Iterator, T>()
//									, block_start
//									, block_end
//									, std::ref(results[i]));
//
//		std::cout << "(" << threads[i].get_id() << ")\n" << std::endl;
//		block_start = block_end;
//	}
//
//	threads[num_threads] = std::thread(accumulate_block<Iterator, T>()
//							, block_start
//							, last
//							, std::ref(results[num_threads]));
//
//	std::for_each(threads.begin()
//				, threads.end()
//				, std::mem_fn(&std::thread::join));
//
//	return std::accumulate(results.begin(), results.end(), init);
//
//}

BEGIN_TEST(Ch2_AccumulateParallel)

	//static const unsigned int MAX_VALUES = 1000000;
	//std::vector<unsigned int> values(MAX_VALUES);
	//std::generate(values.begin(), values.end(), [] { return 2; });

	//int cumulValue = parallel_accumulate(values.begin(), values.end(), 0);

END_TEST()
