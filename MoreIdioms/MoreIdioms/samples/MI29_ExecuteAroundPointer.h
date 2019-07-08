#pragma once
#include "stdafx.h"
/*
Example #1

class VisualizableVector 
{
public:
    class proxy 
    {
    public:
        proxy (std::vector<int> *v) 
            : vect (v) 
        {
            std::cout << "Before size is: " << vect->size ();
        }
        std::vector<int> * operator -> () 
        {
            return vect;
        }

        ~proxy () 
        {
            std::cout << "After size is: " << vect->size ();
        }
    private:
        std::vector <int> * vect;
    };

    VisualizableVector (std::vector<int> *v) 
        : vect(v) 
    
    {
    }    
    proxy operator -> () 
    {
        return proxy (vect);
    }
private:
    std::vector <int> * vect;
};

int main()
{
    VisualizableVector vecc (new std::vector<int>);
    //...
    vecc->push_back (10); // Note use of -> operator instead of . operator
    vecc->push_back (20);
}
*/


//Example #1
////////////////////////////////////////////////////////////////
template <class NextAspect, class Para>
class Aspect
{
protected:
    Aspect (Para p)
        : para_(p) 
    {
    }

public:
    NextAspect operator -> () 
    {
        return para_;
    }

protected:
    Para  para_;
};


////////////////////////////////////////////////////////////////
template <class NextAspect, class Para>
struct Visualizing : Aspect <NextAspect, Para>
{
public:
    Visualizing (Para p) 
        : Aspect <NextAspect, Para> (p) 
    {
        std::cout << "Before Visualization aspect" << std::endl;
    }
    ~Visualizing () 
    {
        std::cout << "After Visualization aspect" << std::endl;
    }
};

////////////////////////////////////////////////////////////////
template <class NextAspect, class Para>
struct Locking : Aspect <NextAspect, Para>
{
public:
    Locking (Para p) 
        : Aspect <NextAspect, Para> (p) 
    {
        std::cout << "Before Lock aspect" << std::endl;
    }
    ~Locking () 
    {
        std::cout << "After Lock aspect" << std::endl;
    }
};

////////////////////////////////////////////////////////////////
template <class NextAspect, class Para>
struct Logging : Aspect <NextAspect, Para>
{
public:
    Logging (Para p) 
        : Aspect <NextAspect, Para> (p) 
    {
        std::cout << "Before Log aspect" << std::endl;
    }
    ~Logging () 
    {
        std::cout << "After Log aspect" << std::endl;
    }
};

////////////////////////////////////////////////////////////////
template <class Aspect, class Para>
class AspectWeaver 
{
public:
    AspectWeaver (Para p) 
        : para_(p) 
    {
    }   

    Aspect operator -> () 
    {
        return Aspect (para_);
    }

private:
    Para para_;
};
////////////////////////////////////////////////////////////////
#define AW1(T,U) AspectWeaver <T <U, U>, U >
#define AW2(T,U,V) AspectWeaver <T < U <V, V> , V>, V >
#define AW3(T,U,V,X) AspectWeaver <T < U <V <X, X>, X> , X>, X >


BEGIN_TEST(ExecuteAroundPointer)
    AW3(Visualizing, Locking, Logging, std::vector <int> *) X = new std::vector<int>();
   
    X->push_back (10); // Note use of -> operator instead of . operator
    X->push_back (20);
END_TEST()