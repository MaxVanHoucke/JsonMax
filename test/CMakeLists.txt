add_executable (JsonMaxTests
        main.cpp
        ValidateNumberTest.cpp
        ValidateStringTest.cpp
        ParsingTest.cpp
        )

target_link_libraries (JsonMaxTests JsonMax)
