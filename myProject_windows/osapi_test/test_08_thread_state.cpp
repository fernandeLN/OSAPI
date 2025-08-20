#include "CUnit/CUnitCI.h"
#include "osapi.h"

static volatile osapi::ThreadState runState = osapi::UNKNOWN;
static volatile int runFlag = 1;

class TestThread08 : public osapi::Thread
{
public:
    TestThread08() : Thread(1, 0, osapi::JOINABLE) { ; }
private:
    virtual void job() {
        // check the state while running
        runState = getState();
        while(runFlag) {
            ;
        }
        sleep(100);
    }
};

void TEST_ThreadStateChecking(void) {

    printf("Running test 08: thread state checking\n");
    fflush(stdout);
    
    // create thread
    TestThread08 t;

    // at this point thread should be in INACTIVE state
    CU_ASSERT(osapi::INACTIVE == t.getState());
    // run the thread
    CU_ASSERT(true == t.run());
    // wait a while
    Sleep(5);
    // at this point runState should be set to RUNNING state
    CU_ASSERT(osapi::RUNNING == runState);
    // at this point thread should be in READY or RUNNING state (inside the while loop)
    osapi::ThreadState state = t.getState();
    CU_ASSERT((osapi::READY == state) || (osapi::RUNNING == state));
    // suspend the thread
    CU_ASSERT(true == t.suspend());
    // at this point thread should be in SUSPENDED state
    CU_ASSERT(osapi::SUSPENDED == t.getState());
    // resume the thread
    CU_ASSERT(true == t.resume());
    // wait for the thread to be resumed
    Sleep(5);
    // at this point thread should be in READY or RUNNING state (inside the while loop)
    state = t.getState();
    CU_ASSERT((osapi::READY == state) || (osapi::RUNNING == state));

    // make the thread end
    runFlag = 0;
    // wait a while so that the thread can enter sleep
    Sleep(5);
    // at this point thread should be in BLOCKED state (during sleep)
    CU_ASSERT(osapi::BLOCKED == t.getState());
    // wait for the thread to finish
    CU_ASSERT(true == t.join(200));
    // at this point thread should be again in INACTIVE state
    CU_ASSERT(osapi::INACTIVE == t.getState());
}
