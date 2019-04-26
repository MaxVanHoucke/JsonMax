add_executable (JsonMaxTests
        test.cpp
        ValidateNumberTest.cpp
        ValidateStringTest.cpp
        )

target_link_libraries (JsonMaxTests JsonMax)
