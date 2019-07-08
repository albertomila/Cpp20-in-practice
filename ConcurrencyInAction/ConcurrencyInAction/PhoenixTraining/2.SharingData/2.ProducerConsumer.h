#include "stdafx.h"
#include <stack>

namespace Ex8
{
	class Factory
	{
	private:
		std::stack<int> _items;
		static int s_nextElement;
		enum
		{
			MAX_ELEMENTS = 40
		};

		std::mutex _mutex;
	public:
		Factory()
		{
		}

		void Produce()
		{
			std::lock_guard<std::mutex> lockGuard(_mutex);
			if (_items.size() < MAX_ELEMENTS)
			{
				int newItem = ++s_nextElement;
				_items.push(newItem);
				//std::cout << "+1" << "\n";
			}
		}

		void Consume()
		{
			std::lock_guard<std::mutex> lockGuard(_mutex);
			if (!_items.empty())
			{
				int topElement = _items.top();
				_items.pop();
				//std::cout << "-1" << "\n";

				if (rand() % 2 == 0)
				{
					if (!_items.empty())
					{
						_items.pop();
						//std::cout << "-1" << "\n";
					}
				}
			}
		}

		void PrintStack()
		{
			size_t count = _items.size();
			char* bars = new char[count + 1];
			for (int i = 0; i < static_cast<int>(count); ++i)
			{
				*(bars + i) = ' ';
			}
			for (int i = 0; i < static_cast<int>(count); ++i)
			{
				*(bars + i) = '|';
			}

			bars[count] = '\0';

			std::cout << "(" << count << ")" << bars << endl;
			delete[] bars;
		}
	};

	int Factory::s_nextElement = 0;

	void ThreadProducer(Factory& factory)
	{
		std::cout << "ThreadA" << "\n" << std::endl;

		while (true)
		{
			sleep(40);
			factory.Produce();
		}
	}

	void ThreadConsumer(Factory& factory)
	{
		std::cout << "ThreadB" << "\n" << std::endl;
		while (true)
		{
			sleep(60);
			factory.Consume();
		}
	}

	void ThreadReader(Factory& factory)
	{
		std::cout << "ThreadReader" << "\n" << std::endl;
		while (true)
		{
			sleep(20);
			factory.PrintStack();
		}
	}

	BEGIN_TEST(Ex8_ProducerConsumer)
		Factory factory;
		std::thread threadProducer(ThreadProducer, std::ref(factory));
		std::thread threadConsumer(ThreadConsumer, std::ref(factory));
		std::thread threadReader(ThreadReader, std::ref(factory));

		threadProducer.join();
		threadConsumer.join();
		threadReader.join();
	END_TEST()
}