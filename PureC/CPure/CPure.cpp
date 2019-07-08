// CPure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>

#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

// Base class
/*
struct VTable;

typedef struct Base 
{
	VTable *vtable;
	int x;
} 
Base;

typedef struct VTable
{
	int(*func)(struct Base* _this);
}
VTable;

int base_func(Base *_this) { return _this->vtable->func(_this); }

Base *base_new(VTable* vtable, int size, int x)
{
	Base *ret = (Base*)calloc(1, size);
	ret->vtable = vtable;
	ret->x = x;
	return ret;
}

typedef struct B {
	Base base;
	int y;
} B;

int b_func(Base *base) 
{
	B*_this = (B*)base;
	return base->x * 20 + _this->y;
}

static VTable B_VTable;

B *b_new(int x)
{
	B *ret = (B*)base_new(&B_VTable, sizeof(B), x);
	ret->y = x * 2;
	return ret;
}

//#define VTABLE(T)		\
//typedef struct V_table		\
//{		\
//	T * (*derived)();		\
//}
//
//#define CLASS(T)		\
//typedef struct CBase	 \
//{						\
//	VTABLE(T)* vtable;	\
//}						\
//CBase;		\
//
//
//typedef struct CDerived 
//{
//}
//CDerived;

struct VTableBase;

#define DYNAMIC_CAST(T, obj) \
(T*)obj->_derived;

#define VIRTUAL()


typedef struct CBase
{
	int _data;

	void (*Method1)(CBase* _this);
	void (*Method2)(CBase* _this);
	void (*Method3)(CBase* _this);

	void(*VirtualMethod1)(CBase* _this);
	void* _VirtualMethod1 = NULL;
	void(*DoVirtualMethod1)(CBase* _this);

	void* _derived;
} 
CBase;

void CBase_Method1(CBase* _this)
{
}
void CBase_Method2(CBase* _this)
{
}
void CBase_Method3(CBase* _this)
{
}

void CBase_VirtualMethod1(CBase* _this)
{
}

struct VTABLE
{
	void(*VirtualMethod1)(CBase* _this);
};

void VTABLE_VirtualMethod1(CBase* base, VTABLE* vtable)
{
	if (vtable->VirtualMethod1 != NULL)
	{
		vtable->VirtualMethod1(base);
	}
	else
	{
		base->VirtualMethod1(base);
	}
}

CBase* NewBase()
{
	CBase* baseInstance = (CBase*)calloc(1, sizeof(CBase));
	baseInstance->Method1 = CBase_Method1;
	baseInstance->Method2 = CBase_Method1;
	baseInstance->Method3 = CBase_Method1;
	baseInstance->VirtualMethod1 = CBase_VirtualMethod1;
	return baseInstance;
}


typedef struct CDerived
{
	CBase* _parent;
	CBase* (*GetParent)(CDerived* _this);
	void(*Method1)(CDerived* _this);
	void(*Method2)(CDerived* _this);
	void(*Method3)(CDerived* _this);
}
CDerived;

void CDerived_Method1(CDerived* _this)
{
}
void CDerived_Method2(CDerived* _this)
{
}
void CDerived_Method3(CDerived* _this)
{
}
void CDerived_VirtualMethod1(CBase* _this)
{
}

CBase* CDerived_GetParent(CDerived* _this)
{
	return _this->_parent;
}


#define STRINGUIZE(a,b) a##b

CDerived* NewDerived()
{
	CBase* derivedBase = NewBase();

	CDerived* derivedInstance = (CDerived*)calloc(1, sizeof(CDerived));
	derivedInstance->_parent = derivedBase;
	derivedInstance->_parent->_derived = derivedInstance;

	derivedInstance->Method1 = CDerived_Method1;
	derivedInstance->Method2 = CDerived_Method2;
	derivedInstance->Method3 = CDerived_Method3;
	derivedInstance->GetParent = CDerived_GetParent;
	derivedBase->_VirtualMethod1 = CDerived_VirtualMethod1;

	return derivedInstance;
}


#define VIRTUAL_CALL(METHOD, T, OBJ)\
{\
	void* virtualMethodBase = OBJ->STRINGUIZE(_, METHOD);\
	if(virtualMethodBase == NULL)\
	{\
		OBJ->METHOD(OBJ);\
	}\
	else\
	{\
		typedef void(*VM)(T* _this);\
		VM& vm = (VM&)virtualMethodBase;\
		vm(OBJ);\
	}\
}


int main()
{
	CBase* base = NewBase();
	base->Method1(base);
	base->Method2(base);
	base->Method3(base);

	CDerived* derived = NewDerived();
	derived->Method1(derived);
	derived->Method2(derived);
	derived->Method3(derived);
	CBase* derivedBase = derived->GetParent(derived);
	CDerived* newDerived = DYNAMIC_CAST(CDerived, derivedBase);
	derivedBase->VirtualMethod1(derivedBase);

	VIRTUAL_CALL(VirtualMethod1, CBase, derivedBase);

	B_VTable.func = b_func;

	Base *o2 = (Base*)b_new(1);
	printf("%d\n", base_func(o2));
	free(o2);
}

*/

