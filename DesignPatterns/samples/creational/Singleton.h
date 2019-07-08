#pragma once
#include "stdafx.h"

class Incopiable
{
	Incopiable(const Incopiable &value) {}
	Incopiable& operator = (const Incopiable &value) {}
protected:
	Incopiable() throw() {}
	virtual ~Incopiable() throw() {}
};

template<typename TypeClass>
class Singleton : public Incopiable
{
public:
	static void CreateInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new TypeClass();
		}
		else
		{
			//error
		}
	}

	static void DestroyInstance()
	{
		delete s_instance;
		s_instance = nullptr;
	}

	static inline TypeClass* Get()
	{
		return s_instance;
	}

protected:
	Singleton() {}
	~Singleton() {}

private:
	static TypeClass* s_instance;
};

template< typename TypeClass >
TypeClass* Singleton<TypeClass>::s_instance = nullptr;

class CManagerUnique : public Singleton<CManagerUnique>
{

};


BEGIN_TEST(SingletonTest)
	CManagerUnique::CreateInstance();
	CManagerUnique* instance = CManagerUnique::Get();
	CManagerUnique::DestroyInstance();
END_TEST()