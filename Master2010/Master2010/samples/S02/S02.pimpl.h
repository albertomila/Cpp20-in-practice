#pragma once
#include "stdafx.h"
using std::cout;
#include "GenSeq.h"
#include "samples/S04/S04.programation.generique.h"


BEGIN_TEST(PImpl)
    using std::cout;
    using std::endl;
	using std::cout;
    using std::endl;
    GenSeq gen;
    for (int i = 0; i < 10; ++i)
       cout << gen.prochain() << endl;

	Tableau<int> tab;
	int x = tab[5];

	END_TEST()