typedef struct GenericVTable
{
	std::unordered_map<void*, void*> _methods;
}
GenericVTable;



#define DECLARE_VIRTUAL_CALL_1(METHOD, TDerived, ARG_1) \
void(*METHOD)(TDerived* _this, ARGS); \
void(*STRINGUIZE(Virtual_,METHOD))(void* thisPtr, ARG_1);

#define DECLARE_VIRTUAL_CALL_2(METHOD, TDerived, ARG_1, ARG_2) \
void(*METHOD)(TDerived* _this, ARG_1, ARG_2); \
void(*STRINGUIZE(Virtual_,METHOD))(void* thisPtr, ARG_1, ARG_2);

#define DECLARE_VIRTUAL_CALL_3(METHOD, TDerived, ARG_1, ARG_2, ARG_3) \
void(*METHOD)(TDerived* _this, ARG_1, ARG_2, ARG_3); \
void(*STRINGUIZE(Virtual_,METHOD))(void* thisPtr, ARG_1, ARG_2, ARG_3);

#define STRINGUIZE(a,b) a##b
#define STRINGUIZE_3(a,b,c) a##b##c
#define STRINGUIZE_4(a,b,c,d) a##b##c##d


#define IMPLEMENT_VIRTUAL_CALL_1(METHOD, TDerived, TARG_1)\
void STRINGUIZE_4(Virtual_,TDerived,_,METHOD)(void* thisPtr, TARG_1 arg_1)\
{\
	TDerived* _this = (TDerived*)thisPtr;\
	if (_this->_vtable == NULL)\
	{\
		STRINGUIZE_3(TDerived,_,METHOD)(_this, arg_1);\
	}\
	else\
	{\
		_this->_vtable->METHOD(_this->_vtable->_derived, arg_1);\
	}\
}

#define IMPLEMENT_VIRTUAL_CALL_2(METHOD, TDerived, TARG_1, TARG_2)\
void STRINGUIZE_4(Virtual_,TDerived,_,METHOD)(void* thisPtr,TARG_1 arg_1, TARG_2 arg_2)\
{\
	TDerived* _this = (TDerived*)thisPtr;\
	if (_this->_vtable == NULL)\
	{\
		STRINGUIZE_3(TDerived,_,METHOD)(_this, arg_1, arg_2);\
	}\
	else\
	{\
		_this->_vtable->METHOD(_this->_vtable->_derived, arg_1, arg_2);\
	}\
}

#define IMPLEMENT_VIRTUAL_CALL_3(METHOD, TDerived, TARG_1, TARG_2, TARG_3)\
void STRINGUIZE_4(Virtual_,TDerived,_,METHOD)(void* thisPtr,TARG_1 arg_1, TARG_2 arg_2, TARG_3 arg_3)\
{\
	TDerived* _this = (TDerived*)thisPtr;\
	if (_this->vtable == NULL)\
	{\
		STRINGUIZE_3(TDerived,_,METHOD)(_this, arg_1, arg_2, arg_3);\
	}\
	else\
	{\
		_this->_vtable->METHOD(_this->_vtable->_derived, arg_1, arg_2, arg_3);\
	}\
}

