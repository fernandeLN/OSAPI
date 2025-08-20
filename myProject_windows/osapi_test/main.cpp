#include "CUnit/CUnitCI.h"

void TEST_ThreadName(void);
void TEST_ThreadCreation(void);
void TEST_ThreadJoin(void);
void TEST_ThreadSuspendResume(void);
void TEST_ThreadSleep(void);
void TEST_ThreadPriority(void);
void TEST_ThreadPriorityChange(void);
void TEST_ThreadRunDetailed(void);
void TEST_ThreadStateChecking(void);
void TEST_ThreadSuspendInactive(void);
void TEST_ThreadStackSize(void);
void TEST_Mutex(void);
void TEST_RecursiveMutex(void);
void TEST_MutexDetailed(void);
void TEST_MortalThread(void);

CUNIT_CI_RUN("osapi",
		CUNIT_CI_TEST(TEST_ThreadName),
		CUNIT_CI_TEST(TEST_ThreadCreation),
		CUNIT_CI_TEST(TEST_ThreadJoin),
		CUNIT_CI_TEST(TEST_ThreadSuspendResume),
		CUNIT_CI_TEST(TEST_ThreadSleep),
		CUNIT_CI_TEST(TEST_ThreadPriority),
		CUNIT_CI_TEST(TEST_ThreadPriorityChange),
		CUNIT_CI_TEST(TEST_ThreadRunDetailed),
		CUNIT_CI_TEST(TEST_ThreadStateChecking),
		CUNIT_CI_TEST(TEST_ThreadSuspendInactive),
		CUNIT_CI_TEST(TEST_ThreadStackSize),
		CUNIT_CI_TEST(TEST_Mutex),
		CUNIT_CI_TEST(TEST_RecursiveMutex),
		CUNIT_CI_TEST(TEST_MutexDetailed),
		CUNIT_CI_TEST(TEST_MortalThread)
);
