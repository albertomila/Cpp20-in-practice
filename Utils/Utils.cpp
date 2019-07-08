#include "stdafx.h"
/*#include <samples/Divers/ReturnBuildDestroyFlow.h>
#include <samples/Divers/auto_ptr.h>
#include <samples/Divers/binary.h>
#include <samples/Divers/char_strings.h>
#include <samples/Divers/contructor_desctructor.h>
#include <samples/Divers/explicit.h>
#include <samples/Divers/friend.h>
#include <samples/Divers/generic_traits.h>
#include <samples/Divers/generic_vector.h>
#include <samples/Divers/reference_pointers.h>
#include <samples/Divers/resize_vector.h>
#include <samples/Divers/shared_ptr.h>
#include <samples/Divers/switch.h>
#include <samples/Divers/test.h>
#include <samples/Divers/union.h>
#include <samples/Divers/unique_ptr.h>
#include <samples/Divers/virtual.h>
#include <samples/GenericProg/GenericVector.h>
#include <samples/MetaProg/IsAbstract.h>
#include <samples/Misc/AddressOf.h>
#include <samples/Misc/VirtualTable.h>
#include <samples/Misc/VaridicMember.h>
#include <samples/Misc/NoSTLDebug.h>
#include <samples/mentoring/partial_template.h>
#include <samples/mentoring/PointerToMethod.h>
#include <samples/mentoring/VirtualConstructor.h>
#include <samples/mentoring/AvoidNamespaceDependencies.h>
#include <samples/mentoring/DisableDynamicCast.h>
#include <samples/mentoring/ReturnValueOptimization.h>
#include <samples/Misc/Dijkstra.h>
#include <samples/Misc/AStar.h>
#include <samples/Misc/Test2.h>
#include <samples/Misc/Test3.h>
#include <samples/Misc/Test4.h>
#include <samples/Misc/Test5.h>*/
#include <samples/Misc/TestOmnidrone1.h>
#include <samples/Misc/TestOmnidrone2.h>
#include <samples/Misc/TestOmnidrone3.h>
#include <samples/Misc/TestOmnidrone4.h>
#include <samples/Misc/TestOmnidrone5.h>
#include <samples/Misc/TestOmnidrone6.h>

using namespace std;

int main()
{
	//AutoPtr().Run();
	//Binary().Run();
	//CharStrings().Run();
	//ConstructorFlow().Run();
	//Explicit().Run();
	//Friend().Run();
	//GenericTraits().Run();
	//GenericVector().Run();
	//RefPointers().Run();
	//ResizeVector().Run();
	//ReturnBuildDestroyFlow().Run();
	//SharedPtr().Run();
	//Switch().Run();
	//Union().Run();
	//UnionReinterpretCast().Run();
	//UniquePtr().Run();
	//Virtual().Run();
	//IsAbstract().Run();
	//OffsetOf().Run();
	//VirtualTable().Run();
	//VaridicMember().Run();
	//PartialTemplate().Run();
	//NoSTLDebug().Run();
	//PointerToMethod().Run();
	//VirtualFunctionsConstructor().Run();
	//AvoidNamespaceDependencies().Run();
	//TechnicalTest5().Run();
	//DisableDynamicCast().Run();
	//NamedReturnValueOptimization().Run();
	//Dijkstra().Run();
	//AStar().Run();
	//TechnicalTest2().Run();
	//TechnicalTest3().Run();
	//TechnicalTest4().Run();
	//TestOmnidrone1().Run();
	//TestOmnidrone2().Run();
	//TestOmnidrone3().Run();
	//TestOmnidrone4().Run();
	//TestOmnidrone5().Run();
	TestOmnidrone6().Run();
	return 0;
}


