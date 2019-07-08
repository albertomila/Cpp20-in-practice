#pragma once
#include "stdafx.h"

namespace nsNullObject
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
			//do something
		}
	};

	class CStrategyNull : public IStrategy
	{
	public:
		void ExecuteAlgorithm() override
		{
			//empty implementation
		}
	};

	class CObject
	{
	public:
		CObject(IStrategy& strategy)
			:_strategy(strategy)
		{
		}

		void ExecuteAlgorithm()
		{
			_strategy.ExecuteAlgorithm();
		}
	private:
		IStrategy& _strategy;
	};
}

BEGIN_TEST(NullObject)
	using namespace nsNullObject;
	
	CStrategyA strategyA;
	CObject object1(strategyA);
	object1.ExecuteAlgorithm();

	CStrategyNull strategyB;
	CObject object2(strategyB);
	object2.ExecuteAlgorithm();

END_TEST()
