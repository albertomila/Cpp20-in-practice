// DesignPatterns.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <samples/creational/AbstractFactory.h>
#include <samples/creational/Builder.h>
#include <samples/creational/Prototype.h>
#include <samples/creational/Singleton.h>
#include <samples/creational/FactoryMethod.h>
#include <samples/creational/RAII.h>
#include <samples/creational/LazyInitization.h>
#include <samples/creational/Multiton.h>
#include <samples/creational/Pool.h>

#include <samples/structural/Adapter.h>
#include <samples/structural/Bridge.h>
#include <samples/structural/Composite.h>
#include <samples/structural/Decorator.h>
#include <samples/structural/Facade.h>
#include <samples/structural/FlyWeight.h>
#include <samples/structural/Proxy.h>
#include <samples/structural/PrivateImplementation.h>
#include <samples/structural/RecursiveTemplate.h>
#include <samples/structural/Tuples.h>
#include <samples/structural/Twin.h>
#include <samples/structural/MarkerInterfacePolicies.h>
#include <samples/behavioral/ChainOfResponsibility.h>
#include <samples/behavioral/Command.h>
#include <samples/behavioral/Iterator.h>
#include <samples/behavioral/Mediator.h>
#include <samples/behavioral/Memento.h>
#include <samples/behavioral/Observer.h>
#include <samples/behavioral/State.h>
#include <samples/behavioral/Strategy.h>
#include <samples/behavioral/TemplateMethod.h>
#include <samples/behavioral/NullObject.h>
#include <samples/behavioral/Visitor.h>

int main()
{
	//creational patterns
	//-----------------------------------
	//AbstractFactory().Run();
	//AbstractFactory2().Run();
	//Builder().Run();
	//Prototype().Run();
	//SingletonTest().Run();
	//FactoryMethod().Run();
	//RAII().Run();
	//LazyInitialization().Run();
	//Multiton().Run();
	//Pool().Run();

	//structural patterns
	//-----------------------------------
	//Adapter().Run();
	//Bridge().Run();
	//Composite().Run();
	//Decorator().Run();
	//Facade().Run();
	//FlyWeight().Run();
	//Proxy().Run();
	//PrivateImplementation().Run();
	RecursiveTemplate().Run();
	//Tuples().Run();
	//Twin().Run();
	//MarkerInterface().Run();

	//behavioral patterns
	//-----------------------------------
	//ChainOfResponsibility().Run();
	//Command().Run();
	//Iterator().Run();
	//Mediator().Run();
	//Memento().Run();
	//Observer().Run();
	//State().Run();
	//Strategy().Run();
	//TemplateMethod().Run();
	//NullObject().Run();
	//Visitor().Run();

	return 0;
}

