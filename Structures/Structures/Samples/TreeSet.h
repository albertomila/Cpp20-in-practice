#pragma once
#include "stdafx.h"

#include "Samples/TreeBinaryBalanced.h"

template<class T>
class TreeSet : public AVLTree<T>
{
public:
	TreeSet()
	{
	}

	virtual void AddEqual( const TypeValue& value, TNode* parent, TNode** currentNode )
	{
		//nothing on purpose
		//TreeSet doesn't allow repeated values
	}
};