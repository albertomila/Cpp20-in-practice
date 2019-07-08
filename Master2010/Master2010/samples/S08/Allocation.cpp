#include "StdAfx.h"
#include "Allocation.h"
#include <iostream>
#include <cstdlib>
#include <new>
using std::bad_alloc;
using std::cerr;
using std::endl;
using std::free;
using std::malloc;
using std::size_t;

void * operator new(size_t n)
{
   //
   // Allocation d'un size_t suppl�mentaire � chaque new (tr�s
   // co�teux, mais simple). Le pointeur retourn� est sur l'espace
   // attribu� pour les donn�es; la taille attribu�e se trouve
   // juste avant les donn�es en m�moire. Le size_t suppl�mentaire
   // n'est pas comptabilis� par la m�canique de d�tection des
   // fuites puisqu'il s'agit d'un d�tail d'impl�mentation.
   //
   void *p = malloc(n + sizeof(size_t));
   if (!p) throw std::bad_alloc();
   ComptableMemoire::get().allocation(n);
   *(reinterpret_cast<size_t *>(p)) = n;
   return reinterpret_cast<size_t *>(p) + 1;
}

void *operator new[](size_t n)
{
   //
   // Allocation d'un size_t suppl�mentaire � chaque new[] (tr�s
   // co�teux, mais simple). Le pointeur retourn� est sur l'espace
   // attribu� pour les donn�es; la taille attribu�e se trouve
   // juste avant les donn�es en m�moire. Le size_t suppl�mentaire
   // n'est pas comptabilis� par la m�canique de d�tection des
   // fuites puisqu'il s'agit d'un d�tail d'impl�mentation.
   //
   void *p = malloc(n + sizeof(size_t));
   if (!p) throw std::bad_alloc();
   ComptableMemoire::get().allocation(n);
   *(reinterpret_cast<size_t *>(p)) = n;
   return reinterpret_cast<size_t *>(p) + 1;
}

void operator delete(void *p)
{
   if (!p) return;
   size_t *q = (reinterpret_cast<size_t *>(p) - 1);
   ComptableMemoire::get().deallocation(*q);
   free(q);
}

void operator delete[](void *p)
{
   if (!p) return;
   size_t *q = (reinterpret_cast<size_t *>(p) - 1);
   ComptableMemoire::get().deallocation(*q);
   free(q);
}

ComptableMemoire ComptableMemoire::singleton;

void* Test::operator new(size_t n)
{
	void* memory = malloc(n + sizeof(size_t));
	if(!memory) throw bad_alloc();

	*(reinterpret_cast<size_t*>(memory)) = n;
	void* ret = reinterpret_cast<size_t*>(memory) + 1;
	return ret;
}
void  Test::operator delete(void* p)
{
	if(!p) return;
	size_t* n = reinterpret_cast<size_t*>(p) - 1;
	free(n);
}
void ComptableMemoire::fuite() throw()
{
   std::cerr << "Fuite de " << combien() << " bytes" << std::endl;
}

void ComptableMemoire::surliberation ()
{
   std::cerr << "Lib�ration abusive de " << combien() << " bytes" << std::endl;
}


ComptableMemoire::TraceurLocalSimplet::~TraceurLocalSimplet() throw()
{
   const value_type diff =
      ComptableMemoire::get().combien() - avant_;
   if (diff) // hum...
      std::cerr << "Fuite locale de " << diff << " bytes" << std::endl;
}