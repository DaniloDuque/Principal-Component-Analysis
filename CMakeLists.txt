cmake_minimum_required(VERSION 3.16)
project(Principal-Component-Analysis)

set(CMAKE_CXX_STANDARD 20)

# ========== OpenCV ==========
find_package(OpenCV REQUIRED)

# ========== Source Files ==========
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
)

add_library(PCALib ${SOURCES})
target_include_directories(PCALib
        PUBLIC src
        PRIVATE ${OpenCV_INCLUDE_DIRS}
)
target_link_libraries(PCALib PUBLIC ${OpenCV_LIBS})

# ========== Main Executable ==========
add_executable(PCA
        main.cpp
        src/main/pca/pca.cpp
        src/main/pca/pca.h
        src/main/input/image/io/ImageIO.cpp
        src/main/input/image/io/ImageIO.h
        src/main/input/image/pca/ImagePCA.cpp
        src/main/input/image/pca/ImagePCA.h
        src/main/matrix/LowRankApproximation.h
)

target_include_directories(PCA PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(PCA PRIVATE PCALib ${OpenCV_LIBS})

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

add_executable(PCA_Tests
        ${TEST_SOURCES}
        test/main/vector/test_vector.cpp
        test/main/matrix/test_Matrix.cpp
        test/main/pca/test_PCA.cpp
)

target_include_directories(PCA_Tests PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(PCA_Tests
        PRIVATE
        GTest::gtest_main
        PCALib
        ${OpenCV_LIBS}
)

include(GoogleTest)
gtest_discover_tests(PCA_Tests)