typedef struct VTable
{
	void* _derived;
	void(*VirtualMethod1)(void* _this, int var, float var2);
}
VTable;

typedef struct CBase
{
	CBase* _parent;
	VTable* _vtable;

	int _data;

	void(*Method1)(CBase* _this);
	void(*Method2)(CBase* _this);
	void(*Method3)(CBase* _this);
	//void(*VirtualMethod1)(CBase* _this, int var);
	//void(*Virtual_VirtualMethod1)(void* thisPtr, int var);
	DECLARE_VIRTUAL_CALL_2(VirtualMethod1,CBase,int,float);
}
CBase;

void CBase_Method1(CBase* _this)
{
}
void CBase_Method2(CBase* _this)
{
}
void CBase_Method3(CBase* _this)
{
}
void CBase_VirtualMethod1(CBase* _this, int var, float var2)
{
}
IMPLEMENT_VIRTUAL_CALL_2(VirtualMethod1,CBase, int, float);

/*
void Virtual_CBase_VirtualMethod1(void* thisPtr, int var, float arg2)
{
	CBase* _this = (CBase*)thisPtr;
	if (_this->vtable == NULL)
	{
		CBase_VirtualMethod1(_this, var, arg2);
	}
	else
	{
		_this->vtable->func(_this->_derived, var, arg2);
	}
}*/

CBase* NewBase()
{
	CBase* baseInstance = (CBase*)calloc(1, sizeof(CBase));
	baseInstance->Method1 = CBase_Method1;
	baseInstance->Method2 = CBase_Method1;
	baseInstance->Method3 = CBase_Method1;
	baseInstance->VirtualMethod1 = CBase_VirtualMethod1;
	baseInstance->Virtual_VirtualMethod1 = Virtual_CBase_VirtualMethod1;
	return baseInstance;
}


typedef struct CDerived
{
	CBase* _parent;
	VTable* _vtable;

	void(*Method1)(CDerived* _this);
	void(*Method2)(CDerived* _this);
	void(*Method3)(CDerived* _this);
	//void(*VirtualMethod1)(CDerived* _this, int var, float var2);
	//void(*Virtual_VirtualMethod1)(void* thisPtr, int var, float var2);
	DECLARE_VIRTUAL_CALL_2(VirtualMethod1, CDerived, int, float);
}
CDerived;

void CDerived_Method1(CDerived* _this)
{
}
void CDerived_Method2(CDerived* _this)
{
}
void CDerived_Method3(CDerived* _this)
{
}

void CDerived_VirtualMethod1(CDerived* _this, int var, float var2)
{
}
IMPLEMENT_VIRTUAL_CALL_2(VirtualMethod1, CDerived, int, float);

/*
void Virtual_CDerived_VirtualMethod1(void* thisPtr, int var, float var2)
{
	CDerived* _this = (CDerived*)thisPtr;
	if (_this->vtable == NULL)
	{
		CDerived_VirtualMethod1(_this, var, var2);
	}
	else
	{
		_this->vtable->func(_this->_derived, var, var2);
	}
}*/

CDerived* NewDerived()
{
	CBase* parent = NewBase();

	CDerived* derivedInstance = (CDerived*)calloc(1, sizeof(CDerived));
	derivedInstance->_parent = parent;
	parent->_vtable = (VTable*)calloc(1, sizeof(VTable));
	parent->_vtable->_derived = derivedInstance;
	parent->_vtable->VirtualMethod1 = Virtual_CDerived_VirtualMethod1;

	derivedInstance->Method1 = CDerived_Method1;
	derivedInstance->Method2 = CDerived_Method2;
	derivedInstance->Method3 = CDerived_Method3;
	derivedInstance->VirtualMethod1 = CDerived_VirtualMethod1;
	derivedInstance->Virtual_VirtualMethod1 = Virtual_CDerived_VirtualMethod1;

	return derivedInstance;
}

int main()
{
	CBase* base = NewBase();
	base->Method1(base);
	base->Method2(base);
	base->Method3(base);

	CBase* derived = NewDerived()->_parent;
	derived->Virtual_VirtualMethod1(derived, 1, 2.0f);
}