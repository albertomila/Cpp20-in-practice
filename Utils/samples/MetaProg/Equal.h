//#include "StdAfx.h"
template <class T>
class equivalence
{
public:
    friend bool operator > (const T &a, const T &b)
    { 
		return b < a; 
	}
    friend bool operator <= (const T &a, const T &b)
    { 
		return !(b < a); 
	}
    friend bool operator >= (const T &a, const T &b)
    { 
		return !(a < b); 
	}
};