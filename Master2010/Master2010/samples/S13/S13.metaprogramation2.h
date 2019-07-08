#pragma once
#include "stdafx.h"
#include "samples/S11/S11.metaprogramation.h"

   
#include <typeinfo>
template <class T>
   struct traits_noms
   {
      static const char* nom()
      { 
		  return typeid(T).name(); 
	  }
   };

#include <ostream>
using std::ostream;
using std::endl;

template <class T, class U>
   void message_de_comparaison_v0(ostream &os)
   {
      if (meme_type<T, U>::VAL)
         os << traits_noms<T>::nom() << " est le même type que "		<< traits_noms<U>::nom() << endl;
      else
         os << traits_noms<T>::nom() << " n'est pas le même type que "	<< traits_noms<U>::nom() << endl;
   }

////////////////////////////////////////////////////////////////////////
template <class T, template <class, class> class Pred>
   struct static_bind1st
   {
      template <class U>
         struct eval
         {
            enum { VAL = Pred<T, U>::VAL };
         };
   };
template <class T, class P>
   void message_de_comparaison_v1(ostream &os)
   {
      if (P::eval<T>::VAL)
         os << traits_noms<T>::nom() << " : pareil" << endl;
      else
         os << traits_noms<T>::nom() << " : pas pareil" << endl;
   }

////////////////////////////////////////////////////////////////////////
   
template <class TList, class T>
   struct est_dans_v0;
template <class T, class Q>
   struct est_dans_v0<type_list<T, Q>, T>
   {
      enum { VAL = true };
   };
template <class T, class Q, class U>
   struct est_dans_v0<type_list<T, Q>, U>
   {
      enum { VAL = est_dans_v0<Q, U>::VAL };
   };
template <class T>
   struct est_dans_v0<Vide, T>
   {
      enum { VAL = false };
   };


template <class TList, class Pred>
   struct static_find_if;
template <class T, class Q, class Pred>
   struct static_find_if<type_list<T, Q>, Pred>
   {
      enum { VAL = Pred::eval<T>::VAL || static_find_if<Q, Pred>::VAL };
   };
template <class Pred>
   struct static_find_if<Vide, Pred>
   {
      enum { VAL = false };
   };

template <class TList, class T>
   struct est_dans_v1
   {
      enum { VAL = static_find_if<TList, static_bind1st<T, meme_type> >::VAL };
   };


template <class TList, class T>
   void message_de_recherche_v0(ostream &os)
   {
      if (est_dans_v0<TList, T>::VAL)
         os << traits_noms<T>::nom() << " est dans la liste" << endl;
      else
         os << traits_noms<T>::nom() << " n'est pas dans la liste" << endl;
   }
template <class TList, class T>
   void message_de_recherche_v1(ostream &os)
   {
      if (est_dans_v1<TList, T>::VAL)
         os << traits_noms<T>::nom() << " est dans la liste" << endl;
      else
         os << traits_noms<T>::nom() << " n'est pas dans la liste" << endl;
   }


///////////////////////////////////////////////////////////////////////////

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

BEGIN_TEST(Metaprogramming2)
   message_de_comparaison_v0<char, char>(cout);
   message_de_comparaison_v0<char, signed char>(cout);
   message_de_comparaison_v0<char, unsigned char>(cout);
   typedef static_bind1st<char, meme_type> static_predicate_type;
   message_de_comparaison_v1<char, static_predicate_type>(cout);
   message_de_comparaison_v1<signed char, static_predicate_type>(cout);
   message_de_comparaison_v1<unsigned char, static_predicate_type>(cout);
   typedef type_list<
      char, type_list<
         signed char, type_list<
            unsigned char, Vide
         >
      >
   > types_caracteres_1_byte;
   message_de_recherche_v0<types_caracteres_1_byte, char>(cout);
   message_de_recherche_v0<types_caracteres_1_byte, signed char>(cout);
   message_de_recherche_v0<types_caracteres_1_byte, unsigned char>(cout);
   message_de_recherche_v0<types_caracteres_1_byte, wchar_t>(cout);
   message_de_recherche_v1<types_caracteres_1_byte, char>(cout);
   message_de_recherche_v1<types_caracteres_1_byte, signed char>(cout);
   message_de_recherche_v1<types_caracteres_1_byte, unsigned char>(cout);
   message_de_recherche_v1<types_caracteres_1_byte, wchar_t>(cout);

   END_TEST()