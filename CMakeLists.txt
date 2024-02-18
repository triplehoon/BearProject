cmake_minimum_required(VERSION 3.0.0)
project(BearProject VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()


file(GLOB sources src/*.cpp )
file(GLOB headers include/*.h *.h)

# add include directories
include_directories(include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# define TEST_BANK_API
add_definitions(-DTEST_BANK_API)

add_executable(BearProject main.cpp ${sources} ${headers})
