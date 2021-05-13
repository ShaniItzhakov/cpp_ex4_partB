#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

namespace pandemic {
    class Dispatcher : public Player {
    public:
        Dispatcher(Board &board, City city);
        Dispatcher& fly_direct(City cardCity) override;
    };
}