#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

namespace pandemic {
    class OperationsExpert : public Player {
    public:
        OperationsExpert(Board &board, City city);
        OperationsExpert& build() override;
    };
}
   