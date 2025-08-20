#include "CUnit/CUnitCI.h"
#include "osapi.h"

static const char* testName = "MY_THREAD";

class TestThread0 : public osapi::Thread
{
public:
    TestThread0() : Thread(0, 0, osapi::NOT_JOINABLE, testName) { ; }
private:
    virtual void job() {
        // nothing to do here yet
        ;
    }
};

void TEST_ThreadName(void) {

    printf("Running test 00: thread name\n");
    fflush(stdout);

  	// create thread
    TestThread0 t;
    // check if name matches
    CU_ASSERT_FATAL(NULL != t.getName());
    CU_ASSERT(0 == strcmp(testName, t.getName()));
}
