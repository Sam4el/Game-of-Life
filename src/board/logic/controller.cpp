#include <iostream>
#include <random>

#include "board/io/printer.h"
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
                            CreationMode mode = CreationMode::AUTO) {
    if (mode == CreationMode::AUTO) {
        state.setBoardState(createBoardState(height, width, Board::StateE::RANDOM));
    }
    else {
        state.setBoardState(createBoardState(height, width, Board::StateE::DEAD));
        // TODO
        // Creation with manually assigned cells
    }
}

void Controller::newBoard(BType& boardState) {
    state = std::move(boardState);
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
            if (boardState[h][w] == true) {
                switch (livingNeighbours) {
                    case 0:
                    case 1:
                        // Rule One
                        newCell(h, w, 0, nextBState);
                        break;
                    case 2:
                    case 3:
                        // Rule Two
                        newCell(h, w, 1, nextBState);
                        break;
                    default:
                        // Rule Three
                        if (livingNeighbours > 3) {
                            newCell(h, w, 0, nextBState);
                        }
                        else if (livingNeighbours < 0) {
                            std::cout << "Something is really bad" << std::endl;
                        }
                }
            }
            // Rule Four
            else if ((boardState[h][w] == 0) && (livingNeighbours == 3)) {
                newCell(h, w, 1, nextBState);
            }
        }
    }
}

int Controller::countLivingNeighbours(int row, int col) {
    int livingNeighbours = 0;

    for (int r = (row - 1); r <= (row + 1); r++) {
        for (int c = (col - 1); c <= (col + 1); c++) {
            if (r == row && c == col) { 
                continue;
            }

            if (r >= 0 && r < state.getWidth()
                && c >= 0 && c < state.getHeight()) {
                livingNeighbours += (getBoardState()[r][c]);
            }
        }
    }

    return livingNeighbours;
}

void Controller::newCell(int row, int col, bool status, BState& nextBState) {
    nextBState.setCellStatus(row, col, status);
}

void Controller::print() {
    Board::IO::Printer printer{state};
    printer.render(std::cout);
}

} // Board::Logic