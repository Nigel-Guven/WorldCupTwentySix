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
#include <thread>
#include <chrono>

League createLeagueFromXMLFile(const std::string& fileName);
std::vector<League> allocateTeamsIntoGroups(std::vector<Team>& teams, int amountOfGroups, int groupSize, bool delay);
std::vector<Team> getSubset(const std::vector<Team>& teams, int start, int end);

int main() {
    
    std::srand(static_cast<unsigned int>(std::time(0)));  // Set the seed for std::rand

    #ifndef  World Rankings

    /*
        World Rankings
    */

    JSONParser parser;
    std::unordered_map<std::string, int> worldRankings = parser.parseJsonFile("world_rankings.json");

    #endif

    #ifndef  Asia

    /*
        Asia
    */

    League asiaFirstRoundTeams = createLeagueFromXMLFile("asia_first_round.xml");
    League asiaSecondRoundTeams = createLeagueFromXMLFile("asia_second_round.xml");
    League asiaThirdRoundTeams;
    League asiaFourthRoundTeams;
    League asianFifthRoundTeams;

    League worldCupAsianQualifiedTeams;
    League asianWorldCupInterConfederationPlayoffTeams;

    std::vector<std::vector<Team>> listOfKnockoutMatches = splitKnockoutTeamsIntoSubsets(asiaFirstRoundTeams.getTeams(), 10);

    for (std::vector<Team> teamVector : listOfKnockoutMatches)
    {
        KnockoutRound* asiaFirstRoundFixture = buildKnockoutTree(teamVector);
        asiaSecondRoundTeams.addTeam(asiaFirstRoundFixture->winner);
    }

    std::vector<League> asianSecondRoundGroups =
        allocateTeamsIntoGroups(asiaSecondRoundTeams.getTeams(), 9, 4, false);

    for (int i = 0; i < asianSecondRoundGroups.size(); i++)
    {
        Tournament asiaSecondRoundTournament(asianSecondRoundGroups.at(i));
        asiaSecondRoundTournament.runRoundRobin(true);

        Team groupWinner = asianSecondRoundGroups.at(i).getTeamByIndex(0);
        Team groupRunnerUp = asianSecondRoundGroups.at(i).getTeamByIndex(1);

        asiaThirdRoundTeams.addTeam(groupWinner);
        asiaThirdRoundTeams.addTeam(groupRunnerUp);
    }

    asiaThirdRoundTeams.sortTeamsByRankingPoints();

    std::vector<League> asiaThirdRoundGroups =
        allocateTeamsIntoGroups(asiaThirdRoundTeams.getTeams(), 3, 6, false);

    for (int i = 0; i < asiaThirdRoundGroups.size(); i++)
    {
        Tournament asiaThirdRoundTournament(asiaThirdRoundGroups.at(i));
        asiaThirdRoundTournament.runRoundRobin(true);

        Team groupWinner = asiaThirdRoundGroups.at(i).getTeamByIndex(0);
        Team groupRunnerUp = asiaThirdRoundGroups.at(i).getTeamByIndex(1);
        Team groupThirdPlace = asiaThirdRoundGroups.at(i).getTeamByIndex(2);
        Team groupFourthPlace = asiaThirdRoundGroups.at(i).getTeamByIndex(3);

        worldCupAsianQualifiedTeams.addTeam(groupWinner);
        worldCupAsianQualifiedTeams.addTeam(groupRunnerUp);
        asiaFourthRoundTeams.addTeam(groupThirdPlace);
        asiaFourthRoundTeams.addTeam(groupFourthPlace);
    }

    asiaFourthRoundTeams.sortTeamsByRankingPoints();

    std::vector<League> asiaFourthRoundGroups =
        allocateTeamsIntoGroups(asiaFourthRoundTeams.getTeams(), 2, 3, false);

    for (int i = 0; i < asiaFourthRoundGroups.size(); i++)
    {
        Tournament asiaFourthRoundTournament(asiaFourthRoundGroups.at(i));
        asiaFourthRoundTournament.runRoundRobin(true);

        Team groupWinner = asiaFourthRoundGroups.at(i).getTeamByIndex(0);
        Team groupRunnerUp = asiaFourthRoundGroups.at(i).getTeamByIndex(1);

        worldCupAsianQualifiedTeams.addTeam(groupWinner);
        asianFifthRoundTeams.addTeam(groupRunnerUp);
    }

    Tournament asiaFifthRoundTournament(asianFifthRoundTeams);
    asiaFifthRoundTournament.runRoundRobin(true);

    asianWorldCupInterConfederationPlayoffTeams.addTeam(asianFifthRoundTeams.getTeams().at(0));

    /*
        ---------------------------------
    */

    #endif       

    #ifndef  North America

    /*
        North America
    */

    League northAmericanFirstRoundTeams = createLeagueFromXMLFile("north_america_first_round.xml");
    League northAmericanSecondRoundTeams = createLeagueFromXMLFile("north_america_second_round.xml");
    League northAmericanThirdRoundTeams;
    League worldCupNorthAmericanQualifiedTeams;
    League northAmericaWorldCupInterConfederationPlayoffTeams;


    Tournament northAmericaFirstRoundTournament(northAmericanFirstRoundTeams);
    northAmericaFirstRoundTournament.runRoundRobin(true);

    northAmericanSecondRoundTeams.addTeam(northAmericanFirstRoundTeams.getTeamByIndex(0));
    northAmericanSecondRoundTeams.addTeam(northAmericanFirstRoundTeams.getTeamByIndex(1));
 
    std::vector<League> northAmericanSecondRoundGroups = 
        allocateTeamsIntoGroups(northAmericanSecondRoundTeams.getTeams(), 6, 5, false);

    for (int i = 0; i < northAmericanSecondRoundGroups.size(); i++)
    {
        Tournament northAmericaSecondRoundTournament(northAmericanSecondRoundGroups.at(i));
        northAmericaSecondRoundTournament.runRoundRobin(true);

        Team groupWinner = northAmericanSecondRoundGroups.at(i).getTeamByIndex(0);
        Team groupRunnerUp = northAmericanSecondRoundGroups.at(i).getTeamByIndex(1);

        northAmericanThirdRoundTeams.addTeam(groupWinner);
        northAmericanThirdRoundTeams.addTeam(groupRunnerUp);
    }

    std::vector<League> northAmericanThirdRoundGroups =
        allocateTeamsIntoGroups(northAmericanThirdRoundTeams.getTeams(), 3, 4, false);

    for (int i = 0; i < northAmericanThirdRoundGroups.size(); i++)
    {
        Tournament northAmericaThirdRoundTournament(northAmericanThirdRoundGroups.at(i));
        northAmericaThirdRoundTournament.runRoundRobin(false);

        Team thirdRoundFirstPlace = northAmericanThirdRoundGroups.at(i).getTeamByIndex(0);
        thirdRoundFirstPlace.resetStats();
        worldCupNorthAmericanQualifiedTeams.addTeam(thirdRoundFirstPlace);

        northAmericaWorldCupInterConfederationPlayoffTeams.addTeam(northAmericanThirdRoundGroups.at(i).getTeamByIndex(1));
        northAmericaWorldCupInterConfederationPlayoffTeams.sortTeamsByLeaguePoints();

        if (northAmericaWorldCupInterConfederationPlayoffTeams.getTeams().size() == 3)
        {
            northAmericaWorldCupInterConfederationPlayoffTeams.removeTeams(1);
        }
    }

    /*
        ---------------------------------
    */

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

    League worldCupUefaQualifiedTeams;
    League uefaGroupsSecondRound;


    for (const auto& group : uefaGroups) {
        League uefaGroup = createLeagueFromXMLFile(group);
        Tournament uefaTournament(uefaGroup);
        uefaTournament.runRoundRobin(true);

        Team team1 = uefaGroup.getTeamByIndex(0);
        Team team2 = uefaGroup.getTeamByIndex(1);

        if (std::find(worldCupUefaQualifiedTeams.getTeams().begin(), worldCupUefaQualifiedTeams.getTeams().end(), team1) == worldCupUefaQualifiedTeams.getTeams().end()) {
            worldCupUefaQualifiedTeams.addTeam(team1);
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
        team.resetStats();
        worldCupUefaQualifiedTeams.addTeam(team);
    }

    /*
        ---------------------------------
    */

    #endif

    #ifndef  South America

    /*
        South America
    */

    League worldCupSouthAmericaQualifiedTeams;

    League southAmericanTable = createLeagueFromXMLFile("south_america.xml");
    Tournament southAmericanTournament(southAmericanTable);
    southAmericanTournament.runRoundRobin(true);

    Team southAmericanInterConfederationPlayoffTeam = southAmericanTable.getTeamByIndex(6);

    for (int i = 0; i < 6; i++)
    {
        Team southAmericanTeam = southAmericanTable.getTeamByIndex(i);
        worldCupSouthAmericaQualifiedTeams.addTeam(southAmericanTeam);
    }

    /*
        ---------------------------------
    */

    #endif

    #ifndef  Africa

    /*
        Africa
    */

    League worldCupAfricaQualifiedTeams;

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

        firstPlaceTeam.resetStats();
        worldCupAfricaQualifiedTeams.addTeam(firstPlaceTeam);
        africaGroupsSecondPlace.addTeam(secondPlaceTeam);
    }

    africaGroupsSecondPlace.sortTeamsByLeaguePoints();
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

    League worldCupOceaniaQualifiedTeams;

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

    finalRoundOceaniaWinner.resetStats();

    worldCupOceaniaQualifiedTeams.addTeam(finalRoundOceaniaWinner);

    /*
        ---------------------------------
    */

    #endif

    #ifndef Inter Confederation Playoffs

    /*
        Inter Confederation Playoffs
    */

    std::cout << asianWorldCupInterConfederationPlayoffTeams.getTeams().at(0).getName() << std::endl;
    std::cout << africanInterConfederationPlayoffTeam.getName() << std::endl;
    std::cout << northAmericaWorldCupInterConfederationPlayoffTeams.getTeams().at(0).getName() << std::endl;
    std::cout << northAmericaWorldCupInterConfederationPlayoffTeams.getTeams().at(1).getName() << std::endl;
    std::cout << southAmericanInterConfederationPlayoffTeam.getName() << std::endl;
    std::cout << oceaniaInterConfederationPlayoffTeam.getName() << std::endl;

    League interConfederationPlayoffTeams;
    League interConfederationPlayoffWinners;

    interConfederationPlayoffTeams.addTeam(asianWorldCupInterConfederationPlayoffTeams.getTeams().at(0));
    interConfederationPlayoffTeams.addTeam(africanInterConfederationPlayoffTeam);
    interConfederationPlayoffTeams.addTeam(northAmericaWorldCupInterConfederationPlayoffTeams.getTeams().at(0));
    interConfederationPlayoffTeams.addTeam(northAmericaWorldCupInterConfederationPlayoffTeams.getTeams().at(1));
    interConfederationPlayoffTeams.addTeam(southAmericanInterConfederationPlayoffTeam);
    interConfederationPlayoffTeams.addTeam(oceaniaInterConfederationPlayoffTeam);
    
    interConfederationPlayoffTeams.sortTeamsByRankingPoints();

    std::vector<League> interConfederationPlayoffPaths =
        allocateTeamsIntoGroups(interConfederationPlayoffTeams.getTeams(), 2, 3, false);


    std::vector<Team> interConfederationPathASemiFinal = getSubset(interConfederationPlayoffPaths.at(0).getTeams(), 1, 2);
    
    KnockoutRound* interConfederationPathASemiFinalFixture
        = buildKnockoutTree(interConfederationPathASemiFinal);

    std::vector<Team> interConfederationPathAFinal =
    {
        interConfederationPlayoffPaths.at(0).getTeams().at(0),  // First team
        interConfederationPathASemiFinalFixture->winner
    };

    KnockoutRound* interConfederationPathAFinalFixture
        = buildKnockoutTree(interConfederationPathAFinal);

    std::vector<Team> interConfederationPathBSemiFinal = getSubset(interConfederationPlayoffPaths.at(1).getTeams(), 1, 2);

    KnockoutRound* interConfederationPathBSemiFinalFixture
        = buildKnockoutTree(interConfederationPathBSemiFinal);

    std::vector<Team> interConfederationPathBFinal =
    {
        interConfederationPlayoffPaths.at(1).getTeams().at(0),  // First team
        interConfederationPathBSemiFinalFixture->winner
    };

    KnockoutRound* interConfederationPathBFinalFixture
        = buildKnockoutTree(interConfederationPathBFinal);

    Team teamFromPathA = interConfederationPathAFinalFixture->winner;
    Team teamFromPathB = interConfederationPathBFinalFixture->winner;

    teamFromPathA.resetStats();
    teamFromPathB.resetStats();

    interConfederationPlayoffWinners.addTeam(teamFromPathA);
    interConfederationPlayoffWinners.addTeam(teamFromPathB);

    for (Team team : interConfederationPlayoffWinners.getTeams()) {
        if (team.getName() == asianWorldCupInterConfederationPlayoffTeams.getTeams().at(0).getName()) {
            worldCupAsianQualifiedTeams.addTeam(team);
        }
        else if (team.getName() == africanInterConfederationPlayoffTeam.getName()) {
            worldCupAfricaQualifiedTeams.addTeam(team);
        }
        else if (team.getName() == southAmericanInterConfederationPlayoffTeam.getName()) {
            worldCupSouthAmericaQualifiedTeams.addTeam(team);
        }
        else if (team.getName() == oceaniaInterConfederationPlayoffTeam.getName()) {
            worldCupOceaniaQualifiedTeams.addTeam(team);
        }
        else if (team.getName() == northAmericaWorldCupInterConfederationPlayoffTeams.getTeams().at(0).getName() ||
            team.getName() == northAmericaWorldCupInterConfederationPlayoffTeams.getTeams().at(1).getName()) {
            worldCupNorthAmericanQualifiedTeams.addTeam(team);
        }
    }
    /*
        ---------------------------------
    */

    #endif

    #ifndef World Cup Allocation

    /*
        World Cup Group Allocation
    */

    League worldCupHosts = createLeagueFromXMLFile("hosts.xml");

    worldCupHosts.displayLeagueTeamAndRank();
    worldCupAfricaQualifiedTeams.displayLeagueTeamAndRank();
    worldCupAsianQualifiedTeams.displayLeagueTeamAndRank();
    worldCupUefaQualifiedTeams.displayLeagueTeamAndRank();
    worldCupNorthAmericanQualifiedTeams.displayLeagueTeamAndRank();
    worldCupSouthAmericaQualifiedTeams.displayLeagueTeamAndRank();
    worldCupOceaniaQualifiedTeams.displayLeagueTeamAndRank();

    League allQualifiedTeams;

    for (Team team : worldCupAfricaQualifiedTeams.getTeams()) { allQualifiedTeams.addTeam(team); }
    for (Team team : worldCupAsianQualifiedTeams.getTeams()) { allQualifiedTeams.addTeam(team); }
    for (Team team : worldCupUefaQualifiedTeams.getTeams()) { allQualifiedTeams.addTeam(team); }
    for (Team team : worldCupNorthAmericanQualifiedTeams.getTeams()) { allQualifiedTeams.addTeam(team); }
    for (Team team : worldCupSouthAmericaQualifiedTeams.getTeams()) { allQualifiedTeams.addTeam(team); }
    for (Team team : worldCupOceaniaQualifiedTeams.getTeams()) { allQualifiedTeams.addTeam(team); }

    allQualifiedTeams.sortTeamsByRankingPoints();

    std::vector<Team> worldCup2026Teams = worldCupHosts.getTeams();
    worldCup2026Teams.insert(
        worldCup2026Teams.end(),
        allQualifiedTeams.getTeams().begin(),
        allQualifiedTeams.getTeams().end());

    std::vector<League> worldCup2026Groups = allocateTeamsIntoGroups(worldCup2026Teams, 12, 4, false);

    League groupWinners;
    League groupRunnersUp;
    League thirdPlace;

    //Group Stage

    for (int i = 0; i < worldCup2026Groups.size(); i++)
    {
        Tournament worldCupGroup(worldCup2026Groups.at(i));
        worldCupGroup.runSingleRound(false);

        Team groupWinner = worldCup2026Groups.at(i).getTeamByIndex(0);
        Team groupRunnerUp = worldCup2026Groups.at(i).getTeamByIndex(1);
        Team groupThirdPlace = worldCup2026Groups.at(i).getTeamByIndex(2);

        groupWinners.addTeam(groupWinner);
        groupRunnersUp.addTeam(groupRunnerUp);
        thirdPlace.addTeam(groupThirdPlace);
    }

    thirdPlace.sortTeamsByLeaguePoints();

    std::vector<Team> bestThirdPlaceTeams = {
        thirdPlace.getTeamByIndex(0), 
        thirdPlace.getTeamByIndex(1), 
        thirdPlace.getTeamByIndex(2), 
        thirdPlace.getTeamByIndex(3),
        thirdPlace.getTeamByIndex(4),
        thirdPlace.getTeamByIndex(5),
        thirdPlace.getTeamByIndex(6),
        thirdPlace.getTeamByIndex(7),
    };

    // Knockout Stage

    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "\nThe round of 32 has started" << std::endl;

    std::vector<Team> roundOf32TeamsFixture1 =
    {
        groupRunnersUp.getTeamByIndex(0),  
        groupRunnersUp.getTeamByIndex(1)
    };

    std::vector<Team> roundOf32TeamsFixture2 =
    {
        groupWinners.getTeamByIndex(4),
        thirdPlace.getTeamByIndex(3)
    };

    std::vector<Team> roundOf32TeamsFixture3 =
    {
        groupWinners.getTeamByIndex(5),
        groupRunnersUp.getTeamByIndex(2)
    };

    std::vector<Team> roundOf32TeamsFixture4 =
    {
        groupWinners.getTeamByIndex(2),
        groupRunnersUp.getTeamByIndex(5)
    };

    std::vector<Team> roundOf32TeamsFixture5 =
    {
        groupWinners.getTeamByIndex(8),
        thirdPlace.getTeamByIndex(4)
    };

    std::vector<Team> roundOf32TeamsFixture6 =
    {
        groupWinners.getTeamByIndex(4),
        groupRunnersUp.getTeamByIndex(8)
    };

    std::vector<Team> roundOf32TeamsFixture7 =
    {
        groupWinners.getTeamByIndex(0),
        thirdPlace.getTeamByIndex(2)
    };

    std::vector<Team> roundOf32TeamsFixture8 =
    {
        groupWinners.getTeamByIndex(11),
        thirdPlace.getTeamByIndex(5)
    };

    std::vector<Team> roundOf32TeamsFixture9 =
    {
        groupWinners.getTeamByIndex(3),
        thirdPlace.getTeamByIndex(1)
    };

    std::vector<Team> roundOf32TeamsFixture10 =
    {
        groupWinners.getTeamByIndex(6),
        thirdPlace.getTeamByIndex(6)
    };

    std::vector<Team> roundOf32TeamsFixture11 =
    {
        groupRunnersUp.getTeamByIndex(10),
        groupRunnersUp.getTeamByIndex(11)
    };

    std::vector<Team> roundOf32TeamsFixture12 =
    {
        groupRunnersUp.getTeamByIndex(7),
        groupRunnersUp.getTeamByIndex(9)
    };

    std::vector<Team> roundOf32TeamsFixture13 =
    {
        groupWinners.getTeamByIndex(1),
        thirdPlace.getTeamByIndex(7)
    };

    std::vector<Team> roundOf32TeamsFixture14 =
    {
        groupWinners.getTeamByIndex(0),
        groupRunnersUp.getTeamByIndex(7)
    };

    std::vector<Team> roundOf32TeamsFixture15 =
    {
        groupWinners.getTeamByIndex(0),
        thirdPlace.getTeamByIndex(0)
    };

    std::vector<Team> roundOf32TeamsFixture16 =
    {
        groupRunnersUp.getTeamByIndex(3),
        groupRunnersUp.getTeamByIndex(6)
    };
    
    KnockoutRound* match73
        = buildKnockoutTree(roundOf32TeamsFixture1);
    KnockoutRound* match74
        = buildKnockoutTree(roundOf32TeamsFixture2);
    KnockoutRound* match75
        = buildKnockoutTree(roundOf32TeamsFixture3);
    KnockoutRound* match76
        = buildKnockoutTree(roundOf32TeamsFixture4);
    KnockoutRound* match77
        = buildKnockoutTree(roundOf32TeamsFixture5);
    KnockoutRound* match78
        = buildKnockoutTree(roundOf32TeamsFixture6);
    KnockoutRound* match79
        = buildKnockoutTree(roundOf32TeamsFixture7);
    KnockoutRound* match80
        = buildKnockoutTree(roundOf32TeamsFixture8);
    KnockoutRound* match81
        = buildKnockoutTree(roundOf32TeamsFixture9);
    KnockoutRound* match82
        = buildKnockoutTree(roundOf32TeamsFixture10);
    KnockoutRound* match83
        = buildKnockoutTree(roundOf32TeamsFixture11);
    KnockoutRound* match84
        = buildKnockoutTree(roundOf32TeamsFixture12);
    KnockoutRound* match85
        = buildKnockoutTree(roundOf32TeamsFixture13);
    KnockoutRound* match86
        = buildKnockoutTree(roundOf32TeamsFixture14);
    KnockoutRound* match87
        = buildKnockoutTree(roundOf32TeamsFixture15);
    KnockoutRound* match88
        = buildKnockoutTree(roundOf32TeamsFixture16);
        
    // Round of 16

    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "\nThe round of 16 has started" << std::endl;

    std::vector<Team> roundOf16TeamsFixture1 =
    {
        match74->winner,
        match77->winner,
    };

    std::vector<Team> roundOf16TeamsFixture2 =
    {
        match73->winner,
        match75->winner,
    };

    std::vector<Team> roundOf16TeamsFixture3 =
    {
        match76->winner,
        match78->winner,
    };

    std::vector<Team> roundOf16TeamsFixture4 =
    {
        match79->winner,
        match80->winner,
    };

    std::vector<Team> roundOf16TeamsFixture5 =
    {
        match83->winner,
        match84->winner,
    };

    std::vector<Team> roundOf16TeamsFixture6 =
    {
        match81->winner,
        match82->winner,
    };

    std::vector<Team> roundOf16TeamsFixture7 =
    {
        match86->winner,
        match88->winner,
    };

    std::vector<Team> roundOf16TeamsFixture8 =
    {
        match85->winner,
        match87->winner,
    };

    KnockoutRound* match89
        = buildKnockoutTree(roundOf16TeamsFixture1);
    KnockoutRound* match90
        = buildKnockoutTree(roundOf16TeamsFixture2);
    KnockoutRound* match91
        = buildKnockoutTree(roundOf16TeamsFixture3);
    KnockoutRound* match92
        = buildKnockoutTree(roundOf16TeamsFixture4);
    KnockoutRound* match93
        = buildKnockoutTree(roundOf16TeamsFixture5);
    KnockoutRound* match94
        = buildKnockoutTree(roundOf16TeamsFixture6);
    KnockoutRound* match95
        = buildKnockoutTree(roundOf16TeamsFixture7);
    KnockoutRound* match96
        = buildKnockoutTree(roundOf16TeamsFixture8);

    // Quarter Finals

    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "\nThe quarter final has started" << std::endl;

    std::vector<Team> quarterFinalTeamsFixture1 =
    {
        match89->winner,
        match90->winner,
    };

    std::vector<Team> quarterFinalTeamsFixture2 =
    {
        match93->winner,
        match94->winner,
    };

    std::vector<Team> quarterFinalTeamsFixture3 =
    {
        match91->winner,
        match92->winner,
    };

    std::vector<Team> quarterFinalTeamsFixture4 =
    {
        match95->winner,
        match96->winner,
    };

    KnockoutRound* match97
        = buildKnockoutTree(quarterFinalTeamsFixture1);
    KnockoutRound* match98
        = buildKnockoutTree(quarterFinalTeamsFixture2);
    KnockoutRound* match99
        = buildKnockoutTree(quarterFinalTeamsFixture3);
    KnockoutRound* match100
        = buildKnockoutTree(quarterFinalTeamsFixture4);

    // Semi Final

    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "\nThe semi final has started" << std::endl;

    std::vector<Team> semiFinalTeamsFixture1 =
    {
        match97->winner,
        match98->winner,
    };

    std::vector<Team> semiFinalTeamsFixture2 =
    {
        match99->winner,
        match100->winner,
    };

    KnockoutRound* match101
        = buildKnockoutTree(semiFinalTeamsFixture1);
    KnockoutRound* match102
        = buildKnockoutTree(semiFinalTeamsFixture2);

    // Third Place

    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "\nThe Third place round has started" << std::endl;

    std::vector<Team> thirdPlaceTeamsFixture =
    {
        match101->loser,
        match102->loser,
    };

    KnockoutRound* match103
        = buildKnockoutTree(thirdPlaceTeamsFixture);

    // Final

    std::cout << "\n-----------------------------------" << std::endl;
    std::cout << "\nThe Final has started!!" << std::endl;

    std::vector<Team> finalTeamsFixture =
    {
        match101->winner,
        match102->winner,
    };

    KnockoutRound* match104
        = buildKnockoutTree(finalTeamsFixture);
    
    std::cout << match103->loser.getName() << " has finished fourth place." << std::endl;
    std::cout << match103->winner.getName() << " has finished third place." << std::endl;
    std::cout << match104->loser.getName() << " has finished second place." << std::endl;
    std::cout << " \n" << std::endl;
    std::cout << match104->winner.getName() << " has won the world cup! Hooray!" << std::endl;

    #endif

    return 0;
}

