#pragma once
#include "stdafx.h"

class Employee 
{
public:
    virtual ~Employee () {}                 // Native support for polymorphic destruction.
    virtual Employee* Create() const = 0; // Virtual constructor (creation) 
    virtual Employee* Clone() const = 0;  // Virtual constructor (copying) 
};

class Manager : public Employee     // "is-a" relationship
{
public:
    Manager () // Default constructor
        : Employee()
    {
        ;
    }   

    Manager ( int x ) 
        : Employee()
        , m_x( x )                     // Default constructor
    {
        ;
    }   

    Manager (Manager const & m ) 
        : Employee()
        , m_x( m.m_x )       // Copy constructor
    {
        ;
    }   

    virtual ~Manager ()                  // Destructor
    {
        ;
    }   
    virtual Manager* Create() const       // Virtual constructor (creation) 
    {
        return new Manager();
    }
    virtual Manager* Clone() const        // Virtual constructor (copying) 
    {
        return new Manager (*this);
    }

    int m_x;
};

Employee* Duplicate(Employee const & e)
{
    return e.Clone();  // Using virtual constructor idiom.
}

BEGIN_TEST(VirtualConstructor)
    Manager m( 99 );
    Manager* mPtr = &m;
    Employee* ePtr = mPtr;
    Employee* ePtr2 = Duplicate( *ePtr );
    Employee* ePtr3 = Duplicate( m );
END_TEST()