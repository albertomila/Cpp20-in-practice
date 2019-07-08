#include "stdafx.h"

#include "samples/1.ManagingThreads/1.HelloWorld.h"
#include "samples/1.ManagingThreads/2.HelloWorldClass.h"
#include "samples/1.ManagingThreads/3.HandleJoinCases.h"
#include "samples/1.ManagingThreads/4.PassingArguments.h"
#include "samples/1.ManagingThreads/5.TransferingOwnership.h"
#include "samples/1.ManagingThreads/5_1.ScopedThread.h"
#include "samples/1.ManagingThreads/6.MultipleThreads.h"

#include "samples/2.SharingData/1.Mutex.h"
#include "samples/2.SharingData/2.ProducerConsumer.h"
#include "samples/2.SharingData/3.ThreadSafeStack.h"
#include "samples/2.SharingData/4.Deadlock.h"
#include "samples/2.SharingData/5.LockHierarchy.h"
#include "samples/2.SharingData/6.UniqueLock.h"
#include "samples/2.SharingData/7.OnceFlag.h"
#include "samples/2.SharingData/8.StaticThreadSafe.h"
#include "samples/2.SharingData/9.Semaphore.h"
#include "samples/2.SharingData/10.AtomicTypes.h"

int main()
{
	//Ex1::Ex1_HelloWorld().Run();
	//Ex2::Ex2_HelloWorldClass().Run();
	//Ex2::Ex2_HelloWorldClass2().Run();
	//Ex2::Ex2_HelloWorldLamda().Run();
	//Ex2::Ex2_HelloWorldClassMethod().Run();
	//Ex3::Ex3_HandleJoinCases().Run();
	//Ex3::Ex3_HandleJoinCases2().Run();
	//Ex3::Ex3_HandleDetach().Run();
	//Ex4::Ex4_PassingArgs().Run();
	//Ex4::Ex4_PassingArgsRef().Run();
	//Ex4::Ex4_PassingArgsMove().Run();
	//Ex5::Ex5_TransferingThreads().Run();
	//Ex5::Ex5_TransferingThreads2().Run();
	//Ex5::Ex5_TransferingThreads3().Run();
	//Ex51::Ex51_ScopedThread().Run();
	//Ex6::Ex6_MultipleThreads().Run();
	//Ex6::Ex6_MultipleThreadsMaxAvailable().Run();

	//Ex7::Ex7_Mutex().Run();
	//Ex8::Ex8_ProducerConsumer().Run();
	//Ex9::Ex9_ThreadSafeStack().Run();
	//Ex10::Ex10_Deadlock().Run();
	Ex11::Ex11_LockHierarchy().Run();
	//Ex12::Ex12_UniqueLock().Run();
	//Ex13::Ex13_OnceFlag().Run();
	//Ex14::Ex14_StaticThreadSafe().Run();
	//Ex15::Ex15_Semaphore().Run();
}