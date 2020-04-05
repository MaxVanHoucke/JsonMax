add_executable(JsonMaxTests
        main.cpp
        cases/HappyDaysParsing.cpp
        cases/NightmareParsing.cpp
        cases/StringValidation.cpp)

target_link_libraries(JsonMaxTests JsonMax)
