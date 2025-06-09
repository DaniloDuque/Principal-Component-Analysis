cmake_minimum_required(VERSION 3.16)
project(SVD_Image_Compressor)

set(CMAKE_CXX_STANDARD 20)

# ========== Source Files ==========
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
)

add_library(SVDLib ${SOURCES})
target_include_directories(SVDLib PUBLIC src)

# ========== Main Executable ==========
add_executable(SVD_Image_Compressor main.cpp)
target_link_libraries(SVD_Image_Compressor PRIVATE SVDLib)

# ========== GoogleTest ==========
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# ========== Test Executable ==========
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp)

add_executable(SVD_Tests ${TEST_SOURCES}
        test/main/util/vector/test_vector.cpp)
target_link_libraries(SVD_Tests
        PRIVATE
        GTest::gtest_main
        SVDLib
)

include(GoogleTest)
gtest_discover_tests(SVD_Tests)