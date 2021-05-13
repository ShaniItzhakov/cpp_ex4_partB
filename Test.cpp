#include "doctest.h"
#include <iostream>
using namespace std;

#include "Board.hpp"
#include "Player.hpp"
#include "City.hpp"
#include "Color.hpp"

#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Scientist.hpp"
#include "Researcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "GeneSplicer.hpp"
#include "FieldDoctor.hpp"

using namespace pandemic;


TEST_CASE("Test board") {
    Board board;

    cout << "Board is clean, should return TRUE: " << board.is_clean() << endl;

    board[City::Atlanta] = 3;
    board[City::HongKong] = 5;
    board[City::LosAngeles] = 1;
    board[City::London] = 0;
    board[City::London] = 3;

    cout << "Board is NOT clean, should return FALSE: " << board.is_clean() << endl;
}

TEST_CASE("Test Player drive and fly functions") {
    Board board;
    OperationsExpert player{board, City::Paris};
        
    // Check take card function
    player.take_card(City::London)
    .take_card(City::Atlanta)
    .take_card(City::NewYork)
    .take_card(City::Bangkok)
    .take_card(City::Lima)
    .take_card(City::Madrid)
    .take_card(City::Paris);

    // Check drive function
    CHECK_NOTHROW(player.drive(City::London)); // Can drive from Paris to London
    CHECK_NOTHROW(player.drive(City::Madrid)); // Can drive from London to Madrid
    CHECK_NOTHROW(player.drive(City::Algiers)); // Can drive from Madrid to Algiers
    CHECK_NOTHROW(player.drive(City::Paris)); // Can drive from Algiers to Paris

    CHECK_THROWS(player.drive(City::Tokyo)); // Cannot drive from Paris to Tokyo
    CHECK_THROWS(player.drive(City::NewYork)); // Cannot drive from Paris to NewYork
    CHECK_THROWS(player.drive(City::Montreal)); // Cannot drive from Paris to Montreal
    CHECK_THROWS(player.drive(City::Riyadh)); // Cannot drive from Paris to Riyadh
    CHECK_THROWS(player.drive(City::SaoPaulo)); // Cannot drive from Paris to SaoPaulo

    // Check fly_direct function
    CHECK_NOTHROW(player.fly_direct(City::NewYork)); // Can fly direct from Paris to NewYork
    CHECK_THROWS(player.fly_direct(City::NewYork)); // No card - Cannot fly direct from Paris to NewYork
    CHECK_NOTHROW(player.fly_direct(City::Lima)); // Can fly direct from Paris to Lima
    CHECK_THROWS(player.fly_direct(City::Lima)); // No card - Cannot fly direct from Paris to Lima
    CHECK_NOTHROW(player.fly_direct(City::Madrid)); // Can fly direct from Paris to Madrid
    CHECK_THROWS(player.fly_direct(City::Madrid)); // No Madrid card - Cannot fly direct from Paris to Madrid

    player.take_card(City::Madrid);

    // Check fly_charter function
    CHECK_NOTHROW(player.fly_charter(City::Atlanta)); // Can fly charter from Madrid to Atlanta
    CHECK_NOTHROW(player.fly_charter(City::Madrid)); // Can fly charter from Atlanta to Madrid
    CHECK_THROWS(player.fly_charter(City::Atlanta)); // No Madrid card - Cannot fly charter from Madrid to Atlanta
}

