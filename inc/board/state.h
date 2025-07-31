#include <vector>

#pragma once

namespace Board {

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
