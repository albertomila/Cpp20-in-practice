#pragma once
#include "stdafx.h"

namespace nsBuilder
{
	class CItem
	{
	public:
		void AddPart(const char* part)
		{
			_parts.push_back(part);
		}

	private:
		std::vector<std::string> _parts;
	};

	class IBuilder
	{
	public:
		IBuilder()
		{
		}
		virtual void BuildFirstStep() = 0;
		virtual void BuildSecondStep() = 0;
		CItem& GetItem() { return _item; };

	protected:
		CItem _item;
	};

	class CBuilderA : public IBuilder
	{
		void BuildFirstStep() override
		{
			_item.AddPart("Part1_A");
		}
		void BuildSecondStep() override
		{
			_item.AddPart("Part2_A");
		}
	};

	class CBuilderB : public IBuilder
	{
		void BuildFirstStep() override
		{
			_item.AddPart("Part1_B");
		}
		void BuildSecondStep() override
		{
			_item.AddPart("Part2_B");
		}
	};

	class CManager
	{
	public:
		CManager()
			:_builder(nullptr)
		{
		}

		void SetBuilder(CBuilderA* builder)
		{
			_builder = builder;
		}

		void BuildItem()
		{
			_builder->BuildFirstStep();
			_builder->BuildSecondStep();
		}

		CItem& GetItemBuilt()
		{
			return _builder->GetItem();
		}

	private:
		IBuilder* _builder;
	};
}

BEGIN_TEST(Builder)
	using namespace nsBuilder;

	CManager manager;
	CBuilderA* builder = new CBuilderA();

	manager.SetBuilder(builder);
	manager.BuildItem();
	CItem& item = manager.GetItemBuilt();


END_TEST()