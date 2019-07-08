#include "stdafx.h"
#include <mutex>
#include <list>
#include <stack>
#include <memory>

struct empty_stack_exception : std::exception
{
	virtual const char* what() const throw() override
	{
		return "empty_stack_exception";
	}
};

template<typename T>
class ThreadSafeStack
{
	private:
		std::stack<T> _stack;
		std::mutex _mutex;
public:
	ThreadSafeStack()
	{
	}

	ThreadSafeStack( const ThreadSafeStack& other)
	{
		std::lock_guard<std::mutex> lock(other._mutex);
		_stack = other._stack;
	}

	ThreadSafeStack& operator = (const ThreadSafeStack& other) = delete;

	void push(T value)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_stack.push(value);
	}

	void push(T& value)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		_stack.push(value);
	}

	void pop(T& value_out)
	{
		std::lock_guard<std::mutex> lock(_mutex);
		if (_stack.empty())
		{
			throw empty_stack_exception();
		}

		T value = _stack.top();
		_stack.pop();
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(_mutex);
		if (_stack.empty())
		{
			throw empty_stack_exception();
		}

		std::shared_ptr<T> returnValue(std::make_shared<T>(std::move(_stack.top())));
		_stack.pop();

		return returnValue;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(_mutex);
		return _stack.empty();
	}
};

BEGIN_TEST(Ch3_ThreadSafeStack)
	ThreadSafeStack<int> threadSafeStack;
	threadSafeStack.push(1);
	threadSafeStack.push(2);
	threadSafeStack.push(3);

	std::shared_ptr<int> x = threadSafeStack.pop();

	int result_out = 0;
	threadSafeStack.pop(result_out);

END_TEST()
