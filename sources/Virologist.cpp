#include <string>
using namespace std;

#include "Virologist.hpp"

namespace pandemic {
    Virologist::Virologist(Board &board, City city) : Player(board, city) {
        this->roleName = "Virologist";
    }

    Virologist& Virologist::treat(City city) {
        if (this->city == city) {
            Player::treat(city);
            return *this;
        }
        if (board[city] == 0) {
            throw invalid_argument("No pandemic in the city, cubes are 0");
        }
        if (citiesCards.count(city) == 0) {
            throw invalid_argument("Cannot treat, no city card to throw");
        }
        Color colorOfCity = Board::getColorOfCity(city);
        if (board.hasDiscoveredCure(colorOfCity)) {
            board[city] = 0;
        }
        else {
            board[city]--;
        }
        citiesCards.erase(city);
        return *this;
    }
}