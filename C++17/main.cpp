
#include "stdafx.h"
#include "Samples/AttributeDeprecated.h"
#include "Samples/AttributeFallthroughSwitch.h"
#include "Samples/AttributeNoDiscart.h"
#include "Samples/AttributesUnkonwn.h"
#include "Samples/AttributeUnused.h"
#include "Samples/AutoTupleReturn.h"
#include "Samples/BaseClassAggergateInitialization.h"
#include "Samples/ChainedNamespaces.h"
#include "Samples/ConstexprInLambda.h"
#include "Samples/EnumListInitialization.h"
#include "Samples/HasInclude.h"
#include "Samples/IfInConstExpr.h"
#include "Samples/InitStatemensIfAndSwitch.h"
#include "Samples/InlineData.h"
#include "Samples/LambdaThisImplicitCaptured.h"
#include "Samples/MoreFeatures.h"
#include "Samples/PackExpansionsInUsing.h"
#include "Samples/StaticAssertNoDescription.h"
#include "Samples/TemplateDeductionForClasses.h"
#include "Samples/TemplateDeductionNonType.h"
#include "Samples/TemplatePointers.h"
#include "Samples/TemplateVariadicCompactOperations.h"
#include "Samples/UncaughtExceptions.h"
#include "Samples/TypenameInTemplateTemplate.h"


int main()
{
	AttributeDeprecated().Run();
	AttributeFallthroughSwitch().Run();
	AttributeNoDiscart().Run();
	AttributesUnkonwn().Run();
	AttributeUnused().Run();
	AutoTupleReturn().Run();
	BaseClassAggergateInitialization().Run();
	ChainedNamespaces().Run();
	ConstexprInLambda().Run();
	EnumListInitialization().Run();
	HasInclude().Run();
	IfInConstExpr().Run();
	InitStatemensIfAndSwitch().Run();
	InlineData().Run();
	LambdaThisImplicitCaptured().Run();
	MoreFeatures().Run();
	PackExpansionsInUsing().Run();
	StaticAssertNoDescription().Run();
	TemplateDeductionForClasses().Run();
	TemplateDeductionNonType().Run();
	TemplatePointers().Run();
	TemplateVariadicCompactOperations().Run();
	UncaughtExceptions().Run();
	TypenameInTemplateTemplate().Run();

	return 0;
}