#include "CUnit/CUnitCI.h"
#include "osapi.h"

static volatile int runFlag;

class TestThread5 : public osapi::Thread
{
public:
    TestThread5() : Thread(0, 0, osapi::JOINABLE) { ; }
private:
    virtual void job() {
        while (runFlag) {
            sleep(100);
        }
    }
};


void TEST_ThreadPriority(void) {

    printf("Running test 05: thread priority set and get\n");
    fflush(stdout);

    // set initial flag values
    runFlag = 1;
    // create thread and run it
    TestThread5 t;
    CU_ASSERT(true == t.run());
    // check if initial priority was set
    CU_ASSERT(0 == t.getPriority());
    // test thread priority setting from outside the thread
    CU_ASSERT(true == t.setPriority(1));
    CU_ASSERT(1 == t.getPriority());
    // terminate thread
    runFlag = 0;
    t.join(1000);
}
