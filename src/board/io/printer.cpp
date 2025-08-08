#include "board/io/printer.h"

namespace Board::IO {
Printer::Printer(const Board::BState& state) 
                            : state{state} {}

void Printer::render(std::ostream& os) {
    std::string output;
    output += " ";

    for (int row = 0; row < state.getBoardState().size(); row++) {
        output += "--";
    }

    output += '\n';

    for (int row = 0; row < state.getBoardState().size(); row++) {
        output += "|";
        for (int col = 0; col < state.getBoardState()[0].size(); col++) {
            if (state.getBoardState()[row][col] == true) {
                output += "# ";
            }
            else {
                output += "  ";
            }
        }
        output += "|";
        output += '\n';
    }

    output += " ";

    for (int row = 0; row < state.getBoardState().size(); row++) {
        output += "--";
    }

    output += '\n';
    os << output;
}
} // Board::IO