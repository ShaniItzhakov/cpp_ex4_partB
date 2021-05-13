#include <string>
using namespace std;

#include "Scientist.hpp"

namespace pandemic {
    Scientist::Scientist(Board &board, City city, int numOfCards) : Player(board, city) {
        this->numOfCards = numOfCards;
        this->roleName = "Scientist";
    }

    Scientist& Scientist::discover_cure(Color color) {
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
        if (checkNumOfCards < this->numOfCards) {
            throw invalid_argument("Cannot discover cure, no n city colors cards");
        }
        int counter = 1;
        for (auto it = citiesCards.begin(); it != citiesCards.end();) {
                if (counter == this->numOfCards) {
                    break;
                }
                if (Board::getColorOfCity(*it) == color) {
                    it = citiesCards.erase(it);
                    counter++;
                }
                else {
                    it++;
                }
        }
        board.addDiscoveredCure(color);
        return *this;
    }       
}