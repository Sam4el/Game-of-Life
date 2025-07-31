#include <gtest/gtest.h>
#include "board/state.h"

TEST(BoardTest, createStateDead) {
    Board::BState state;
    Board::BType deadState{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    state.createState(3, 3, Board::BState::StateE::DEAD);
    
    ASSERT_EQ(state.getBoardState(), deadState);
}

TEST(BoardTest, getBoardState) {
    Board::BState state;
    Board::BType testState;

    state.createState(5, 5, Board::BState::StateE::RANDOM);
    testState = state.getBoardState();

    ASSERT_EQ(testState, state.getBoardState());
}