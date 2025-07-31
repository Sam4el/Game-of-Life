#include <gtest/gtest.h>
#include "board/state.h"
#include "board/io/printer.h"

using namespace Board;

TEST(PrinterTest, renderState) {
    std::stringstream buffer;
    // Reads cout output from streambuf? and saves in buffer
    // std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    BType testBoardState1{{0, 0, 1}, {0, 0, 1}, {0, 1, 0}};
    BType testBoardState2{{0}};

    BState state{testBoardState1};
    IO::Printer printer{state};

    printer.render(std::cout);

    state.setBoardState(testBoardState2);
    printer.render(buffer);

    std::string expected = " --\n|  |\n --\n";
    EXPECT_EQ(buffer.str(), expected);
}