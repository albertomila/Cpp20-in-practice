#pragma once
#include "stdafx.h"

// Visitor part
class BaseVisitor
{
public:
    virtual ~BaseVisitor() {}
};

template <class T, typename R = void>
class Visitor
{
public:
    typedef R ReturnType; // Available for clients
    virtual ReturnType Visit(T&) = 0;
};

// Visitable part
template <typename R = void>
class BaseVisitable
{
public:
    typedef R ReturnType;
    virtual ~BaseVisitable() {}
    virtual R Accept(BaseVisitor&) = 0;
protected:
    template <class T>
    static ReturnType AcceptImpl(T& visited, BaseVisitor& guest)
    {
        // Apply the Acyclic Visitor
        if (Visitor<T>* p = dynamic_cast<Visitor<T>*>(&guest))
        {
            return p->Visit(visited);
        }
        return ReturnType();
    }
};


#define DEFINE_VISITABLE() \
    virtual ReturnType Accept(BaseVisitor& guest) \
   { return AcceptImpl(*this, guest); }

class DocElement : public BaseVisitable<>
{
public:
    DEFINE_VISITABLE()
};

class Paragraph : public DocElement
{
public:
    DEFINE_VISITABLE()
};

class MyConcreteVisitor :
    public BaseVisitor,  // required
    public Visitor<DocElement>,// visits DocElements
    public Visitor<Paragraph>   // visits Paragraphs
{
public:
    void Visit(DocElement&) 
    { 
        std::cout << "Visit(DocElement&) \n"; 
    }
    void Visit(Paragraph&) 
    { 
        std::cout << "Visit(Paragraph&) \n"; 
    }
};


BEGIN_TEST(VisitorTest)
    MyConcreteVisitor visitor;
    Paragraph par;
    DocElement* d = &par;  // "hide" the static type of 'par'
    d->Accept(visitor);
END_TEST()

