#pragma once
#include "stdafx.h"
#include "compose2_fx_gx.h"
#include <functional>
using std::unary_function;
using std::cout;
using std::endl;
using std::for_each;


template <class T>
   class CF2_cumuler
      : public std::unary_function<T,void>
   {
   public:
      typedef T value_type;
   private:
      value_type &cumul_;
   public:
      CF2_cumuler(value_type init = value_type())
         : cumul_(init)
      {
      }
      result_type operator()(argument_type val)
         { cumul_ += val; }
      value_type valeur() const
         { return cumul_; }
   };

template <class T>
T carre(const T &val)
{ 
	return val * val; 
}

BEGIN_TEST(CompositionFunctions2)
   int vals[] =
   {
      1, 2, 3, 4, 5
   };
   const int NB_VALS = sizeof(vals)/sizeof(*vals);
	compose2_fx_gx_impl<CF2_cumuler<int>, int(*)(const int&)> cumul= for_each ( 
							   vals, 
							   vals + NB_VALS, 
							   compose2_fx_gx(CF2_cumuler<int>(),carre<int>)
						   );

	CF2_cumuler<int> c = cumul.to_<CF2_cumuler<int>>();
	
	cout << c.valeur();
	/*
	
	cout <<					for_each ( 
							   vals, 
							   vals + NB_VALS, 
							   compose2_fx_gx(CF2_cumuler<int>(),carre<int>)
							   ).to_<CF2_cumuler<int>>().valeur();
	
	*/

	END_TEST()