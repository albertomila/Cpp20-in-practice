#pragma once
#include "stdafx.h"

#define named(blockname)    goto blockname; \
                            blockname##_skip: if (0) \
                            blockname:

#define break(blockname)    goto blockname##_skip;

/////////////////////////////////////////////////////
struct test
{
    test (char* s) 
        : str(s) 
    { 
        std::cout << "test::test()::" << str << "\n"; 
    }

    ~test () 
    { 
        std::cout << "~test::" << str << "\n";
    }

	char* str;
};

////////////////////////////////////////////////////
BEGIN_TEST(NamedLoop)
    named (outer) 
        for (int i = 0; i < 10; i++)
        {
            test t1("t1");
            int j = 0;
            named(inner)
                for (test t2("t2"); j < 5; j++)
                {
                    test t3("t3");
                    if (j == 1) break(outer);
                    if (j == 3) break(inner);
                    test t4("t4");
                }
                std::cout << "after inner\n";
        }
END_TEST()

/*

////////////////////////////////////////////////////
int main(void)
{
    goto outer;
    outer_skip: if (0)
        outer:  
        for (int i = 0; i < 10; i++)
        {
            test t1("t1");
            int j = 0;

            goto inner;
            inner_skip: if (0)
                inner: 
                for (test t2("t2"); j < 5; j++)
                {
                    test t3("t3");
                    if (j == 1) break(outer);
                    if (j == 3) break(inner);
                    test t4("t4");
                }
                std::cout << "after inner\n";
        }
        return 0;
}

*/