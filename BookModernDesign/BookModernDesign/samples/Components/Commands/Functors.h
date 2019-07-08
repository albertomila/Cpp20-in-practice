#pragma once
#include "stdafx.h"
#include "samples/Techniques/Typelists.h"
#include <stdlib.h>
#include <memory>

template <typename R, class TList>
class FunctorImpl
{
};

template <typename R>
class FunctorImpl<R, NullType>
{
public:
    virtual R operator()(){ return R(); };
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1>
class FunctorImpl<R, TYPELIST_1(P1)>
{
public:
    virtual R operator()(P1){ return R(); };
    virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2>
class FunctorImpl<R, TYPELIST_2(P1, P2)>
{
public:
    virtual R operator()(P1, P2){ return R(); };
    virtual ~FunctorImpl() {}
};

template <typename R, class TList>
class Functor
{
    typedef FunctorImpl<R, TList> Impl;
public:
    typedef R ResultType;
    typedef TList ParmList;
    typedef typename TypeAtNonStrict<TList, 0, EmptyType>::Result Parm1;
    typedef typename TypeAtNonStrict<TList, 1, EmptyType>::Result Parm2;
  
    Functor()
        : spImpl_( new Impl() )
    {
    }

    template <class Fun>
    Functor(const Fun& fun);
    /*
    template <class PtrObj, typename MemFn>
    Functor(const PtrObj& p, MemFn memFn)
    : spImpl_(new MemFunHandler<Functor, PtrObj, MemFn>(p, memFn))
    {
    }
    */

    //Functor(const Functor&);
    //Functor& operator=(const Functor&);
    explicit Functor(std::auto_ptr<Impl> spImpl)
    {

    }
  
    R operator()()
    {
        return (*spImpl_)();
    }

    R operator()(Parm1 p1)
    {
        return (*spImpl_)(p1);
    }

    R operator()(Parm1 p1, Parm2 p2)
    {
        return (*spImpl_)(p1, p2);
    }

private:
    std::auto_ptr<Impl> spImpl_;
};



template <class ParentFunctor,  typename Fun>
class FunctorHandler
    : public FunctorImpl
    <
        typename ParentFunctor::ResultType,
        typename ParentFunctor::ParmList
    >
{
public:
    typedef typename ParentFunctor::ResultType ResultType;

    FunctorHandler(const Fun& fun) : fun_(fun) {}
    FunctorHandler* Clone() const
    { return new FunctorHandler(*this); }

    ResultType operator()()
    {
        return fun_();
    }
    ResultType operator()(typename ParentFunctor::Parm1 p1)
    {
        return fun_(p1);
    }
    ResultType operator()(typename ParentFunctor::Parm1 p1,
        typename ParentFunctor::Parm2 p2)
    {
        return fun_(p1, p2);
    }
private:
    Fun fun_;
};
/*
template <class ParentFunctor, typename PointerToObj,
    typename PointerToMemFn>
class MemFunHandler
    : public FunctorImpl
    <
        typename ParentFunctor::ResultType,
        typename ParentFunctor::ParmList
    >
{
public:
    typedef typename ParentFunctor::ResultType ResultType;
    MemFunHandler(const PointerToObj& pObj, PointerToMemFn pMemFn)
        : pObj_(pObj)
        , pMemFn_(pMemFn) 
    {
    }

    MemFunHandler* Clone() const
    { 
        return new MemFunHandler(*this); 
    }

    ResultType operator()()
    {
        return ((*pObj_).*pMemFn_)();
    }

    ResultType operator()(typename ParentFunctor::Parm1 p1)
    {
        return ((*pObj_).*pMemFn_)(p1);
    }

    ResultType operator()(typename ParentFunctor::Parm1 p1,
        typename ParentFunctor::Parm2 p2)
    {
        return ((*pObj_).*pMemFn_)(p1, p2);
    }

private:
    PointerToObj pObj_;
    PointerToMemFn pMemFn_;
};

*/


template <typename R, class TList>
template <typename Fun>
Functor<R, TList>::Functor(const Fun& fun)
    : spImpl_(new FunctorHandler<Functor, Fun>(fun))
{
}

