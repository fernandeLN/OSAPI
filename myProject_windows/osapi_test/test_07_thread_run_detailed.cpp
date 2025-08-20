#include "CUnit/CUnitCI.h"
#include "osapi.h"

static volatile int testFlag;
static volatile int runFlag = 1;

class TestThread07 : public osapi::Thread
{
public:
	TestThread07() : Thread(0, 0, osapi::JOINABLE) { ; }
private:
	virtual void job() {
		testFlag = 1;
		while(runFlag) {
			sleep(5);
		}
	}
};


/**
Returns the thread count of the current process or -1 in case of failure.
Source: https://stackoverflow.com/questions/3749668/how-to-query-the-thread-count-of-a-process-using-the-regular-windows-c-c-apis
 */
#include <tlhelp32.h>
int GetCurrentThreadCount()
{
	// first determine the id of the current process
	DWORD const  id = GetCurrentProcessId();

	// then get a process list snapshot.
	HANDLE const  snapshot = CreateToolhelp32Snapshot( TH32CS_SNAPALL, 0 );

	// initialize the process entry structure.
	PROCESSENTRY32 entry = { 0 };
	entry.dwSize = sizeof( entry );

	// get the first process info.
	BOOL  ret = true;
	ret = Process32First( snapshot, &entry );
	while( ret && entry.th32ProcessID != id ) {
		ret = Process32Next( snapshot, &entry );
	}
	CloseHandle( snapshot );
	return ret ? entry.cntThreads : -1;
}

void TEST_ThreadRunDetailed(void) {

	printf("Running test 07: detailed thread run\n");
	fflush(stdout);

	// set initial test flag value
	testFlag = 0;
	// create thread
	TestThread07 t;
	// thread should not be running at this point
    CU_ASSERT(false == t.isRunning());
	// get number of threads running in the current Windows process
	int taskCount = GetCurrentThreadCount();
	// run the thread
	CU_ASSERT(true == t.run());
	// this should increase thread count
	CU_ASSERT(taskCount+1 == GetCurrentThreadCount());
	// it shouldn't be possible to run the thread again
	CU_ASSERT(false == t.run());
	// wait a while
	Sleep(10);
	// test result
	CU_ASSERT(1 == testFlag);
	runFlag = 0;
	CU_ASSERT(true == t.join(100));
	// thread should not be running at this point
	CU_ASSERT(false == t.isRunning());
}
