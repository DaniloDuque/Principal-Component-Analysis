cmake_minimum_required(VERSION 3.16)
project(PCA_Image_Compressor)

set(CMAKE_CXX_STANDARD 20)

# ========== Source Files ==========
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
)

add_library(PCALib ${SOURCES})
target_include_directories(PCALib PUBLIC src)

# ========== Main Executable ==========
add_executable(PCA_Image_Compressor main.cpp
        src/main/pca/pca.cpp
        src/main/pca/pca.h
        src/main/eigen/QR.cpp
        src/main/eigen/QR.h)
target_link_libraries(PCA_Image_Compressor PRIVATE PCALib)

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

add_executable(PCA_Image_Compressor_Tests ${TEST_SOURCES}
        test/main/vector/test_vector.cpp
        test/main/matrix/test_Matrix.cpp
        test/main/eigen/test_QR.cpp)
target_link_libraries(PCA_Image_Compressor_Tests
        PRIVATE
        GTest::gtest_main
        PCALib
)

include(GoogleTest)
gtest_discover_tests(PCA_Image_Compressor_Tests)