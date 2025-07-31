#include "board/io/printer.h"

namespace Board::IO {
Printer::Printer(const Board::BState& state) 
                            : state{state} {}

void Printer::render(std::ostream& os) {
    os << " ";

    for (int row = 0; row < state.getBoardState().size(); row++) {
        os << "--";
    }

    os << std::endl;

    for (int row = 0; row < state.getBoardState().size(); row++) {
        os << "|";
        for (int col = 0; col < state.getBoardState()[0].size(); col++) {
            if (state.getBoardState()[row][col] == 1) {
                os << "# ";
            }
            else {
                os << "  ";
            }
        }
        os << "|" << std::endl;
    }

    os << " ";

    for (int row = 0; row < state.getBoardState().size(); row++) {
        os << "--";
    }

    os << std::endl;
}
} // Board::IO