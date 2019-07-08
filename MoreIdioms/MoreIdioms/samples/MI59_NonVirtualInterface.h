#pragma once
#include "stdafx.h"

class NVI_Base
{
public:
    void Action()  
	{
        DoAction();
    }

private:
    virtual void DoAction() = 0;
};

class NVI : public NVI_Base
{
private:
    virtual void DoAction() override
    {
    }
};

BEGIN_TEST(NonVirtualInterface)
	NVI nvi;
	nvi.Action();
END_TEST()