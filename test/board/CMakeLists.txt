add_executable(boardTests
    io/printer_test.cpp
    logic/controller_test.cpp
    state_test.cpp
)

target_link_libraries(boardTests gtest_main board)
include(GoogleTest)
gtest_discover_tests(boardTests)