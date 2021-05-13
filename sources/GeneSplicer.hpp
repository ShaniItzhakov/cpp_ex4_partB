#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

namespace pandemic {
    class GeneSplicer : public Player {
    public:
        GeneSplicer(Board &board, City city);
        GeneSplicer& discover_cure(Color color) override;
    };
}
   