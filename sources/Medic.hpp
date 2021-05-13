#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

namespace pandemic {
    class Medic : public Player {
    public:
        Medic(Board &board, City city);
        Medic& treat(City city) override;
        void treatAfterMoving() override;
    };
}