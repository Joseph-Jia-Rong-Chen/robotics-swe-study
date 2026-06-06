cmake_minimum_required(VERSION 3.14)
project(week01-memory-raii)

add_executable(${PROJECT_NAME}
    main.cpp
    releasecamera.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)