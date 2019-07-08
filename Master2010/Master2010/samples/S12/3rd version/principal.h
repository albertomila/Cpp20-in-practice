#pragma once
#include "stdafx.h"
#include <functional>
#include <cmath>
#include "compose3_fx_gx.h"
using std::for_each;
using std::cout;
using std::endl;
using std::sqrt;

using std::unary_function;

template <class T>
   class cumuler
      : public std::unary_function<T,void>
   {
   public:
      typedef T value_type;
   private:
      value_type val_;
   public:
      cumuler(value_type init = value_type())
         : val_(init)
      {
      }
      value_type valeur() const
         { return val_; }
      result_type operator()(argument_type val)
         { val_+= val; }
   };


  
template <class T>
   struct racine_carree
      : std::unary_function<T, T>
   {
      result_type operator() (argument_type arg)
         { return sqrt(arg); }
   };


template <class T>
   struct negate
      : std::unary_function<T, T>
   {
      result_type operator()(argument_type arg)
         { return -arg; }
   };

template <class T>
   struct compter
      : std::unary_function<T, T>
   {
   private:
      int cpt_;
   public:
      compter ()
         : cpt_(0)
      {
      }
      int valeur() const
         { return cpt_; }
      result_type operator()(argument_type arg)
         { ++cpt_; return arg; }
   };


   
struct bidon
{
   int valeur ()
      { return 3; }
};

BEGIN_TEST(Composite)
   int vals[] = { 1, 4, 9, 16, 25 };
   const int NB_ELEMS = sizeof(vals)/sizeof(*vals);
   
   cout << for_each (vals, vals + NB_ELEMS,
                     compose3_fx_gx
                        (cumuler<double>(), compose3_fx_gx
                           (compter<double>(), racine_carree<double>()))).to_<
                                cumuler<double>
						   >().valeur() << endl;

   END_TEST()
   
   /*
   cout << for_each (vals, vals + NB_ELEMS,
                     compose3_fx_gx
                        (cumuler<double>(), compose3_fx_gx
                           (compter<double>(), racine_carree<double>()))).to_<
                                compter<double>
                            >().valeur() << endl;
		*/				
//
// L'EXEMPLE CI_DESSOUS NE COMPILE PAS (TANT MIEUX!)
//
   /*
   cout << for_each (vals, vals + NB_ELEMS,
                     compose3_fx_gx
                        (cumuler<double>(), compose3_fx_gx
                           (compter<double>(), racine_carree<double>()))).to_<
                                bidon
                            >().valeur() << endl;
*/