#ifndef Functions

League createLeagueFromXMLFile(const std::string& fileName) {
    XMLParser parser(fileName);
    std::vector<Team> xmlTeams = parser.parseXML();

    League league;
    for (const auto& team : xmlTeams) {
        league.addTeam(team);
    }

    return league;
}

std::vector<League> allocateTeamsIntoGroups(std::vector<Team>& teams, int amountOfGroups, int groupSize, bool delay) {

    std::vector<League> listOfLeagues;

    if (teams.size() < amountOfGroups * groupSize) {
        std::cout << "Not enough teams to fill the groups!" << std::endl;
        return listOfLeagues;
    }

    std::srand(static_cast<unsigned int>(std::time(0)));

    // Vector to store the groups
    std::vector<std::vector<Team>> groups(amountOfGroups);

    // Step 1: Shuffle each group of n teams separately
    std::vector<std::vector<Team>> shuffledBlocks;

    for (size_t i = 0; i < teams.size(); i += groupSize) {
        // Create a block of n teams
        std::vector<Team> block(teams.begin() + i, teams.begin() + std::min(i + groupSize, teams.size()));

        // Shuffle the block
        std::random_shuffle(block.begin(), block.end());

        // Add shuffled block to shuffledBlocks
        shuffledBlocks.push_back(block);
    }

    // Step 2: Allocate the shuffled blocks into the groups
    int groupIndex = 0;
    for (auto& block : shuffledBlocks) {
        for (auto& team : block) {
            groups[groupIndex % amountOfGroups].push_back(team);
            groupIndex++;
        }
    }

    // Step 3: Print the groups
    for (int i = 0; i < amountOfGroups; ++i) {
        
        League league;
        
        std::cout << "Group " << (i + 1) << ": ";
        for (const Team& team : groups[i]) {
            league.addTeam(team);
            std::cout << team.getName() << " ";
            if (delay) {
                std::this_thread::sleep_for(std::chrono::seconds(2)); // Sleep for 2 seconds
            }
        }
        std::cout << std::endl;

        listOfLeagues.push_back(league);
    }

    return listOfLeagues;
}

std::vector<Team> getSubset(const std::vector<Team>& teams, int start, int end) {
    // Check if start and end are valid
    if (start < 0 || end >= teams.size() || start > end) {
        throw std::invalid_argument("Invalid range for subset.");
    }

    // Extract the subset using iterators
    return std::vector<Team>(teams.begin() + start, teams.begin() + end + 1);
}

#endif