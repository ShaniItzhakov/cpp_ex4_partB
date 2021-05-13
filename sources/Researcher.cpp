#include <string>
using namespace std;

#include "Researcher.hpp"

const int CARDS_TO_THROW = 5;

namespace pandemic {
    Researcher::Researcher(Board &board, City city) : Player(board, city) {
        this->roleName = "Researcher";
    }

    Researcher& Researcher::discover_cure(Color color) {
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
}