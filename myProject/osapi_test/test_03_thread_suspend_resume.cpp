#include "CUnit.h"
#include "osapi.h"

static volatile int testFlag;
static volatile int runFlag;

class TestThread3 : public osapi::Thread
{
public:
    TestThread3() : Thread(3, 256, osapi::JOINABLE) { ; }
private:
    virtual void job() {
        while (runFlag) {
            testFlag = 1;
            sleep(10);
        }
        testFlag = 2;
    }
};


void TEST_ThreadSuspendResume(void) {

    printf("Running test 03: thread suspend and resume       ");

    // set initial flag values
    testFlag = 0;
    runFlag = 1;
    // create thread and run it
    TestThread3 t;
    CU_ASSERT(true == t.run());
    // test thread operation - after 500ms the testFlag should already change to 1
    vTaskDelay(500);
    CU_ASSERT(1 == testFlag);
    // suspend the thread
    CU_ASSERT(true == t.suspend());
    // test if thread was actually suspended - testFlag should not go to 1
    testFlag = 0;
    vTaskDelay(500);
    CU_ASSERT(0 == testFlag);
    // resume the thread
    CU_ASSERT(true == t.resume());
    // test thread operation - after 500ms the testFlag should already change to 1
    vTaskDelay(500);
    CU_ASSERT(1 == testFlag);
    // send signal to terminate the thread
    runFlag = 0;
    // join thread
    CU_ASSERT(true == t.join(1000));
    // test thread termination
    CU_ASSERT(2 == testFlag);
}
