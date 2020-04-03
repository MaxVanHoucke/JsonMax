add_executable(JsonMaxTests
        main.cpp
        ValidateStringTest.cpp
        ParsingTest.cpp
        )

target_link_libraries(JsonMaxTests JsonMax)
