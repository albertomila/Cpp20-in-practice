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
   // Allocation d'un size_t supplémentaire à chaque new (très
   // coûteux, mais simple). Le pointeur retourné est sur l'espace
   // attribué pour les données; la taille attribuée se trouve
   // juste avant les données en mémoire. Le size_t supplémentaire
   // n'est pas comptabilisé par la mécanique de détection des
   // fuites puisqu'il s'agit d'un détail d'implémentation.
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
   // Allocation d'un size_t supplémentaire à chaque new[] (très
   // coûteux, mais simple). Le pointeur retourné est sur l'espace
   // attribué pour les données; la taille attribuée se trouve
   // juste avant les données en mémoire. Le size_t supplémentaire
   // n'est pas comptabilisé par la mécanique de détection des
   // fuites puisqu'il s'agit d'un détail d'implémentation.
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
   std::cerr << "Libération abusive de " << combien() << " bytes" << std::endl;
}


ComptableMemoire::TraceurLocalSimplet::~TraceurLocalSimplet() throw()
{
   const value_type diff =
      ComptableMemoire::get().combien() - avant_;
   if (diff) // hum...
      std::cerr << "Fuite locale de " << diff << " bytes" << std::endl;
}