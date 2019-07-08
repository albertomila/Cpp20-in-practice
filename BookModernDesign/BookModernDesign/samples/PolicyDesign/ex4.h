#pragma once
#include "stdafx.h"

namespace nsPolicyDesign4
{
	class Widget
	{
	public:
		int m_value;
	};

	class ExtendedWidget : public Widget
	{
	};

	///////////////////////////////////////
	//CheckingPolicy
	///////////////////////////////////////
	template <class T>
	struct NoChecking
	{
		static void Check(T*) {}
	};

	///////////////////////////////////////
	template <class T>
	struct EnforceNotNull
	{
		class NullPointerException : public std::exception
		{
		};

		EnforceNotNull()
		{
		}

		EnforceNotNull(NoChecking<T>& nocheck)
		{
		}

		static void Check(T* ptr)
		{
			if (!ptr) throw NullPointerException();
		}
	};

	///////////////////////////////////////
	template <class T>
	struct EnsureNotNull
	{
		static void Check(T*& ptr)
		{
			if (!ptr) ptr = GetDefaultValue();
		}
	};

	///////////////////////////////////////
	//Threating policy
	///////////////////////////////////////
	template <class T>
	struct SingleThreaded
	{
		typedef T Lock;
	};

	///////////////////////////////////////
	template <class T>
	struct MultiThreaded
	{
		typedef T Lock;
	};

	///////////////////////////////////////
	//Pointer storage
	///////////////////////////////////////
	template <class T>
	class DefaultSmartPtrStorage
	{
	public:
		typedef T* PointerType;
		typedef T& ReferenceType;
	protected:
		PointerType GetPointer() { return ptr_; }
		void SetPointer(PointerType ptr) { pointee_ = ptr; }
	private:
		PointerType ptr_;
	};


	///////////////////////////////////////
	//SmartPtr
	///////////////////////////////////////
	template
		<
		class T
		, template <class> class CheckingPolicy
		>
		class SmartPtr
		: public CheckingPolicy<T>
	{
	public:
		SmartPtr()
		{
		}

		template
			<
			class T1,
			template <class> class CP1
			>
			SmartPtr(const SmartPtr<T1, CP1>& other)
			: pointee_(other.pointee_), CheckingPolicy<T>(other)
		{ }


	public:
		T* pointee_;
	};
}
BEGIN_TEST(PolicyDesign4)
	using namespace nsPolicyDesign4;
    SmartPtr<ExtendedWidget, NoChecking> smartPtr1;
    //SmartPtr<Widget, EnforceNotNull> smartPtr = smartPtr1;

END_TEST()