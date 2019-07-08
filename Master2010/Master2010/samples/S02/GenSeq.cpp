#include "stdafx.h"
#include "GenSeq.h"

class GenerateurFullGenial
    : public IGenSeq
{
    value_type cur_;
public:
    GenerateurFullGenial(const value_type &init = value_type())
       : cur_(init)
    {
    }
    value_type prochain()
    { 
		return cur_++; 
	}
};

IGenSeq *GenSeq::Creer()
{ 
	return new GenerateurFullGenial; 
}
void GenSeq::Liberer(const IGenSeq *p) throw()
{ 
		delete p; 
}