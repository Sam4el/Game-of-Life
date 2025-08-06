#include <random>
#include <iostream>
#include "board/logic/controller.h"

namespace Board::Logic {

void Controller::nextState() {
    BState nextBState{createBoardState(state.getHeight(),
                                  state.getWidth(),
                                  Board::StateE::DEAD)};
    iterateRules(nextBState);
    state.setBoardState(std::move(nextBState.getBoardState()));
}

void Controller::newBoard(int height,
                            int width,
                            CreationMode mode = CreationMode::AUTOMATIC) {
    if (mode == CreationMode::AUTOMATIC) {
        state.setBoardState(createBoardState(height, width, Board::StateE::RANDOM));
    }
    else {
        state.setBoardState(createBoardState(height, width, Board::StateE::DEAD));
        // TODO
        // Creation with manually assigned cells
    }
}

void Controller::newBoard(BType& boardState) {
    boardState = std::move(boardState);
}

BType Controller::getBoardState() const {
    return state.getBoardState();
}

BType Controller::createBoardState(int height, int width, Board::StateE stateE) {
    if (height <= 0 || width <= 0) {
        std::cout << "Size must be at least 1x1" << std::endl;
        // TODO Throw exception
    }
    BType boardState{createDeadBoardState(height, width)};

    if (stateE == Board::StateE::RANDOM) {
        for (int h = 0; h < height; h++) {
            for (int w = 0; w < width; w++) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::bernoulli_distribution dist(0.2);
                boardState[h][w] = dist(gen) ? 1 : 0;
            }
        }
    }

    return boardState;
}

BType Controller::createDeadBoardState(int width, int height) {
    return BType(height, std::vector<bool>(width, 0));
}

void Controller::iterateRules(BState& nextBState) {
    for (int h = 0; h < state.getHeight(); h++) {
        for (int w = 0; w < state.getWidth(); w++) {
            int livingNeighbours = countLivingNeighbours(h, w);
            const BType& boardState = state.getBoardState();
            if (boardState[h][w] == 1) {
                switch (livingNeighbours) {
                    case 0:
                    case 1:
                        newCell(h, w, 0, nextBState);
                        break;
                    case 2:
                    case 3:
                        newCell(h, w, 1, nextBState);
                        break;
                    default:
                        if (livingNeighbours > 3) {
                            newCell(h, w, 0, nextBState);
                        }
                        else if (livingNeighbours < 0) {
                            std::cout << "Something is really bad" << std::endl;
                        }
                }
            }
            else if ((boardState[h][w] == 0) && (livingNeighbours == 3)) {
                newCell(h, w, 1, nextBState);
            }
        }
    }
}

int Controller::countLivingNeighbours(int row, int col) {
    int livingNeighbours = 0;

    for (int i = (row - 1); i <= (row + 1); row++) {
        for (int j = (col - 1); j <= (col + 1); col++) {
            if (i == 1 && j == 1) { continue; }
            int r = row + i;
            int c = col + j;
            if (r >= 0 && row < state.getWidth()
                && c >= 0 && col < state.getHeight()) {
                livingNeighbours += (getBoardState()[r][c]);
            }
        }
    }

    return livingNeighbours;
}

void Controller::newCell(int row, int col, bool status, BState& nextBState) {
    nextBState.setCellStatus(row, col, status);
}

} // Board::Logic