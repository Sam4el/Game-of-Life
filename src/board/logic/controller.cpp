#include "board/logic/controller.h"

namespace Board::Logic {
Controller::Controller(Board::BState& state) : state{state} {}

void Controller::nextState(Board::BState& state) {
    
    nextBState.createDeadState()
    ruleOne();
    ruleTwo();
    ruleThree();
    ruleFour();

    state = nextBState;
}

void ruleOne() {

}

void ruleTwo() {

}

void ruleThree() {

}

void ruleFour() {

}

void 

} // Board::Logic