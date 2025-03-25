
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "XMLParser.h"
#include "League.h"
#include "Tournament.h"

void processGroup(const std::string& fileName);
void processOceaniaGroup(const std::string& fileName, Team knockoutRoundWinner);

int main() {
    
    //Generate Random Seed

    std::srand(std::time(0));

    /*
        South America
    */ 
    
    //std::cout << "Starting South America Tournament...\n";
    //processGroup("south_america.xml");
    

    /*
        Africa
    */
    /*
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
        std::cout << "Starting Tournament for " << group << "...\n";
        processGroup(group);
    }
    */
    /*
        Oceania
    */

    League oceaniaFirstRound;

    Team winner = oceaniaFirstRound.processKnockoutFromXMLFile("oceania_knockout_round.xml");

    std::cout << winner.getName() << "...\n" << std::endl;

    XMLParser groupAParser("oceania_group_a.xml");
    XMLParser groupBParser("oceania_group_b.xml");

    std::vector<Team> groupATeams = groupAParser.parseXML();
    std::vector<Team> groupBTeams = groupBParser.parseXML();

    League leagueA;
    League leagueB;

    for (const auto& team : groupATeams) {
        leagueA.addTeam(team);
    }

    for (const auto& team : groupBTeams) {
        leagueB.addTeam(team);
    }

    leagueB.addTeam(winner);

    Tournament tournamentA(leagueA);
    tournamentA.runRoundRobin();

    Tournament tournamentB(leagueB);
    tournamentB.runRoundRobin();

    Team groupAWinner = leagueA.getTeamByIndex(0);
    Team groupBWinner = leagueB.getTeamByIndex(0);
    Team groupARunnerUp = leagueA.getTeamByIndex(1);
    Team groupBRunnerUp = leagueB.getTeamByIndex(1);

    groupAWinner.resetStats();
    groupBWinner.resetStats();
    groupARunnerUp.resetStats();
    groupBRunnerUp.resetStats();

    League finalRound;

    std::cout << "Starting final knockout round\n\n" << std::endl;

    finalRound.displayLeagueTable();

    finalRound.addTeam(groupAWinner);
    finalRound.addTeam(groupBRunnerUp);
    finalRound.addTeam(groupBWinner);
    finalRound.addTeam(groupARunnerUp);

    

    finalRound.processKnockoutFromLeague(finalRound);

    /*
        Europe
    */

    /*
        North America
    */

    /*
        Asia
    */

    return 0;
}

void processGroup(const std::string& fileName) {
    XMLParser parser(fileName);
    std::vector<Team> teams = parser.parseXML();

    if (teams.empty()) {
        std::cout << "No teams parsed from " << fileName << std::endl;
        return;
    }

    League league;
    for (const auto& team : teams) {
        league.addTeam(team);
    }

    Tournament tournament(league);
    tournament.runRoundRobin();
}
