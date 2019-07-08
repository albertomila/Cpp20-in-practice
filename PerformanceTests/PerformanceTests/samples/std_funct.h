#pragma once
#include "stdafx.h"
#include "PerformanceTests.h"
#include <functional>
#include <iostream>

namespace nsTestStdFunct
{
	class CDataEmpty
	{
	};

	class CData
	{
	public:
		CData()
			: _data1("_data1")
			, _data2("_data2")
			, _data3("_data3")
			, _data4("_data4")
			, _data5("_data5")
			, _data6("_data6")
			, _data7("_data7")
			, _data8("_data8")
			, _data9("_data9")
			, _data10("_data10")
		{
		}

		CData(const CData& data)
			: _data1(data._data1)
			, _data2(data._data2)
			, _data3(data._data3)
			, _data4(data._data4)
			, _data5(data._data5)
			, _data6(data._data6)
			, _data7(data._data7)
			, _data8(data._data8)
			, _data9(data._data9)
			, _data10(data._data10)
		{
		}

		std::string _data1;
		std::string _data2;
		std::string _data3;
		std::string _data4;
		std::string _data5;
		std::string _data6;
		std::string _data7;
		std::string _data8;
		std::string _data9;
		std::string _data10;
	};

	CDataEmpty emptyData;
	CData fullData;

	void EmptyArgsFoo()
	{
	}

	void EmptyDataFoo(CDataEmpty& data)
	{
	}

	void FullDataFoo(CData& data)
	{
	}

	void ControlGroupTest()
	{
	}

	////test1
	static std::function<void()> empty_args_foo = &EmptyArgsFoo;
	static std::function<void()> empty_data_foo = std::bind(&EmptyDataFoo, emptyData);
	static std::function<void()> full_data_foo = std::bind(&FullDataFoo, fullData);
	static std::function<void(CData&)> full_data_arg_foo = std::bind(&FullDataFoo, fullData);

	std::function<void()> _memberLambda = empty_args_foo;
	std::function<void(CData&)> _memberLambdaArg = full_data_arg_foo;

	void Test1_Foo(std::function<void()> lambda)
	{
		lambda();
	}
	void Test1()
	{
		Test1_Foo(empty_args_foo);
	}

	////test2
	void Test2_Foo(std::function<void()>& lambda)
	{
		lambda();
	}
	void Test2()
	{
		Test2_Foo(empty_args_foo);
	}

