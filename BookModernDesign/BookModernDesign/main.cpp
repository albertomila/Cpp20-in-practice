// BookModernDesign.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <samples/Components/Commands/FunctorTest.h>
#include <samples/Components/Commands/PointerToFunction.h>
#include <samples/Components/Visitor.h>
#include <samples/PolicyDesign/ex1.h>
#include <samples/PolicyDesign/ex2.h>
#include <samples/PolicyDesign/ex3.h>
#include <samples/PolicyDesign/ex4.h>
#include <samples/Techniques/CompileTimeAssert.h>
#include <samples/Techniques/DetectInherit.h>
#include <samples/Techniques/FunctionPartialSpecialization.h>
#include <samples/Techniques/IntegralConstantType.h>
#include <samples/Techniques/LocalClasses.h>
#include <samples/Techniques/TypeToType.h>
#include <samples/Techniques/TypeTraits.h>


int main()
{
	CompileTimeAssert().Run();
	DetectInherit().Run();
	FunctorTest().Run();
	IntegralConstantType().Run();
	LocalClasses().Run();
	PartialSpecialization().Run();
	PointerToFunction().Run();
	PolicyDesign1().Run();
	PolicyDesign2().Run();
	PolicyDesign3().Run();
	PolicyDesign3().Run();
	TypeToType().Run();
	TypeTraits().Run();
	VisitorTest().Run();

    return 0;
}

