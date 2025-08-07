#include <gtest/gtest.h>

#include "board/logic/controller.h"

using namespace Board;

TEST(ControllerTest, newBoardReference) {
    BType deadBoardState{{0, 0, 0}, {0, 1, 1}, {0, 0, 1}};
    BType expectedBoardState{{0, 0, 0}, {0, 1, 1}, {0, 0, 1}};

    Logic::Controller controller{};
    controller.newBoard(deadBoardState);
    
    ASSERT_EQ(controller.getBoardState(), expectedBoardState);
}

// TODO How do I test AUTO better?
TEST(ControllerTest, newBoardAutomatic) {
    BType expectedBoardState{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    Logic::Controller controller{};
    controller.newBoard(5, 5, Logic::Controller::CreationMode::AUTO);
    
    ASSERT_NE(controller.getBoardState(), expectedBoardState);
}

// TODO newBoardManual after implementation
// TEST(ControllerTest, newBoardManual) {
//     BType deadBoardState{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

//     Logic::Controller controller{};
//     controller.newBoard(deadBoardState);
    
//     ASSERT_EQ(controller.getBoardState(), deadBoardState);
// }

TEST(ControllerTest, ruleOne) {
    Logic::Controller controller{};

    BType boardState{{1, 0, 0, 0},
                     {0, 0, 1, 1},
                     {0, 0, 0, 0},
                     {1, 0, 0, 0}};

    BType expectedOutput{{0, 0, 0, 0},
                         {0, 0, 0, 0},
                         {0, 0, 0, 0},
                         {0, 0, 0, 0}};

    controller.newBoard(boardState);
    controller.nextState();

    ASSERT_EQ(controller.getBoardState(), expectedOutput);
}

TEST(ControllerTest, ruleTwo) {
    Logic::Controller controller{};

    BType boardState{{0, 1, 0, 0},
                     {0, 0, 1, 0},
                     {0, 0, 0, 1},
                     {0, 0, 0, 0}};

    BType expectedOutput{{0, 0, 0, 0},
                         {0, 0, 1, 0},
                         {0, 0, 0, 0},
                         {0, 0, 0, 0}};

    controller.newBoard(boardState);
    controller.nextState();

    ASSERT_EQ(controller.getBoardState(), expectedOutput);

    boardState =   {{1, 1, 0, 0},
                    {1, 1, 0, 0},
                    {0, 0, 0, 0},
                    {0, 0, 0, 0}};

    expectedOutput = {{1, 1, 0, 0},
                      {1, 1, 0, 0},
                      {0, 0, 0, 0},
                      {0, 0, 0, 0}};

    controller.newBoard(boardState);
    controller.nextState();

    ASSERT_EQ(controller.getBoardState(), expectedOutput);
}

TEST(ControllerTest, ruleThree) {
    Logic::Controller controller{};

    BType boardState{{1, 1, 0, 0},
                     {1, 1, 0, 0},
                     {1, 0, 0, 0},
                     {0, 0, 0, 0}};

    BType expectedOutput{{1, 1, 0, 0},
                         {0, 0, 0, 0},
                         {1, 1, 0, 0},
                         {0, 0, 0, 0}};

    controller.newBoard(boardState);
    controller.nextState();

    ASSERT_EQ(controller.getBoardState(), expectedOutput);
}

TEST(ControllerTest, ruleFour) {
    Logic::Controller controller{};

    BType boardState{{0, 0, 0, 0},
                     {0, 1, 0, 0},
                     {1, 0, 0, 0},
                     {0, 0, 1, 0}};

    BType expectedOutput{{0, 0, 0, 0},
                         {0, 0, 0, 0},
                         {0, 1, 0, 0},
                         {0, 0, 0, 0}};
    controller.newBoard(boardState);
    controller.nextState();

    ASSERT_EQ(controller.getBoardState(), expectedOutput);
}