/*
template<class T>
void foo(){}

template<>
void foo<int_<2>>(){}

template<>
void foo<int_<3>>(){}

template<>
void foo<int_<5>>(){}

template<>
void foo<int_<7>>(){}

template<>
void foo<int_<11>>(){}

struct Test
{
static const short x1 = 10;
static const int x2 = 10;
static const long x3 = 10;
static const long long x4 = 10;
static const bool b = true;
static const float c1(){ return 10.0f; };
static const double c2(){ return 10.0; };
static const char d1 = 'A';
static const char* d2()
{
char d[2] = {'A','B'};
return d;
};
static const char* d3() { return "hola"; };
static const char* d4;
};
const char* Test::d4 = "hola";

template< int i >
struct LOOP
{
static inline void EXEC()
{
cout << "A-" << i << " ";
LOOP< i-1 >::EXEC();
cout << "B-" << i << " ";
}
};

template<>
struct LOOP< 0 >
{
static inline void EXEC()
{
cout << "A-" << 0;
cout << "\n";
cout << "B-" << 0;
}
};
#include <typeinfo.h>

#include <vector>
#include <algorithm>
#include "GenericProg\GenericFoncteurs.h"
using std::vector;

#define PROPERTY_W(type,value) void Set##value(const type& val) { value = val; }
#define PROPERTY_R(type,value) type Get##value() { return value; }
#define PROPERTY_RW(type,value) \
PROPERTY_R(type,value)		\
PROPERTY_W(type,value)


class Test1
{
int value_;
int speed_;
int acccel_;
vector<int> v;
public:
PROPERTY_RW(int, value_)
PROPERTY_RW(int, speed_)
PROPERTY_R(int, acccel_)
PROPERTY_W(int, acccel_)
Test1()
{
v.push_back(0);
v.push_back(1);
v.push_back(2);
v.push_back(3);
v.push_back(4);
v.push_back(5);
v.push_back(6);
};
void TestFunc1(const int value)
{
}
bool TestFunc3(const int value)
{
return value == 10;
}
void TestFunc2()
{
std::for_each(
v.begin(),
v.end(),
GenericMethod<Test1,int>(this, &Test1::TestFunc1)
);

std::find_if(
v.begin(),
v.end(),
GenericMethodBool<Test1,int>(this, &Test1::TestFunc3)
);
}
};


template<class T>
void foo(const T& value)
{

}


class EntityTest
{
};
class BaseEventTest
{
public:
typedef BaseEventTest base_type;
int m_value;
BaseEventTest() : m_value(0){}
BaseEventTest(int val) : m_value(val){}
};

class SuperEventTest : public BaseEventTest
{
public:
typedef BaseEventTest base_type;
SuperEventTest(int val) : BaseEventTest(val){}
};

class SuperSuperEventTest : public SuperEventTest
{
public:
typedef SuperEventTest base_type;
SuperSuperEventTest(int val) : SuperEventTest(val){}
};

template<class T>
void OnEventTest(const T* eventTest)
{
if( !meme_type<T, T::base_type>::VAL )
{
OnEventTest<T::base_type>(eventTest);
}
}

template<>
void OnEventTest<BaseEventTest>(const BaseEventTest* eventTest)
{
int x = 0;
x = eventTest->m_value;
}
template<>
void OnEventTest<SuperEventTest>(const SuperEventTest* eventTest)
{
int x = 0;
x = eventTest->m_value;
}
template<>
void OnEventTest<SuperSuperEventTest>(const SuperSuperEventTest* eventTest)
{
int x = 0;
x = eventTest->m_value;
}

class ContainerEvents
{
public:
std::vector<EntityTest> m_entities;
typedef std::vector<EntityTest>::iterator Itt;

ContainerEvents()
{
m_entities.push_back(EntityTest());
m_entities.push_back(EntityTest());
m_entities.push_back(EntityTest());
m_entities.push_back(EntityTest());
m_entities.push_back(EntityTest());
}

template<class T>
void DispatchEvent( const T* eventTest )
{
static_assert_< std::is_base_of<BaseEventTest, T>::value >();

const BaseEventTest* base = eventTest;

for(Itt itt = m_entities.begin(); itt != m_entities.end(); ++itt )
{
OnEventTest<T>( eventTest );
//OnEventTest( eventTest );
//OnEventTest<T>( static_cast<const T*>(base) );
}
}


//typedef typename static_if_else< std::is_base_of<BaseEventTest, T>::value,
//				BaseEventTest,
//				static_assert_<false>
//>::type type_value;

};*/
/*
class BaseClass{};*/
/*
class BBase
{
};
template<class T>
class CBase : public BBase
{
public:
typedef T type_value;
};
class CDerived : public CBase<CDerived>
{
public:
typedef CBase<CDerived>::type_value type_value;
};
*/
/*
template <class T>
struct vect
{
T getA1()
{
return T();
}
};

template <template<class> class Object, class T>
void func1(Object<T> &o1, Object<T> &o2)
{
T x = o1.getA1();
x += 2;
cout << x << endl;
}
*/
/*


template <template<class> class Object, class T>
void func1(Object<T>* o1)
{

}
*/
/*
struct CBase
{
Clonable* clonable_;

void SetClonable( Clonable* clonable )
{
clonable_ = clonable;
}

template<class T>
void Call()
{

}

virtual void implementation() = 0;
};

template <class T>
struct BBase : public CBase
{
typedef T type_value;

void implementation()
{
// ...
static_cast<type_value*>(this)->GetValue<type_value>();
// ...
}
};

struct Derived : BBase<Derived>
{
template<class T>
void GetValue()
{
}
};
*/

