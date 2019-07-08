#pragma once
#include "stdafx.h"
/*
#include <ctime>
using std::clock;
using std::clock_t;
template <class C>
   clock_t InsererElements (C & conteneur, const int NbElems)
   {
      clock_t Avant = clock();
     // for (int i = 0; i < NbElems; i++) conteneur.push_back (i+1);
	  for (int i = 0; i < NbElems; i++) conteneur.insert (conteneur.begin(),i+1);
      clock_t Apres = clock();
      return Apres - Avant;
   }
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <list>
using std::list;
#include <deque>
using std::deque;


int _tmain(int argc, _TCHAR* argv[])
{ 
   const int NB_INSERTIONS = 5000;
   vector<int> v;
   list<int> lst;
   deque<int> d;
   const clock_t t_v = InsererElements (v, NB_INSERTIONS);
   const clock_t t_lst = InsererElements (lst, NB_INSERTIONS);
   const clock_t t_d = InsererElements (d, NB_INSERTIONS);
   cout << "Résultats pour " << NB_INSERTIONS << " insertions (ms):" << endl
        << "\tvector: " << static_cast<double>(t_v)/CLOCKS_PER_SEC * 1000 << endl
        << "\tlist: " << static_cast<double>(t_lst)/CLOCKS_PER_SEC * 1000 << endl
        << "\tdeque: " << static_cast<double>(t_d)/CLOCKS_PER_SEC * 1000 << endl;

   getchar();
}

*/

/*
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <deque>
using std::deque;
#include <ctime>
using std::clock;
using std::clock_t;
#include <iostream>
using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
   const int NB_ELEMENTS = 5000000; 
   int *Tab = new int [NB_ELEMENTS];
   std::srand (static_cast<int>(std::time (0)));
   for (int i = 0; i < NB_ELEMENTS; i++)
      Tab[i] = std::rand () % 10 + 1; // entre 1 et 10
   // par souci d'intégrité, tous nos conteneurs contiendront la même
   // séquence pour la réalisation du tri demandé
   vector<int> v (Tab, Tab+NB_ELEMENTS);
   list<int> lst (Tab, Tab+NB_ELEMENTS);
   deque<int> d  (Tab, Tab+NB_ELEMENTS);
   clock_t Avant, Apres;
   long Somme;
   // Test sur le tableau (avec index)
   Somme = 0;
   Avant = clock();
   for (int i = 0; i < NB_ELEMENTS; i++)
      Somme += Tab[i];
   Apres = clock();
   const clock_t t_t0 = Apres-Avant;
   // Test sur le tableau (avec index)
   Somme = 0;
   Avant = clock();
   for (int *p = Tab; p != Tab+NB_ELEMENTS; p++) Somme += *p;
   Apres = clock();
   const clock_t t_t1 = Apres-Avant;
   // Test sur un std::vector
   Somme = 0;
   Avant = clock();
   for (vector<int>::iterator itt = v.begin (); itt != v.end (); itt++) Somme += *itt;
   Apres = clock();
   const clock_t t_v = Apres-Avant;
   // Test sur une std::list
   Somme = 0;
   Avant = clock();
   for (list<int>::iterator itt = lst.begin (); itt != lst.end (); itt++) Somme += *itt;
   Apres = clock();
   const clock_t t_lst = Apres-Avant;
   // Test sur une std::deque
   Somme = 0;
   Avant = clock();
   for (deque<int>::iterator itt = d.begin (); itt != d.end (); itt++) Somme += *itt;
   Apres = clock();
   const clock_t t_d = Apres-Avant;
   cout << "Résultats pour la somme de " << NB_ELEMENTS << " éléments (ms):" << endl
        << "\ttableau (index): " << static_cast<double>(t_t0)/CLOCKS_PER_SEC * 1000 << endl
        << "\ttableau (itérateur): " << static_cast<double>(t_t1)/CLOCKS_PER_SEC * 1000 << endl
        << "\tvector: " << static_cast<double>(t_v)/CLOCKS_PER_SEC * 1000 << endl
        << "\tlist: " << static_cast<double>(t_lst)/CLOCKS_PER_SEC * 1000 << endl
        << "\tdeque: " << static_cast<double>(t_d)/CLOCKS_PER_SEC * 1000 << endl;
   delete [] Tab;
   getchar();
}

*/
/*
#include <ctime>
using std::time;
using std::clock;
using std::clock_t;
namespace
{
   long g_Somme = 0;
}

template <class Itt>
   clock_t CalculerSommeElements (Itt debut, Itt fin)
   {
      g_Somme = 0;
      clock_t Avant = clock();
      for (; debut != fin; debut++) g_Somme += *debut;
      clock_t Apres = clock();
      return Apres - Avant;
   }

#include <vector>
using std::vector;
#include <list>
using std::list;
#include <deque>
using std::deque;
#include <cstdlib>
using std::rand;
using std::srand;
#include <iostream>
using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
   const int NB_ELEMENTS = 5000000;
   int *Tab = new int [NB_ELEMENTS];
   srand (static_cast<int>(time (0)));
   for (int i = 0; i < NB_ELEMENTS; i++)
      Tab[i] = rand () % 10 + 1; // entre 1 et 10
   // par souci d'intégrité, tous nos conteneurs contiendront la même
   // séquence pour la réalisation du tri demandé
   vector<int> v (Tab, Tab+NB_ELEMENTS);
   list<int> lst (Tab, Tab+NB_ELEMENTS);
   deque<int> d  (Tab, Tab+NB_ELEMENTS);
   const clock_t t_t = CalculerSommeElements (Tab, Tab+NB_ELEMENTS);
   const clock_t t_v = CalculerSommeElements (v.begin (), v.end ());
   const clock_t t_lst = CalculerSommeElements (lst.begin (), lst.end ());
   const clock_t t_d = CalculerSommeElements (d.begin (), d.end ());
   cout << "Résultats pour la somme de " << NB_ELEMENTS << " éléments (ms):" << endl
        << "\ttableau: " << static_cast<double>(t_t)/CLOCKS_PER_SEC * 1000 << endl
        << "\tvector: " << static_cast<double>(t_v)/CLOCKS_PER_SEC * 1000 << endl
        << "\tlist: " << static_cast<double>(t_lst)/CLOCKS_PER_SEC * 1000 << endl
        << "\tdeque: " << static_cast<double>(t_d)/CLOCKS_PER_SEC * 1000 << endl;
   delete [] Tab;
   getchar();
}

*/

