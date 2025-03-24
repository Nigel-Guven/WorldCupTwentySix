// Tournament.cpp
#include "Tournament.h"
#include "League.h"
#include <iostream>

Tournament::Tournament(League& league) : league(league) {}

void Tournament::runRoundRobin() {

    int numTeams = league.getTeams().size();

    for (int i = 0; i < numTeams; ++i) {
        for (int j = i + 1; j < numTeams; ++j) {
            league.simulateMatch(i, j);
            league.simulateMatch(j, i);
        }
    }

    league.sortTeams();
    
    /*
    // Display the top 6 teams
    std::cout << "\nTop 6 Teams:\n";
    int topTeamsCount = std::min(6, static_cast<int>(league.getTeams().size())); // In case there are fewer than 6 teams
    for (int i = 0; i < topTeamsCount; ++i) {
        league.getTeams()[i].getName();  // Display stats of the top team
    }*/
    
    league.displayLeagueTable();

    /*
    * // Display the winner
    if (!league.getTeams().empty()) {
        std::cout << "\nWinner: " << league.getTeams().front().getName() << "\n";
    }
    else {
        std::cout << "\nNo teams in the league.\n";
    }
    */

    for (auto& team : league.getTeams()) {
        team.resetStats();
    }

}
