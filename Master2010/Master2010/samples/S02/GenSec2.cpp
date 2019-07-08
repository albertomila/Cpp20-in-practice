#include "stdafx.h"
#include "GenSec2.h"

class GenSeq2::Impl
{
public:
    typedef GenSeq2::value_type value_type;
private:
    value_type cur_;
public:
    Impl(const value_type &init = value_type())
       : cur_(init)
    {
    }
    value_type prochain()
    { 
		return cur_++; 
	}
};

GenSeq2::Impl *GenSeq2::Creer()
{ 
	return new GenSeq2::Impl; 
}
void GenSeq2::Liberer(const Impl *p)
{ 
	delete p; 
}
GenSeq2::value_type GenSeq2::prochain()
{ 
	return p_->prochain(); 
}