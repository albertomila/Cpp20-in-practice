#include "stdafx.h"
#include <memory>

class WidgetSmartPointer
{

};

class Investment 
{
public:
    Investment()
    {
    }
    virtual ~Investment()
    {
    }
};

class Stock : public Investment 
{
public:
    Stock()
    {
    }
    virtual ~Stock()
    {
    }
};

class Bond : public Investment 
{
public:
    Bond()
    {
    }
    virtual ~Bond()
    {
    }
};

class RealEstate : public Investment 
{
public:
    RealEstate()
    {
    }
    virtual ~RealEstate()
    {
    }
};

void makeLogEntry(Investment* pInvestment)
{

}

auto delInvmt = [](Investment* pInvestment)       // custom
{                                 // deleter
    makeLogEntry(pInvestment);      // (a lambda
    delete pInvestment;             // expression)
};


typedef std::unique_ptr<Investment, decltype(delInvmt)> TUniquePtr;

template<typename... Ts>                          // revised
TUniquePtr makeInvestment(Ts&&... params)  // return type
{
    TUniquePtr pInv(nullptr, delInvmt);// ptr to be returned
           
    if ( true /* a Stock object should be created */)
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if ( true/* a Bond object should be created */)
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if ( true/* a RealEstate object should be created */)
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }

    return pInv;
}

BEGIN_TEST(TestSmartPointer)
    {
        std::unique_ptr<Investment> investmentPtr;
        investmentPtr.reset(new Stock());
    }//auto delete

    {
        std::unique_ptr<Investment> investmentPtr;
        investmentPtr.reset(new Stock());
        investmentPtr.reset(nullptr);
    }

    {
        TUniquePtr ptr = makeInvestment();
        if (ptr != nullptr)
        {
            ptr.reset(nullptr);
            //return true;
        }
        else
        {
           // return false;
        }
    }

    {
        WidgetSmartPointer* pw = new WidgetSmartPointer();                          // pw is raw ptr
        std::shared_ptr<WidgetSmartPointer> spw1(pw);  // create control
        std::shared_ptr<WidgetSmartPointer> spw2(spw1);  // create control
        //bad!!! two shared pointers for the same raw pointer
        //std::shared_ptr<WidgetSmartPointer> spw2(pw);  // create 2nd control block for *pw!

        //good! only one raw pointer
        std::shared_ptr<WidgetSmartPointer> spw3(new WidgetSmartPointer());  // create control
    }
END_TEST()