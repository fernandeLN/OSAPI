project(osapi C)
# Define osapi library
add_library(osapi STATIC 
    windows/osapi_windows.cpp
)
# Define include directories
target_include_directories(osapi PUBLIC ${CMAKE_CURRENT_LIST_DIR} PRIVATE windows)
