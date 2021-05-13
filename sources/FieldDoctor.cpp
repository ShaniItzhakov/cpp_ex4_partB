#include <string>
using namespace std;

#include "FieldDoctor.hpp"

namespace pandemic {
    FieldDoctor::FieldDoctor(Board &board, City city) : Player(board, city) {
        this->roleName = "FieldDoctor";
    }

    FieldDoctor& FieldDoctor::treat(City city) {
        if (board[city] == 0) {
            throw invalid_argument("No pandemic in the city, cubes are 0");
        }
        if (this->city != city && !Board::isConnectedCity(this->city, city)) {
            throw invalid_argument("Cannot treat, cities are not connected");
        }
        Color colorOfCity = Board::getColorOfCity(city);
        if (board.hasDiscoveredCure(colorOfCity)) {
            board[city] = 0;
        }
        else {
            board[city]--;
        }
        return *this;
    }
}