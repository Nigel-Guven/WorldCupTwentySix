#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "League.h"
#include "xmlParser.h"
#include "simulations.h"

League::League() {}

void League::addTeam(const Team& team) {
    teams.push_back(team);
}

void League::sortTeamsByLeaguePoints() {
    std::sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
        if (a.getLeaguePoints() == b.getLeaguePoints())
            return a.getRankingPoints() > b.getRankingPoints();
        return a.getLeaguePoints() > b.getLeaguePoints();
        });
}

void League::sortTeamsByRankingPoints() {
    std::sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) 
    {
        return a.getRankingPoints() > b.getRankingPoints();
    });
}

void League::displayLeagueTable() const {
    std::cout << "\nLeague Table: \n";
    for (const auto& team : teams) {
        team.displayStats();
    }
    std::cout << "\n";
}

void League::displayLeagueTeamAndRank() const {
    std::cout << "\nLeague Table: \n";
    for (const auto& team : teams) {
        std::cout << team.getName() << ", Rank: " << team.getRankingPoints() << std::endl;
    }
    std::cout << "\n";
}

std::vector<Team>& League::getTeams() {
    return teams;
}

Team& League::getTeamByIndex(int index) {
    if (index >= 0 && index < teams.size()) {
        return teams[index];
    }
    throw std::out_of_range("Index is out of range");
}

// New removeTeams function
void League::removeTeams(int n) {
    // Ensure we remove no more than the number of teams available
    if (n > teams.size()) {
        n = teams.size(); // Adjust n if it's larger than the available teams
    }

    // Remove the last 'n' teams
    teams.erase(teams.end() - n, teams.end());
}