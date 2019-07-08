#pragma once
#include "stdafx.h"

namespace nsExample23
{
	template 
	<
		template <typename...> 
		typename Container
	>
	struct STest
	{
	};

	void DoSomething()
	{
	}
}


BEGIN_TEST(MoreFeatures)
	using namespace nsExample23;

	//typename in a template template parameter
	{
		STest<std::vector> data;
	}

	//u8 character literals
	{
		const char data = u8'C'; //char in UTF-8
	}



	//remove deprecated operator++ for bool
	{
		bool value = false;
//		++value;
	}




	//using in attributes
	{
//		[[rpr::kernel, rpr::target(cpu, gpu)]] //before
//		[[using rpr:     kernel, target(cpu, gpu)]] //after
		DoSomething();
	}






	//operator "new" and "delete" now suppoprts std::align_val_t
	{
/*		void* operator new(std::size_t, std::align_val_t);
		void* operator new[](std::size_t, std::align_val_t);
		void operator delete(void*, std::align_val_t);
		void operator delete[](void*, std::align_val_t);
		void operator delete(void*, std::size_t, std::align_val_t);
		void operator delete[](void*, std::size_t, std::align_val_t);*/
	}

	//hexadecimal floating points
	{
		//smallest floating point.
		//float f = 0x1.0p-126;
	}


END_TEST()