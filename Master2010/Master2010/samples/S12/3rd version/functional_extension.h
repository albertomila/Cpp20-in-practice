#pragma once
#include "stdafx.h"
#include <functional>
#include "samples/S11/S11.metaprogramation.h"
using std::unary_function;

template <class R>
   struct nullary_function : std::unary_function<R, void>
   {
   };

template <class T>
   struct nullary_function_traits
   {
      typedef typename T::result_type result_type;
   };

template <class R>
   struct nullary_function_traits<R(*)()>
   {
      typedef R result_type;
   };

template <class T>
   struct unary_function_traits
   {
      typedef typename T::argument_type argument_type;
      typedef typename T::result_type	result_type;
   };

template<class R, class A>
   struct unary_function_traits<R(*)(A)>
   {
      typedef A argument_type;
      typedef R result_type;
   };