TEST_CASE("Test Player build functions") {
    Board board;
    OperationsExpert operationsExpertPlayer{board, City::Milan};
    Dispatcher dispatcherPlayer{board, City::MexicoCity};
    
    dispatcherPlayer.take_card(City::MexicoCity);

    // Check build function
    CHECK_NOTHROW(operationsExpertPlayer.build()); // No card thrown - Build research station in Milan (current city)
    CHECK_NOTHROW(operationsExpertPlayer.build()); // Cannot build more than one research station

    CHECK_NOTHROW(dispatcherPlayer.build()); // Card thrown - Build research station in MexicoCity (current city)
    CHECK_NOTHROW(dispatcherPlayer.build()); // Cannot build more than one research station
    CHECK_NOTHROW(dispatcherPlayer.fly_direct(City::Santiago)); // No card thrown - dispatcher
    CHECK_THROWS(dispatcherPlayer.build()); // Cannot build - no Santiago card

    dispatcherPlayer.take_card(City::Santiago);

    CHECK_NOTHROW(dispatcherPlayer.build()); // Card thrown - Build research station in Santiago (current city)
    CHECK_NOTHROW(dispatcherPlayer.build()); // Cannot build more than one research station

    // Check fly_shuttle function
    CHECK_NOTHROW(operationsExpertPlayer.fly_shuttle(City::Santiago)); // Fly from a research station city (Milan) to a different research station city (Santiago)
    CHECK_NOTHROW(dispatcherPlayer.fly_shuttle(City::Milan)); // Fly from a research station city (Santiago) to a different research station city (Milan)

    CHECK_THROWS(operationsExpertPlayer.fly_shuttle(City::Taipei)); // Cannot fly shuttle - no research station in Taipei
    CHECK_THROWS(dispatcherPlayer.fly_shuttle(City::Tokyo)); // Cannot fly shuttle - no research station in Tokyo

    operationsExpertPlayer.take_card(City::Lagos);

    CHECK_NOTHROW(operationsExpertPlayer.fly_direct(City::Lagos)); // Card thrown - fly direct to Lagos
    CHECK_THROWS(operationsExpertPlayer.fly_shuttle(City::Santiago)); // Cannot fly from a NOT research station city (Lagos) to a different research station city (Santiago)
}

TEST_CASE("Test Player discover_cure function") {
    Board board;

    // Researcher
    Researcher researcherPlayer{board, City::Moscow}; // Moscow - black card
    researcherPlayer.take_card(City::Atlanta) // Taking 5 blue cards
    .take_card(City::London)
    .take_card(City::Madrid)
    .take_card(City::Chicago)
    .take_card(City::Essen)
    .take_card(City::Osaka) // Taking 2 red cards
    .take_card(City::Sydney);

    CHECK_NOTHROW(researcherPlayer.discover_cure(Color::Blue)); // Resercher does not need a research station to discover cure
    CHECK_NOTHROW(researcherPlayer.discover_cure(Color::Blue)); // Does nothing - cards not thrown
    CHECK_THROWS(researcherPlayer.discover_cure(Color::Red)); // No 5 red cards to discover cure

    board.remove_cures();

    // GeneSplicer
    GeneSplicer geneSplicerPlayer{board, City::BuenosAires}; // BuenosAires- yellow card

    geneSplicerPlayer.take_card(BuenosAires).build(); // Build a research station in BuenosAires - needed for discover cure
    geneSplicerPlayer.take_card(City::Algiers) // Taking 5 black cards
    .take_card(City::Cairo)
    .take_card(City::Delhi)
    .take_card(City::Baghdad)
    .take_card(City::Kolkata)
    .take_card(City::London) // Taking 2 blue cards
    .take_card(City::Atlanta);

    CHECK_NOTHROW(geneSplicerPlayer.discover_cure(Color::Red)); // GeneSplicer does not need the same color of thrown cards
    CHECK_NOTHROW(geneSplicerPlayer.discover_cure(Color::Red)); // Does nothing - cards not thrown
    CHECK_THROWS(geneSplicerPlayer.discover_cure(Color::Yellow)); // No 5 cards to discover cure

    board.remove_cures();

    // Scientist
    Scientist scientistPlayer{board, City::Milan, 3};

    scientistPlayer.take_card(Milan).build(); // Build a research station in Milan - needed for discover cure
    scientistPlayer.take_card(City::Atlanta) // Taking 3 blue cards
    .take_card(City::London)
    .take_card(City::Madrid)
    .take_card(City::Osaka) // Taking 2 red cards
    .take_card(City::Sydney);

    CHECK_NOTHROW(scientistPlayer.discover_cure(Color::Blue)); // Scientist needs only n = 3 cards to discover cure
    CHECK_NOTHROW(scientistPlayer.discover_cure(Color::Blue)); // Does nothing - cards not thrown
    CHECK_THROWS(scientistPlayer.discover_cure(Color::Red)); // No 3 red cards to discover cure

    board.remove_cures();
}

