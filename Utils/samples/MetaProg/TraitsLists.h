#include "TraitsUtils.h"

class Dummy;
class DB_End;

template <class T, int N, const char* NAME, class Arg>
   struct DB_Cols
   {
      typedef T				type_class;
      typedef const int		type_position;
      typedef const size_t	type_size;
	  typedef const char*	type_name;
	  typedef Arg			type_argument;

	  enum{ POS = N };
   };

   template<class T, class V>
   struct DB_Row
   {
		typedef	T			first_;
		typedef	V			second_;
   };

   char DummyChar[] = "HELLO";

   typedef
		  DB_Row< DB_Cols< Dummy, 0, DummyChar, Dummy>
		, DB_Row< DB_Cols< Dummy, 1, DummyChar, Dummy>
		, DB_Row< DB_Cols< Dummy, 2, DummyChar, Dummy>
		, DB_Row< DB_Cols< Dummy, 3, DummyChar, Dummy>
		, DB_End
		>>>>
	DataBase;

   
template <class TList, unsigned int i>
   struct DB_GetByPos
   {
      typedef TList type;
   };
   
template <class T, class Q>
   struct DB_GetByPos<DB_Row<T,Q>,0>
   {
      typedef T type;
   };
   
template <class T, class Q, unsigned int i>
   struct DB_GetByPos<DB_Row<T,Q>,i>
   {
      typedef typename
          DB_GetByPos<Q,i-1>::type type;
   };
   
//////////////////////////////////////////LISTE DE TYPES
class Vide {};
	

template <int N>
   struct int_
   {
      enum { VAL = N };
   }; 

template <class T, class U>
   struct type_list
   {
      typedef T Tete;
      typedef U Queue;
   };

typedef type_list <
   char, type_list <
      unsigned char, type_list <
         signed char, type_list <
            wchar_t, Vide
         >
      >
   >
> types_caracteres;

typedef type_list <
   short, type_list <
      unsigned short, type_list <
         int, type_list <
            unsigned int, type_list <
               long, type_list <
                  unsigned long, Vide
               >
            >
         >
      >
   >
> types_entiers_numeriques;

typedef type_list <
   float, type_list <
      double, type_list <
         long double, Vide
      >
   >
> types_virgule_flottante;
//////////////////////////////////////////SIZE DE LE LISTE DE TYPES
template <class>
struct static_length
{
    enum { VAL = 0 };
};

template <>
struct static_length<Vide>
{
    enum { VAL = 0 };
};

template <class T, class Q>
struct static_length< type_list<T, Q> >
{
    enum { VAL = 1 + static_length<Q>::VAL };
};

///////////////////////////////////////////GET TYPE BY INDEX

template <class TList, unsigned int i>
   struct type_par_indice
   {
      typedef TList type;
   };
template <class T, class Q>
   struct type_par_indice<type_list<T,Q>,0>
   {
      typedef T type;
   };

template <class T, class Q, unsigned int i>
   struct type_par_indice<type_list<T,Q>,i>
   {
      typedef typename
          type_par_indice<Q,i-1>::type type;
   };
   
///////////////////////////////////////////GET INDEX BY TYPE
template <class TList, class T>
   struct indice_par_type
   {
      enum { VAL = -1 };
   };

template <class T>
   struct indice_par_type<Vide, T>
   {
      enum { VAL = -1 };
   };

template <class T, class Q>
   struct indice_par_type<type_list<T, Q>, T>
   {
      enum { VAL = 0 };
   };

template <class T, class Q, class U>
   struct indice_par_type <type_list<T, Q>, U>
   {
   private: // constante privée, une sorte de temporaire
      enum
      {
         pos_dans_queue = indice_par_type<Q, U>::VAL
      };
   public: // l'indice en tant que tel
      enum
      {
         VAL = pos_dans_queue == -1 ? -1 : 1 + pos_dans_queue
      };
   };
///////////////////////////////////////////IS PRIMITIVE

template <class T>
	struct est_primitif
	{
		static const bool VAL = indice_par_type<types_primitifs, T>::VAL != -1;
	};

