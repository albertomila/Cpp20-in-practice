#pragma once
#include "stdafx.h"

template <class Pair>
struct Reverse
{
	typedef typename Pair::second_type first_type;
	typedef typename Pair::first_type  second_type;
	second_type second;
	first_type first;
};

template <class Pair>
struct ReverseRef
{
	typedef typename Pair::second_type first_type;
    typedef typename Pair::first_type  second_type;
    second_type& second;
    first_type& first;
};

template <class Pair>
Reverse<Pair> & mutate(Pair & p)
{
	/*
	Reverse<Pair> rp;
	rp.first = p.second;
	rp.second = p.first;
	*/

    return reinterpret_cast<Reverse<Pair> &>(p);
}


template <class Pair>
ReverseRef<Pair> & mutateRef(Pair & p)
{
	return ReverseRef<Pair>{ p.first, p.second };
}

BEGIN_TEST(ReversePair)
    std::pair<double, int> p(1.34, 5);
    Reverse< std::pair<double, int>  > reversPair = mutate(p);
	ReverseRef< std::pair<double, int>  > reversPairRef = mutateRef(p);

    std::cout << "p.first = " << p.first << ", p.second = "  << p.second << std::endl;
    std::cout << "reversPair.first = " << reversPair.first << ", reversPair.second = "  << reversPair.second << std::endl;
END_TEST()