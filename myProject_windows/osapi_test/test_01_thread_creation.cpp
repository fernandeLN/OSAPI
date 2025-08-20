#include "CUnit/CUnitCI.h"
#include "osapi.h"

static volatile int testFlag;

class TestThread1 : public osapi::Thread
{
public:
	TestThread1() : Thread(0, 0, osapi::NOT_JOINABLE) { ; }
private:
	virtual void job() {
		testFlag = 1;
	}
};

void TEST_ThreadCreation(void) {

	printf("Running test 1: thread creation\n");
	fflush(stdout);
		
	// set initial test flag value
	testFlag = 0;
	// create thread
	TestThread1 t;
	// run the thread
	CU_ASSERT(true == t.run());
	// wait a while
	Sleep(1000);
	// test result
	CU_ASSERT(1 == testFlag);
}
