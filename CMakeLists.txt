cmake_minimum_required(VERSION 3.9)
project(JsonMax)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -pthread)
set(CMAKE_CXX_FLAGS:STRING=-fPIC)

set(SOURCE_FILES src/main.cpp src/JsonObject.cpp src/JsonElement.cpp)
set(DEBUG_SOURCE_FILES test/MainTest.cpp)

add_executable(JsonMax ${SOURCE_FILES})
add_executable(JsonMaxTest ${DEBUG_SOURCE_FILES})

# GTEST
include_directories(gtest/include)
link_directories(gtest/lib)
target_link_libraries(JsonMaxTest gtest)