/*   
#include <ctime>
using std::time;
using std::clock;
using std::clock_t;
template <class Itt>
   clock_t CalculerSommeElements (Itt debut, Itt fin, long &Somme)
   {
      Somme = 0;
      clock_t Avant = clock();
      for (; debut != fin; debut++) Somme += *debut;
      clock_t Apres = clock();
      return Apres - Avant;
   }
#include <vector>
using std::vector;
#include <list>
using std::list;
#include <deque>
using std::deque;
#include <cstdlib>
using std::rand;
using std::srand;
#include <iostream>
using std::cout;
using std::endl;
int main ()
{
   const int NB_ELEMENTS = 5000000;
   int *Tab = new int [NB_ELEMENTS];
   srand (static_cast<int>(time (0)));
   for (int i = 0; i < NB_ELEMENTS; i++)
      Tab[i] = rand () % 10 + 1; // entre 1 et 10
   long Somme;
   // par souci d'intégrité, tous nos conteneurs contiendront la même
   // séquence pour la réalisation du tri demandé
   clock_t t_t = CalculerSommeElements (Tab, Tab+NB_ELEMENTS, Somme);
   vector<int> v (Tab, Tab+NB_ELEMENTS);
   list<int> lst (Tab, Tab+NB_ELEMENTS);
   deque<int> d  (Tab, Tab+NB_ELEMENTS);
   const clock_t t_v = CalculerSommeElements (v.begin (), v.end (), Somme);
   const clock_t t_lst = CalculerSommeElements (lst.begin (), lst.end (), Somme);
   const clock_t t_d = CalculerSommeElements (d.begin (), d.end (), Somme);
   cout << "Résultats pour la somme de " << NB_ELEMENTS << " éléments (ms):" << endl
        << "\ttableau: " << static_cast<double>(t_t)/CLOCKS_PER_SEC * 1000 << endl
        << "\tvector: " << static_cast<double>(t_v)/CLOCKS_PER_SEC * 1000 << endl
        << "\tlist: " << static_cast<double>(t_lst)/CLOCKS_PER_SEC * 1000 << endl
        << "\tdeque: " << static_cast<double>(t_d)/CLOCKS_PER_SEC * 1000 << endl;
   delete [] Tab;
   getchar();
}
*/

