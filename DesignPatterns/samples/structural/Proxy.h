#pragma once
#include "stdafx.h"
#include <vector>

namespace nsProxy
{
	class IComponent
	{
	public:
		virtual void ExecuteCall() = 0;
	};

	class CGameplayComponent : public IComponent
	{
	public:
		void ExecuteCall() override {}
	};

	class CProxy : public IComponent
	{
	public:
		CProxy()
			: _component(nullptr)
		{
		}

		void ExecuteCall() override 
		{
			LazyInit();
			_component->ExecuteCall();
		}

		IComponent* operator()()
		{
			LazyInit();
			return _component;
		}

	private:
		void LazyInit()
		{
			if (_component == nullptr)
			{
				_component = new CGameplayComponent();
			}
		}

		IComponent* _component;
	};
}

BEGIN_TEST(Proxy)
	using namespace nsProxy;

	CProxy proxy;
	proxy.ExecuteCall();
	proxy()->ExecuteCall();

END_TEST()