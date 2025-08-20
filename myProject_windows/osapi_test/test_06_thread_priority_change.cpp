#include "CUnit/CUnitCI.h"
#include "osapi.h"

static volatile int runFlag = 1;

static volatile int osapiInitialPriorityA = -999;
static volatile int osapiInitialPriorityB = -999;
static volatile int priorityDifferenceA = 0;
static volatile int priorityDifferenceB = 0;
	
class TestThread06A : public osapi::Thread
{
public:
    TestThread06A() : Thread(0, 0, osapi::JOINABLE) { run(); }
private:
    virtual void job() {
	    // get initial priority using osapi
		osapiInitialPriorityA = getPriority();
		// get initial priority using Windows
		unsigned int p1 = GetThreadPriority(GetCurrentThread());
		// change priority using osapi
		setPriority(1);
		// get new priority using Windows
		unsigned int p2 = GetThreadPriority(GetCurrentThread());
		// calculate difference
		priorityDifferenceA = p2 - p1;
		while (runFlag) {
			sleep(5);
		}
    }
};

class TestThread06B : public osapi::Thread
{
public:
    TestThread06B() : Thread(1, 0, osapi::JOINABLE) { run(); }
private:
    virtual void job() {
		// get initial priority using osapi
		osapiInitialPriorityB = getPriority();
		// get initial priority using Windows
		unsigned int p1 = GetThreadPriority(GetCurrentThread());
		// change priority using osapi
		setPriority(0);
		// get new priority using Windows
		unsigned int p2 = GetThreadPriority(GetCurrentThread());
		priorityDifferenceB = p2 - p1;
		// calculate difference
		while (runFlag) {
			sleep(5);
		}
    }
};


void TEST_ThreadPriorityChange(void) {

    printf("Running test 06: detailed thread priority set and get\n");
    fflush(stdout);

    // create 2 threads with initial priorities 0 and 1
    TestThread06A tA;
    TestThread06B tB;
    Sleep(100);
	CU_ASSERT(0 == osapiInitialPriorityA);
	CU_ASSERT(1 == osapiInitialPriorityB);
	CU_ASSERT(1 == tA.getPriority());
	CU_ASSERT(0 == tB.getPriority());
	CU_ASSERT(1 == priorityDifferenceA);
	CU_ASSERT(-1 == priorityDifferenceB);
	runFlag = 0;
	CU_ASSERT(true == tA.join(100));
	CU_ASSERT(true == tB.join(100));
}
