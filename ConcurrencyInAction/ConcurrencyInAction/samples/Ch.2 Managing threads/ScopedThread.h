#include "stdafx.h"

class ScopedThread
{
public:

	explicit ScopedThread(std::thread t)
		:_t(std::move(t))
	{
		if (!_t.joinable())
		{
			throw std::logic_error("No thread");
		}
	}

	~ScopedThread()
	{
		_t.join();
	}

	ScopedThread(ScopedThread const&) = delete;
	ScopedThread& operator=(ScopedThread const&) = delete;

private:
	std::thread _t;
};

struct StructTestThread
{
	StructTestThread()
		:x(0)
	{
	}

	StructTestThread(int value)
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

BEGIN_TEST(Ch2_ScopedThread)
	int localState = 1;

	StructTestThread test = StructTestThread(localState);
	std::thread t1(test);
	ScopedThread scopedThread(std::move(t1));
	
END_TEST()

//int main(){MainExample(); return 0;}
