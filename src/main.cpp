#include <iostream>
#include "board/state.h"
#include "board/io/printer.h"

int main() {
    std::cout << "Game Of Life" << std::endl;

    Board::BState state;
    state.createState(30, 30, Board::BState::StateE::RANDOM);

    Board::IO::Printer printer{state};
    printer.render(std::cout);
    
    return 0;
}