#pragma once
#include "stdafx.h"

#include "Samples/TreeBinaryBalanced.h"

template<class T, class V>
class TreeMultiMap : public AVLTree< std::pair< T, V >
									, PairTypeOperations<T,V> >
{
public:
	typedef T TypeKey;
	typedef V TypeValue;
	typedef std::pair< TypeKey, TypeValue > TypeValuePair;
	typedef AVLTree< TypeValuePair, PairTypeOperations<TypeKey,TypeValue> > super;

public:
	TreeMultiMap()
	{
	}

	virtual void Push( const TypeValuePair& pairValue ) override
	{
		super::Push( pairValue );
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

	void DeleteAll( const TypeKey& key )
	{
		TypeValuePair pairValue( key, TypeValue() );
		while( Exist( pairValue ) )
		{
			super::Delete( pairValue );
		}
	}
};