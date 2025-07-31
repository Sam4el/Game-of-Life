#include <iostream>
#include "board/state.h"

#pragma once

namespace Board::IO {

class Printer {
public:
Printer() = delete;
Printer(const BState& state);

void render(std::ostream& os);

private:
const BState& state;
};

} // Board::IO