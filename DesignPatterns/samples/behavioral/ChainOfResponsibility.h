#pragma once
#include "stdafx.h"
#include <assert.h> 

namespace nsChainOfResponsibility
{
	class IApprover
	{
	public:
		IApprover()
			:_successor(nullptr)
		{

		}
		
		void SetSuccessor(IApprover* successor)
		{
			_successor = successor;
		}

	protected:

		virtual void ProcessPurchase() = 0;
		void DoProcessSuccessorPurchase()
		{
			_successor->ProcessPurchase();
		}

	private:
		IApprover* _successor;
	};

	class CDirector : public IApprover
	{
	public:
		void RequestPurchase(int amount)
		{
			_requestAmount = amount;
			ProcessPurchase();
		}

	protected:
		void ProcessPurchase() override
		{
			assert(_requestAmount > 0);
			if (_companyBudget > _requestAmount)
			{
				DoProcessSuccessorPurchase();
			}
			_requestAmount = 0;
		}
	private:
		int _companyBudget = 9999;
		int _requestAmount = 0;
	};
	
	class CProducer : public IApprover
	{
	public:
		void ProcessPurchase() override
		{
			DoProcessSuccessorPurchase();
		}
	};

	class CFinancesManager : public IApprover
	{
	public:
		void ProcessPurchase() override
		{
			//process final purchase
		}
	};
}

BEGIN_TEST(ChainOfResponsibility)
	using namespace nsChainOfResponsibility;

	CDirector director;
	CProducer producer;
	CFinancesManager financesManger;

	director.SetSuccessor(&producer);
	producer.SetSuccessor(&financesManger);

	director.RequestPurchase(1000);

END_TEST()