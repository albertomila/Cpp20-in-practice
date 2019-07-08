#pragma once
#include "stdafx.h"
#include <iostream>
#include <thread>


namespace Ex5
{
	void Foo1()
	{
	}

	void Foo2()
	{
	}

	BEGIN_TEST(Ex5_TransferingThreads)
	{
		std::thread thread1(Foo1);
		std::thread thread2 = std::move(thread1); //thread2 takes thread1

		thread1 = std::thread(Foo2); //thread1 creates new thread

		std::thread thread3;
		thread3 = std::move(thread2); //thread3 takes thread2

		//thread1 takes thread3
		//thread1 already had a running thread so std::terminate() will be called and the previous thread is finished
		thread1 = std::move(thread3);
	}
	END_TEST()

	///////////////////////////////////////////////////////////////////////////

	void Foo3()
	{
	}
	std::thread ReturnThread()
	{
		return std::thread(Foo3);
	}

	BEGIN_TEST(Ex5_TransferingThreads2)
	{
		std::thread thread(ReturnThread());
	}
	END_TEST()

	///////////////////////////////////////////////////////////////////////////
	void Foo4()
	{
	}

	void ThreadAsArgument(std::thread& trhead)
	{
	}

	BEGIN_TEST(Ex5_TransferingThreads3)
	{
		std::thread thread(Foo4);
		ThreadAsArgument(thread);
	}
	END_TEST()
}