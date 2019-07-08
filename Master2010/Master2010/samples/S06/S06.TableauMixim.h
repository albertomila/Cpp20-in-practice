#pragma once
#include "stdafx.h"
#include <stdexcept>
using std::copy;

template <class T>
class AxiomeTabDyn
{
	// données brutes et services de base
public:
	typedef T value_type;
	typedef int size_type;
	typedef value_type& reference;
	typedef const T& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
private:
	enum { CAPACITE_DEFAUT = 10 };
	size_type nelems_;
	pointer elems_;
	size_type capacite_;
protected:
	void croitreBase(const size_type nouv_cap)
	{
		pointer p = new value_type[nouv_cap];
		try
		{
			std::copy(begin(), end(), p);
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
	virtual void croitre() = 0;
	void AjouterALaFin(const_reference val)
	{
		elems_[size()] = val;
		++nelems_;
	}
public:
	size_type size() const throw()
	{ return nelems_; }
	size_type capacity() const throw()
	{ return capacite_; }
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	iterator begin() throw()
	{ return elems_; }
	const_iterator begin() const throw()
	{ return elems_; }
	iterator end() throw ()
	{ return begin() + size(); }
	const_iterator end() const throw()
	{ return begin() + size(); }
	AxiomeTabDyn()
		: nelems_(0), capacite_(CAPACITE_DEFAUT), elems_(new value_type[CAPACITE_DEFAUT])
	{
	}
	AxiomeTabDyn(const AxiomeTabDyn &t)
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
	virtual ~AxiomeTabDyn() throw()
	{ delete [] elems_; }
	bool full() const throw()
	{ return size() == capacity(); }
	value_type element(const size_type n) const
	{
		if (static_cast<unsigned int>(n) >= size())
			throw std::invalid_argument("Indice illégal");
		return elems_[n];
	}
	reference element(const size_type n)
	{
		if (static_cast<unsigned int>(n) >= size())
			throw std::invalid_argument("Indice illégal");
		return elems_[n];
	}
};

template <class T>
class ModeleCroissanceType
	: public virtual AxiomeTabDyn<T>
{
protected:
	void croitre()
	{
		//
		// Politique: ratio de croissance 1.5 de la capacité
		//
		const float RATIO_CROISSANCE = 1.5f;
		const size_type nouv_cap = static_cast<size_type>(capacity() * RATIO_CROISSANCE);
		croitreBase(nouv_cap);
	}
};

template <class T>
class ITabDyn // interface à utiliser
	: public virtual AxiomeTabDyn<T>
{
	// implémentation des algorithmes à utiliser
public:
	virtual ~ITabDyn() throw(){ }
	virtual ITabDyn *cloner() const = 0;
	void push_back(const_reference val)
	{
		if (full())
		{
			croitre();
		}
		AjouterALaFin(val);
	}
};

//
// Idéalement anonyme, mais bon
//
template <class T>
class MixinTabDyn
	: public ITabDyn<T>, public ModeleCroissanceType<T>
{
public:
	MixinTabDyn()
		: AxiomeTabDyn<T>(), ITabDyn<T>(), ModeleCroissanceType<T>()
	{
	}
protected:
	MixinTabDyn(const MixinTabDyn &m)
		: AxiomeTabDyn<T>(m), ITabDyn<T>(m), ModeleCroissanceType<T>(m)
	{
	}
	MixinTabDyn *cloner() const
	{ return new MixinTabDyn(*this); }
};

template <class T>
ITabDyn <T> *CreerTableauType()
{
	return new MixinTabDyn<T>;
}

template <class T>
class TableauDynamique
{
	ITabDyn<T> *dyn_impl_;
public:
	typedef typename ITabDyn<T>::value_type value_type;
	typedef typename ITabDyn <T>::size_type size_type;


	size_type size() const throw()
	{ return dyn_impl_->size(); }
	size_type capacity() const throw()
	{ return dyn_impl_->capacity (); }
	typedef typename ITabDyn<T>::iterator iterator;
	typedef typename ITabDyn<T>::const_iterator const_iterator;
	iterator begin() throw()
	{ return dyn_impl_->begin(); }
	const_iterator begin() const throw()
	{ return dyn_impl_->begin(); }
	iterator end() throw()
	{ return dyn_impl_->end(); }
	const_iterator end() const throw()
	{ return dyn_impl_->end(); }
	//
	// Constructeurs
	//
	TableauDynamique()
		: dyn_impl_(CreerTableauType<T>())
	{
	}
	TableauDynamique(const TableauDynamique &t)
		: dyn_impl_(t.dyn_impl_->cloner())
	{
	}
	~TableauDynamique() throw()
	{ delete dyn_impl_; }
	bool full() const throw()
	{ return dyn_impl_->full(); }
	
	void push_back(value_type val)
	{ dyn_impl_->push_back(val); }
	
	value_type operator[](const size_type n) const
	{ return dyn_impl_->element(n); }
	/*
	reference operator[](const size_type n)
	{ return dyn_impl_->element(n); }*/
};


#include <iostream>
#include <algorithm>
#include <iterator>

BEGIN_TEST(TableMinimum)
	using std::cout;
	using std::endl;
	using std::copy;
	using std::ostream_iterator;
	TableauDynamique<int> tab;
	const int NB_ELEMS = 30;
	for (int i = 0; i < NB_ELEMS; ++i)
		tab.push_back(i);
	copy(tab.begin(), tab.end(),
		ostream_iterator<TableauDynamique<int>::value_type>(cout, " "));
	cout << endl;

	END_TEST()