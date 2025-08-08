#include <iostream>
#include "board/logic/controller.h"

#include "board/state.h"

using Controller = Board::Logic::Controller;

int main() {
    std::ios::sync_with_stdio(false);
    std::cout << "\033[2J\033[?25l"; // Clear screen and hide cursor

    Controller controller{};

    controller.newBoard(30, 30, Controller::CreationMode::AUTO);
    controller.print();

    while (true) {
        controller.nextState();
        controller.print();
    }

    //TODO end game without crashing
    
    std::cout << "\033[?25h"; // Show cursor again

    return 0;
}