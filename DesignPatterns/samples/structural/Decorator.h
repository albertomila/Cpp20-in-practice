#pragma once
#include "stdafx.h"
#include <vector>

namespace nsDecorator
{
	class IComponent
	{
	public:
		virtual void Update() = 0;
	};

	class CGameplayComponent : public IComponent
	{
	public:
		void Update() override {}
	};

	class CAIComponent : public IComponent
	{
	public:
		void Update() override {}
	};

	class CUIComponent : public IComponent
	{
	public:
		void Update() override {}
	};

	class IDecorator : public IComponent
	{
	public:

		void SetComponent(IComponent* component)
		{
			_component = component;
		}

		void Update() override final
		{
			PreUpdate();
			_component->Update();
			PostUpdate();
		}

		virtual void PreUpdate() = 0;
		virtual void PostUpdate() = 0;

		IComponent* _component;
	};

	class CDecoratorRegular : public IDecorator
	{
	public:
		void PreUpdate()
		{

		}

		void PostUpdate()
		{

		}
	};

	class CDecoratorDebug : public IDecorator
	{
	public:
		void PreUpdate()
		{

		}

		void PostUpdate()
		{

		}
	};
}

BEGIN_TEST(Decorator)
	using namespace nsDecorator;

	CGameplayComponent gameplayComponent;
	CAIComponent aiComponent;

	CDecoratorRegular decoratorRegular;
	decoratorRegular.SetComponent(&gameplayComponent);
	
	IComponent* component = &decoratorRegular;
	component->Update();

END_TEST()