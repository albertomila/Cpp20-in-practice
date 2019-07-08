#include "stdafx.h"

class ItemFlag
{
private:
	std::once_flag _initFlag;

private:
	void DoSomethingUnique()
	{
	}

	void DoSomethingGeneral()
	{
	}

public:
	ItemFlag()
	{
	}

	void DoSomething()
	{
		std::call_once(_initFlag, &ItemFlag::DoSomethingUnique, this);
		DoSomethingGeneral();
	}

	void DoSomethingElse()
	{
		std::call_once(_initFlag, &ItemFlag::DoSomethingUnique, this);
		DoSomethingGeneral();
	}
};


void ThreadA(ItemFlag& item1)
{
	std::cout << "ThreadA" << "\n" << std::endl;
	
	item1.DoSomething();
}

void ThreadB(ItemFlag& item1)
{
	std::cout << "ThreadB" << "\n" << std::endl;
	item1.DoSomethingElse();
}


BEGIN_TEST(Ch3_OnceFlag)
	ItemFlag item;
	std::thread threadA(ThreadA, std::ref(item));
	std::thread threadB(ThreadB, std::ref(item));

	threadA.join();
	threadB.join();

END_TEST()

//int main(){MainExample(); return 0;}
