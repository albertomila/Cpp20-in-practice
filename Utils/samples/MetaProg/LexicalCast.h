#include <string>
#include "TraitsUtils.h"
using std::basic_string;
using std::string;
#include <sstream>
using std::basic_stringstream;
using std::stringstream;

class T_IMPLICITE   {};
class T_TEXTE_DEST  {};
class T_TEXTE_TEXTE {};
class T_GENERAL     {};

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

template <class D, class S>
D lexical_cast(const S &src)
{
	traits_conversion<D,S>::type ty = traits_conversion<D,S>::type();
	return lexical_cast<D, S>(src, ty);
}



/*

template <class D, class S, class T>
struct LexicalCast
{
static D Get(const S &src)
{
stringstream sstr;
sstr << src;
D dest;
sstr >> dest;
return dest;
}
};

template <class D, class S>
struct LexicalCast<D,S,T_TEXTE_DEST>
{
static D Get(const S &src )
{
typedef typename D::value_type value_type;
basic_stringstream<value_type> sstr;
sstr << src;
return sstr.str();
}
};

template <class D, class S>
struct LexicalCast<D,S,T_TEXTE_TEXTE>
{
static D Get(const S &src )
{ 
return D(src.begin(), src.end()); 
}
};

template <class D, class S>
struct LexicalCast<D,S,T_IMPLICITE>
{
static D Get(const S &src)
{ 
return src; 
}
};


template <class D, class S>
D lexical_cast(const S &src)
{
//traits_conversion<D,S>::type ty = traits_conversion<D,S>::type();
return LexicalCast<D, S,traits_conversion<D,S>::type>::Get(src);


*/