/*
template<class T>
void StaticFoo( CollectableInventory& collectableInventory )
{
CollectableInventory::TTypeContainer hashmap = collectableInventory.hashmap_;
}

template<>
void StaticFoo<CollectableInventory>( CollectableInventory& collectableInventory )
{
CollectableInventory::TTypeContainer hashmap = collectableInventory.hashmap_;
}



struct OperatorTest
{
int value_;
OperatorTest()
:value_(0)
{
}

OperatorTest( const int val )
:value_( val )
{
}

OperatorTest( const OperatorTest& val )
:value_( val.value_ )
{
}

~OperatorTest()
{
}

void operator == ( const OperatorTest& val )
{
value_ = val.value_;
}
};

void TestOverride()
{
}

void TestOverride( OperatorTest )
{
}


template<class T>
class Traits
{
public:
typedef T TValue;
typedef vector<TValue> TListValue;

void PushValue( const TValue& value )
{
m_valueList.push_back( value );
}

const TListValue& GetValues() const{ return m_valueList; }

TListValue m_valueList;
};

template< class T, class U, class V >
struct TraitsDispatcher
{
static bool IsValid( const V& value )
{
return false;
}
};

template< template<class> class T >
struct TraitsDispatcher<  Traits<T>
, typename Traits<T>::TListValue
, typename Traits<T>::TValue >
{
static bool IsValid(  const typename Traits<T>::TValue& value )
{
return value.length() > 0;
}
};

template<>
struct TraitsDispatcher<  Traits<string>
, Traits<string>::TListValue
, Traits<string>::TValue >
{
static bool IsValid(  const Traits<string>::TValue& value )
{
return value.length() > 0;
}
};

template<class T>
void FooTraitTest( const T& value )
{
TraitsDispatcher<T>( value );
}
*/



