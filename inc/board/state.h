#include <vector>

#pragma once

namespace Board {

using BType = std::vector<std::vector<int>>;

class BState{ 
public:
    enum StateE {
        RANDOM, 
        DEAD
    };

    void createState(const int width, const int height, BState::StateE stateE);
    BType getBoardState() const;

private:
    BType createDeadState(const int width, const int height);
    BType boardState;
};

} // Board
