cmake_minimum_required(VERSION 3.21)
project(EIGENRAD CXX)


set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Set default configuration to "Release"
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()


find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

# Add subdirectory for this project
add_subdirectory(src)



# Configure a project for testing with CTest/CDash
# See https://cmake.org/cmake/help/latest/module/CTest.html
include(CTest)
if(BUILD_TESTING)
    # Defines functions to help use the Google Test infrastructure
    # See https://cmake.org/cmake/help/latest/module/FindGTest.html
    find_package(GTest REQUIRED)
    include(GoogleTest)
    
    add_subdirectory(tests)
endif()

