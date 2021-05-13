#include "OperationsExpert.hpp"

namespace pandemic {
    OperationsExpert::OperationsExpert(Board &board, City city) : Player(board, city) {
        this->roleName = "OperationsExpert";
    }

    OperationsExpert& OperationsExpert::build() {
        board.buildResearchStation(this->city);
        return *this;
    } 
}