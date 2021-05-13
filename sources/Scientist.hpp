#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Player.hpp"

namespace pandemic {
    class Scientist : public Player {
    private:
        int numOfCards;
    public:
        Scientist(Board &board, City city, int numOfCards);
        Scientist& discover_cure(Color color) override;
    };
}