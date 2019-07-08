#pragma once
#include "stdafx.h"

namespace nsTwin
{
	class IObjectBase
	{
	};

	class IUpdater
	{
	public:
		virtual void Update() = 0;
	};

	class CMainObject;
	class CPartialExtensionObject : public IUpdater
	{
		friend class CMainObject;

	public:
		void Update() override
		{
		}

	private:
		CPartialExtensionObject(CMainObject* mainObject)
			:_mainObject(mainObject)
		{

		}

		CMainObject* _mainObject;
	};

	class CMainObject : public IObjectBase
	{
		friend class CPartialExtensionObject;
	public:
		CMainObject()
			:_partialExtension(this)
		{
		}

		void Update()
		{
			_partialExtension.Update();
		}

		IUpdater* GetUpdaterInterface()
		{
			return &_partialExtension;
		}

	private:
		CPartialExtensionObject _partialExtension;
	};
}

BEGIN_TEST(Twin)
	using namespace nsTwin;

	CMainObject mainObject;
	mainObject.Update();
	IUpdater* updaterInterface = mainObject.GetUpdaterInterface();
	updaterInterface->Update();

END_TEST()