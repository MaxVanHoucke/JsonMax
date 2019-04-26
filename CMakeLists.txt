cmake_minimum_required(VERSION 3.9)
project(JsonMax)

include_directories(gtest/include)
link_directories(gtest/lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -pthread)
set(CMAKE_CXX_FLAGS:STRING=-fPIC)

set(SOURCE_FILES src/main.cpp src/Object.cpp src/Element.cpp src/Parser.cpp src/Tools.cpp src/Type.cpp src/Pair.cpp)
#set(SOURCE_FILES test.cpp)

set(DEBUG_SOURCE_FILES test/test.cpp test/ValidateNumberTest.cpp test/ValidateStringTest.cpp
        src/Parser.cpp src/Element.cpp src/Object.cpp)

add_executable(JsonMax ${SOURCE_FILES})
add_executable(JsonMaxTest ${DEBUG_SOURCE_FILES})

target_link_libraries(JsonMaxTest gtest)
