#include "board/state.h"

namespace Board {

BState::BState(BType boardState) : boardState{std::move(boardState)} {}

void BState::setBoardState(BType newBoardState) {
    boardState = std::move(newBoardState);
}

void BState::setCellStatus(int row, int col, bool status) {
    boardState[row][col] = status;
}

BType BState::getBoardState() const {
    return boardState;
}

int BState::getHeight() const {
    return boardState.size();
}

int BState::getWidth() const {
    return boardState[0].size();
}

} // Board
