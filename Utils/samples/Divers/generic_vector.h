#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Clonable
{
public:
	virtual Clonable* Clone() const= 0;
	//virtual ~Clonable() throw();
	virtual const std::type_info& DeudireType() throw() = 0;
};

template<class T>
class Capsule : public Clonable
{
	typedef T type_data;
public:
	type_data value_;

	Capsule(const type_data& value = type_data()) : value_(value)
	{
	}
	Capsule(const Capsule<T>& value) : value_(value.GetValue())
	{

	}
	/*~Capsule() throw() 
	{
	}*/
	const std::type_info& DeudireType() throw() 
	{
		return typeid(value_);
	}

	Clonable* Clone() const
	{
		return new Capsule<T>(*this);
	}

	type_data GetValue() const
	{
		return value_;
	}
};

class Whatever
{
	Clonable* capsule_;
public:
	
	Clonable* GetCapsule()
	{
		return capsule_;
	}

	
	Whatever() : capsule_(0) {}
	


	template<class T>
	Whatever(const T& value) : capsule_(new Capsule<T>(value))
	{
	}

	Whatever(Clonable* clonable) : capsule_(clonable->Clone())
	{
	}

	Whatever(Whatever& whatever) : capsule_(whatever.GetCapsule()->Clone())
	{

	}

	~Whatever()
	{
		delete capsule_;
	}

	template<class T>
	Capsule<T> GetCapsule()
	{
		return static_cast<Capsule<T>*>(capsule_);
	}

	template<class T>
	bool IsType() throw()
	{
		return capsule_->DeudireType() == typeid(T);
	}

};

BEGIN_TEST(GenericVector)
	Capsule<int>* caps = new Capsule<int>(0);
	Whatever w = Whatever(caps);
	vector<Whatever> v;
	v.push_back(w);
	v.push_back(true);
	v.push_back(5.5f);

	END_TEST()