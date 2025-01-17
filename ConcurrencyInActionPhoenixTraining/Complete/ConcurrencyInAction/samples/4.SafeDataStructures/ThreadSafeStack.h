#pragma once
#include "stdafx.h"
#include <exception>
#include <stack>

namespace Ex26
{
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
		mutable std::mutex _mutex;

	public:
		threadsafe_stack() {}
		threadsafe_stack(const threadsafe_stack& other)
		{
			std::lock_guard<std::mutex> lock(other._mutex);
			data = other.data;
		}

		threadsafe_stack& operator = (const threadsafe_stack&) = delete;

		void push(T value)
		{
			std::lock_guard<std::mutex> lock(_mutex);
			data.push(std::move(value));
		}

		std::shared_ptr<T> pop()
		{
			std::lock_guard<std::mutex> lock(_mutex);
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
			std::lock_guard<std::mutex> lock(_mutex);
			if (data.empty())
			{
				throw empty_stack_tss();
			}

			value = std::move(data.top());
			data.pop();
		}

		bool empty() const
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			return data.empty();
		}
	};

	BEGIN_TEST(Ex26_ThreadSafeStack)
	END_TEST()
}