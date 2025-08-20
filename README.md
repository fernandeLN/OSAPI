# OSAPI
OSAPI: An Operating System Abstraction Layer in C++

1. Introduction

The purpose of this project is the design and implementation of a small C++ library that abstracts essential operating system mechanisms. The goal is to provide a portable, object-oriented interface that can be deployed on different real-time and general-purpose operating systems.

The library, named osapi, encapsulates the two most fundamental mechanisms of an OS:

Threads

Mutexes

This abstraction enables software developers to write portable applications without concern for the underlying OS specifics.

2. Objectives

The objectives of the project are as follows:

Design the architecture of the library using UML diagrams to represent class structures and interactions.

Implement the osapi library in C++ with support for three operating systems:

FreeRTOS

RTX

Windows

Validate the implementation by executing unit tests on a Jenkins-based continuous integration platform.

3. Methodology
3.1 Library Design

The library is structured around an abstract interface layer and concrete OS-specific backends.

UML diagrams were employed to model the class hierarchy and design decisions prior to implementation.

3.2 Implementation Strategy

Common interface:

osapi::Thread for thread management.

osapi::Mutex for synchronization.

OS-specific modules:

osapi_freertos – FreeRTOS implementation.

osapi_rtx – RTX implementation.

osapi_windows – Windows implementation.

3.3 Testing and Validation

A unit test suite was developed to ensure correctness and portability.

Automated tests were integrated into a Jenkins CI pipeline, which builds and runs the test cases across supported platforms.

4. Results

A working implementation of the osapi library was produced for FreeRTOS, RTX, and Windows.

The library successfully abstracts threads and mutexes in a uniform, object-oriented interface.

The unit test suite validates correctness, and all tests pass on the Jenkins platform, confirming functional portability.
