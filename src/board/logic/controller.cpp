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

BType Controller::createBoardState(int width, int height, Board::StateE stateE) {
    BType boardState{createDeadBoardState(width, height)};

    if (stateE == Board::StateE::RANDOM) {
        for (int w = 0; w < width; w++) {
            for (int h = 0; h < height; h++) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::bernoulli_distribution dist(0.2);
                boardState[w][h] = dist(gen) ? 1 : 0;
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
            int livingCells = countLivingCells();
            const BType& boardState = state.getBoardState();
            if (boardState[h][w] == 1) {
                switch (livingCells) {
                    case 0:
                    case 1:
                        newCell(h, w, 0, nextBState);
                        break;
                    case 2:
                    case 3:
                        newCell(h, w, 1, nextBState);
                        break;
                    default:
                        if (livingCells > 3) {
                            newCell(h, w, 0, nextBState);
                        }
                        else if (livingCells < 0) {
                            std::cout << "Something is really bad" << std::endl;
                        }
                }
            }
            else if ((boardState[h][w] == 0) && (livingCells == 3)) {
                newCell(h, w, 1, nextBState);
            }
        }
    }
}

int Controller::countLivingCells() {

    return 0;
}

void Controller::newCell(int row, int col, bool status, BState& nextBState) {
    nextBState.setCellStatus(row, col, status);
}

} // Board::Logic