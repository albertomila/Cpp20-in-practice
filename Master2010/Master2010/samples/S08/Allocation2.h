#pragma once
#include "stdafx.h"
#include "samples/S02/Incopiable.h"
#include <cassert>
#include <iostream>
using std::cout;
using std::endl;
/*
void* operator new(size_t);
void* operator new[](size_t);
void operator delete(void*);
void operator delete[](void*);
*/
class ComptableMemoire2
	: Incopiable
{
public:
	typedef long value_type;
	struct Rappelable
	{
		virtual void sur_allocation(const size_t){ }
		virtual void sur_deallocation(const size_t){ }
		virtual ~Rappelable() throw(){ }
	};

private:
	std::vector<Rappelable *> abonnes_;
	static ComptableMemoire2 singleton;
	value_type alloue_;
	ComptableMemoire2()
	{
		alloue_ = 0;
		abonnes_.clear();
	}
	void fuite();
	void surliberation();


	class RappelerAllocation
	{
		const size_t qte_;
	public:
		RappelerAllocation(const size_t qte) throw()
			: qte_(qte)
		{
		}
		void operator()(Rappelable *p)
		{ 
			p->sur_allocation(qte_); 
		}
	};


	class RappelerDeallocation
	{
		const size_t qte_;
	public:
		RappelerDeallocation(const size_t qte) throw()
			: qte_(qte)
		{
		}
		void operator()(Rappelable *p)
		{ 
			p->sur_deallocation(qte_); 
		}
	};

public:
	void abonner(Rappelable *p)
	{
		assert(p);
		abonnes_.push_back(p);
	}
	void desabonner(Rappelable *p)
	{
		assert(p);
		abonnes_.erase
			(std::find(abonnes_.begin(), abonnes_.end(), p));
		std::vector<Rappelable *>(abonnes_).swap(abonnes_);
	}

	void allocation(const size_t n)
	{
		alloue_ += static_cast<value_type>(n);
		std::for_each(abonnes_.begin(), abonnes_.end(), RappelerAllocation(n));
	}
	void deallocation(const size_t n)
	{
		std::for_each(abonnes_.begin(), abonnes_.end(),
			RappelerDeallocation(n));
		alloue_ -= static_cast<value_type>(n);
		if (combien() < 0) surliberation();
	}
	value_type combien() const throw()
	{ 
		return alloue_; 
	}
	static ComptableMemoire2 &get() throw()
	{ 
		return singleton; 
	}
	~ComptableMemoire2() throw()
	{ 
		if (combien()) fuite(); 
	}



	class TraceurLocalSimplet
	{
		value_type avant_;
	public:
		TraceurLocalSimplet() throw()
			: avant_(ComptableMemoire2::get().combien())
		{
		}
		~TraceurLocalSimplet() throw();
	};
};

class SignalGrosseAllocation
	: public ComptableMemoire2::Rappelable
{
	const size_t seuil_;
	size_t tolerance() const throw()
	{ 
		return seuil_; 
	}
public:
	SignalGrosseAllocation(const size_t seuil)
		: seuil_(seuil)
	{
	}
	void sur_allocation(const size_t n)
	{
		if (n > tolerance())
			std::cout << "Allocation suspecte de "
			<< n << " bytes (tolérance: "
			<< tolerance ()
			<< " bytes)." << std::endl;
	}
};



BEGIN_TEST(Allocation2)
	SignalGrosseAllocation sga(100);
	ComptableMemoire2::get().abonner(&sga);
	{
		ComptableMemoire2::TraceurLocalSimplet tr;
		int *temp = new int [5];
		int *temp2 = new int (4);
		delete  temp2;
	}
	int *p = new int (3);
	int *q = new int [50];
	delete p;
	ComptableMemoire2::get().desabonner(&sga);

	END_TEST()

