#include <gtest/gtest.h>
#include "board/state.h"
#include "board/io/printer.h"

TEST(PrinterTest, renderState) {
    std::stringstream buffer;
    // Reads cout output from streambuf? and saves in buffer
    // std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    Board::BState state;
    Board::IO::Printer printer{state};

    state.createState(10,10, Board::BState::StateE::RANDOM);
    printer.render(std::cout);

    state.createState(2, 1, Board::BState::StateE::DEAD);
    printer.render(buffer);

    std::string expected = " --\n|    |\n --\n";
    EXPECT_EQ(buffer.str(), expected);
}