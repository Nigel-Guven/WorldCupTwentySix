#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "XMLParser.h"
#include "League.h"
#include "Tournament.h"
#include <random>
#include "KnockoutRound.h"
#include "jsonParser.h"

League createLeagueFromXMLFile(const std::string& fileName);

int main() {
    
    std::srand(static_cast<unsigned int>(std::time(0)));  // Set the seed for std::rand

    #ifndef  World Rankings

    /*
        Europe
    */

    JSONParser parser;
    std::unordered_map<std::string, int> worldRankings = parser.parseJsonFile("world_rankings.json");

    #endif

    #ifndef  UEFA

    /*
        Europe
    */

    const std::vector<std::string> uefaGroups = {
        "uefa_group_a.xml",
        "uefa_group_b.xml",
        "uefa_group_c.xml",
        "uefa_group_d.xml",
        "uefa_group_e.xml",
        "uefa_group_f.xml",
        "uefa_group_g.xml",
        "uefa_group_h.xml",
        "uefa_group_i.xml",
        "uefa_group_j.xml",
        "uefa_group_k.xml",
        "uefa_group_l.xml"
    };

    XMLParser uefaNationsLeagueParser("uefa_nations_league_rankings.xml");
    std::vector<Team> nationsLeagueTeams = uefaNationsLeagueParser.parsePlayoffXML();

    League worldCupUefaQualifiedTeamsForWorldCup;
    League uefaGroupsSecondRound;
    


    for (const auto& group : uefaGroups) {
        League uefaGroup = createLeagueFromXMLFile(group);
        Tournament uefaTournament(uefaGroup);
        uefaTournament.runRoundRobin(true);

        Team team1 = uefaGroup.getTeamByIndex(0);
        Team team2 = uefaGroup.getTeamByIndex(1);

        if (std::find(worldCupUefaQualifiedTeamsForWorldCup.getTeams().begin(), worldCupUefaQualifiedTeamsForWorldCup.getTeams().end(), team1) == worldCupUefaQualifiedTeamsForWorldCup.getTeams().end()) {
            worldCupUefaQualifiedTeamsForWorldCup.addTeam(team1);
        }

        if (std::find(uefaGroupsSecondRound.getTeams().begin(), uefaGroupsSecondRound.getTeams().end(), team2) == uefaGroupsSecondRound.getTeams().end()) {
            uefaGroupsSecondRound.addTeam(team2);
        }

        for (int i = 0; i < 2; ++i) {
            Team teamQualified = uefaGroup.getTeamByIndex(i);

            auto it = std::find(nationsLeagueTeams.begin(), nationsLeagueTeams.end(), teamQualified);
            if (it != nationsLeagueTeams.end()) {
                nationsLeagueTeams.erase(it);
            }
        }
        
    }

    for (int i = 0; i < 4; ++i) 
    {
        Team teamQualifiedViaNationsLeague = nationsLeagueTeams.at(i);
        auto it = worldRankings.find(teamQualifiedViaNationsLeague.getName());

        if (it != worldRankings.end()) {
            // Update the team's points if it exists in the world rankings
            teamQualifiedViaNationsLeague.setRankingPoints(it->second);
            uefaGroupsSecondRound.addTeam(teamQualifiedViaNationsLeague);
        }
    }

    std::vector<Team> secondRoundWinners = buildMultipleKnockoutTrees(uefaGroupsSecondRound.getTeams());

    for (Team team : secondRoundWinners)
    {
        worldCupUefaQualifiedTeamsForWorldCup.addTeam(team);
    }

    /*
        ---------------------------------
    */

    #endif

    #ifndef  South America

    /*
        South America
    */

    League worldCupSouthAmericaQualifiedTeamsForWorldCup;

    League southAmericanTable = createLeagueFromXMLFile("south_america.xml");
    Tournament southAmericanTournament(southAmericanTable);
    southAmericanTournament.runRoundRobin(true);

    Team southAmericanInterConfederationPlayoffTeam = southAmericanTable.getTeamByIndex(6);

    for (int i = 0; i < 6; i++)
    {
        Team southAmericanTeam = southAmericanTable.getTeamByIndex(i);
        worldCupSouthAmericaQualifiedTeamsForWorldCup.addTeam(southAmericanTeam);
    }

    /*
        ---------------------------------
    */

    #endif

    #ifndef  Africa

    /*
        Africa
    */

    League worldCupAfricaQualifiedTeamsForWorldCup;

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

    League africaGroupsSecondPlace;

    for (const auto& group : africaGroups) {
        League africanGroup = createLeagueFromXMLFile(group);
        Tournament africaTournament(africanGroup);
        africaTournament.runRoundRobin(false);

        Team firstPlaceTeam = africanGroup.getTeamByIndex(0);
        Team secondPlaceTeam = africanGroup.getTeamByIndex(1);

        worldCupAfricaQualifiedTeamsForWorldCup.addTeam(firstPlaceTeam);
        africaGroupsSecondPlace.addTeam(secondPlaceTeam);
    }

    africaGroupsSecondPlace.sortTeams();
    africaGroupsSecondPlace.displayLeagueTable();

    std::vector<Team> knockoutRoundTeams = {
        africaGroupsSecondPlace.getTeamByIndex(0), // First team from Group A
        africaGroupsSecondPlace.getTeamByIndex(3), // Second team from Group B
        africaGroupsSecondPlace.getTeamByIndex(2), // Second team from Group A
        africaGroupsSecondPlace.getTeamByIndex(1)  // First team from Group B
    };

    KnockoutRound* africaRunnersUpRound = buildKnockoutTree(knockoutRoundTeams);

    Team africanInterConfederationPlayoffTeam = africaRunnersUpRound->winner;

    /*
        ---------------------------------
    */
    #endif

    #ifndef Oceania
    
    /*
        OCEANIA
    */

    League worldCupOceaniaQualifiedTeamsForWorldCup;

    XMLParser groupAParser("oceania_knockout_round.xml");
    std::vector<Team> groupATeams = groupAParser.parseXML();


    KnockoutRound* firstOceaniaRound = buildKnockoutTree(groupATeams);

    Team firstRoundOceaniaWinner = firstOceaniaRound->winner;

    League oceaniaGroupA = createLeagueFromXMLFile("oceania_group_a.xml");
    League oceaniaGroupB = createLeagueFromXMLFile("oceania_group_b.xml");

    oceaniaGroupB.addTeam(firstRoundOceaniaWinner);

    Tournament tournament1(oceaniaGroupA);
    tournament1.runRoundRobin(true);
    Tournament tournament2(oceaniaGroupB);
    tournament2.runRoundRobin(true);

    std::vector<Team> finalOceaniaRoundTeams = {
        oceaniaGroupA.getTeamByIndex(0), // First team from Group A
        oceaniaGroupB.getTeamByIndex(1), // Second team from Group B
        oceaniaGroupA.getTeamByIndex(1), // Second team from Group A
        oceaniaGroupB.getTeamByIndex(0)  // First team from Group B
    };

    // Build the final knockout round tree
    KnockoutRound* finalOceaniaRound = buildKnockoutTree(finalOceaniaRoundTeams);
    
    Team finalRoundOceaniaWinner = finalOceaniaRound->winner;
    Team oceaniaInterConfederationPlayoffTeam = finalOceaniaRound->loser;

    worldCupOceaniaQualifiedTeamsForWorldCup.addTeam(finalRoundOceaniaWinner);

    /*
        ---------------------------------
    */

    #endif

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

