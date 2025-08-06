#include "board/state.h"

#pragma once

namespace Board::Logic {

class Controller {
public:

enum class CreationMode {
    AUTOMATIC,
    MANUAL
};

Controller() = default;

void nextState();
void newBoard(int height, int width, CreationMode mode);
void newBoard(BType& boardState);
BType getBoardState() const;

private:
BType createBoardState(const int width, const int height, Board::StateE stateE);
BType createDeadBoardState(const int width, const int height);
void iterateRules(BState& state);
int countLivingNeighbours(int row, int col);
void newCell(int row, int col, bool status, BState& state);

// Rules:

// Any live cell with 0 or 1 live neighbors becomes dead, 
// because of underpopulation

// Any live cell with 2 or 3 live neighbors stays alive, 
// because its neighborhood is just right

// Any live cell with more than 3 live neighbors becomes dead, 
// because of overpopulation

// Any dead cell with exactly 3 live neighbors becomes alive, 
// by reproduction

Board::BState state;

};
} // Board::Logic