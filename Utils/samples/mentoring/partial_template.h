
#include "stdafx.h"

namespace nsPartialTemplate
{
	struct CATCH_GENERIC_CASE {};
	struct CATCH_SOUND_COMPONENT_CASE {};
	struct CATCH_PHYSICS_COMPONENT_CASE {};
	struct CATCH_GAMEPLAY_COMPONENT_CASE {};


	template<class T, class V, class W>
	class CTest0
	{
	public:
		void DoSomething(T& value1, V& value2, W& value3) {}
	};

	template<class T>
	class CTest0<T, int, double>
	{
	public:
		void DoSomething(T& value1, int& value2, double& value3) {}
	};


	/*
	class CTest2
	{
	public:
	template<class T, class V>
	void Test() {}

	template<class T>
	void Test<T, int>() {}

	template<class T>
	void Test<T, double>() {}
	};
	*/

	class CTest3
	{
	public:
		template<class T, class V>
		void Test() {}

		template<class T>
		void Test(int) {}
	};


	class CTest4
	{
		template<class T, class V>
		class CTestArgumentHandle
		{
		public:
			static void Process(CTest4* parent)
			{
				parent->DoTest<T, V>();
			}
		};

		template<class T>
		class CTestArgumentHandle <T, int>
		{
		public:
			static void Process(CTest4* parent)
			{
				//Here it creates a value in order to use method overload
				parent->DoTest<T>(int());
			}
		};

	public:
		template<class T, class V>
		void Test()
		{
			CTestArgumentHandle<T, V>::Process(this);
		}

		template<class T, class V>
		void DoTest() {}

		template<class T>
		void DoTest(int) {}
	};

	struct SJsonFile {};
	struct SXmlFile {};
	struct SCsvFile {};
	struct STextFile {};

	struct SJsonPolicy {};
	struct SXmlPolicy {};
	struct SCsvPolicy {};
	struct SGenericPolicy {};


	template<class SourceType, class TargetPolicy>
	class CDataParser
	{
	public:
		static void SerializeData(const std::vector<SourceType>& data)
		{
			//generic policy to convert from sourceObject to an object of TargetType
		}
	};


	template<class SourceType>
	class CDataParser<SourceType, SJsonPolicy>
	{
	public:
		static void SerializeData(const std::vector<SourceType>& data)
		{
			//specific policy to convert from sourceObject to an object of JsonFile
		}
	};

	template<class SourceType>
	class CDataParser<SourceType, SXmlPolicy>
	{
	public:
		static void SerializeData(const std::vector<SourceType>& data)
		{
			//specific policy to convert from sourceObject to an object of XMLFile
		}
	};

	template<class SourceType>
	class CDataParser<SourceType, SCsvPolicy>
	{
	public:
		static void SerializeData(const std::vector<SourceType>& data)
		{
			//specific policy to convert from sourceObject to an object of CsvFile
		}
	};

	/*
	class CDataParser2
	{
	public:
	template<class SourceType, class TargetPolicy>
	static TargetPolicy* SerializeData(const std::vector<SourceType>& data)
	{
	//generic policy to convert from sourceObject to an object of TargetType
	return nullptr;
	}

	template<class SourceType>
	static SJsonPolicy::TFileType* SerializeData<SJsonPolicy>(const std::vector<SourceType>& data)
	{
	//specific policy to convert from sourceObject to an object of JsonFile
	return nullptr;
	}

	template<class SourceType>
	static SXmlPolicy::TFileType* SerializeData<SXmlPolicy>(const std::vector<SourceType>& data)
	{
	//specific policy to convert from sourceObject to an object of XMLFile
	return nullptr;
	}

	template<class SourceType>
	static SCsvPolicy::TFileType* SerializeData<SCsvPolicy>(const std::vector<SourceType>& data)
	{
	//specific policy to convert from sourceObject to an object of CsvFile
	return nullptr;
	}
	};
	*/

	class CDataParser3
	{
	public:
		template<class SourceType, class TargetPolicy>
		static void SerializeData(TargetPolicy, const std::vector<SourceType>& data)
		{
			//generic policy to convert from sourceObject to an object of TargetType
		}

		template<class SourceType>
		static void SerializeData(SJsonPolicy, const std::vector<SourceType>& data)
		{
			//specific policy to convert from sourceObject to an object of JsonFile
		}

		template<class SourceType>
		static void SerializeData(SXmlPolicy, const std::vector<SourceType>& data)
		{
			//specific policy to convert from sourceObject to an object of XMLFile
		}

		template<class SourceType>
		static void SerializeData(SCsvPolicy, const std::vector<SourceType>& data)
		{
			//specific policy to convert from sourceObject to an object of CsvFile
		}
	};

	struct CATCH_INT {};
	struct CATCH_VECTOR_INT {};

	class CTest5
	{
	public:
		template<class T, class V>
		void Test(CATCH_GENERIC_CASE, const V& data) {}

		template<class T>
		void Test(CATCH_INT, int data) {}

		template<class T>
		void Test(CATCH_VECTOR_INT, const std::vector<int>& data) {}

		template<class T, class V>
		void TestMain(const V& data)
		{
			using typeCatcher = std::conditional<true, V, int>::type
		}
	};

	struct SFullData
	{
		int megaData[1024];
	};


	template<class T, class V>
	class CTestPure
	{
	public:
		void Test(V& value) {}
	};

	template<class T>
	class CTestPure<T, int>
	{
	public:
		void Test(int value) {}
	};

	template<class T>
	class CTestPure<T, double>
	{
	public:
		void Test(double value) {}
	};



}

BEGIN_TEST(PartialTemplate)
	using namespace nsPartialTemplate;
	SFullData megaData;

	CTest5 test5;
	test5.Test<std::string>(CATCH_GENERIC_CASE(), megaData);
	test5.Test<std::string>(CATCH_INT(), 4);
	test5.Test<std::string>(CATCH_VECTOR_INT(), std::vector<int>());

	CTestPure<float, int> test;
	test.Test(3);

	CTest3 test31;
	test31.Test<float, int>();
	test31.Test<float>(int());

	CTest4 test4;
	test4.Test<float, int>();
	test4.Test<float, float>();

	std::vector<int> data;
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);

	CDataParser<int, SJsonPolicy>::SerializeData(data);
	//	CDataParser2::SerializeData<int, SJsonPolicy>(data);
	CDataParser3::SerializeData<int>(SGenericPolicy(), data);

END_TEST()
