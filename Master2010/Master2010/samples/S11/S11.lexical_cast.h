#pragma once
#include "stdafx.h"
#include "samples/S11/S11.metaprogramation.h"

using std::basic_string;
using std::string;
#include <sstream>
using std::basic_stringstream;
using std::stringstream;

class T_IMPLICITE   {};
class T_TEXTE_DEST  {};
class T_TEXTE_TEXTE {};
class T_GENERAL     {};


template <class T>
struct est_texte
{
	enum { VAL = false };
};
template <class C>
struct est_texte<basic_string<C>>
{
	enum { VAL = true };
};

template <class D, class S>
struct traits_conversion
{
	typedef typename static_if_else< meme_type<D,S>::VAL || est_convertible<S, D>::VAL,
						T_IMPLICITE,
						typename static_if_else< est_texte<D>::VAL,
									typename static_if_else< est_texte<S>::VAL,
												T_TEXTE_TEXTE,
												T_TEXTE_DEST
											>::type,
									T_GENERAL
								>::type
						>::type type;
};


template <class D, class S>
D lexical_cast(const S &src, T_GENERAL)
{
	stringstream sstr;
	sstr << src;
	D dest;
	sstr >> dest;
	return dest;
}
template <class D, class S>
D lexical_cast(const S &src, T_TEXTE_DEST)
{
	typedef typename D::value_type value_type;
	basic_stringstream<value_type> sstr;
	sstr << src;
	return sstr.str();
}
template <class D, class S>
D lexical_cast(const S &src, T_TEXTE_TEXTE)
{ 
	return D(src.begin(), src.end()); 
}
template <class D, class S>
D lexical_cast(const S &src, T_IMPLICITE)
{ 
	return src; 
}

#include <iostream>
using std::cout;
using std::endl;

//template <class T, class U>
//   void diag ()
//   {
//      cout << typeid(T).name () << " <-- \n\t" << typeid(U).name () << endl;
//      cout << "\tMeme type? " << meme_type<T,U>::VAL << endl;
//      cout << "\t" << typeid(traits_conversion<T, U>::type()).name() << endl;
//   }
template <class S, class D>
class LC_Test
{/*
	typedef int type_1;
	typedef float type_2;
	typedef char type_3;*/
	struct type_1 { char _[1]; } ;
	struct type_2 { char _[2]; } ;
	struct type_3 { char _[3]; } ;
	
	static type_1 test(S s);
	static type_2 test(D d);
	static type_3 test(...);
	static S createS;
	static D createD;


public:
	enum { VAL = sizeof(test(createS))==sizeof(type_1) };
	enum { VAL2 = sizeof(test(createS))== sizeof(test(createD)) };	
	LC_Test()
	{
		string type2 = typeid(createS).name();
		string type22 = typeid(test(createS)).name();
		
		string type3 = typeid(createD).name();
		string type33 = typeid(test(createD)).name();
		
		string var_;
		string type4 = typeid(test(var_)).name();

		int x = 0;
		x = 0;
	}																								
};
template <class D, class S>
D lexical_cast(const S &src)
{
	//LC_Test<int,float>* c = new LC_Test<int,float>();

	size_t t8 = est_convertible<int, std::string>::VAL1;
	size_t t16 = est_convertible<int, std::string>::VAL2;

	bool b1 = est_convertible<int, int>::VAL;
	bool b2 = est_convertible<int, char>::VAL;
	bool b3 = est_convertible<int, std::string>::VAL;

	traits_conversion<D,S>::type ty = traits_conversion<D,S>::type();
	string s1 = typeid(D).name();
	string s2 = typeid(S).name();
	string s3 = typeid(ty).name();

	return lexical_cast<D, S>(src, ty);
}

#include <iostream>
using std::istream;
using std::ostream;

class LC_X {};
istream& operator>>(istream &is, LC_X&)
{ 
	return is; 
}
ostream& operator<<(ostream &os, const LC_X&)
{ 
	return os; 
}

struct LC_Y
{
	LC_Y()
	{ }
	LC_Y(const LC_X &)
	{}
};
istream& operator>>(istream & is, LC_Y&)
{ 
	return is; 
}
ostream& operator<<(ostream &os, const LC_Y&)
{ 
	return os; 
}
#include <stdio.h>
#include <stdarg.h>

BEGIN_TEST(LexicalCast)
	using std::wstring;
	string s = "3";
	int i = lexical_cast<int>(s); // sérialisation par flux
	s = lexical_cast<string>(i);  // sérialisation par flux, texte en sortie
	s = lexical_cast<string>(s);  // T_IMPLICITE
	wstring ws = lexical_cast<wstring>(s); // texte à texte
	LC_X x;
	LC_Y y;
	y = lexical_cast<LC_Y>(x); // T_IMPLICITE
	x = lexical_cast<LC_X>(y); // via flux

	END_TEST()