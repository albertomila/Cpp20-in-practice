#pragma once
#include "stdafx.h"
#include <mutex>

namespace Ex23
{
	template<typename T>
	class threadsafe_list
	{
	private:
		struct node
		{
			std::mutex mutex;
			std::shared_ptr<T> data;
			std::unique_ptr<node> next;

			node()
				: next()
			{
			}

			node(const T& value)
				: data(std::make_shared<T>(value))
			{
			}
		};

	public:
		threadsafe_list()
		{
		}
		~threadsafe_list()
		{
			remove_if
			(
				[](const node&)
			{
				return true;
			}
			);
		}

		threadsafe_list(const threadsafe_list& other) = delete;
		threadsafe_list& operator = (const threadsafe_list& other) = delete;

		void push_front(const T& value)
		{
			std::unique_ptr<node> new_node(new node(value));
			std::lock_guard<std::mutex> lockGuard(head.mutex);
			new_node->next = std::move(head.next);
			head.next = std::move(new_node);
		}

		template<typename Function>
		void for_each(Function f)
		{
			node* current = &head;
			std::unique_lock<std::mutex> lockGuard(head.mutex);

			while (const node* next = current->next.get())
			{
				std::unique_lock<std::mutex> next_lockGuard(next->mutex);
				lockGuard.unlock();
				f(*next->data);
				current->next;
				lockGuard = std::move(next_lockGuard);
			}
		}

		template<typename Predicate>
		std::shared_ptr<T> find_first_if(Predicate predicate)
		{
			node* current = &head;
			std::unique_lock<std::mutex> lk(head.mutex);

			while (const node* next = current->next.get())
			{
				std::unique_lock<std::mutex> next_lk(next->mutex);
				lk.unlock();
				if (predicate(*next->data))
				{
					return next->data;
				}
				current = next;
				lk = std::move(next_lk);
			}
			return std::shared_ptr<T>();
		}

		template<typename Predicate>
		void remove_if(Predicate predicate)
		{
			node* current = &head;
			std::unique_lock<std::mutex> lk(head.mutex);
			while (node* next = current->next.get())
			{
				std::unique_lock<std::mutex> next_lk(next->mutex);
				if (predicate(*next->data))
				{
					std::unique_ptr<node> old_next = std::move(current->next);
					current->next = std::move(next->next);
					next_lk.unlock();
				}
				else
				{
					lk.unlock();
					current = next;
					lk = std::move(next_lk);
				}
			}
		}

	private:
		node head;
	};


	BEGIN_TEST(Ex23_ThreadSafeList)
		threadsafe_list<int> tsl;
	END_TEST()
}