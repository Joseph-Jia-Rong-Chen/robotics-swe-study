cmake_minimum_required(VERSION 3.16)

project(sensor_logger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fix for AppleClang 14 old SDK math.h bug
add_compile_options(-D_LIBCPP_DISABLE_AVAILABILITY)

# fetch googletest automatically
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# library target
add_library(sensor_logger_lib
    src/imu_sensor.cpp
    src/lidar_sensor.cpp
    src/sensorBuffer.cpp
    src/file_writer.cpp
)
target_include_directories(sensor_logger_lib PUBLIC include)

# main executable
add_executable(sensor_logger src/main.cpp)
target_link_libraries(sensor_logger PRIVATE sensor_logger_lib)

# test target
add_executable(sensor_test tests/test_sensor_buffer.cpp)
target_link_libraries(sensor_test PRIVATE
    sensor_logger_lib
    GTest::gtest_main
    )

include(Googletest)
gtest_discover_tests(sensor_test)