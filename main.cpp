#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "XMLParser.h"
#include "League.h"
#include "Tournament.h"
#include <random>
#include "KnockoutRound.h"

League createLeagueFromXMLFile(const std::string& fileName);

int main() {
    
    std::srand(static_cast<unsigned int>(std::time(0)));  // Set the seed for std::rand

    /*
        South America
    */

    std::cout << "Starting South America Tournament...\n";

    League africanGroup = createLeagueFromXMLFile("south_america.xml");
    Tournament africaTournament(africanGroup);
    africaTournament.runRoundRobin();

    /*
        ---------------------------------
    */

    /*
        Africa
    */

    const std::vector<std::string> africaGroups = {
        "africa_group_a.xml",
        "africa_group_b.xml",
        "africa_group_c.xml",
        "africa_group_d.xml",
        "africa_group_e.xml",
        "africa_group_f.xml",
        "africa_group_g.xml",
        "africa_group_h.xml",
        "africa_group_i.xml"
    };

    for (const auto& group : africaGroups) {
        League africanGroup = createLeagueFromXMLFile(group);
        Tournament africaTournament(africanGroup);
        africaTournament.runRoundRobin();
    }

    /*
        ---------------------------------
    */

    /*
        OCEANIA
    */

    XMLParser groupAParser("oceania_knockout_round.xml");
    std::vector<Team> groupATeams = groupAParser.parseXML();


    KnockoutRound* firstOceaniaRound = buildKnockoutTree(groupATeams);

    Team firstRoundOceaniaWinner = firstOceaniaRound->winner;

    League oceaniaGroupA = createLeagueFromXMLFile("oceania_group_a.xml");
    League oceaniaGroupB = createLeagueFromXMLFile("oceania_group_b.xml");

    oceaniaGroupB.addTeam(firstRoundOceaniaWinner);

    Tournament tournament1(oceaniaGroupA);
    tournament1.runRoundRobin();
    Tournament tournament2(oceaniaGroupB);
    tournament2.runRoundRobin();

    std::vector<Team> finalOceaniaRoundTeams = {
        oceaniaGroupA.getTeamByIndex(0), // First team from Group A
        oceaniaGroupB.getTeamByIndex(1), // Second team from Group B
        oceaniaGroupA.getTeamByIndex(1), // Second team from Group A
        oceaniaGroupB.getTeamByIndex(0)  // First team from Group B
    };

    // Build the final knockout round tree
    KnockoutRound* finalOceaniaRound = buildKnockoutTree(finalOceaniaRoundTeams);
    
    Team finalRoundOceaniaWinner = finalOceaniaRound->winner;

    /*
        ---------------------------------
    */

    return 0;
}

League createLeagueFromXMLFile(const std::string& fileName) {
    XMLParser parser(fileName);
    std::vector<Team> xmlTeams = parser.parseXML();

    League league;
    for (const auto& team : xmlTeams) {
        league.addTeam(team);
    }

    return league;
}

