#include <vector>

#pragma once

namespace Board {

// TODO Think of refactoring BType to std::vector<bool> (flattened 2D array)
using BType = std::vector<std::vector<bool>>;

enum class StateE {
    RANDOM, 
    DEAD
};

class BState{ 
public:
BState() = default;
BState(BType boardState);

void setBoardState(BType nextBoardState);
void setCellStatus(int row, int col, bool status);

BType getBoardState() const;
int getHeight() const;
int getWidth() const;

private:
BType boardState;

};

} // Board
