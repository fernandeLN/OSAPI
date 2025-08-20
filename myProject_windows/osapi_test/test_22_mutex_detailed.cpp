#include "CUnit/CUnitCI.h"
#include "osapi.h"

static osapi::Mutex m;
static bool mutexTaken = false;

class TestThread22 : public osapi::Thread
{
public:
    TestThread22() : Thread(0, 256, osapi::JOINABLE) { run(); }
private:
    virtual void job() {
    	// try to take mutex
    	mutexTaken = m.lock(1000);
    }
};

void TEST_MutexDetailed(void) {

	printf("Running test 22: detailed mutex\n");
	fflush(stdout);

    // lock mutex
	CU_ASSERT(true == m.lock(100));
	// run concurrent thread
	TestThread22 t;
	Sleep(500);
	// unlock mutex so that the thread can take it
	m.unlock();
	// wait for the thread to end
	CU_ASSERT(true == t.join(500));
	// check if mutex was taken
	CU_ASSERT(true == mutexTaken);
}
