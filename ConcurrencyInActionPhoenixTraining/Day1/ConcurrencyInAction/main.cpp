#include "stdafx.h"

#include "samples/1.ManagingThreads/1.HelloWorld.h"
#include "samples/1.ManagingThreads/2.HelloWorldClass.h"
#include "samples/1.ManagingThreads/3.HandleJoinCases.h"
#include "samples/1.ManagingThreads/4.PassingArguments.h"
#include "samples/1.ManagingThreads/5.TransferingOwnership.h"
#include "samples/1.ManagingThreads/5_1.ScopedThread.h"
#include "samples/1.ManagingThreads/6.MultipleThreads.h"

int main()
{
	//Ex1::Ex1_HelloWorld().Run();
	//Ex2::Ex2_HelloWorldClass().Run();
	//Ex2::Ex2_HelloWorldClass2().Run();
	//Ex2::Ex2_HelloWorldLamda().Run();
	//Ex2::Ex2_HelloWorldClassMethod().Run();
	//Ex3::Ex3_HandleJoinCases().Run();
	//Ex3::Ex3_HandleJoinCases2().Run();
	Ex3::Ex3_HandleDetach().Run();
	//Ex4::Ex4_PassingArgs().Run();
	//Ex4::Ex4_PassingArgsRef().Run();
	//Ex4::Ex4_PassingArgsMove().Run();
	//Ex5::Ex5_TransferingThreads().Run();
	//Ex5::Ex5_TransferingThreads2().Run();
	//Ex5::Ex5_TransferingThreads3().Run();
	//Ex51::Ex51_ScopedThread().Run();
	//Ex6::Ex6_MultipleThreads().Run();
	//Ex6::Ex6_MultipleThreadsMaxAvailable().Run();
}