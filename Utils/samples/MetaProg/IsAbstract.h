#include "stdafx.h"
#include <typeinfo> 
#include <type_traits>

namespace nsIsAbstract
{
	class Test1{};

	class Test2
	{
		virtual void VirtualMethod() = 0;
	};

	template <class T>
	struct is_pointer
	{
		template <class U>
		static char is_ptr(U*);

		template <class X, class Y>
		static char is_ptr(Y X::*);

		template <class U>
		static char is_ptr(U (*)());

		static double is_ptr(...);

		static T t;
		enum { value = sizeof(is_ptr(t)) == sizeof(char) };
	};

	struct Foo {
		int bar;
		int* barp;
	};

	template<typename T>
	class CWhatIsThisClassDoing
	{
		class Type1
		{
		};

		class Type2
		{
			char dataUnknown[3];
		};

		template<class U>
		static Type1 test(U(*)[1]);

		template<class U>
		static Type2 test(...);

	public:
		enum
		{
			value = sizeof(test<T>(0)) == sizeof(Type2);
		};
	};

	template<typename T>
	class is_abstract 
	{
		class TypeResultYes
		{
		};

		class TypeResultNo
		{
			char dataUnknown[3];
		};

		template<class U> 
		static TypeResultYes CheckIfCanInstantiateArray(U(*)[]); // defined

		template<class U> 
		static TypeResultNo CheckIfCanInstantiateArray(...); // not defined 

	public:
		static const bool value = sizeof(CheckIfCanInstantiateArray<T>(nullptr)) == sizeof(TypeResultNo);
	};

	template<typename T>
	class is_abstract_cpp11
	{
		template<class U>
		static constexpr bool CheckIfCanInstantiateArray(U(*)[]) { return true; } // defined

		template<class U>
		static constexpr bool CheckIfCanInstantiateArray(...) { return false; }

	public:
		static constexpr bool value = CheckIfCanInstantiateArray<T>(nullptr) == false;
	};
}

template<class T>
void Check(T(*)[1])
{
}

BEGIN_TEST(IsAbstract)
	using namespace nsIsAbstract;

	nsIsAbstract::Test1 t[1];
	Check(&t);
	

	typedef int* IntPtr;
	typedef int Foo::* FooMemberPtr;
	typedef int(*FuncPtr)();

	bool b0 = nsIsAbstract::is_pointer<Foo>::value;        // prints 1
	bool b1 = nsIsAbstract::is_pointer<IntPtr>::value;        // prints 1
	bool b2 = nsIsAbstract::is_pointer<FooMemberPtr>::value;  // prints 1
	bool b3 = nsIsAbstract::is_pointer<FuncPtr>::value;       // prints 1

	const bool isAstract1 = nsIsAbstract::is_abstract<nsIsAbstract::Test1>::value;
	const bool isAstract2 = nsIsAbstract::is_abstract<nsIsAbstract::Test2>::value;
	static_assert(nsIsAbstract::is_abstract<nsIsAbstract::Test1>::value == false, "test1");
	static_assert(nsIsAbstract::is_abstract<nsIsAbstract::Test2>::value == true, "test2");




	const bool isAstract3 = nsIsAbstract::is_abstract_cpp11<nsIsAbstract::Test1>::value;
	const bool isAstract4 = nsIsAbstract::is_abstract_cpp11<nsIsAbstract::Test2>::value;
	static_assert(nsIsAbstract::is_abstract_cpp11<nsIsAbstract::Test1>::value == false, "test3");
	static_assert(nsIsAbstract::is_abstract_cpp11<nsIsAbstract::Test2>::value == true, "test4");




	//false
	constexpr bool isAbstract1 = std::is_abstract<nsIsAbstract::Test1>::value;

	//true
	constexpr bool isAbstract2 = std::is_abstract<nsIsAbstract::Test2>::value;

	int x = 0;
	++x;

	int y = x + 1;
	++y;

	/*
	nsIsAbstract::Test1 testArray[4];
	using T3 = nsIsAbstract::Test1(*)[4];
	T3 t3 = &testArray;
	nsIsAbstract::Test1 arrtest = (*t3)[0];
	*/

END_TEST()