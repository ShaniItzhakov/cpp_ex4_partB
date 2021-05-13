#pragma once

#include <iostream>
#include <string>
#include <map>
#include <set>
#include "City.hpp"
#include "Color.hpp"

namespace pandemic {
    class Board {
    private:
        std::map<City, int> pandemicMap;
        std::set<Color> discoveredCures;
        std::set<City> researchStations;
    public:
        int& operator[](City city);
        friend std::ostream& operator<<(std::ostream &os, const Board &board);
        bool is_clean();
        void remove_cures(); 
        void remove_stations();

        // Help functions
        bool hasResearchStation(City city);
        void buildResearchStation(City city);
        bool hasDiscoveredCure(Color color);
        void addDiscoveredCure(Color color);
        static bool isConnectedCity(City srcCity, City destCity);
        static Color getColorOfCity(City city);
    };
}