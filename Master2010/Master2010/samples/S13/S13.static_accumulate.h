#pragma once
#include "stdafx.h"
#include "samples/S11/S11.metaprogramation.h"


template <int N>
   struct int_
   {
      enum { VAL = N };
   }; 

////////////////////////////////////////////////////////////
template <class>
   struct static_somme;

template <class T, class Q>
   struct static_somme<type_list<T,Q> >
   {
      enum { VAL = T::VAL + static_somme<Q>::VAL };
   };

template <>
   struct static_somme<Vide>
   {
      enum { VAL = 0 };
   }; 

   
////////////////////////////////////////////////////////////
template <template <class, class> class>
   struct init_value_traits;

template <class, template <class, class> class>
   struct static_accumulate;

template <class T, class Q, template <class, class> class F>
   struct static_accumulate<type_list<T, Q>, F>
   {
      typedef typename F<T, typename static_accumulate<Q, F>::type>::type type;
      enum { VAL = type::VAL };
   };

template <template <class, class> class F>
   struct static_accumulate<Vide, F>
   {
      typedef typename init_value_traits<F>::type type;
      enum { VAL = type::VAL };
   }; 

   
////////////////////////////////////////////////////////////

template <class V, class CUMUL>
   struct somme_statique
   {
      typedef int_<V::VAL + CUMUL::VAL> type;
      enum { VAL = type::VAL };
   };
template <class V, class CUMUL>
   struct produit_statique
   {
      typedef int_<V::VAL * CUMUL::VAL> type;
      enum { VAL = type::VAL };
   };
   
////////////////////////////////////////////////////////////
template <>
   struct init_value_traits<somme_statique>
   {
      typedef int_<0> type;
      enum { VAL = type::VAL };
   };
template <>
   struct init_value_traits<produit_statique>
   {
      typedef int_<1> type;
      enum { VAL = type::VAL };
   };
   
////////////////////////////////////////////////////////////
#include <iostream>

   BEGIN_TEST(StaticAccumulate)
   using std::cout;
   using std::endl;
   typedef type_list<
      int_<2>, type_list<
         int_<3>, type_list<
            int_<5>, type_list<
               int_<7>, type_list<
                  int_<11>, Vide
               >
            >
         >
      >
   > vals;
   cout << static_somme<vals>::VAL << endl;
   cout << static_accumulate<vals, somme_statique>::VAL << endl;
   cout << static_accumulate<vals, produit_statique>::VAL << endl;

   END_TEST()