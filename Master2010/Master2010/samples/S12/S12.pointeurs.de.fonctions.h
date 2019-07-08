#pragma once
#include "stdafx.h"
using std::cout;
using std::endl;
using std::basic_ostream;
#include <iterator>
using std::ostream_iterator;
using std::iterator_traits;
using std::basic_string;

#include <functional>
using std::unary_function;
using std::binary_function;



/*
template <class A0, class A1, class R>
   class binary_function_wrapper  : public binary_function<A0, A1,R>
   {
      result_type (*p_)(first_argument_type, second_argument_type);
   public:
      binary_function_wrapper(result_type (*p)(first_argument_type, second_argument_type))
         : p_(p)
      {
      }
      result_type operator()(first_argument_type a0, second_argument_type a1) const
      { 
		  return p_(a0, a1); 
	  }
   };

template <class A0, class A1, class R>
   binary_function_wrapper<A0, A1, R> pointeur_fonction(R (*p)(A0,A1))
   { 
	  return binary_function_wrapper<A0,A1,R>(p); 
   }



   
template <class A, class R>
   class unary_function_wrapper : public unary_function<A,R>
   {
      result_type (*p_)(argument_type);
   public:
      unary_function_wrapper(result_type (*p)(argument_type))
         : p_(p)
      {
      }
      result_type operator()(argument_type arg) const
      { 
			 return p_(arg); 
	  }
   };

template <class A, class R>
   unary_function_wrapper<A,R> pointeur_fonction(R (*p)(A))
   { 
	   return unary_function_wrapper<A,R>(p); 
   }


int arrondir(double d)
{ 
	   return static_cast<int>(d > 0? d + 0.5 : d - 0.5); 
}
int sum(double d1,double d2)
{ 
	   return static_cast<int>(d1); 
}

template <class Itt, class C>
   void afficher_sequence(Itt debut, Itt fin, basic_ostream<C> &os,
                          const basic_string<C> &msg = basic_string<C>(),
                          const basic_string<C> &sep = basic_string<C>())
   {
      using std::copy;
      os << msg;
      copy (debut, fin, ostream_iterator<
                           typename iterator_traits<Itt>::value_type
                        >(os, sep.c_str()));
      os << endl;
   }
template <class Itt, class C>
   void afficher_sequence(Itt debut, Itt fin, basic_ostream<C> &os, const C *msg)
   {
      afficher_sequence(debut, fin, os, basic_string<C>(msg));
   }
template <class Itt, class C>
   void afficher_sequence(Itt debut, Itt fin, basic_ostream<C> &os, const C *msg, const C *sep)
   {
      afficher_sequence(debut, fin, os, basic_string<C>(msg), basic_string<C>(sep));
   }


int main()
{
   using std::transform;
   double vals[] = { 1.3, -2.4, 3.5, -4.6 };
   double* vals1;
   enum { N = sizeof(vals) / sizeof(vals[0]) };
   int res[N];
   transform(vals, vals + N, res, pointeur_fonction(arrondir));
  // copy(vals, vals + N, res, pointeur_fonction(sum));
   afficher_sequence(vals, vals + N, cout, "Valeurs originales : ", " ");
   afficher_sequence(res, res + N,   cout, "Valeurs arrondies :  ", " ");
}
*/

template <class R, class T>
   class method_wrapper : public std::unary_function<T*, R>
   {
      result_type (T::*p_)() const;
   public:
      method_wrapper(result_type (T::*p)() const)
         : p_(p)
      {
      }
      result_type operator()(argument_type p) const
      { 
		  return (p->*p_)(); 
	  }
   };


template <class R, class T>
method_wrapper<R, T> pointeur_methode(R (T::*p)() const)
{ 
	return method_wrapper<R, T>(p); 
}

#include <ostream>
class X
{
	std::ostream &os_;
	int val_;
public:
	X (std::ostream &os, int val)
      : os_(os), val_(val)
	{
	}
	void afficher() const
	{ 
		  os_ << "X de valeur " << val_ << std::endl; 
	}
};

BEGIN_TEST(FunctionPointer)
   using std::for_each;
   using std::cout;
   X x0(cout, 3),
     x1(cout, 4);

   X *x[] =
   {
      &x0, &x1
   };

   enum { N = sizeof(x) / sizeof(x[0]) };

   for_each(x, x + N, pointeur_methode(&X::afficher));

   END_TEST()