#include <gtest/gtest.h>

#include "board/logic/controller.h"

using namespace Board;

TEST(ControllerTest, newBoardReference) {
    BType deadBoardState{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    Logic::Controller controller{};
    controller.newBoard(deadBoardState);
    
    ASSERT_EQ(controller.getBoardState(), deadBoardState);
}

TEST(ControllerTest, newBoardAutomatic) {
    BType deadBoardState{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    Logic::Controller controller{};
    controller.newBoard(deadBoardState);
    
    ASSERT_EQ(controller.getBoardState(), deadBoardState);
}

// TODO
// TEST(ControllerTest, newBoardManual) {
//     BType deadBoardState{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

//     Logic::Controller controller{};
//     controller.newBoard(deadBoardState);
    
//     ASSERT_EQ(controller.getBoardState(), deadBoardState);
// }

TEST(ControllerTest, nextState) {
    // TODO
}



