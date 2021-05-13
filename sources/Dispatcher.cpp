#include <string>
using namespace std;

#include "Dispatcher.hpp"

namespace pandemic {
    Dispatcher::Dispatcher(Board &board, City city) : Player(board, city) {
        this->roleName = "Dispatcher";
    }

    Dispatcher& Dispatcher::fly_direct(City cardCity) {
        if (this->city == cardCity) {
            throw invalid_argument("Cannot fly direct to current city");
        }
        if (!board.hasResearchStation(this->city)) {
            Player::fly_direct(cardCity);
        }
        this->city = cardCity;
        return *this;
    }
}