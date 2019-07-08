#pragma once
#include "stdafx.h"
using std::copy;



template <class T, class Cap>
struct TGC_Croisseur // hum...
{
    typedef T value_type;
    typedef value_type * pointer;
    typedef typename pointer & ptrref_t;
    typedef Cap size_type;
};


template <class T, class Cap>
struct TGC_CroisseurType
    : TGC_Croisseur<T, Cap>
{
    void croitre(ptrref_t tab, size_type &cap)
    {
        const float RATIO_CROISSANCE = 1.5f;
        const size_type nouv_cap =
        static_cast<size_type>(cap * RATIO_CROISSANCE);
        value_type *p = new value_type[nouv_cap];
        try
        {
        std::copy(tab, tab+cap, p);
        delete [] tab;
        tab = p;
        cap = nouv_cap;
        }
        catch(...)
        {
        delete [] p;
        throw;
        }
    }
};

#include <stdexcept>

template <class T, class Croiss = TGC_CroisseurType<T,int> >
class TGC_TabDyn
{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef Croiss strategie_croiss_type;
    typedef typename
        strategie_croiss_type::size_type size_type;
private:
    enum { CAPACITE_DEFAUT = 10 };
    size_type nelems_;
    pointer elems_;
    size_type capacite_;
    strategie_croiss_type croisseur_;
    void croitre()
        { croisseur_.croitre(elems_, capacite_); }
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
    iterator end() throw()
        { return begin() + size(); }
    const_iterator end() const throw()
        { return begin() + size(); }
    //
    // Constructeurs
    //
    TGC_TabDyn()
        : nelems_(0), capacite_(CAPACITE_DEFAUT),
        elems_(new value_type[CAPACITE_DEFAUT]), croisseur_()
    {
    }
    TGC_TabDyn(const TGC_TabDyn &t)
        : nelems_(t.size()), capacite_(t.capacity()),
        elems_(new value_type[tcapacity()]), croisseur_()
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
    ~TGC_TabDyn() throw()
        { delete [] elems_; }
    bool full() const throw()
        { return size() == capacity(); }
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


BEGIN_TEST(TableGenericCollaborative)
   using std::cout;
   using std::endl;
   using std::copy;
   using std::ostream_iterator;
   const int NB_ELEMS = 30;
   TGC_TabDyn<int> tab;
   for (int i = 0; i < NB_ELEMS; ++i)
      tab.push_back(i);
   copy(tab.begin(), tab.end(),
       ostream_iterator<TGC_TabDyn<int>::value_type>(cout, " "));
   cout << endl;

   END_TEST()