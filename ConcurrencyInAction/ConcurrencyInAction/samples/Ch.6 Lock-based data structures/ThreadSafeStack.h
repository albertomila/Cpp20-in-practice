#pragma once
#include "stdafx.h"
#include <exception>
#include <stack>

struct empty_stack_tss : std::exception
{
	const char* what() const throw()
	{
		return "Empty stack!";
	}
};

template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m;

public:
	threadsafe_stack() {}
	threadsafe_stack(const threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data;
	}

	threadsafe_stack& operator = (const threadsafe_stack&) = delete;

	void push(T value)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data.push(std::move(value));
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(other.m);
		if (data.empty())
		{
			throw empty_stack_tss();
		}

		const std::shared_ptr<T> res(std::make_shared<T>(std::move(data.top())));
		data.pop();

		return res;
	}

	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(other.m);
		if (data.empty())
		{
			throw empty_stack_tss();
		}

		value = std::move(data.top());
		data.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};

BEGIN_TEST(Ch6_ThreadSafeStack)
END_TEST()
