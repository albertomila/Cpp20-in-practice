#include "stdafx.h"
#include <typeinfo>

namespace nsOffsetOf
{
	struct SData
	{
		int _member1;
		char _member2;
		char _member3;
		int64_t _member4;
	};
}

template<class T, class M >
int GetAddress(T& obj, M &objMember)
{
	void* objPtr = &obj;
	void* objMemberPtr = &objMember;

	std::size_t addressObjPtr = reinterpret_cast<std::size_t>(objPtr);
	std::size_t addressObjMemberPtr = reinterpret_cast<std::size_t>(objMemberPtr);

	int diffAddress = addressObjMemberPtr - addressObjPtr;
	return diffAddress;
}


#define OFFSET_OF_V1(obj, member, offset_out)		\
{													\
	size_t addressObj = reinterpret_cast<size_t>(&(*obj));			\
	void* memberPtr = &(obj->member);			\
	size_t addressMember = reinterpret_cast<size_t>(memberPtr);	\
	offset_out = addressMember - addressObj;		\
};

#define OFFSET_OF_V2(obj, member, offset_out)		\
{													\
	size_t addressObj = reinterpret_cast<size_t>(&(*obj));			\
	void* memberPtr = &member;					\
	size_t addressMember = reinterpret_cast<size_t>(memberPtr);	\
	offset_out = addressMember - addressObj;		\
};

#define OFFSET_OF_V3(TypeObj, member, offset_out)		\
{														\
	TypeObj* obj = nullptr;								\
	size_t addressObj = reinterpret_cast<size_t>(&(*obj));			\
	void* memberPtr = &(obj->member);				\
	size_t addressMember = reinterpret_cast<size_t>(memberPtr);	\
	offset_out = addressMember - addressObj;			\
};

#define OFFSET_OF_V4(TypeObj, Member)		\
	(size_t)&(((TypeObj*)nullptr)->Member);
/*
TypeObj* obj = nullptr;								\
void* memberAddress = &(obj->Member);				\
size_t addressMember = (size_t)memberAddress;		\
offset_out = addressMember - 0;			\

TypeObj* obj = nullptr;								\
void* memberAddress = &(obj->Member);				\
offset_out = (size_t)memberAddress;		\

TypeObj* obj = nullptr;								\
offset_out = (size_t)&(obj->Member);		\

offset_out = (size_t)&(((TypeObj*)nullptr)->Member);		\
*/


template<class TMember>
size_t GetOffsetT_V1(TMember& member)
{
	TMember* memberPtr = &member;
	void* memberVoidPtr = memberPtr;
	size_t offset = reinterpret_cast<size_t>(memberVoidPtr);

	return offset;
}

template<class T, class TMember>
size_t GetOffsetT_V2(TMember T::*member)
{
	T* obj = nullptr;
	TMember* memberPtr = &(obj->*member);
	void* memberVoidPtr = memberPtr;
	size_t offset = reinterpret_cast<size_t>(memberVoidPtr);

	return offset;
}

template<class T, typename TMemberPtr, TMemberPtr memberPtr>
size_t GetOffsetT_V3()
{
	T* obj = nullptr;
	void* memberVoidPtr = &(obj->*memberPtr);
	size_t offset = reinterpret_cast<size_t>(memberVoidPtr);

	return offset;
}

#define GET_TYPE( TMember ) \
	decltype(&TMember), &TMember


template<class T, typename TMember, TMember member>
inline size_t GetOffsetT()
{
	return reinterpret_cast<size_t>(&(((T*)nullptr)->*member));
}

#define GET_OFFSET(T, TMember)				\
	GetOffsetT<T, GET_TYPE(T::TMember)>();


template <typename T, typename M> 
M get_member_type(M T::*);

template <typename T, typename M> 
T get_class_type(M T::*);


template<class T>
struct GetMemberType
{
	using TMember = decltype(T);
};

template 
<
	typename T,
	typename R,
	R T::*M
>
std::size_t offset_of()
{
	return reinterpret_cast<std::size_t>(&(((T*)nullptr)->*M));
}

#define OFFSET_OF(m)  \
	offset_of\
	<\
		  decltype(get_class_type(m))\
		, decltype(get_member_type(m))\
		, m\
	>()

BEGIN_TEST(OffsetOf)
	using namespace nsOffsetOf;

	SData* data = nullptr;

	size_t offsetof = OFFSET_OF(&SData::_member1);


	size_t offs1(0);
	OFFSET_OF_V1(data, _member2, offs1);

	size_t offs2(0);
	OFFSET_OF_V2(data, data->_member2, offs2);

	size_t offs3(0);
	OFFSET_OF_V3(SData, _member2, offs3);

	size_t offset41 = OFFSET_OF_V4(SData, _member1); //offset
	size_t offset42 = OFFSET_OF_V4(SData, _member2);
	size_t offset43 = OFFSET_OF_V4(SData, _member3);
	size_t offset44 = OFFSET_OF_V4(SData, _member4);

	int offset5 = GetOffsetT_V1(data->_member2);
	int offset6 = GetOffsetT_V2<SData>(&SData::_member2);
	int offset7 = GetOffsetT_V3<SData, decltype(&SData::_member2), &SData::_member2>();
	int offset8 = GetOffsetT_V3<SData, GET_TYPE(SData::_member2)>();

	int address = GetAddress(data, data->_member1);
	address = GetAddress(data, data->_member2);
	address = GetAddress(data, data->_member3);
	address = GetAddress(data, data->_member4);


	size_t offset51 = GET_OFFSET(SData, _member1);
	size_t offset52 = GET_OFFSET(SData, _member2);
	size_t offset53 = GET_OFFSET(SData, _member3);
	size_t offset54 = GET_OFFSET(SData, _member4);
	

	size_t offset61 = GetOffsetT_V3<SData, GET_TYPE(SData::_member1)>();
	size_t offset62 = GetOffsetT_V3<SData, GET_TYPE(SData::_member2)>();
	size_t offset63 = GetOffsetT_V3<SData, GET_TYPE(SData::_member3)>();
	size_t offset64 = GetOffsetT_V3<SData, GET_TYPE(SData::_member4)>();
	
	size_t of = GetOffsetT<SData, GET_TYPE(SData::_member2)>();


	SData* dataPtr = nullptr;
	void* memberAddress = &(dataPtr)->_member2;
	size_t offset = (size_t)memberAddress;
	size_t offset2 = (             
						(size_t)&    
								(   
									((SData*)0)->_member2     
								)                        
					);

	int off = offsetof(SData, _member1);

END_TEST()