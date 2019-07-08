#pragma once
#include "stdafx.h"
#include <tuple>
#include <map>

namespace nsAutoTupleReturn
{
	std::tuple<int, float, char> GetTupleData()
	{
		std::tuple<int, float, char> tupleData(1, 2.5f, 'A');
		return tupleData;
	}

	std::pair<int, float> GetPairData()
	{
		std::pair<int, float> tupleData(1, 2.5f);
		return tupleData;
	}
}

BEGIN_TEST(AutoTupleReturn)
	using namespace nsAutoTupleReturn;

	//auto[gear, speed, type] carData = GetTupleData();
	//auto[gear, speed] carData2 = GetPairData();

	std::map<int,std::string> dataMap;
	dataMap[10] = "1234";
	dataMap[100] = "5678";
	dataMap[1000] = "9999";

//	for (const auto&[key, value] : dataMap)
	{

	}
	
	// structs too
	// arrays too
END_TEST()