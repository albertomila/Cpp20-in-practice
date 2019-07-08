#pragma once
#include "stdafx.h"
#include <vector>

namespace nsComposite
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

	class CObject
	{
	public:
		CObject()
		{
		}

		template<class T>
		void AddComponent()
		{
			_components.push_back(new T());
		}

		void Update()
		{
			for (IComponent* component : _components)
			{
				component->Update();
			}
		}

	private:
		std::vector<IComponent*> _components;
	};
}

BEGIN_TEST(Composite)
	using namespace nsComposite;

	CObject obj;
	obj.AddComponent<CGameplayComponent>();
	obj.AddComponent<CAIComponent>();
	obj.AddComponent<CUIComponent>();

	while (true)
	{
		obj.Update();
	}
END_TEST()