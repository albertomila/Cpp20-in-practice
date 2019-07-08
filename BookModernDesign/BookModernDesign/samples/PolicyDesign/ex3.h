#pragma once
#include "stdafx.h"

namespace nsPolicyDesign3
{
	class Widget
	{
	public:
		int m_value;
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
		, template <class> class CheckingPolicy = EnsureNotNull
		, template <class> class ThreadingModel
		, template <class> class Storage = DefaultSmartPtrStorage
		>
		class SmartPtr
		: public CheckingPolicy<T>
		, public ThreadingModel<SmartPtr<T, ThreadingModel, CheckingPolicy> >
	{
	public:

		T* operator->()
		{
			typename ThreadingModel<SmartPtr>::Lock guard(*this);
			CheckingPolicy<T>::Check(pointee_);
			return pointee_;
		}
	private:
		T* pointee_;
	};

	typedef SmartPtr<Widget, NoChecking, SingleThreaded>        WidgetPtr;
	typedef SmartPtr<Widget, EnforceNotNull, SingleThreaded>    SafeWidgetPtr;
}

BEGIN_TEST(PolicyDesign3)
	using namespace nsPolicyDesign3;

    WidgetPtr widgetptr;
	widgetptr->m_value;
END_TEST()