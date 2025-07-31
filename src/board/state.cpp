#include <random>
#include "board/state.h"

namespace Board {

void BState::createState(int width, int height, BState::StateE stateE) {
    boardState = createDeadState(width, height);

    if (stateE == BState::StateE::RANDOM) {
        for (int w = 0; w < width; w++) {
            for (int h = 0; h < height; h++) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::bernoulli_distribution dist(0.2);
                boardState[w][h] = dist(gen) ? 1 : 0;
            }
        }
    }
}

BType BState::createDeadState(int width, int height) {
    std::vector<int> rows(width, 0);
    BType cols{static_cast<size_t>(height), std::move(rows)};

    return std::move(cols);
}

BType BState::getBoardState() const {
    return boardState;
}

} // Board
