#pragma once
#include "stdafx.h"
using std::cout;
using std::endl;

///////////////////////////////////////////////// BAD SOLUTION
/*
class PetiteUsine
{
   void monter ()
      { cout << "Je monte!" << endl; }
   void descendre ()
      { cout << "Je descend!" << endl; }
   void boucaner ()
      { cout << "Je boucane!" << endl; }
   void vibrer ()
      { cout << "Je vibre!" << endl; }
public:
   enum Code
   {
      MONTER = 0x00, DESCENDRE = 0x01, BOUCANER = 0x02, VIBRER = 0x03
   };
   void agir (const Code c)
   {
      switch (c)
      {
      case MONTER:
         monter();
         break;
      case DESCENDRE:
         descendre();
         break;
      case BOUCANER:
         boucaner();
         break;
      case VIBRER:
         vibrer();
         break;
      default: // exception?
         ;
      }
   }
};
//
// Petit test tout simple
//
int main ()
{
   PetiteUsine miniU;
   miniU.agir (PetiteUsine::BOUCANER);
}

*/



///////////////////////////////////////////////// SOLUTION 0 polymorphisme et objets d'action
/*
#include <algorithm>
using std::for_each;

struct meurs
{
   template <class T>
      void operator()(T p) throw()
      { 
		  delete p; 
	  }
};
class PetiteUsine
{
   struct Acteur
   {
      virtual void agir () = 0;
      virtual ~Acteur () throw()
         { }
   };
   struct Monteur : Acteur
   {
      void agir ()
         { cout << "Je monte!" << endl; }
   };
   struct Descendeur : Acteur
   {
      void agir ()
         { cout << "Je descend!" << endl; }
   };
   struct Boucaneur : Acteur
   {
      void agir ()
         { cout << "Je boucane!" << endl; }
   };
   struct Vibreur : Acteur
   {
      void agir ()
         { cout << "Je vibre!" << endl; }
   };
public:
   enum Code
   {
      MONTER = 0x00, DESCENDRE = 0x01, BOUCANER = 0x02, VIBRER = 0x03,
      NB_CODES // sentinelle
   };
private:
   Acteur *acteurs_[NB_CODES];
public:
   PetiteUsine() // prudence: pas exception-safe
   {
      acteurs_[MONTER]		= new Monteur;
      acteurs_[DESCENDRE]	= new Descendeur;
      acteurs_[BOUCANER]	= new Boucaneur;
      acteurs_[VIBRER]		= new Vibreur;
   }
   ~PetiteUsine() throw()
   { 
		for_each (acteurs_, acteurs_ + NB_CODES, meurs()); 
   }
   void agir (const Code c)
   {
      // Valider que c >= 0 && c < NB_CODES au besoin
      acteurs_[c]->agir();
   }
};
int main ()
{
   PetiteUsine miniU;
   miniU.agir (PetiteUsine::BOUCANER);
}
*/

///////////////////////////////////////////////// SOLUTION 1 polymorphisme et objets d'action indirects
/*
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::for_each;


struct meurs
{
   template <class T>
      void operator()(T p) throw()
      { 
		  delete p; 
	  }
};
class PetiteUsine
{
   void monter ()
   { 
	   cout << "Je monte!" << endl; 
   }
   void descendre ()
   { 
	   cout << "Je descend!" << endl; 
   }
   void boucaner ()
   { 
	   cout << "Je boucane!" << endl; 
   }
   void vibrer ()
   { 
	   cout << "Je vibre!" << endl; 
   }


   class Acteur
   {
      PetiteUsine *p_;
   public:
      Acteur (PetiteUsine *p) throw()
         : p_ (p)
      {
      }
      PetiteUsine *petite_usine() throw()
      { 
		  return p_; 
	  }
      virtual void agir() = 0;
      virtual ~Acteur() throw()
      { 
	  }
   };



   struct Monteur : Acteur
   {
      Monteur(PetiteUsine *p) throw()
         : Acteur(p)
      {
      }
      void agir ()
      { 
		  petite_usine()->monter(); 
	  }
   };


   struct Descendeur : Acteur
   {
      Descendeur(PetiteUsine *p) throw()
         : Acteur(p)
      {
      }
      void agir()
      { 
		  petite_usine()->descendre(); 
	  }
   };


   struct Boucaneur : Acteur
   {
      Boucaneur (PetiteUsine *p) throw()
         : Acteur (p)
      {
      }
      void agir ()
      { 
		  petite_usine()->boucaner(); 
	  }
   };


   struct Vibreur : Acteur
   {
      Vibreur(PetiteUsine *p) throw()
         : Acteur (p)
      {
      }
      void agir ()
      { 
		  petite_usine()->vibrer(); 
	  }
   };
public:
   enum Code
   {
      MONTER = 0x00, DESCENDRE = 0x01, BOUCANER = 0x02, VIBRER = 0x03,
      NB_CODES // sentinelle
   };
private:
   Acteur *acteurs_[NB_CODES];
public:
   PetiteUsine() // prudence: pas exception-safe
   {
      acteurs_[MONTER] = new Monteur(this);
      acteurs_[DESCENDRE] = new Descendeur(this);
      acteurs_[BOUCANER] = new Boucaneur(this);
      acteurs_[VIBRER] = new Vibreur(this);
   }
   ~PetiteUsine() throw()
   { 
	   for_each (acteurs_, acteurs_ + NB_CODES, meurs()); 
   }
   void agir(const Code c)
   {
      // Valider que c >= 0 && c < NB_CODES au besoin
      acteurs_[c]->agir ();
   }
};
int main ()
{
   PetiteUsine miniU;
   miniU.agir(PetiteUsine::BOUCANER);
}
*/


