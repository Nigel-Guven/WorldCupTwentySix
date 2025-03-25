
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "XMLParser.h"
#include "League.h"
#include "Tournament.h"

int main() {

    XMLParser parser("south_america.xml");
    std::srand(std::time(0));

    std::vector<Team> teams = parser.parseXML();

    League southAmericanLeague;

    for (const auto& team : teams) {
        southAmericanLeague.addTeam(team);
    }

    Tournament tournament(southAmericanLeague);
    tournament.runRoundRobin();


    return 0;
}
