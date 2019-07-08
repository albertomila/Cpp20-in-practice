#include "stdafx.h"
#include <xutility>

#include <utility>      // std::forward
#include <iostream>     // std::cout
#include <vector>
#include <set>
#include <array>

class WidgetMove
{
public:
    WidgetMove()
        : m_var("Widget_Test")
        , m_varChar(nullptr)
    {
    }

    WidgetMove(const WidgetMove& widget)
        : m_varChar(nullptr)
    {
        m_var = widget.m_var;
        strcpy_s(m_varChar, strlen(const_cast<const char*>(widget.m_varChar)), const_cast<const char*>(widget.m_varChar) );
    }

    WidgetMove(WidgetMove&& widget)
        : m_var(std::move(widget.m_var))
        , m_varChar( std::move(widget.m_varChar))
    {
    }

    WidgetMove* operator = (WidgetMove& widget)
    {
        m_var = widget.m_var;
        strcpy_s(m_varChar, strlen(const_cast<const char*>(widget.m_varChar)), const_cast<const char*>(widget.m_varChar));

        return this;
    }

    WidgetMove* operator = (WidgetMove&& widget)
    {
        m_var = std::move(widget.m_var);
        m_varChar = std::move(widget.m_varChar);
        
        return this;
    }

    void Init()
    {
        m_varChar = new char[128];
        m_varChar[0] = '\0';
        strcpy_s(m_varChar, 128, const_cast<const char*>("Widget_CharArray_test"));
    }
                                       // return value
public:
    std::string m_var;
    char* m_varChar;
};

void process(const WidgetMove& lvalArg)     // process lvalues
{

}

void process(WidgetMove&& rvalArg)          // process rvalues
{

}

template<typename T>                     // template that passes
void logAndProcess(T&& param)            // param to process
{
    process(std::forward<T>(param));
}


// function with lvalue and rvalue reference overloads:
void overloaded(const int& x) 
{ 
    std::cout << "[lvalue]"; 
}

void overloaded(int&& x) 
{ 
    std::cout << "[rvalue]"; 
}

// function template taking rvalue reference to deduced type:
template <class T> 
void fn(T&& x) //T&& means universal reference
{
    overloaded(x);                   // always an lvalue
    overloaded(std::forward<T>(x));  // rvalue if argument is rvalue
}

class WidgetHandler
{
public:

    void AddWidget(WidgetMove&& widget)
    {
        m_Widget = std::move(widget);
    }

    WidgetMove m_Widget;
};

void AddWidget(WidgetHandler& wh, WidgetMove&& w)
{
    wh.AddWidget(std::move(w));
}


std::multiset<std::string> names;     // global data structure
template<typename T>
void AddName(T&& name)
{
    names.emplace(std::forward<T>(name));
}

class WData
{
public:
	WData()
		: _value(nullptr)
	{
		_value = new char[128];
		strcpy_s(_value, 128, "WData_value");
	}

	~WData()
	{
		delete _value;
		_value = nullptr;
	}

	
	WData(WData&& wData)
		: _value(wData._value)
	{
		wData._value = nullptr;
	}
	//WData(WData&& wData) = default;

private:
	char* _value;
};

BEGIN_TEST(TestMove)

	WData w1;
	WData w2 = std::move(w1);


    WidgetHandler wh;
    {
        WidgetMove w;
        w.Init();
        AddWidget(wh, std::move(w));
    }


    {
        WidgetMove wLvalue;

        logAndProcess(wLvalue);
        logAndProcess<WidgetMove&>(wLvalue);

        logAndProcess(std::move(wLvalue));
        logAndProcess<WidgetMove>(std::move(wLvalue));
    }
    
    {
        int a;

        std::cout << "calling fn with lvalue: ";
        fn(a);
        std::cout << '\n';

        std::cout << "calling fn with rvalue: ";
        fn(0);
        std::cout << '\n';

        std::cout << "calling fn with rvalue: ";
        fn(std::move(a));
        std::cout << '\n';

    }


    {
        std::string petName("Darla");          // as before

        AddName(petName);                    // as before, copy
                                               // lvalue into multiset

        AddName(std::string("Persephone"));  // move rvalue instead
                                               // of copying it

        AddName("Patty Dog");                // create std::string
                                               // in multiset instead
                                               // of copying a temporary
                                               // std::string
    }

    {
        std::array<WidgetMove, 10000> aw1;
        std::array<WidgetMove, 10000> aw2 = std::move(aw1); //move not suported for std::array, entire data copied.
    }
END_TEST()