#include <string>
using namespace std;

#include "Medic.hpp"

namespace pandemic {
    Medic::Medic(Board &board, City city) : Player(board, city) {
        this->roleName = "Medic";
    }

    Medic& Medic::treat(City city) {
        if (this-> city != city) {
            throw invalid_argument("Not the current location");
        }
        if (board[city] == 0) {
            throw invalid_argument("No pandemic in the city, cubes are 0");
        }
        board[city] = 0;
        return *this;
    }

    void Medic::treatAfterMoving() {
        Color colorOfCity = Board::getColorOfCity(city);
        if (board.hasDiscoveredCure(colorOfCity)) {
            board[this->city] = 0;
        }
    }
}