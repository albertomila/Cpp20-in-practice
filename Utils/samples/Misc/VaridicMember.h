#pragma once
#include "stdafx.h"
#include <typeinfo>
#include <functional>

namespace nsVaridicMember
{
	struct SData
	{
		SData()
			:_data(-1)
		{
		}

		SData(int data)
			:_data(data)
		{
		}

		int _data;
	};

	template<class... TArgs>
	class CVaridicContainer
	{
	public:
		using TCallback = std::function<void(TArgs...)>;
		using TVaridicTuple = std::tuple<TArgs...>;

		CVaridicContainer(TArgs... args)
			: _varidicArgs(args...)
		{
		}

		void Call(TCallback& callback)
		{
			const std::size_t TTupleSize = std::tuple_size<TVaridicTuple>::value;
			DoCall(callback, std::make_index_sequence<TTupleSize>());
		}

	private:
		template<size_t... TSequence >
		void DoCall(TCallback& callback, std::index_sequence<TSequence...> /*indexSequence*/)
		{
			//typeid(indexSequence) is
			//struct std::integer_sequence<size_t, 0, 1, 2, 3>
			callback
			(
				std::get<TSequence>
				(
					_varidicArgs
				)...
			);
		}

		TVaridicTuple _varidicArgs;
	};

	void TestMethod(const SData& data, int arg1, const std::string& arg2, float arg3)
	{
	}
}

BEGIN_TEST(VaridicMember)
	using namespace nsVaridicMember;

	SData data(100);

	CVaridicContainer<const SData&, int, const std::string&, float> varidicContainer(data, 1, "test", 99.f);

	std::function<void(const SData&, int, const std::string&, float)> callback 
		= [](const SData& arg0, int arg1, const std::string& arg2, float arg3)
	{
		TestMethod(arg0, arg1, arg2, arg3);
	};

	varidicContainer.Call(callback);


END_TEST()