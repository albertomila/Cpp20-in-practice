#pragma once
#include "stdafx.h"

#include "Samples/TreeBinaryBalanced.h"
#include "Samples/TreeHelpers.h"

template<class T, class V>
class TreeMap : public AVLTree< std::pair< T, V >
								, PairTypeOperations<T,V> >
{
public:
	typedef T TypeKey;
	typedef V TypeValue;
	typedef std::pair< TypeKey, TypeValue > TypeValuePair;
	typedef AVLTree< TypeValuePair, PairTypeOperations<TypeKey,TypeValue> > super;

public:
	TreeMap()
	{
	}

	virtual void Push( const TypeValuePair& value ) override
	{
		super::Push( value );
	}

	void Push( const TypeKey& key, const TypeValue& value )
	{
		TypeValuePair pairValue( key, value );
		super::Push( pairValue );
	}

	void Delete( const TypeKey& key )
	{
		TypeValuePair pairValue( key, TypeValue() );
		super::Delete( pairValue );
	}

	virtual void AddEqual( const TypeValuePair& value, TNode* parent, TNode** currentNode )
	{
		(*currentNode)->m_value.second = value.second;
	}

	TypeValue& operator[]( const TypeKey& key ) 
	{
		return Get( key );
	}

	TypeValue& Get( const TypeKey& key )
	{
		TypeValuePair pairValue( key, TypeValue() );
		if( Exist( pairValue ) )
		{
			return GetInternal( pairValue, m_root );
		}
		else
		{
			Push( pairValue );
			return GetInternal( pairValue, m_root );
		}
	}

private:
	TypeValue& GetInternal( TypeValuePair& value, TNode* currentNode )
	{
		if(  super::TTypeOperations::IsLess( value, currentNode->m_value ) ) //currentNode->m_value > value
		{
			return GetInternal( value, currentNode->m_left );
		}
		else if(  super::TTypeOperations::IsLess( currentNode->m_value, value) ) //currentNode->m_value < value
		{
			return GetInternal( value, currentNode->m_right );
		}
		else //equal, currentNode->m_value == value
		{
			return currentNode->m_value.second;
		}
	}
};