/*
int main()
{
	Traits<string> traitsTest;
	traitsTest.PushValue( "test1" );
	traitsTest.PushValue( "test2" );
	traitsTest.PushValue( "test3" );
	traitsTest.PushValue( "test4" );

	for( Traits<string>::TListValue::const_iterator it = traitsTest.GetValues().begin(),
	end = traitsTest.GetValues().end();
	it != end;
	++it
	)
	{
	TraitsDispatcher< Traits<string>
	, Traits<string>::TListValue
	, Traits<string>::TValue  >::IsValid( *it );

	}

	OperatorTest optest( 5 );
	TestOverride( optest );

	StaticFoo<CollectableInventory>( collectableInventory );

	genvector v1;
	v1.push_back(3.0f);
	v1.push_back(5);
	v1.push_back('C');

	Deriv* deriv1= new Deriv();
	deriv1->DispatchValue( v1[0].GetCapsule() );
	//Dispatcher( deriv1, v1[2].GetCapsule() );


	Deriv2* deriv2= new Deriv2();
	deriv2->DispatchValue( v1[2].GetCapsule() );
	//Dispatcher( deriv2, v1[0].GetCapsule() );

	return 0;
}	
*/
/*
Whatever w(3);
v1.push_back(w);

Whatever w1(4.0f);
v1.push_back(w1);
*/
/*

Clonable* c = v1[0].GetCapsule();
Capsule<int>* caps = v1[0].GetCapsule<int>();
func1(caps);*/
//v1.push_back(false);
//v1.push_back(3.0f);
//v1.push_back('c');

//	TestType testType;
//	v1[0].GetCapsule()->GetType<TestType>(testType);

/*
std::vector<Whatever> v1;
//v1.push_back(true);
v1.push_back(3);


//v1.push_back(3.0f);
//v1.push_back('c');



CBase* derived = new Derived();
derived->implementation();



ContainerEvents containerEvents;

BaseEventTest* baseEventTest = new BaseEventTest(100);
SuperEventTest* superEventTest = new SuperEventTest(200);
SuperSuperEventTest* superSuperEventTest = new SuperSuperEventTest(300);

//BaseClass* baseClassTest = new BaseClass();
//containerEvents.DispatchEvent<BaseClass>(baseClassTest);

containerEvents.DispatchEvent<BaseEventTest>(baseEventTest);
containerEvents.DispatchEvent<SuperEventTest>(superEventTest);
containerEvents.DispatchEvent<SuperSuperEventTest>(superSuperEventTest);


foo(4);
foo(4.1f);
foo('C');
foo("CCC");


Whatever w = v1[0];
Clonable* clon = w.GetCapsule();
//	Capsule<int>* caps1 = w.GetCapsule<int>();

/*
Whatever w = v1[0];
Clonable* c = w.GetCapsule();
*/


//Test1* t1 = new Test1();
//t1->TestFunc2();
/*
vector<Test1> v;
v.push_back(Test1());
v.push_back(Test1());
v.push_back(Test1());
v.push_back(Test1());
v.push_back(Test1());


std::for_each(
v.begin(),
v.end(),
GenericFunction<Test1>(&Test1::TestFunc1)
);
*/
/*
int pows = POW<2,4>::VAL;

int digits1 = NumberOfDigits<0>::VAL;
int digits2 = NumberOfDigits<1>::VAL;
int digits6 = NumberOfDigits<10>::VAL;

float f1 = float_<11,2>::VAL();
float f2 = float_<242,1>::VAL();
float f3 = float_<3034,2>::VAL();
float f4 = float_<64093,3>::VAL();
LOOP<8>::EXEC();

typedef type_list<
int_<2>, type_list<
int_<3>, type_list<
int_<5>, type_list<
int_<7>, type_list<
int_<11>, Vide
>
>
>
>
> vals;

const int x = 0;
foo<type_par_indice<vals,x>::type>();

int n = type_par_indice<vals,x>::type::VAL;
*/




/*
class T_{};
class F_{};

template<bool b>
struct GetBool
{
typedef T_ type_value;
};

template<>
struct GetBool<false>
{
typedef F_ type_value;
};
template<class T>
void OnEventTest(const T* eventTest,T_)
{
}
template<class T>
void OnEventTest(const T* eventTest,F_)
{
typedef GetBool<meme_type<T, T::base_type>::VAL>::type_value type;
OnEventTest<T::base_type>(eventTest, type());
}
template<class T>
void OnEventTest(const T* eventTest)
{
typedef GetBool<meme_type<T, T::base_type>::VAL>::type_value type;
OnEventTest<T::base_type>(eventTest, type());
}
*/

