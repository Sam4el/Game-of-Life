#include "board/state.h"

#pragma once

namespace Board::Logic {
class Controller {
public:
Controller() = delete;
Controller(Board::BState& state);

void nextState(Board::BState& state);

private:
// Any live cell with 0 or 1 live neighbors becomes dead, 
// because of underpopulation
void ruleOne();

// Any live cell with 2 or 3 live neighbors stays alive, 
// because its neighborhood is just right
void ruleTwo();

// Any live cell with more than 3 live neighbors becomes dead, 
// because of overpopulation
void ruleThree();

// Any dead cell with exactly 3 live neighbors becomes alive, 
// by reproduction
void ruleFour();

Board::BState& state;
Board::BState nextBState;

};
} // Board::Logic