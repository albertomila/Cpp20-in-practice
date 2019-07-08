#pragma once
#include "stdafx.h"

namespace nsStrategy
{
	class IStrategy
	{
	public:
		virtual void ExecuteAlgorithm() = 0;
	};

	class CStrategyA : public IStrategy
	{
	public:
		void ExecuteAlgorithm() override
		{
		}
	};

	class CStrategyB : public IStrategy
	{
	public:
		void ExecuteAlgorithm() override
		{
		}
	};

	class CObject
	{
	public:
		CObject(IStrategy* strategy)
			:_strategy(strategy)
		{
		}

		void ExecuteAlgorithm()
		{
			_strategy->ExecuteAlgorithm();
		}
	private:
		IStrategy* _strategy;
	};
}

BEGIN_TEST(Strategy)
	using namespace nsStrategy;
	
	CStrategyA strategyA;
	CObject object1(&strategyA);
	object1.ExecuteAlgorithm();

	CStrategyB strategyB;
	CObject object2(&strategyB);
	object2.ExecuteAlgorithm();

END_TEST()
