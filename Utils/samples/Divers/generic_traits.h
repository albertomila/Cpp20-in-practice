#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

namespace nsGenericTraits
{
	struct Remove
	{
		Remove(){}
		template <class T>
		bool operator()(const T& t)
		{
			delete t;
			return true;
		}
	};
	struct Delete
	{
		Delete(){}
		template <class T>
		void operator()(const T& t)
		{
			delete t;
		}
	};
	struct Update
	{
		Update(){}
		template <class T>
		void operator()(const T& t)
		{
			t->Update();
		}
	};
}

class GenericTraits_Data
{
public:
	int pos_;
	GenericTraits_Data(int pos) : pos_(pos)
	{
	}
	~GenericTraits_Data()
	{
	}
	void Update()
	{
		pos_++;
	}
};

struct GenericTraits_Predicate
{
	int removeValue_;
	GenericTraits_Predicate(int removeValue) : removeValue_(removeValue){}
	bool operator()(GenericTraits_Data& t1)
	{
		return (t1.pos_ == removeValue_);
	}
};

BEGIN_TEST(GenericTraits)
	GenericTraits_Data* t1 = new GenericTraits_Data(0);
	GenericTraits_Data* t2 = new GenericTraits_Data(1);
	GenericTraits_Data* t3 = new GenericTraits_Data(2);
	vector<GenericTraits_Data*> v;
	v.push_back(t1);
	v.push_back(t2);
	v.push_back(t3);
	for_each(v.begin(),v.end(), nsGenericTraits::Delete());

	END_TEST()

