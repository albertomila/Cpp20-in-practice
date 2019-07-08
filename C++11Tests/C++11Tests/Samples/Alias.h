// C++11Tests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <unordered_map>

template<typename Key, typename Data>                           // MyAllocList<T>
using MyHashMap_alias = std::unordered_map<Key, Data>;  // is synonym for
                                               // std::list<T,
                                               //   MyAlloc<T>>

template<typename Key, typename Data>                               // MyAllocList<T>::type
struct MyHashMap_typedef
{                     // is synonym for
    typedef std::unordered_map<Key, Data> type; // std::list<T,
};                                       //   MyAlloc<T>>

BEGIN_TEST(TestAlias)
    MyHashMap_alias<int, int> HashMapAlias;                        // client code

    MyHashMap_typedef<int, int>::type HashMapTypedef;            // client code
END_TEST()