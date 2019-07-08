#pragma once
#include "stdafx.h"
#include <iostream>

namespace Ex4
{
	//All arguments are copies, even those passed by references
	//They are references to internal copies.
	void PassingArgsFoo(int i, const std::string& value)
	{
	}

	void Thread()
	{
	}
	BEGIN_TEST(Ex4_PassingArgs)
		std::thread threadTest(Thread);
		//Special care to pass pointers
		//If we pass char* as string the pointer can be destroyed when the thread is started
		std::thread t(PassingArgsFoo, 3, std::string("Test"));
		t.detach();
	END_TEST()

		////////////////////////////////////////////////////////////////////
		class ClassData
	{
	public:
		ClassData()
			: _x(10)
		{
		}

		~ClassData()
		{
			_x = -1;
		}


		ClassData(const ClassData& testClass)
			: _x(testClass._x)
		{
		}

		ClassData(const ClassData&& testClass)
			: _x(std::move(testClass._x))
		{
		}

		void SetValue(int value)
		{
			_x = value;
		}
		void operator = (const ClassData& testClass)
		{
			_x = testClass._x;
		}

	private:
		int _x;
	};

	//The string value is really passed by reference in this use case
	void PassingArgsFooRef(ClassData& value)
	{
		sleep(1000);
	}

	BEGIN_TEST(Ex4_PassingArgsRef)
		ClassData classData;

		std::thread t(PassingArgsFooRef, std::ref(classData));
		classData.SetValue(100);
		t.join();
	END_TEST()

	////////////////////////////////////////////////////////////////////
	void PassingArgsFooMove(ClassData&& value)
	{
		sleep(1000);
		value.SetValue(1);
	}

	void Foo(ClassData value)
	{
		sleep(1000);
	}

	BEGIN_TEST(Ex4_PassingArgsMove)
		ClassData classData;
		std::thread t(PassingArgsFooMove, std::move(classData));
		classData.SetValue(100);
		t.join();
	END_TEST()
}