/*
   class Sommation
{
   long &cumul_;
public:
   Sommation (long &dest) : cumul_ (dest) {}
   void operator() (const int Val) throw()
      { cumul_ += Val; }
};
#include <ctime>
using std::time;
using std::clock;
using std::clock_t;
#include <algorithm>
using std::for_each;
template <class Itt>
   clock_t CalculerSommeElements (Itt debut, Itt fin, long &Somme)
   {
      Somme = 0;
      clock_t Avant = clock();
      for_each (debut, fin, Sommation (Somme));
      clock_t Apres = clock();
      return Apres - Avant;
   }

#include <vector>
using std::vector;
#include <list>
using std::list;
#include <deque>
using std::deque;
#include <cstdlib>
using std::rand;
using std::srand;
#include <iostream>
using std::cout;
using std::endl;
int main ()
{
   const int NB_ELEMENTS = 5000000;
   int *Tab = new int [NB_ELEMENTS];
   srand (static_cast<int>(time (0)));
   for (int i = 0; i < NB_ELEMENTS; i++)
      Tab[i] = rand () % 10 + 1; // entre 1 et 10
   long Somme;
   // par souci d'intégrité, tous nos conteneurs contiendront la même
   // séquence pour la réalisation du tri demandé
   clock_t t_t = CalculerSommeElements (Tab, Tab+NB_ELEMENTS, Somme);
   vector<int> v (Tab, Tab+NB_ELEMENTS);
   list<int> lst (Tab, Tab+NB_ELEMENTS);
   deque<int> d  (Tab, Tab+NB_ELEMENTS);
   const clock_t t_v = CalculerSommeElements (v.begin (), v.end (), Somme);
   const clock_t t_lst = CalculerSommeElements (lst.begin (), lst.end (), Somme);
   const clock_t t_d = CalculerSommeElements (d.begin (), d.end (), Somme);
   cout << "Résultats pour la somme de " << NB_ELEMENTS << " éléments (ms):" << endl
        << "\ttableau: " << static_cast<double>(t_t)/CLOCKS_PER_SEC * 1000 << endl
        << "\tvector: " << static_cast<double>(t_v)/CLOCKS_PER_SEC * 1000 << endl
        << "\tlist: " << static_cast<double>(t_lst)/CLOCKS_PER_SEC * 1000 << endl
        << "\tdeque: " << static_cast<double>(t_d)/CLOCKS_PER_SEC * 1000 << endl;
   delete [] Tab;
}

*/

/*
// Pour les fins de notre test, une entite aura une chance sur deux en moyenne
// d'être inactive
#include <cstdlib>
using std::rand;
using std::srand;
class Entite
{
   bool actif_;
public:
   Entite ()
      : actif_(rand () %2 == 0)
   {
   }
   bool EstInactive () const throw ()
      { return !actif_; }
};

// Le compte manuel teste chaque Entite et incrémente le compteur d'entités
// inactives seulement ci celle examinée est inactive
#include <ctime>
using std::clock_t;
using std::clock;
using std::time;
template <class Itt>
   clock_t CompterLesInactifsManuel (Itt debut, Itt fin, int &NbInactifs)
   {
      NbInactifs = 0;
      clock_t Avant = clock();
      for (; debut != fin; ++debut)
         if (debut->EstInactive()) ++NbInactifs;
      clock_t Apres = clock();
      return Apres - Avant;
   }

// Le compte standard définit une fonction prenant une Entite en paramètre et
// retournant true si et seulement si cette entité est inactive, puis utilise
// cette fonction comme prédicat pour l'algorithme standard::count_if()
#include <algorithm>
using std::count_if;
using std::generate_n;
bool EstInactif(const Entite &e) throw()
   { return e.EstInactive (); }

template <class Itt>
   clock_t CompterLesInactifsSTD (Itt debut, Itt fin, int &NbInactifs)
   {
      NbInactifs = 0;
      clock_t Avant = clock();
      NbInactifs = count_if (debut, fin, EstInactif);
      clock_t Apres = clock();
      return Apres - Avant;
   }

// Pour faciliter la mécanique, le code préparant le test générera NB_ELEMENTS
// instances de Entite à l'aide de l'algorithme standard std::generate_n()
Entite CreerEntite () throw()
   { return Entite (); }

#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
int main ()
{
   const int NB_ELEMENTS = 50000000;
   srand (static_cast<unsigned int>(time (0)));
   vector<Entite> v (NB_ELEMENTS);
   generate_n (v.begin (), NB_ELEMENTS, CreerEntite);
   int NbInactifs;
   const clock_t t_man =
      CompterLesInactifsManuel (v.begin (), v.end (), NbInactifs);
   cout << "Compatibilité manuelle, nb d'inactifs sur "
        << NB_ELEMENTS << " éléments: "
        << NbInactifs << ", temps requis (ms):" << t_man << endl;
   const clock_t t_std =
      CompterLesInactifsSTD (v.begin (), v.end (), NbInactifs);
   cout << "Compatibilité standard, nb d'inactifs sur "
        << NB_ELEMENTS << " éléments: "
        << NbInactifs << ", temps requis (ms):" << t_std << endl;

   getchar();
}

*/

