
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

    Tournament tournament2(southAmericanLeague);
    tournament2.runRoundRobin();

    Tournament tournament3(southAmericanLeague);
    tournament3.runRoundRobin();

    Tournament tournament4(southAmericanLeague);
    tournament4.runRoundRobin();

    Tournament tournament5(southAmericanLeague);
    tournament5.runRoundRobin();

    Tournament tournament6(southAmericanLeague);
    tournament6.runRoundRobin();

    Tournament tournament7(southAmericanLeague);
    tournament7.runRoundRobin();

    Tournament tournament8(southAmericanLeague);
    tournament8.runRoundRobin();

    Tournament tournament9(southAmericanLeague);
    tournament9.runRoundRobin();


    return 0;
}
