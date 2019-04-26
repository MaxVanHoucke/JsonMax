add_library(JsonMax
        Element.cpp
        Object.cpp
        Pair.cpp
        Parser.cpp
        Tools.cpp
        Type.cpp
        )

add_executable(JsonMaxDemo main.cpp)
target_link_libraries(JsonMaxDemo JsonMax)
