#include "stdafx.h"

#include "PhoenixTraining/1.ManagingThreads/1.HelloWorld.h"
#include "PhoenixTraining/1.ManagingThreads/2.HelloWorldClass.h"
#include "PhoenixTraining/1.ManagingThreads/3.HandleJoinCases.h"
#include "PhoenixTraining/1.ManagingThreads/4.PassingArguments.h"
#include "PhoenixTraining/1.ManagingThreads/5.TransferingOwnership.h"
#include "PhoenixTraining/1.ManagingThreads/5_1.ScopedThread.h"
#include "PhoenixTraining/1.ManagingThreads/6.MultipleThreads.h"

#include "PhoenixTraining/2.SharingData/1.Mutex.h"
#include "PhoenixTraining/2.SharingData/2.ProducerConsumer.h"
#include "PhoenixTraining/2.SharingData/3.ThreadSafeStack.h"
#include "PhoenixTraining/2.SharingData/4.Deadlock.h"
#include "PhoenixTraining/2.SharingData/5.LockHierarchy.h"
#include "PhoenixTraining/2.SharingData/6.UniqueLock.h"
#include "PhoenixTraining/2.SharingData/7.OnceFlag.h"
#include "PhoenixTraining/2.SharingData/8.StaticThreadSafe.h"
#include "PhoenixTraining/2.SharingData/9.Semaphore.h"
#include "PhoenixTraining/2.SharingData/10.AtomicTypes.h"

#include "PhoenixTraining/3.Synchronizing/1.ConditionVariable.h"
#include "PhoenixTraining/3.Synchronizing/2.ThreadsafeQueue.h"
#include "PhoenixTraining/3.Synchronizing/3.Future.h"
#include "PhoenixTraining/3.Synchronizing/4.PackageTask.h"
#include "PhoenixTraining/3.Synchronizing/5.Promise.h"
#include "PhoenixTraining/3.Synchronizing/6.SharedFuture.h"

#include "PhoenixTraining/4.SafeDataStructures/ThreadSafeList.h"
#include "PhoenixTraining/4.SafeDataStructures/ThreadSafeLookupTable.h"
#include "PhoenixTraining/4.SafeDataStructures/ThreadSafeQueue.h"
#include "PhoenixTraining/4.SafeDataStructures/ThreadSafeStack.h"

#include "PhoenixTraining/5.ThreadFindAlgorithms/ParallelFind.h"
#include "PhoenixTraining/5.ThreadFindAlgorithms/ParallelForEach.h"
#include "PhoenixTraining/5.ThreadFindAlgorithms/ParallelQuickSort.h"

int main()
{
	Ex1::Ex1_HelloWorld().Run();
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
	//Ex11::Ex11_LockHierarchy().Run();
	//Ex12::Ex12_UniqueLock().Run();
	//Ex13::Ex13_OnceFlag().Run();
	//Ex14::Ex14_StaticThreadSafe().Run();
	//Ex15::Ex15_Semaphore().Run();
	
	//Ex16::Ex16_ConditionVariable().Run();
	//Ex17::Ex17_ThreadSafeQueue().Run();
	//Ex18::Ex18_Future().Run();
	//Ex19::Ex19_PackageTask().Run();
	//Ex20::Ex20_Promise().Run();
	//Ex21::Ex21_SharedFuture().Run();

	//Ex22::Ex22_AtomicTypes_Flag().Run();
	//Ex22::Ex22_AtomicTypes_Bool().Run();
	//Ex22::Ex22_AtomicTypes_Class().Run();

	//Ex23::Ex23_ThreadSafeList().Run();
	//Ex24::Ex24_ThreadSafeLookupTable().Run();
	//Ex25::Ex25_ThreadSafeQueue().Run();
	//Ex26::Ex26_ThreadSafeStack().Run();

	//Ex27::Ex27_ParallelFind().Run();
	//Ex28::Ex28_ParallelForEach().Run();
	//Ex29::Ex29_ParallelQuickSort().Run();
}