TEST_CASE("Test Player treat function") {
    Board board;

    board[City::Madrid] = 3;
    board[City::HongKong] = 5;
    board[City::LosAngeles] = 1;
    board[City::London] = 0;
    board[City::London] = 3;

    // Medic
    Medic medicPlayer{board, City::London};

    CHECK(board[City::London] == 3); // 3
    CHECK_NOTHROW(medicPlayer.treat(City::London)); // Medic removes all disease cubes in London
    CHECK(board[City::London] == 0); // 0

    medicPlayer.take_card(City::Atlanta) // Taking 5 blue cards
    .take_card(City::London)
    .take_card(City::Madrid)
    .take_card(City::Chicago)
    .take_card(City::Essen);

    CHECK(board[City::Madrid] == 3); // 3
    medicPlayer.build().take_card(Madrid).discover_cure(Color::Blue); // Discover cure using 5 blue cards
    medicPlayer.drive(Madrid);
    CHECK(board[City::Madrid] == 0); // 0

    board.remove_cures();

    //Virologist
    Virologist virologistPlayer{board, City::MexicoCity};

    virologistPlayer.take_card(City::Sydney);

    board[City::Sydney] = 2;

    CHECK(board[City::Sydney] == 2); // 2
    CHECK_NOTHROW(virologistPlayer.treat(City::Sydney)); // Virologist removes 1 disease cube in Sydney
    CHECK(board[City::Sydney] == 1); // 1
    CHECK_NOTHROW(virologistPlayer.take_card(Sydney).treat(City::Sydney)); // Virologist removes 1 disease cube in Sydney
    CHECK(board[City::Sydney] == 0); // 0
    CHECK_THROWS(virologistPlayer.treat(City::Sydney)); // No disease cubes in Sydney

    //FieldDoctor
    FieldDoctor fieldDoctorPlayer{board, City::Tokyo};

    board[City::SanFrancisco] = 3;

    CHECK(board[City::SanFrancisco] == 3); // 3
    CHECK_NOTHROW(fieldDoctorPlayer.treat(City::SanFrancisco)); // FieldDoctor removes 1 disease cube in SanFrancisco
    CHECK(board[City::SanFrancisco] == 2); // 2
    CHECK_THROWS(fieldDoctorPlayer.treat(City::NewYork)); // FieldDoctor cannot treat unconnected city
}

TEST_CASE("Test Player role function") {
    Board board;

    OperationsExpert player{board, City::Paris};  
    CHECK(player.role() == "OperationsExpert");

    Dispatcher dispatcherPlayer{board, City::MexicoCity};
    CHECK(dispatcherPlayer.role() == "Dispatcher");

    GeneSplicer geneSplicerPlayer{board, City::BuenosAires};
    CHECK(geneSplicerPlayer.role() == "GeneSplicer");

    Scientist scientistPlayer{board, City::Milan, 3};
    CHECK(scientistPlayer.role() == "Scientist");

    Researcher researcherPlayer{board, City::Moscow};  
    CHECK(researcherPlayer.role() == "Researcher");

    Medic medicPlayer{board, City::London};
    CHECK(medicPlayer.role() == "Medic");

    Virologist virologistPlayer{board, City::MexicoCity};
    CHECK(virologistPlayer.role() == "Virologist");
    
    FieldDoctor fieldDoctorPlayer{board, City::Tokyo};
    CHECK(fieldDoctorPlayer.role() == "FieldDoctor");
}