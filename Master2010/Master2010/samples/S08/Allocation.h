#pragma once
#include "stdafx.h"
#include "samples/S02/Incopiable.h"
//
// Allocation et libération dynamique de mémoire. Surcharge
// des opérateurs globaux par une version comptabilisant ce
// qui est alloué et facilitant le traçage des fuites.
//
void* operator new(size_t);
void* operator new[](size_t);
void operator delete(void*);
void operator delete[](void*);

class ComptableMemoire : Incopiable
{
public:
   typedef long value_type;
private:
   static ComptableMemoire singleton;
   value_type alloue_;
   ComptableMemoire()
      : alloue_(0)
   {
   }
   void fuite() throw();
   void surliberation() throw();
public:
   void allocation(const size_t n)
   { 
	   alloue_ += static_cast<value_type>(n); 
   }
   void deallocation(const size_t n)
   {
      alloue_ -= static_cast<value_type>(n);
      if (combien() < 0) surliberation();
   }
   value_type combien() const throw()
   { 
	   return alloue_; 
   }
   static ComptableMemoire &get() throw()
   { 
	   return singleton; 
   }
   ~ComptableMemoire() throw()
   { 
	   if (combien()) fuite(); 
   }


   class TraceurLocalSimplet
   {
      value_type avant_;
   public:
      TraceurLocalSimplet ()
         : avant_(ComptableMemoire::get().combien())
      {
      }
      ~TraceurLocalSimplet() throw();
   };
};

class Test
{
public:
	int num1;
	float num2;
	double num3;
	long num4;
	char* value1[10];
	Test()
	{
	}
	void* operator new(size_t n);
	void operator delete(void* p);
};

BEGIN_TEST(Allocation)
	Test* cp = new Test();
	delete cp;
   {
      ComptableMemoire::TraceurLocalSimplet tr;
      int *temp = new int[5];
      int *temp2 = new int(4);
      delete[] temp;
   }
   int *p = new int(3);
   int *q = new int[10];
   delete p;

   END_TEST()