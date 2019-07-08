#pragma once
#include "stdafx.h"
#include "Singleton.h"

//
// Ceci est un exemple pour démontrer la technique
//
class Service
   : Singleton<Service> // magie!
{
   // sans ceci, le parent ne peut instancier son enfant
   friend class Singleton <Service>;
   Service()
      : cur_(0)
   {
      // bla bla
   }
   ~Service() throw()
   {
      // bla bla
   }
   int cur_;
public:
   // vos services vont ici
   int prochain() throw()
      { return ++cur_; }
};

BEGIN_TEST(SingletonTest)
   using std::cout;
   for (int i = 0; i < 10; ++i)
      cout << Singleton<Service>::get().prochain() << ' ';

   END_TEST()