///////////////////////////////////////////////// SOLUTION 2—polymorphisme et objets d'action indirects (suite)
/*
#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>
using std::for_each;
struct meurs
{
   template <class T>
      void operator()(T p) throw()
      { 
		  delete p; 
	  }
};
class PetiteUsine
{
	void monter ()
	{ 
		cout << "Je monte!" << endl; 
	}
	void descendre ()
	{ 
		cout << "Je descend!" << endl; 
	}
	void boucaner ()
	{ 
		cout << "Je boucane!" << endl; 
	}
	void vibrer ()
	{ 
		cout << "Je vibre!" << endl; 
	}
   struct Acteur
   {
      virtual void agir(PetiteUsine *) = 0;
      virtual ~Acteur() throw()
         { }
   };
   struct Monteur : Acteur
   {
      void agir (PetiteUsine *p)
         { p->monter(); }
   };
   struct Descendeur : Acteur
   {
      void agir (PetiteUsine *p)
         { p->descendre(); }
   };
   struct Boucaneur : Acteur
   {
      void agir (PetiteUsine *p)
         { p->boucaner(); }
   };
   struct Vibreur : Acteur
   {
      void agir (PetiteUsine *p)
         { p->vibrer(); }
   };
public:
   enum Code
   {
      MONTER = 0x00, DESCENDRE = 0x01, BOUCANER = 0x02, VIBRER = 0x03,
      NB_CODES // sentinelle
   };
private:
   Acteur *acteurs_[NB_CODES];
public:
   PetiteUsine() // prudence: pas exception-safe
   {
      acteurs_[MONTER] = new Monteur;
      acteurs_[DESCENDRE] = new Descendeur;
      acteurs_[BOUCANER] = new Boucaneur;
      acteurs_[VIBRER] = new Vibreur;
   }
   ~PetiteUsine () throw()
      { for_each (acteurs_, acteurs_ + NB_CODES, meurs()); }
   void Agir (const Code c)
   {
      // Valider que c >= 0 && c < NB_CODES au besoin
      acteurs_[c]->agir(this);
   }
};
int main ()
{
   PetiteUsine miniU;
   miniU.Agir (PetiteUsine::BOUCANER);
}
*/

///////////////////////////////////////////////// SOLUTION 3—pointeurs de méthodes d'instance
using std::cout;
using std::endl;
class PetiteUsine
{
	void monter ()
	{ 
		cout << "Je monte!" << endl; 
	}
	void descendre ()
	{ 
		cout << "Je descend!" << endl; 
	}
	void boucaner ()
	{ 
		cout << "Je boucane!" << endl; 
	}
	void vibrer ()
	{ 
		cout << "Je vibre!" << endl; 
	}
	// type de ces méthodes
	typedef void (PetiteUsine::*methode_action)();
public:
	enum Code
	{
		MONTER = 0x00, DESCENDRE = 0x01, BOUCANER = 0x02, VIBRER = 0x03,
		NB_CODES // sentinelle
	};
private:
	methode_action action_[NB_CODES];
public:
	PetiteUsine() throw()
	{
		// Capture des pointeurs sur les méthodes
		action_[MONTER] = &PetiteUsine::monter;
		action_[DESCENDRE] = &PetiteUsine::descendre;
		action_[BOUCANER] = &PetiteUsine::boucaner;
		action_[VIBRER] = &PetiteUsine::vibrer;
	}
	void agir(const Code c)
	{
		// Valider que c >= 0 && c < NB_CODES au besoin
		(this->*action_[c])();
	}
};

BEGIN_TEST(InstanceMethods)
	PetiteUsine miniU;
	miniU.agir(PetiteUsine::BOUCANER);

	END_TEST()