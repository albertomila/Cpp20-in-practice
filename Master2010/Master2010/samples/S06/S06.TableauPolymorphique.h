#pragma once
#include "stdafx.h"
using std::copy;
#include <algorithm>
#include <stdexcept>

template <class T>
   class TP_TabDyn
   {
   public:
      typedef T value_type;
      typedef int size_type;
      typedef value_type& reference;
      typedef const value_type& const_reference;
      typedef value_type* pointer;
      typedef const value_type* const_pointer;
   private:
      enum { CAPACITE_DEFAUT = 10 };
      size_type nelems_;
   protected:
      pointer elems_;
      size_type capacite_;
      virtual void croitre() = 0;
   public:
      size_type size() const throw()
         { return nelems_; }
      size_type capacity() const throw()
         { return capacite_; }
      typedef value_type* iterator;
      typedef const value_type* const_iterator;
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
      TP_TabDyn()
         : nelems_(0), capacite_(CAPACITE_DEFAUT), elems_(new value_type[CAPACITE_DEFAUT])
      {
      }
      TP_TabDyn(const TP_TabDyn &t)
         : nelems_(t.size()), capacite_(t.capacity()), elems_(0)
      {
         elems_ = new value_type[capacity()];
         try
         {
            std::copy(t.begin(), t.end(), begin());
         }
         catch(...)
         {
            delete [] elems_;
            throw;
         }
      }
      virtual ~TP_TabDyn() throw()
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

template <class T>
struct TP_TabDynCool : TP_TabDyn<T>
{
    void croitre()
    {
        //
        // Politique: ratio de croissance 1.5 de la capacité (arbitraire)
        //
        const float RATIO_CROISSANCE = 1.5f;
        const size_type nouv_cap = static_cast<size_type>(capacity() * RATIO_CROISSANCE);
        value_type *p = new value_type[nouv_cap];

        try
        {
			std::copy(begin(), end(), p);
			delete[] elems_;
			elems_ = p;
			capacite_ = nouv_cap;
        }
        catch(...)
        {
            delete [] p;
            throw;
        }
    }
};


#include <iostream>
#include <algorithm>
#include <iterator>

//
// Modifs: on utilise TP_TabDynCool<T> plutôt que TP_TabDyn<T>
//

BEGIN_TEST(TablePolimorphic)
   using std::cout;
   using std::endl;
   using std::copy;
   using std::ostream_iterator;
   const int NB_ELEMS = 30;
   TP_TabDynCool<int> tab;

   for (int i = 0; i < NB_ELEMS; ++i)
      tab.push_back(i);

   copy(tab.begin(), tab.end(), ostream_iterator<TP_TabDynCool<int>::value_type>(cout, " "));
   cout << endl;

   END_TEST()