#pragma once
#include "stdafx.h"

namespace nsAdapter
{
	class COldSystem
	{
	public:
		void DoUpdate()
		{
		}
	};


	class IUpdater
	{
	public:
		virtual void Update() = 0;
	};

	class CNewSystem : public IUpdater
	{
	public:
		void Update() override
		{
			_oldSystem.DoUpdate();
		}

	private:
		COldSystem _oldSystem;
	};
}


BEGIN_TEST(Adapter)
	using namespace nsAdapter;

	IUpdater* newSystem = new CNewSystem();
	while (true)
	{
		newSystem->Update();
	}
END_TEST()