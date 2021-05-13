#include <string>
using namespace std;

#include "GeneSplicer.hpp"

const int CARDS_TO_THROW = 5;

namespace pandemic {
    GeneSplicer::GeneSplicer(Board &board, City city) : Player(board, city) {
        this->roleName = "GeneSplicer";
    }

    GeneSplicer& GeneSplicer::discover_cure(Color color) {
        if (!board.hasResearchStation(this->city)) {
            throw invalid_argument("Current city has no research station, cannot discover cure");
        }
        if (board.hasDiscoveredCure(color)) {
            return *this;
        }
        if (citiesCards.size() < CARDS_TO_THROW) {
            throw invalid_argument("Cannot discover cure, no 5 city cards of any color");
        }   
        int counter = 1;
        for (auto it = citiesCards.begin(); it != citiesCards.end();) {     
            if (counter == CARDS_TO_THROW) {
                break;
            }
            it = citiesCards.erase(it);
            counter++;
            it++;
        }
        board.addDiscoveredCure(color);
        return *this;
    }
}