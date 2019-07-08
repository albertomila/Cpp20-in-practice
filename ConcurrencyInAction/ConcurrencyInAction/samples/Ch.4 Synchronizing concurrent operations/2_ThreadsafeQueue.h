#include "stdafx.h"
#include <queue>

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

		TPredicate predicate(this, &ThreadsafeQueue<TypeValue>::WaitCondition);
		_conditionVar.wait(uniqueLock, predicate); //unlock when true, when pushed

		/*
		_conditionVar.wait(uniqueLock, 
		[this]
		{
			return WaitCondition();
		});
		*/

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

void TSQ_ThreadDataPreparation(ThreadsafeQueue<int>& threadSafeQueue)
{
	while (true)
	{
		threadSafeQueue.Push(1);

		std::cout << "Push: " << threadSafeQueue.Size() << std::endl;
	}
}

void TSQ_ThreadDataProcessing(ThreadsafeQueue<int>& threadSafeQueue)
{
	while (true)
	{
		int value = 0;
		threadSafeQueue.WaitAndPop(value);

		std::cout << "value: " << value << std::endl;
	}
}

BEGIN_TEST(Ch4_AccumulateParallel)
	ThreadsafeQueue<int> threadSafeQueue;

	std::thread threadPreparation(TSQ_ThreadDataPreparation, std::ref(threadSafeQueue));
	std::thread threadProcessing(TSQ_ThreadDataProcessing, std::ref(threadSafeQueue));

	threadPreparation.join();
	threadProcessing.join();

END_TEST()
