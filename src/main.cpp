#include <iostream>
#include "board/logic/controller.h"

#include "board/state.h"

using Controller = Board::Logic::Controller;

int main() {
    Controller controller{};

    controller.newBoard(20, 20, Controller::CreationMode::AUTO);
    controller.print();

    while (true) {
        controller.nextState();
        controller.print();
    }

    //TODO end game without crashing
    
    return 0;
}