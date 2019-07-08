#pragma once

////////////////////////////////////////////
////Base class
////////////////////////////////////////////
class ITest
{
public:
	virtual void Run() = 0;
	virtual ~ITest(){}
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