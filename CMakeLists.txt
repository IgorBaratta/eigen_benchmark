cmake_minimum_required(VERSION 3.10)

project(benchmark)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set c++ flags
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

CHECK_CXX_COMPILER_FLAG("-O3" COMPILER_SUPPORTS_O3)
if(COMPILER_SUPPORTS_O3)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread")

find_package(benchmark REQUIRED)
find_package(Eigen3 REQUIRED)
message(STATUS "Found Eigen ${EIGEN3_INCLUDE_DIRS}")
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIRS})

add_executable(ndvector ndvector.cpp)
target_link_libraries(ndvector PRIVATE benchmark::benchmark)

add_executable(eigen eigen.cpp)
target_link_libraries(eigen PRIVATE benchmark::benchmark)