	////test3
	void Test3_Foo(std::function<void()> lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test3()
	{
		Test3_Foo(empty_args_foo);
	}

	////test4
	void Test4_Foo(std::function<void()>& lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test4()
	{
		Test3_Foo(empty_args_foo);
	}

	////test5
	void Test5_Foo(std::function<void()> lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test5()
	{
		Test5_Foo(empty_data_foo);
	}

	////test6
	void Test6_Foo(std::function<void()>& lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test6()
	{
		Test5_Foo(empty_data_foo);
	}

	////test7
	void Test7_Foo(std::function<void()> lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test7()
	{
		Test7_Foo(full_data_foo);
	}

	////test8
	void Test8_Foo(std::function<void()>& lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test8()
	{
		Test8_Foo(full_data_foo);
	}





	////test10
	void Test10_Foo(std::function<void()> lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test10()
	{
		std::function<void()> _empty_args_foo = &EmptyArgsFoo;
		Test10_Foo(_empty_args_foo);
	}

	////test11
	void Test11_Foo(std::function<void()>& lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test11()
	{
		std::function<void()> _empty_args_foo = &EmptyArgsFoo;
		Test11_Foo(_empty_args_foo);
	}

	////test12
	void Test12_Foo(std::function<void()> lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test12()
	{
		std::function<void()> _full_data_foo = &EmptyArgsFoo;
		Test12_Foo(_full_data_foo);
	}

	////test13
	void Test13_Foo(std::function<void()>& lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test13()
	{
		std::function<void()> _full_data_foo = &EmptyArgsFoo;
		Test13_Foo(_full_data_foo);
	}



	////test20
	void Test20_Foo(std::function<void()> lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test20()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, fullData);
		Test20_Foo(_full_data_foo);
	}

	/*
	void Test20()
	{
		CData& fullData2 = *&fullData;
		std::function<void()> _full_data_foo = [&fullData2]() {FullDataFoo(fullData2); };
		Test20_Foo(_full_data_foo);
	}
	*/

	////test21
	void Test21_Foo(std::function<void()>& lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test21()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, fullData);
		Test21_Foo(_full_data_foo);
	}

	////test22
	void Test22_Foo(std::function<void()> lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test22()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, fullData);
		Test22_Foo(_full_data_foo);
	}

	////test23
	void Test23_Foo(std::function<void()>& lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test23()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, fullData);
		Test23_Foo(_full_data_foo);
	}




	////test30
	void Test30_Foo(std::function<void()> lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test30()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, std::ref(fullData));
		Test30_Foo(_full_data_foo);
	}

	////test31
	void Test31_Foo(std::function<void()>& lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test31()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, std::ref(fullData));
		Test31_Foo(_full_data_foo);
	}

	////test33
	void Test32_Foo(std::function<void()> lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test32()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, std::ref(fullData));
		Test32_Foo(_full_data_foo);
	}

	////test33
	void Test33_Foo(std::function<void()>& lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test33()
	{
		std::function<void()> _full_data_foo = std::bind(&FullDataFoo, std::ref(fullData));
		Test33_Foo(_full_data_foo);
	}


	////test40
	void Test40_Foo(std::function<void(CData&)> lambda)
	{
		_memberLambdaArg = lambda;
		_memberLambdaArg(fullData);
	}
	void Test40()
	{
		std::function<void(CData&)> _full_data_foo = std::bind(&FullDataFoo, std::placeholders::_1);
		Test40_Foo(_full_data_foo);
	}
	////test41
	void Test41_Foo(std::function<void(CData&)>& lambda)
	{
		_memberLambdaArg = lambda;
		_memberLambdaArg(fullData);
	}
	void Test41()
	{
		std::function<void(CData&)> _full_data_foo = std::bind(&FullDataFoo, std::placeholders::_1);
		Test41_Foo(_full_data_foo);
	}

	////test43
	void Test42_Foo(std::function<void(CData&)> lambda)
	{
		_memberLambdaArg = std::move(lambda);
		_memberLambdaArg(fullData);
	}
	void Test42()
	{
		std::function<void(CData&)> _full_data_foo = std::bind(&FullDataFoo, std::placeholders::_1);
		Test42_Foo(_full_data_foo);
	}

	////test43
	void Test43_Foo(std::function<void(CData&)>& lambda)
	{
		_memberLambdaArg = std::move(lambda);
		_memberLambdaArg(fullData);
	}
	void Test43()
	{
		std::function<void(CData&)> _full_data_foo = std::bind(&FullDataFoo, std::placeholders::_1);
		Test43_Foo(_full_data_foo);
	}

	////test50
	void Test50_Foo(std::function<void()> lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test50()
	{
		CData& fullData2 = *&fullData;
		std::function<void()> _full_data_foo = [&fullData2]() {FullDataFoo(fullData2); };
		Test20_Foo(_full_data_foo);
	}


	////test51
	void Test51_Foo(std::function<void()>& lambda)
	{
		_memberLambda = lambda;
		_memberLambda();
	}
	void Test51()
	{
		CData& fullData2 = *&fullData;
		std::function<void()> _full_data_foo = [&fullData2]() {FullDataFoo(fullData2); };
		Test51_Foo(_full_data_foo);
	}

	////test52
	void Test52_Foo(std::function<void()> lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test52()
	{
		CData& fullData2 = *&fullData;
		std::function<void()> _full_data_foo = [&fullData2]() {FullDataFoo(fullData2); };
		Test52_Foo(_full_data_foo);
	}

	////test53
	void Test53_Foo(std::function<void()>& lambda)
	{
		_memberLambda = std::move(lambda);
		_memberLambda();
	}
	void Test53()
	{
		CData& fullData2 = *&fullData;
		std::function<void()> _full_data_foo = [&fullData2]() {FullDataFoo(fullData2); };
		Test53_Foo(_full_data_foo);
	}
}

BEGIN_TEST(TestStdFunct)
	CPerformanceTests performanceTests(1);
	performanceTests.SetEntryTest("Control", &nsTestStdFunct::ControlGroupTest);
	/*
	performanceTests.SetEntryTest("Test1", &nsTestStdFunct::Test1);
	performanceTests.SetEntryTest("Test2", &nsTestStdFunct::Test2);
	performanceTests.SetEntryTest("Test3", &nsTestStdFunct::Test3);
	performanceTests.SetEntryTest("Test4", &nsTestStdFunct::Test4);
	performanceTests.SetEntryTest("Test5", &nsTestStdFunct::Test5);
	performanceTests.SetEntryTest("Test6", &nsTestStdFunct::Test6);
	performanceTests.SetEntryTest("Test7", &nsTestStdFunct::Test7);
	performanceTests.SetEntryTest("Test8", &nsTestStdFunct::Test8);
	*/
	/*
	performanceTests.SetEntryTest("Test10", &nsTestStdFunct::Test10);
	performanceTests.SetEntryTest("Test11", &nsTestStdFunct::Test11);
	performanceTests.SetEntryTest("Test12", &nsTestStdFunct::Test12);
	performanceTests.SetEntryTest("Test13", &nsTestStdFunct::Test13);
	
	performanceTests.SetEntryTest("Test20", &nsTestStdFunct::Test20);
	performanceTests.SetEntryTest("Test21", &nsTestStdFunct::Test21);
	performanceTests.SetEntryTest("Test22", &nsTestStdFunct::Test22);
	performanceTests.SetEntryTest("Test23", &nsTestStdFunct::Test23);
	*/
	performanceTests.SetEntryTest("Test30", &nsTestStdFunct::Test30);
	performanceTests.SetEntryTest("Test31", &nsTestStdFunct::Test31);
	performanceTests.SetEntryTest("Test32", &nsTestStdFunct::Test32);
	performanceTests.SetEntryTest("Test33", &nsTestStdFunct::Test33);
	/*
	performanceTests.SetEntryTest("Test40", &nsTestStdFunct::Test40);
	performanceTests.SetEntryTest("Test41", &nsTestStdFunct::Test41);
	performanceTests.SetEntryTest("Test42", &nsTestStdFunct::Test42);
	performanceTests.SetEntryTest("Test43", &nsTestStdFunct::Test43);
	*/
	performanceTests.SetEntryTest("Test50", &nsTestStdFunct::Test50);
	performanceTests.SetEntryTest("Test51", &nsTestStdFunct::Test51);
	performanceTests.SetEntryTest("Test52", &nsTestStdFunct::Test52);
	performanceTests.SetEntryTest("Test53", &nsTestStdFunct::Test53);

	performanceTests.StartTest();

END_TEST()