// Nous ajoutons un nom à toute entité et les strates opérationnelles qui
// accompagnent ajout. L'opérateur == sur une Entite et une std::string
// retournera true si la chaîne standard correspond au nom de l'entité
#include <string>
using std::string;
class Entite
{
   enum Grade { NEOPHYTE, APPRENTI, ADEPTE, EXPERT, MAITRE };
   Grade grade_;
   string nom_;
public:
   Entite (const string &Nom = "Joe Blo")
      : grade_ (NEOPHYTE), nom_ (Nom)
   {
   }
   Grade GetGrade () const throw()
      { return grade_; }
   const string & GetNom () const throw ()
      { return nom_; }
   void Renommer (const string &Nom)
      { nom_ = Nom; }
   bool Promotion ()
   {
      if (GetGrade() == MAITRE)
         return false;
      grade_ = static_cast<Grade> (GetGrade () + 1);
      return true;
   }
   bool EstExpert () const throw()
      { return GetGrade () >= EXPERT; }
   bool operator == (const Entite &e) const
      { return GetGrade() == e.GetGrade() && GetNom() == e.GetNom(); }
   bool operator == (const string &s) const
      { return GetNom () == s; }
};

// Les recherches ont été légèrement adaptées pour tenir compte de la recherche
// par nom plutôt que par grade
#include <ctime>
using std::clock;
using std::clock_t;
using std::time;
template <class Itt>
   Itt TrouverEntiteManuel (Itt debut, Itt fin, const string &s, clock_t &Temps)
   {
      clock_t Avant = clock();
      Itt itt = fin;
      for (; debut != fin; ++debut)
         if (*debut == s)
         {
            itt = debut;
            Temps = clock() - Avant;
            return itt;
         }
      Temps = clock() - Avant;
      return itt;
   }

// La recherche standard avec std::find () se base sur l'opérateur == de Entite
// et ne nécessite donc pas de prédicat externe pour réaliser sa tâche
#include <algorithm>
using std::find;
using std::generate_n;
using std::random_shuffle;
template <class Itt>
   Itt TrouverEntiteSTD (Itt debut, Itt fin, const string &s, clock_t &Temps)
   {
      clock_t Avant = clock();
      Itt itt = find (debut, fin, s);
      Temps = clock() - Avant;
      return itt;
   }

Entite CreerEntite () throw()
   { return Entite (); }

#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>
using std::srand;

BEGIN_TEST(Iterators)
   const int NB_ELEMENTS = 5000000;
   srand (static_cast<unsigned int>(time (0)));
   vector<Entite> v (NB_ELEMENTS);
   // Création de NB_ELEMENTS, tous Joe Blo et néophytes
   generate_n (v.begin (), NB_ELEMENTS, CreerEntite);
   // L'une des entités se nomme "Fred"
   v.front ().Renommer ("Fred");
   // On brasse la séquence... où est rendu Fred?
   random_shuffle (v.begin (), v.end ());

   {
      clock_t t_man;
      vector <Entite>::iterator itt =
         TrouverEntiteManuel (v.begin (), v.end (), "Fred", t_man);
      cout << "Recherche manuelle sur " << NB_ELEMENTS
           << " éléments: position" << static_cast<int>(v.end () - itt)
           << ", temps requis (ms):" << t_man << endl;
   }
   {
      clock_t t_std;
      vector <Entite>::iterator itt =
         TrouverEntiteSTD (v.begin (), v.end (), "Fred", t_std);
      cout << "Recherche standard sur " << NB_ELEMENTS
           << " éléments: position" << static_cast<int>(v.end () - itt)
           << ", temps requis (ms):" << t_std << endl;
   }

   END_TEST()