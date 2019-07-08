#include <string>
#include <cassert>
#include <iostream>
using namespace std;
////////////////////////////////////////UNUSE VARIABLE
template <class T>
void unused(const T &)
{ 
}
   
////////////////////////////////////////STATIC ASSERT
 template <bool>
struct static_assert_;

template <>
struct static_assert_<true>
{
};


////////////////////////////////////////dimensions of an array
template < typename T >
struct calc_dim
{
    static const unsigned int value = 0;
};

template < typename T, unsigned int N >
struct calc_dim< T[N] >
{
    static const unsigned int value = calc_dim< T >::value + 1;
};

///////////////////////////////////////STATIC IF ELSE

template <bool Condition,  class SiVrai, class SiFaux>
struct static_if_else;

template <class SiVrai, class SiFaux>
struct static_if_else <true, SiVrai, SiFaux>
{
    typedef SiVrai type;
};
template <class SiVrai, class SiFaux>
struct static_if_else <false, SiVrai, SiFaux>
{
    typedef SiFaux type;
};

////////////////////////////////////////////////////////
template <class S, class D>
class est_convertible
{
	typedef int oui_type;
	typedef long long non_type;

	static oui_type test(D);
	static non_type test(...);
	static S createurBidon();

public:
	enum { VAL = sizeof(test(createurBidon()))==sizeof(oui_type) };																												
};




////////////////////////////////////////////////////////

template <class T>
struct est_texte
{
	enum { VAL = false };
};

template <class T>
struct est_texte<basic_string<T>>
{
	enum { VAL = true };
};




////////////////////////////////////////////////////////
template <class T, class U>
struct meme_type
{
	enum { VAL = false };
};
template <class T>
struct meme_type<T,T>
{
	enum { VAL = true };
};



/////////////////////////////////////////EST CONST

template <class T>
struct est_const
{
	static const bool VAL = false;
};

template <class T>
struct est_const<const T>
{
	static const bool VAL = true;
};

template <class T>
struct est_const<const T*>
{
	static const bool VAL = true;
};

template <class T>
struct est_const<const T&>
{
	static const bool VAL = true;
};


//////////////////////////////////////////SUPRIMER CONST

template <class T>
struct supprimer_const
{
    typedef T type;
};

template <class T>
struct supprimer_const<const T>
{
    typedef T type;
};

//////////////////////////////////////////SUPRIMER REF

template <class T>
struct supprimer_reference
{
    typedef T type;
};

template <class T>
struct supprimer_reference<T&>
{
    typedef T type;
};


///////////////////////////////////////INCOMPILABLE
template <class Raison>
   class Incompilable
   {
      static static_assert_<false> bloquer_la_compilation();
      enum { bidon = sizeof(bloquer_la_compilation ()) };
   };

class Compilable{};
class ValeurNegative{};


///////////////////////////////////////FACTORIELLE
template <int N>
   struct factorielle
      : static_if_else<
           (N<0),
           Incompilable<ValeurNegative>,
           Compilable
        >::type
   {
      static const int VAL = N * factorielle<N-1>::VAL;
   };
template<>
   struct factorielle<0>
   {
      static const int VAL = 1;
   };

   
////////////////////////////////////////ABS
template <int T>
struct ABS
{
	enum { VAL = T > 0 ? T : -T};
};

////////////////////////////////////////NUMBER OF DIGITS
template <int T>
struct NumberOfDigits
{
	struct NumberOfDigitsZero { enum { VAL = 0 }; };
	enum { VAL = 1+ static_if_else<	ABS<T>::VAL < 10,
									NumberOfDigitsZero,
									NumberOfDigits<T / 10>
								>::type::VAL	
		};
};

template<>
struct NumberOfDigits<0>
{
	enum { VAL = 1 };
};


/////////////////////////////////////POW

template<int BASE, int N>
struct POW
{
	enum { VAL = BASE * POW<BASE,N-1>::VAL };
};

template<int BASE>
struct POW<BASE,0>
{
	enum { VAL = 1 };
};

template <int N, int D>
struct float_
{
	enum { NUM = N, DEC = D };
	static const float VAL()
	{
		return NUM / static_cast<float>(POW<10,DEC>::VAL);
	}
};


//////////////////////////////////////////ADD CONST

template <class T>
struct add_const
{
    typedef const T type;
};