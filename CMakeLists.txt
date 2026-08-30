cmake_minimum_required(VERSION 3.21)
project(EIGENRAD CXX)

# The available modules can be queried with the following commands:
#   cmake --help-module-list #< lists all available modules
#   cmake --help-module <mod> #< prints the documentation for module <mod>
#   cmake --help-modules #< lists all modules and their documentation
#
# A list of modules shipped with CMake can be found at
# https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html



set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
# set( CMAKE_BUILD_TYPE Release )

# set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -fopenmp -march=native -mtune=native")

find_package(BLAS REQUIRED)
find_package(LAPACK REQUIRED)

# Configure a project for testing with CTest/CDash
# See https://cmake.org/cmake/help/latest/module/CTest.html
# include(CTest)


# Defines functions to help use the Google Test infrastructure
# See https://cmake.org/cmake/help/latest/module/FindGTest.html
# find_package(GTest REQUIRED)
# include(GoogleTest)


# Find the OpenSSL encryption library.
# See https://cmake.org/cmake/help/latest/module/FindOpenSSL.html
# find_package(OpenSSL REQUIRED COMPONENTS SSL)


# Add subdirectory for this project
add_subdirectory(src)
