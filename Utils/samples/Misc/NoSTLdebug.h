#pragma once
#include "stdafx.h"
#include <typeinfo>
#include <functional>

namespace nsNoSTLDebug
{
	class CTest
	{
	public:
		void SetCallback(std::function<void(int)> callback)
		{
			m_callback = std::move(callback);
		}

		void Call(int value)
		{
			m_callback(value);
		}

	private:
		std::function<void(int)> m_callback;
	};

	void Callback(int value)
	{
	}
}

BEGIN_TEST(NoSTLDebug)
	using namespace nsNoSTLDebug;

	CTest test;

	std::function<void(int)> functionCallback = Callback;
	test.SetCallback(functionCallback);
	test.Call(99);

END_TEST()
