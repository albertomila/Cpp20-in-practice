#pragma once
#include "stdafx.h"
using std::cout;
using std::endl;

namespace relation
{
   //
   // equivalence <T> définit une relation d'équivalence
   // pour T si T::operator< (const T&) const existe.
   //
   template <class T>
      class equivalence
      {
      public:
         friend bool operator>(const T &a, const T &b)
            { return b < a; }
         friend bool operator<=(const T &a, const T &b)
            { return !(b < a); }
         friend bool operator>=(const T &a, const T &b)
            { return !(a < b); }
      };
}

class nombre
   : relation::equivalence<nombre>
{
   int valeur_;
public:
   nombre(const int n = 0) throw()
      : valeur_(n)
   {
   }
   //
   // La sainte-trinité (constructeurde copie,
   // affectation, destructeur) est Ok telle
   // quelle; on ne les réécrit pas.
   //
   int valeur() const throw()
      { return valeur_; }
   friend bool operator<(const nombre &n0, const nombre &n1) throw()
      { return n0.valeur() < n1.valeur(); }
};
#include <iosfwd>
using std::ostream;
// implémentation évidente; je vous laisse la faire
ostream& operator<<(ostream & cout, const nombre & nom)
{
	return cout << nom.valeur();
}


BEGIN_TEST(BartonNackman)
   nombre n0(4), n1(4);
   if (n0 <  n1)
      cout << n0 << "< " << n1 << endl;
   if (n0 <= n1)
      cout << n0 << "<=" << n1 << endl;
   if (n0 >  n1)
      cout << n0 << "> " << n1 << endl;
   if (n0 >= n1)
      cout << n0 << ">=" << n1 << endl;

   END_TEST()