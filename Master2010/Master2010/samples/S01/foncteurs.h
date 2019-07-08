#pragma once
#include "stdafx.h"

template <class T>
class Draw
{
	std::ostream &os_;
public:
	Draw(std::ostream &os) throw() : os_(os) {}
	void operator()(const T &value) 
	{
		os_ << value;
	}
};


class Draw2
{
	std::ostream &os_;
public:
	Draw2(std::ostream &os) throw() : os_(os) {}

	template <class T>
	void operator()(const T &value) 
	{
		os_ << value;
	}
};

template<class T>
class MIN
{
	T val_;
public:
	MIN(const T &val) throw() : val_(val){}
	void operator() (const T &currentValue)
	{
		if(val_ > currentValue)
		{
			val_ = currentValue;
		}
	}
	T value() const
	{
		return val_;
	}
};


struct Random
{
	int max_;
	Random(int max) throw() : max_(max){}
	int operator() ()
	{ 
		return (rand() % max_); 
	}
};
struct Init
{
	int value_;
	Init() throw() : value_(-1){}
	Init(int value) throw() : value_(value){}
	int operator() ()
	{ 
		return value_; 
	}
};

struct Cumul
{
	int cumul_;
	Cumul() throw() : cumul_(0){}
	void operator() (const int &inValue)
	{ 
		cumul_ += inValue;
	}
	int total(){ return cumul_; }
};