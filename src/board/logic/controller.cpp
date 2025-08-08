#include <iostream>
#include <random>
#include <thread>

#include "board/io/printer.h"
#include "board/logic/controller.h"

namespace Board::Logic {
namespace {

int countLivingNeighbours(const BState& actualBState, int row, int col) {
    int livingNeighbours = 0;

    for (int r = (row - 1); r <= (row + 1); r++) {
        for (int c = (col - 1); c <= (col + 1); c++) {
            if (r == row && c == col) { 
                continue;
            }

            if (r >= 0 && r < actualBState.getWidth()
                && c >= 0 && c < actualBState.getHeight()) {
                livingNeighbours += (actualBState.getBoardState()[r][c]);
            }
        }
    }

    return livingNeighbours;
}

void newCell(BState& nextBState, int row, int col, bool status) {
    nextBState.setCellStatus(row, col, status);
}

void iterateRules(const BState& actualBState, BState& nextBState, int startRow, int endRow) {
    for (int h = startRow; h < endRow; h++) {
        for (int w = 0; w < actualBState.getWidth(); w++) {
            int livingNeighbours = countLivingNeighbours(actualBState, h, w);
            const BType& boardState = actualBState.getBoardState();
            if (boardState[h][w]) {
                switch (livingNeighbours) {
                    case 0:
                    case 1:
                        // Rule One
                        newCell(nextBState, h, w, 0);
                        break;
                    case 2:
                    case 3:
                        // Rule Two
                        newCell(nextBState, h, w, 1);
                        break;
                    default:
                        // Rule Three
                        if (livingNeighbours > 3) {
                            newCell(nextBState, h, w, 0);
                        }
                        else if (livingNeighbours < 0) {
                            std::cout << "Something is really bad" << std::endl;
                        }
                }
            }
            // Rule Four
            else if ((boardState[h][w] == 0) && (livingNeighbours == 3)) {
                newCell(nextBState, h, w, 1);
            }
        }
    }
}

} // namespace

void Controller::nextState() {
    int height = state.getHeight();
    BState nextBState{createBoardState(height,
                                  state.getWidth(),
                                  Board::StateE::DEAD)};
    
    int numOfHwThreads = std::thread::hardware_concurrency();
    numOfHwThreads = std::min(height, numOfHwThreads);
    std::vector<std::thread> threads;
    int rowsPerThread = height / numOfHwThreads;

    for (int t = 0; t < numOfHwThreads; t++) {
        int startRow = t * rowsPerThread;
        int endRow = (t == numOfHwThreads - 1) ? height : (t + 1) * rowsPerThread;
        threads.emplace_back(iterateRules, std::cref(state), std::ref(nextBState), startRow, endRow);
    }

    for (auto& t : threads) {
        t.join();
    }
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
        // TODO Throw exception when implementing Manual creation
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

void Controller::print() {
    Board::IO::Printer printer{state};
    std::cout << "\033[H";
    printer.render(std::cout);
}

} // Board::Logic