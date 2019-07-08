#pragma once
#include "stdafx.h"
#include "samples/S11/S11.metaprogramation.h"
//
// La passe à laquelle j'avais pensé, plus une twist inspirée
// de BOOST_STATIC_ASSERT... que c'est brillant (celle avec le
// enum et le sizeof())!
//
template <class Raison>
   class Incompilable
   {
      static static_assert_<false> bloquer_la_compilation ();
      enum { bidon = sizeof (bloquer_la_compilation ()) };
   };

struct Compilable {};

//
// La raison du problème, s'il yu en a un : factorielle<N>::valeur
// sera illégal si N est négatif
//
class ValeurNegative {};

//
// factorielle<N> est compilable ssi N est positif
//
template <int N>
   struct factorielle
      : static_if_else<
           (N<0),
           Incompilable<ValeurNegative>,
           Compilable
        >::type
   {
      static const int VALEUR = N * factorielle<N-1>::VALEUR;
   };
template<>
   struct factorielle<0>
   {
      static const int VALEUR = 1;
   };

#include <iostream>
using std::cout;
using std::endl;

BEGIN_TEST(IncompilableTest)
   cout << factorielle<5>::VALEUR << endl;
   // ce qui suit ne compile pas si on enlève les commentaires. Essayez-le!
   //cout << factorielle<-3>::VALEUR << endl;

END_TEST()