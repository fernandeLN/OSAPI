#include "CUnit/CUnitCI.h"
#include "osapi.h"

static volatile int runFlag = 1;

class TestThread10 : public osapi::Thread
{
public:
    TestThread10() : Thread(0, 0, osapi::JOINABLE) { ; }
private:
    virtual void job() {
    	volatile unsigned int table[10000] __attribute__((unused)) ;
        while(runFlag) {
            sleep(5);
        }
    }
};

void TEST_ThreadStackSize(void) {

    printf("Running test 10: thread stack size\n");
    fflush(stdout);

    // create thread
    TestThread10 t;

    // check the initial stack size and usage
    CU_ASSERT(0 == t.getTotalStackSize());
    CU_ASSERT(0 == t.getUsedStackSize());

    // run the thread
    CU_ASSERT(true == t.run());
    // wait a while
    Sleep(10);
    // check thread usage during run
    CU_ASSERT(40000 < t.getTotalStackSize());
    CU_ASSERT(40000 < t.getUsedStackSize());

    // make the thread end
    runFlag = 0;
    // wait for the thread to finish
    CU_ASSERT(true == t.join(200));

}