/////////////////////////////////////////// INSERT TYPE INTO LIST

template <class TList, class T>
   struct static_insert
   {
      typedef Vide type;
   };

template <>
   struct static_insert <Vide, Vide>
   {
      typedef Vide type;
   };

template <class T>
   struct static_insert <Vide, T>
   {
      typedef type_list<T, Vide> type;
   };

template <class T, class Q>
   struct static_insert <Vide, type_list<T, Q> >
   {
      typedef type_list<T, Q> type;
   };

template <class T, class Q, class U>
   struct static_insert<type_list<T, Q>,U>
   {
      typedef type_list <
         T, typename static_insert<Q, U>::type
      > type;
   };

/////////////////////////////////////////// REMOVE TYPE FROM LIST

template <class TList, class T>
   struct static_remove;

template <class T>
   struct static_remove<Vide, T>
   {
      typedef Vide type;
   };

template <class T, class Q>
   struct static_remove<type_list<T, Q>, T>
   {
     typedef Q type;
   };

template <class T, class Q, class U>
   struct static_remove<type_list<T, Q>, U>
   {
      typedef type_list<
         T, typename static_remove<Q, U>::type
      > type;
   };

/////////////////////////////////////////// SIGNE OF TYPE CHAR
typedef 
   static_if_else <
      (static_cast<char>(-1)<0),
      char,
      Vide
   >::type char_signe;

typedef 
   static_if_else <
      (static_cast<char>(-1)>=0),
      char,
      Vide
   >::type char_non_signe;

typedef type_list <
   signed char, type_list <
      short , type_list <
         int, type_list <
            long, type_list <
               char_signe, Vide
            >
         >
      >
   >
> types_entiers_signes;


/////////////////////////////////////////// CONCATENATE 2 LISTS

typedef
   static_insert <
      types_entiers_signes, types_virgule_flottante
   >::type types_signes;
/////////////////////////////////////////// FINAL PRIMITIVE TYPE LIST

typedef
	static_insert <
      types_entiers_numeriques, static_insert <
            types_virgule_flottante, void
         >::type
   >::type types_primitifs;
   

///////////////////////////////////////////EXAMPLE
/*
template <class T>
   struct type_traits
   {
      static const bool est_const =				::est_const<T>::VAL;
      static const bool est_volatile =			::est_volatile<T>::VAL;
      static const bool est_reference =			::est_reference<T>::VAL;
      static const bool est_primitif =			::est_primitif<T>::VAL;
      static const bool est_entier =			::est_entier<T>::VAL;
      static const bool est_virgule_flottante = ::est_virgule_flottante<T>::VAL;
      static const bool est_signe =				::est_signe<T>::VAL;
      static const bool est_non_signe =			::est_non_signe<T>::VAL;
	  
	private:
      template <class U>
         struct traits_pointeur
         {
            static const bool VAL = false;
            typedef Vide type_pointe;
         };
      template <class U>
         struct traits_pointeur<U*>
         {
            static const bool VAL = true;
            typedef U type_pointe;
         };
      template <class U>
         struct traits_pointeur_methodes
         {
            static const bool VAL = false;
         };
      template <class U, class V>
         struct traits_pointeur_methodes<U V::*>
         {
            static const bool VAL = true;
         };
		 
	public:
      static const bool est_pointeur =			traits_pointeur<T>::VAL;
      static const bool est_pointeur_methode =  traits_pointeur_methodes<T>::VAL;
	  
      typedef typename supprimer_const<T>::type type_sans_const;
      typedef typename supprimer_reference<T>::type type_sans_reference;
	  
      typedef typename traits_pointeur<T>::type_pointe type_pointe;
      typedef typename
         static_if_else <
            est_pointeur || est_pointeur_methode || est_primitif,
            T,
            typename
               static_if_else <
                  !est_reference,
                  const type_sans_reference &,
                  type_sans_reference &
               >::type
         >::type meilleur_type_parametre;
  };
*/