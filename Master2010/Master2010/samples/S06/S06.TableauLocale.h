#pragma once
#include "stdafx.h"
#include <algorithm>
#include <stdexcept>
using std::copy;

template <class T>
class TL_TabDyn
{
public:
	typedef T					value_type;
	typedef int					size_type;
	typedef value_type&			reference;
	typedef const T&			const_reference;
	typedef value_type*			pointer;
	typedef const value_type*	const_pointer;

private:
	enum { CAPACITE_DEFAUT = 10 };
	pointer elems_;
	size_type nelems_;
	size_type capacite_;
	void croitre()
	{
		//
		// Politique: ratio de croissance 1.5 de la capacité
		//
		const float RATIO_CROISSANCE = 1.5f;
		const size_type nouv_cap = static_cast<size_type>(capacity() * RATIO_CROISSANCE);
		pointer p = new value_type[nouv_cap];
		try
		{
			copy(begin(), end(), p);
			delete [] elems_;
			elems_ = p;
			capacite_ = nouv_cap;
		}
		catch(...)
		{
			delete [] p;
			throw;
		}
	}
public:
	size_type size() const throw()
	{ 
		return nelems_; 
	}
	size_type capacity() const throw()
	{ 
		return capacite_; 
	}
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	iterator begin() throw()
	{ 
		return elems_; 
	}
	const_iterator begin() const throw()
	{ 
		return elems_; 
	}
	iterator end() throw()
	{ 
		return begin() + size(); 
	}
	const_iterator end() const throw()
	{ 
		return begin() + size();
	}
	//
	// Constructeurs
	//
	TL_TabDyn()
		: nelems_(0), capacite_(CAPACITE_DEFAUT), elems_(new value_type[CAPACITE_DEFAUT])
	{
	}
	TL_TabDyn(const TL_TabDyn &t)
		: nelems_(t.size()), capacite_(t.capacity()), elems_(new value_type[t.capacity()])
	{
		try
		{
			copy(t.begin(), t.end(), begin());
		}
		catch(...)
		{
			delete [] elems_;
			throw;
		}
	}
	~TL_TabDyn() throw()
	{ 
		delete [] elems_; 
	}
	bool full() const throw()
	{ 
		return size() == capacity (); 
	}
	void push_back(const_reference val)
	{
		if (full()) croitre();
		elems_[size()] = val;
		++nelems_;
	}
	value_type operator[](const size_type n) const
	{
		if (static_cast<unsigned int>(n) >= size())
			throw std::invalid_argument("Indice illégal");
		return elems_[n];
	}
	reference operator[](const size_type n)
	{
		if (static_cast<unsigned int>(n) >= size())
			throw std::invalid_argument("Indice illégal");
		return elems_[n];
	}
};


#include <iostream>
#include <algorithm>
#include <iterator>

BEGIN_TEST(TableLocal)
   using std::cout;
   using std::endl;
   using std::copy;
   using std::ostream_iterator;
   const int NB_ELEMS = 30;
   TL_TabDyn<int> tab;

   for (int i = 0; i < NB_ELEMS; ++i)
      tab.push_back(i);

   try
   {
	 tab[100];
   }
   catch(std::invalid_argument e) 
   {
	   e.what();
   }

   copy(tab.begin(), tab.end(), ostream_iterator<TL_TabDyn<int>::value_type>(cout, " "));

   cout << endl;

   END_TEST()