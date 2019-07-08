#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
 
#include <cstdarg>

#include "../MetaProg/TraitsLists.h"
using namespace std;
 
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
class Deriv2;
class Deriv;
class Base;

typedef        
    type_list < Deriv,	//0
    type_list < Deriv2, //1
                Vide	//2
	>>
list_types;
 
const int LIST_TYPES_SIZE = static_length<list_types>::VAL;
 
template<class T>
struct TypePosition
{
    enum{ LIST_TYPE_POS = indice_par_type<list_types, T>::VAL };
};
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
 
struct IDispatchable
{
      virtual void DispatchValue(Base* base)
	  {
	  }
};

class Clonable2 : public IDispatchable
{
public:
      virtual Clonable2* Clone() const= 0;

      virtual ~Clonable2() throw(){}

      virtual const std::type_info& DeudireType() const throw() = 0;
};
 
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
 
template<class T>
class Capsule2 : public Clonable2
{
public:
		typedef T type_data;
 
		type_data value_;
		const std::type_info& DeudireType() const throw()
		{
			return typeid(value_);
		}
public:
		Capsule2(const type_data& value = type_data())
			: value_(value)
		{
		}
		Capsule2<T>* Clone() const
		{
			return new Capsule2<T>(*this);
		}
 
		type_data GetValue() const
		{
			return value_;
		}
		~Capsule2() throw()
		{
		}    

		////////////////////////////////////////////////////////////////////////
		virtual void DispatchValue(Base* base)
		{
            base->DispatchTypeAndValue< type_data >( value_ );
		}
};
 
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
 
 
class Whatever2
{
      Clonable2* capsule_;
public:
      Clonable2* GetCapsule()
      {
            return capsule_;
      }
 
      template<class T>
      Capsule2<T>* GetCapsule()
      {
            return static_cast<Capsule2<T>*>(capsule_);
      }
 
     
      Whatever2() : capsule_(0) {}
     
      template<class T>
      Whatever2(const T& value) : capsule_(new Capsule2<T>(value))
      {
      }
 
      Whatever2(Clonable2* clonable) : capsule_(clonable->Clone())
      {
      }
 
      ~Whatever2()
      {
            //delete capsule_;
      }
     
 
      template<class T>
      bool IsType() throw()
      {
            return capsule_->DeudireType() == typeid(T);
      }
      const std::type_info& DeudireType()
      {
            return capsule_->DeudireType();
      }
};
 
typedef vector<Whatever2> genvector;
 
 
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
 
class Base
{
    const unsigned int typeListPos_;
public:
 
    Base( const unsigned int typeListPos)
        : typeListPos_(typeListPos)
    {
    }

    template<class T>
    void DispatchTypeAndValue(const T& value)
    {
        SelectType< 0 >::Select<T>(value, this, typeListPos_);
    }
	
    template<class DerivedType, class T>
    void DispatchValue(const T& value)
    {
		DerivedType* obj = static_cast< DerivedType*>(this);
		if( obj )
		{
			//test with templates
			obj->GetTemplateValue<T>( value ); 
 
			//test with function overrides
			obj->GetArgumentValue( value );  
		}  
    }
            
	void DispatchValue(IDispatchable* dispatchable)
	{
		dispatchable->DispatchValue(this);
	}
};
 
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
 
struct Dispatcher
{
	Dispatcher(Base* deriv, IDispatchable* dispatchable)
	{
		dispatchable->DispatchValue( deriv );
	}
};

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

template<unsigned int N>
class SelectType
{
    enum
	{ 
		POS = N, 
		NEXT_POS = N+1, 
	};
 
    typedef 
        typename type_par_indice<list_types,POS>::type
    type_request;
 
public:
    template<class T>
    static void Select(const T& value, Base* base, const unsigned int pos)
    {
		if (POS == pos) 
			base->DispatchValue< type_request, T >( value );
		else 
			SelectType< NEXT_POS >::Select<T>(value, base, pos);
    }
};

template<>
class SelectType<LIST_TYPES_SIZE>
{
public:
    template<class T>
    static void Select(const T& value, Base* base, const unsigned int pos){}
};
 
 
class Deriv : public Base, TypePosition<Deriv>
{
public:
	Deriv() : Base( LIST_TYPE_POS )
	{
	}
 
	template<class T>
	void GetTemplateValue(const T& value)
	{
	}
 
	template<>
	void GetTemplateValue<int>(const int& value)
	{
	}
	template<>
	void GetTemplateValue<float>(const float& value)
	{
	}
	template<>
	void GetTemplateValue<char>(const char& value)
	{
	}
	template<>
	void GetTemplateValue<double>(const double& value)
	{
	}
 
	void GetArgumentValue(...){}
	void GetArgumentValue(const int& value)
	{
	}
	void GetArgumentValue(const float& value)
	{
	}
	void GetArgumentValue(const char& value)
	{
	}
};
 
class Deriv2 : public Base
{
public:
    Deriv2() : Base( indice_par_type<list_types, Deriv2>::VAL )
    {
    }
    template<class T> void GetTemplateValue(const T& value){}
    void GetArgumentValue(...){}
};
