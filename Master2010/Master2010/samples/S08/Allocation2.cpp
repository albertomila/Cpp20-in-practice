#include "StdAfx.h"
#include "Allocation2.h"
#include <iostream>
#include <cstdlib>
#include <new>
using std::bad_alloc;
using std::cerr;
using std::endl;
using std::free;
using std::malloc;
using std::size_t;
/*
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
   ComptableMemoire2::get().allocation(n);
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
   ComptableMemoire2::get().allocation(n);
   *(reinterpret_cast<size_t *>(p)) = n;
   return reinterpret_cast<size_t *>(p) + 1;
}

void operator delete(void *p)
{
   if (!p) return;
   size_t *q = (reinterpret_cast<size_t *>(p) - 1);
   ComptableMemoire2::get().deallocation(*q);
   free(q);
}

void operator delete[](void *p)
{
   if (!p) return;
   size_t *q = (reinterpret_cast<size_t *>(p) - 1);
   ComptableMemoire2::get().deallocation(*q);
   free(q);
}
*/
ComptableMemoire2 ComptableMemoire2::singleton;

void ComptableMemoire2::fuite() throw()
{
   std::cerr << "Fuite de " << combien() << " bytes" << std::endl;
}

void ComptableMemoire2::surliberation ()
{
   std::cerr << "Libération abusive de " << combien() << " bytes" << std::endl;
}


ComptableMemoire2::TraceurLocalSimplet::~TraceurLocalSimplet() throw()
{
   const value_type diff =
      ComptableMemoire2::get().combien() - avant_;
   if (diff) // hum...
      std::cerr << "Fuite locale de " << diff << " bytes" << std::endl;
}