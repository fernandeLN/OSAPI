#include <cstdio>
#include "CUnit.h"
#include "Basic.h"
#include "FreeRTOS.h"
#include "task.h"

int myPow(int x, unsigned int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result = result * x;
    }
    return result;
}


void TEST_myPow(void) {
    // test using standard test macro
    CU_ASSERT(1 == myPow(1,1));
    CU_ASSERT(0 == myPow(0,1));
    CU_ASSERT(1 == myPow(1,0));
    // test using macro better suited for comparing numbers:
    CU_ASSERT_EQUAL(4, myPow(2,2));
    CU_ASSERT_EQUAL(10, myPow(10,1));
    // this should fail:
    CU_ASSERT_EQUAL(0, myPow(2,2));
}

void threadCUnit(void* param) {
    CU_pSuite myTestSuite;

    // initialize CUnit
    CU_initialize_registry();
    // create new test suite
    myTestSuite = CU_add_suite("my test suite", NULL, NULL);
    // add test to test suite
    CU_add_test(myTestSuite, "my test", TEST_myPow);
    // set verbose mode
    CU_basic_set_mode(CU_BRM_VERBOSE);
    // run all tests
    CU_basic_run_tests();
    printf("\n");
    // print results
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");
    // deinitialize CUnit
    CU_cleanup_registry();

    vTaskDelete(NULL);
}

