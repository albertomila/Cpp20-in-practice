#pragma once
#include "stdafx.h"

struct null_wrapper // un Null Object (politique par défaut)
{
   std::ostream& operator()(std::ostream &os) const
      { return os; }
};

struct open_paren // exemple cool pour un préfixe
{
   std::ostream& operator()(std::ostream &os) const
      { return os << '('; }
};

struct close_paren // exemple cool pour un suffixe
{
   std::ostream& operator()(std::ostream &os) const
      { return os << ')'; }
};

class tabify // autre exemple pour un préfixe
{
   char c_;
public:
   tabify(const char c = '-')
      : c_(c)
   {
   }
   std::ostream& operator()(std::ostream &os) const
      { return os << "[" << c_ << "]"; }
};

//
// Exemple de classe par politiques
//
template <class T, class PRE = null_wrapper, class POST = null_wrapper>
   class print_wrapper
   {
      PRE pre_;
      POST post_;
      T val_;
   public:
      //
      // C'est une bonne idée de permettre au code client de passer
      // ses propres politiques à la construction, s'il le souhaite
      // (il est possible que les politiques aient des constructeurs
      // paramètriques auxquels il pourrait vouloir avoir recours).
      //
      print_wrapper(const T &val, PRE pre = PRE(), POST post = POST())
         : val_(val), pre_(pre), post_(post)
      {
      }
      //
      // Application des politiques
      //
      friend std::ostream& operator<< (std::ostream &os, const print_wrapper &pw)
      {
         pw.pre_(os);
         os << pw.val_;
         pw.post_(os);
         return os;
      }
   };

#include <algorithm>
#include <iostream>
#include <iterator>

BEGIN_TEST(Policies)
   using std::cout;
   using std::endl;
   using std::copy;
   using std::ostream_iterator;
   
   //
   // Application des politiques par défaut: « enrobage vide »
   //
   print_wrapper<int> pw0(3);
   cout << pw0 << endl; // affiche 3
   //
   // Application de politiques au choix du code client
   //
   print_wrapper<int, open_paren, close_paren> pw1(3);
   cout << pw1 << endl; // affiche (3)
   //
   // Application d'une combinaison de politiques, au choix du code client
   //
   
   print_wrapper<print_wrapper<int, open_paren, close_paren>, tabify> pw2(3);
   cout << pw2 << endl;
   
   int tab[] = { 2, 3, 5, 7, 11 };
   enum { N = sizeof(tab)/sizeof(*tab) };
   //
   // Affiche les éléments de tab, une par ligne, précédés
   // de '-' et d'une tabulation
   //
   copy(tab, tab + N, ostream_iterator<print_wrapper<int, tabify> >(cout));
   cout << endl;
   //
   // Affiche les éléments de tab, entourés de parenthèses et séparés
   // l'un de l'autre par un espace
   //
   copy(tab, tab + N, ostream_iterator<print_wrapper<int, open_paren, close_paren> >(cout, " "));
   cout << endl;

   END_TEST()