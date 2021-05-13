#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

namespace pandemic {
    class FieldDoctor : public Player {
    public:
        FieldDoctor(Board &board, City city);
        FieldDoctor& treat(City city) override;
    };
}  