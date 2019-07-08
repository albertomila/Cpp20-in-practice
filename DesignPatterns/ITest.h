#pragma once

////////////////////////////////////////////
////Base class
////////////////////////////////////////////
class ITest
{
public:
	virtual void Run() = 0;
	virtual ~ITest() {}
};


////////////////////////////////////////////
////Macro Run class
////////////////////////////////////////////
#define BEGIN_TEST(TestName)		\
class TestName : public ITest		\
{									\
public:								\
	virtual ~TestName() {}			\
	virtual void Run() override		\
	{

#define END_TEST()					\
	}								\
};



////////////////////////////////////////////
////Macro Run global method
////////////////////////////////////////////
#define CONCAT(a,b) a ## b

#define START_TEST_FOO(FunctionName)	\
class CONCAT(Test_, FunctionName)		\
{										\
public:									\
	CONCAT(Test_,FunctionName)()		\
	{									\
		g_mainPtr = &FunctionName;		\
	}									\
};										\
CONCAT(Test_,FunctionName) CONCAT(g_,FunctionName);

