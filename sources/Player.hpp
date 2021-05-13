#pragma once
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <set>

namespace pandemic {
    class Player {
    protected:
        Board &board;
        City city;
        std::string roleName = "Player";
        std::set<City> citiesCards;
    public:
        Player(Board &board, City city);
        Player& drive(City destCity);
        virtual Player& fly_direct(City cardCity);
        Player& fly_charter(City city);
        Player& fly_shuttle(City city);
        virtual Player& build();
        virtual Player& discover_cure(Color color);
        virtual Player& treat(City city);
        virtual void treatAfterMoving(){};
        std::string role();
        Player& take_card(City city);
        void remove_cards(); 
    };
}