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
   // Allocation d'un size_t suppl�mentaire � chaque new (tr�s
   // co�teux, mais simple). Le pointeur retourn� est sur l'espace
   // attribu� pour les donn�es; la taille attribu�e se trouve
   // juste avant les donn�es en m�moire. Le size_t suppl�mentaire
   // n'est pas comptabilis� par la m�canique de d�tection des
   // fuites puisqu'il s'agit d'un d�tail d'impl�mentation.
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
   // Allocation d'un size_t suppl�mentaire � chaque new[] (tr�s
   // co�teux, mais simple). Le pointeur retourn� est sur l'espace
   // attribu� pour les donn�es; la taille attribu�e se trouve
   // juste avant les donn�es en m�moire. Le size_t suppl�mentaire
   // n'est pas comptabilis� par la m�canique de d�tection des
   // fuites puisqu'il s'agit d'un d�tail d'impl�mentation.
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
   std::cerr << "Lib�ration abusive de " << combien() << " bytes" << std::endl;
}


ComptableMemoire2::TraceurLocalSimplet::~TraceurLocalSimplet() throw()
{
   const value_type diff =
      ComptableMemoire2::get().combien() - avant_;
   if (diff) // hum...
      std::cerr << "Fuite locale de " << diff << " bytes" << std::endl;
}