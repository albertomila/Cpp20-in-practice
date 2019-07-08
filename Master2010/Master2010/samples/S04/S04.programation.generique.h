#pragma once
#include "stdafx.h"

template <class T>
class Tableau
{
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
private:
	T* elems_;
	size_type	capacite_,
				nbelems_;
public:
	Tableau() throw()
		: capacite_(0), nbelems_(0), elems_(0)
	{
	}
	~Tableau() throw()
	{ 
		delete[] elems_; 
	}
	size_type capaciy() const throw()
	{ 
		return capacite_; 
	}
	size_type size() const throw()
	{ 
		return nbelems_; 
	}
	bool empty() const throw()
	{ 
		return !size(); 
	}
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
		return elems_ + size(); 
	}
	const_iterator end() const throw()
	{ 
		return elems_ + size(); 
	}
	Tableau (const Tableau &tab)
		: capacite_(tab.capacity()), nbelems_(tab.size()), elems_(0)
	{
		if (empty()) return;
		elems_ = new value_type[capacity()];
		try
		{
			std::copy(tab.begin(), tab.end(), begin());
		}
		catch(...)
		{
			delete [] elems_;
			throw;
		}
	}

	template <class U>
	Tableau (const Tableau<U> &tab)
		: capacite_(tab.capacity()), nbelems_(tab.size()), elems_(0)
	{
		if (empty()) return;
		elems_ = new value_type[capacity()];
		try
		{
			std::copy(tab.begin(), tab.end(), begin());
		}
		catch(...)
		{
			delete [] elems_;
			throw;
		}
	}

	template <class Itt>
	Tableau(const Itt debut, const Itt fin)
		: capacite_(std::distance(debut, fin)), nbelems_(0), elems_(0)
	{
		nbelems_ = capacity()
			if (empty()) return;
		elems_ = new value_type[capacity()];
		try
		{
			std::copy(debut, fin, begin());
		}
		catch(...)
		{
			delete [] elems_;
			throw;
		}
	}

	void swap(Tableau &tab) throw()
	{
		std::swap(nbelems_, tab.nbelems_);
		std::swap(capacite_, tab.capacite_);
		std::swap(elems_, tab.elems_);
	}

	Tableau& operator=(const Tableau &tab)
	{
		Tableau(tab).swap(*this);
		return *this;
	}
	template <class U>
	Tableau& operator=(const Tableau<U> &tab)
	{
		Tableau(tab).swap(*this);
		return *this;
	}

	class HorsBornes {};
	value_type& operator[](const size_type n) // throw(HorsBornes)
	{
		if (n >= size()) throw HorsBornes();
		return elems_[n];
	}
	value_type operator[](const size_type n) const // throw(HorsBornes)
	{
		if (n >= size()) throw HorsBornes();
		return elems_[n];
	}

	bool operator==(const Tableau &tab) const
	{
		if (size() != tab.size())
			return false;
		for (const_iterator ittA = begin(), ittB = tab.begin(); ittA != end(); ++ittA, ++ittB)
			if (*ittA != *ittB) return false;
		return true;
	}

	bool operator!= (const Tableau &tab) const
	{ 
		return !(*this == tab); 
	}

	Tableau& operator+=(const value_type &val)
	{
		push_back(val);
		return *this;
	}
	void push_back (const T &val)
	{
		if (full()) croitre();
		elems_[nbelems_] = val;
		++nbelems_;
	}

private:
	bool full() const throw()
	{ 
		return size() == capacity(); 
	}
	void croitre() // coûteux
	{
		static const size_type TAILLE_BASE = 128; // arbitraire
		static const float FACTEUR_CROISSANCE = 1.5f; // arbitraire
		const size_type new_cap = capacity()?
										static_cast<size_t>(capacity() * FACTEUR_CROISSANCE) :
										TAILLE_BASE;
		value_type *p = new value_type[new_cap];
		try
		{
			std::copy (begin(), end(), temp);
			delete [] elems_;
			elems_ = temp;
			capacity_ = new_cap;
		}
		catch(...)
		{
			delete [] p;
			throw;
		}
	}
};

template <class T>
std::ostream& operator << (std::ostream &os, const Tableau<T> &tab)
{
	std::copy(tab.begin(), tab.end(),
		std::ostream_iterator<T>(os, " "));
	return os;
}
namespace std
{
	template <class T>
	void swap (Tableau<T> &a, Tableau<T> &b)
	{ 
		a.swap(b); 
	}
}