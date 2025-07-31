#include <gtest/gtest.h>

#include "board/state.h"

using namespace Board;

TEST(BoardTest, getAndSetBoardState) {
    BType testBoardState{{0, 0, 1}, {0, 0, 1}, {0, 1, 0}};
    BState state{};

    state.setBoardState(std::move(testBoardState));
    testBoardState = state.getBoardState();

    ASSERT_EQ(testBoardState, state.getBoardState());
}

TEST(BoardTest, setCellStatus) {
    BType testBoardState{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    BState state{testBoardState};

    state.setCellStatus(1, 1, 1);

    ASSERT_NE(testBoardState, state.getBoardState());
}

TEST(BoardTest, getWidth) {
    BType testBoardState{{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 1, 0, 1}};
    BState state{testBoardState};

    ASSERT_EQ(state.getWidth(), 4);
}

TEST(BoardTest, getHeight) {
    BType testBoardState{{0, 0, 1, 1}, {0, 0, 1, 1}, {0, 1, 0, 1}};
    BState state{testBoardState};

    ASSERT_EQ(state.getHeight(), 3);
}
