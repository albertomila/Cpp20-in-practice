#pragma once
#include "stdafx.h"
#include <cstring>
using namespace std;
 
class Persona {
  public:
   Persona(char *n) { strcpy_s(nombre, n); }
   virtual void VerNombre() { cout << nombre << endl; }
   void Nombre() { cout << nombre << endl; }
   virtual ~Persona()
	{
		strcpy_s(nombre, ""); 
   }
   virtual void Test()
   {
	   cout << "Test" << nombre << endl; 
   }
  protected:
   char nombre[30];
   
};

class Empleado : public Persona {
  public:
   Empleado(char *n) : Persona(n) {}
   void VerNombre() { cout << "Emp: " << nombre << endl; }
   void Nombre() { cout << "Emp: " << nombre << endl; }
   ~Empleado()
	{
		int x = 0;
		x = 0;
   }
};

class Estudiante : public Persona {
  public:
   Estudiante(char *n) : Persona(n) {}
   void VerNombre() { cout << "Est: " << nombre << endl; }
   void Nombre() { cout << "Est: " << nombre << endl; }
   void Test()
   {
	  Persona::Test();
	  ::Persona::Test();
	  Estudiante::Persona::Test();
   }
   ~Estudiante()
	{
		int x = 0;
		x = 0;
   }
};

BEGIN_TEST(Virtual)
   Persona *Pepito = new Estudiante("Jose");
   Persona P2 = *Pepito;
   P2.VerNombre();

   Estudiante *Mila = new Estudiante("Mila");
   Mila->Test();

   Persona P = *dynamic_cast<Persona*>(Mila);
   P.VerNombre();



   Persona *Carlos = new Empleado("Carlos");

   Carlos->VerNombre();
   Carlos->Nombre();
   Pepito->VerNombre();
   Pepito->Nombre();
   delete Pepito;
   delete Carlos;

   
   Persona Pepito1 = Estudiante("Jose1");
   Persona Carlos1 = Empleado("Carlos1");

   Carlos1.VerNombre();
   Carlos1.Nombre();
   Pepito1.VerNombre();
   Pepito1.Nombre();
   

   Estudiante Pepito2("Jose");
   Empleado Carlos2("Carlos");
   Persona &rPepito = Pepito2; // Referencia como Persona
   Persona &rCarlos = Carlos2; // Referencia como Persona

   rCarlos.VerNombre();
   rCarlos.Nombre();
   rPepito.VerNombre();
   rPepito.Nombre();

   END_TEST()