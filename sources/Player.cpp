#include <string>
using namespace std;

#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"

const int CARDS_TO_THROW = 5;

namespace pandemic {
    Player::Player(Board &b, City c) : board(b), city(c){}

    Player& Player::drive(City destCity) {
        if (this->city == destCity) {
            throw invalid_argument("Cannot drive to current city");
        }
        if (!Board::isConnectedCity(this->city, destCity)) {
            throw invalid_argument("Cannot drive to unconnected city");
        }
        this->city = destCity;
        treatAfterMoving();
        return *this;
    }

    Player& Player::fly_direct(City cardCity) {
        if (this->city == cardCity) {
            throw invalid_argument("Cannot fly direct to current city");
        }
        if (citiesCards.count(cardCity) == 0) {
            throw invalid_argument("No card to throw, no card of destination city");
        }
        citiesCards.erase(cardCity);
        this->city = cardCity;
        treatAfterMoving();
        return *this;
    }

    Player& Player::fly_charter(City city) {
        if (this->city == city) {
            throw invalid_argument("Cannot drive to current city");
        }
        if (citiesCards.count(this->city) == 0) {
            throw invalid_argument("No card to throw, no card of current city");
        }
        citiesCards.erase(this->city);
        this->city = city;
        treatAfterMoving();
        return *this;
    }

    Player& Player::fly_shuttle(City city) {
        if (this->city == city) {
            throw invalid_argument("Cannot fly shuttle to current city");
        }
        if (!board.hasResearchStation(this->city) || !board.hasResearchStation(city)) {
            throw invalid_argument("Current city or destination city has no research station, cannot fly shuttle");
        }
        this->city = city;
        treatAfterMoving();
        return *this;
    }

    Player& Player::build() {
        if (citiesCards.count(this->city) == 0) {
            throw invalid_argument("Cannot build, no current city card to throw");
        }
        if (!board.hasResearchStation(this->city)) {
            board.buildResearchStation(this->city);
            citiesCards.erase(this->city);
        }
        return *this;
    }
  
    Player& Player::discover_cure(Color color) {
        if (!board.hasResearchStation(this->city)) {
            throw invalid_argument("Current city has no research station, cannot discover cure");
        }
        if (board.hasDiscoveredCure(color)) {
            return *this;
        }
        int checkNumOfCards = 0;
        for (const auto &cityCard: citiesCards) {
            if (Board::getColorOfCity(cityCard) == color) {
                checkNumOfCards++;
            }
        }
        if (checkNumOfCards < CARDS_TO_THROW) {
            throw invalid_argument("Cannot discover cure, no 5 city colors cards");
        }
        int counter = 1;
        for (auto it = citiesCards.begin(); it != citiesCards.end(); it++) {
            if (counter == CARDS_TO_THROW) {
                break;
            }
            if (counter < CARDS_TO_THROW && Board::getColorOfCity(*it) == color) {
                it = citiesCards.erase(it);
                counter++;
            }
        }
        board.addDiscoveredCure(color);
        return *this;
    }

    Player& Player::treat(City city) {
        if (this-> city != city) {
            throw invalid_argument("Not the current location");
        }
        if (board[city] == 0) {
            throw invalid_argument("No pandemic in the city, cubes are 0");
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

    string Player::role() {
        return this->roleName;
    }

    Player& Player::take_card(City city) {
        citiesCards.insert(city);
        return *this;
    }

    void Player::remove_cards() {
       citiesCards.clear();
    }
}