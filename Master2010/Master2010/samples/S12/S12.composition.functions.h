#pragma once
#include "stdafx.h"
#include "compose_fx_gx.h"
#include <functional>
using std::unary_function;
class afficher
   : public std::unary_function<int,void>
{
   std::ostream &os_;
public:
   afficher(std::ostream &os)
      : os_(os)
   {
   }
   result_type operator()(argument_type arg)
   { 
	   os_ << arg << ' '; 
   }
};


template <class T>
   class CF_cumuler
      : public std::unary_function<T,void>
   {
   public:
      typedef T value_type;
   private:
      value_type &cumul_;
   public:
      CF_cumuler(value_type &init)
         : cumul_(init)
      {
      }
      result_type operator()(argument_type val)
         { cumul_ += val; }
   };

template <class T>
T CF_carre(const T &val)
{ 
	return val * val; 
}

BEGIN_TEST(CompositionFunctions)
   using std::cout;
   using std::endl;
   using std::for_each;

   int vals[] =
   {
      1, 2, 3, 4, 5
   };
   enum { N = sizeof(vals)/sizeof(*vals) };
   int cumul = 0;
   /*
   compose_fx_gx_impl< CF_cumuler<int>, int(*)(const int&)> f_g_(CF_cumuler<int>(cumul),carre<int>);
   for (int i = 0; i < N; ++i)
      f_g_(vals[i]);
   */

  // compose_fx_gx_impl<afficher, int(*)(const int&)> f_g_(afficher(cout),carre<int>);
   for_each(vals, vals + N, compose_fx_gx(afficher(cout), CF_carre<int>));

   cout << cumul;

   END_TEST()