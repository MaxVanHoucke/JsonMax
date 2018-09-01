cmake_minimum_required(VERSION 3.9)
project(JsonMax)

include_directories(gtest/include)
link_directories(gtest/lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -pthread)
set(CMAKE_CXX_FLAGS:STRING=-fPIC)

set(SOURCE_FILES src/main.cpp src/JsonObject.cpp src/JsonElement.cpp src/JsonParser.cpp)

set(DEBUG_SOURCE_FILES  test/MainTest.cpp test/ValidateNumberTest.cpp test/ValidateStringTest.cpp
                        src/JsonParser.cpp src/JsonElement.cpp src/JsonObject.cpp)

add_executable(JsonMax ${SOURCE_FILES})
add_executable(JsonMaxTest ${DEBUG_SOURCE_FILES})

target_link_libraries(JsonMaxTest gtest)
