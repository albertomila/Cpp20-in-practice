#include "stdafx.h"
#include <thread>

namespace Ex51
{
	class scoped_thread
	{
	public:
		explicit scoped_thread(std::thread& t)
			:_t(std::move(t)) //it takes ownership of the thread
		{
			if (!_t.joinable())
			{
				throw std::logic_error("No thread");
			}
		}

		~scoped_thread()
		{
			_t.join();
		}

		scoped_thread(const scoped_thread&) = delete;
		scoped_thread& operator=(const scoped_thread &) = delete;

	private:
		std::thread _t;
	};

	struct Data
	{
		Data()
			:x(0)
		{
		}

		Data(int value)
			:x(value)
		{
		}

		void operator()()
		{
			int y = 0;
			while (true)
			{
				++y;
			}
		}
		int x;
	};

	BEGIN_TEST(Ex51_ScopedThread)
		Data data = Data(99);
		std::thread thread(data);
		scoped_thread scopedThread(thread);
	END_TEST()
}