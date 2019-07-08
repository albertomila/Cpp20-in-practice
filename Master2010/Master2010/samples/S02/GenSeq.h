#pragma once
#include "stdafx.h"
#include "Incopiable.h"

struct IGenSeq
{
    typedef int value_type;
    virtual value_type prochain() = 0;
protected:
    virtual ~IGenSeq() throw()
    { 
	}
    friend class GenSeq;
};

class GenSeq
    : Incopiable
{
    IGenSeq *p_;
    static IGenSeq *Creer();
    static void Liberer(const IGenSeq *) throw();
public:
    GenSeq()
       : p_(Creer())
    {
    }
    ~GenSeq() throw()
    { 
		   Liberer(p_); 
	}
    typedef IGenSeq::value_type value_type;
    value_type prochain()
    { 
		return p_->prochain(); 
	}
};

BEGIN_TEST(GenSeqTest)
	GenSeq* genSeq2 = new GenSeq();
	int x = genSeq2->prochain();
END_TEST()