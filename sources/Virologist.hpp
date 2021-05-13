#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

namespace pandemic {
    class Virologist : public Player {
    public:
        Virologist(Board &board, City city);
        Virologist& treat(City city) override;
    };
}