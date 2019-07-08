#pragma once
#include "stdafx.h"

namespace nsTemplateMethod
{
	class ITemplateOperations
	{
	public:
		void Execute()
		{
			LoadResources();
			InitSystems();
			LoadData();
		}

	protected:
		virtual void LoadResources() = 0;
		virtual void InitSystems() = 0;
		virtual void LoadData() = 0;
	};

	class CSystem : public ITemplateOperations
	{
	protected:
		void LoadResources() override
		{

		}

		void InitSystems() override
		{

		}

		void LoadData() override
		{

		}
	};

	class CSystem2 : public ITemplateOperations
	{
	protected:
		void LoadResources() override
		{

		}

		void InitSystems() override
		{

		}

		void LoadData() override
		{

		}
	};
}

BEGIN_TEST(TemplateMethod)
	using namespace nsTemplateMethod;

	CSystem system;
	system.Execute();

	CSystem2 system2;
	system2.Execute();

END_TEST()