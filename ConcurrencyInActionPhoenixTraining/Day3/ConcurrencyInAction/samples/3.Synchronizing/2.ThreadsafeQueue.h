#pragma once
#include "stdafx.h"
#include <queue>

namespace Ex17
{
	template<typename T, typename Method>
	struct MyPredicateWrapper
	{
		T* _ptr;
		Method _method;

		explicit MyPredicateWrapper(T* ptr, Method method)
			: _ptr(ptr)
			, _method(method)
		{
		}

		bool operator() () const
		{
			return (_ptr->*_method)();
		}
	};

	template<typename T>
	class ThreadsafeQueue
	{
	private:
		typedef T TypeValue;
		typedef bool (ThreadsafeQueue<TypeValue>::*TPtrToWaitCondition)();
		typedef MyPredicateWrapper<ThreadsafeQueue<T>, TPtrToWaitCondition> TPredicate;
	private:
		mutable std::mutex _mutex;
		std::queue<TypeValue> _dataQueue;
		std::condition_variable _conditionVar;

	public:
		ThreadsafeQueue()
		{
		}

		ThreadsafeQueue(const ThreadsafeQueue& other)
		{
			std::lock_guard<std::mutex> lockGuard(other._mutex);
			_dataQueue = other._dataQueue;
		}

		bool Empty() const
		{
			std::lock_guard<std::mutex> lockGuard(_mutex);
			return _dataQueue.empty();
		}

		void Push(TypeValue newValue)
		{
			std::lock_guard<std::mutex> lockGuard(_mutex);
			_dataQueue.push(newValue);
			_conditionVar.notify_one();
		}

		void WaitAndPop(TypeValue& value)
		{
			std::unique_lock<std::mutex> uniqueLock(_mutex);

			TPredicate waitCondition(this, &ThreadsafeQueue<TypeValue>::WaitCondition);
			_conditionVar.wait(uniqueLock, waitCondition); //unlock when true, when pushed

			value = _dataQueue.front();
			_dataQueue.pop();
		}

		size_t Size()
		{
			return _dataQueue.size();
		}

	public:
		bool WaitCondition()
		{
			return !_dataQueue.empty();
		}
	};

	void ThreadDataPreparation(ThreadsafeQueue<int>& threadSafeQueue)
	{
		while (true)
		{
			sleep(1000);
			int randValue = rand() % 100;
			threadSafeQueue.Push(randValue);

			std::cout << "Push: " << randValue << "\n" << std::endl;
		}
	}

	void ThreadDataProcessing(ThreadsafeQueue<int>& threadSafeQueue)
	{
		while (true)
		{
			sleep(1000);
			int value_ref = -1;
			threadSafeQueue.WaitAndPop(value_ref);

			std::cout << "value: " << value_ref << "\n" << std::endl;
		}
	}

	BEGIN_TEST(Ex17_ThreadSafeQueue)
		ThreadsafeQueue<int> threadSafeQueue;

		std::thread threadPreparation(ThreadDataPreparation, std::ref(threadSafeQueue));
		std::thread threadProcessing(ThreadDataProcessing, std::ref(threadSafeQueue));

		threadPreparation.join();
		threadProcessing.join();

	END_TEST()
}