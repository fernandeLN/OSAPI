# Set minimum cmake version
cmake_minimum_required(VERSION 3.15)
# Set project name and language definition
project(myproject_windows VERSION 1.0 LANGUAGES CXX)

# Add the CUnit library
add_subdirectory(cunit)

# Add the osapi implementation (as a library)
add_subdirectory(osapi)

# Define the executable and the source files required to build it
add_executable(myproject_windows
    osapi_test/main.cpp
    osapi_test/test_00_thread_name.cpp
    osapi_test/test_01_thread_creation.cpp
    osapi_test/test_02_thread_join.cpp
    osapi_test/test_03_thread_suspend_resume.cpp
    osapi_test/test_04_thread_delay.cpp
    osapi_test/test_05_thread_priority.cpp
    osapi_test/test_06_thread_priority_change.cpp
    osapi_test/test_07_thread_run_detailed.cpp
    osapi_test/test_08_thread_state.cpp
    osapi_test/test_09_thread_suspend_inactive.cpp
    osapi_test/test_10_thread_stack_size.cpp
    osapi_test/test_20_mutex.cpp
    osapi_test/test_21_recursive_mutex.cpp
    osapi_test/test_22_mutex_detailed.cpp
    osapi_test/test_30_mortal_thread.cpp
)
# Set C++ language standard
target_compile_features(myproject_windows PRIVATE cxx_std_20)
# Define where to look for include files
target_include_directories(myproject_windows PRIVATE cunit osapi osapi_test)
# Define link libraries
target_link_libraries(myproject_windows PRIVATE cunit osapi)