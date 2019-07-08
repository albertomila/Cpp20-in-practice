#pragma once
#include "stdafx.h"
#include <stdexcept>
using std::copy;

template <class T, class Cap>
   struct TI_Croisseur // hum...
   {
      typedef T value_type;
      typedef value_type * pointer;
      typedef typename pointer & ptrref_t;
      typedef Cap size_type;
   };

template <class T, class Cap>
   struct TI_CroisseurType
      : TI_Croisseur <T, Cap>
   {
      void croitre(ptrref_t tab, size_type &cap)
      {
         const float RATIO_CROISSANCE = 1.5f;
         const size_type nouv_cap = static_cast<size_type>(cap * RATIO_CROISSANCE);
         pointer p = new value_type[nouv_cap];
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

template <class T, class Croiss = TI_CroisseurType<T,int> >
   class TI_TabDyn
      : Croiss // privé!
   {
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
      void croitre()
         { Croiss::croitre(elems_, capacite_); }
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
      TI_TabDyn()
         : Croiss(), nelems_(0), capacite_(CAPACITE_DEFAUT), elems_(new value_type[CAPACITE_DEFAUT])
      {
      }
      TI_TabDyn(const TI_TabDyn &t)
         : Croiss(t), nelems_(t.size()), capacite_(t.capacity()),
           elems_(new value_type[t.capacity()])
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
      ~TI_TabDyn() throw()
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


BEGIN_TEST(TableInjection)
   using std::cout;
   using std::endl;
   using std::copy;
   using std::ostream_iterator;
   const int NB_ELEMS = 30;
   TI_TabDyn<int> tab;
   for (int i = 0; i < NB_ELEMS; ++i)
      tab.push_back(i);
   copy(tab.begin(), tab.end(),
        ostream_iterator<TI_TabDyn<int>::value_type>(cout, " "));
   cout << endl;

   END_TEST()