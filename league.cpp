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

void League::sortTeams() {
    std::sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
        if (a.getLeaguePoints() == b.getLeaguePoints())
            return a.getRankingPoints() > b.getRankingPoints();
        return a.getLeaguePoints() > b.getLeaguePoints();
        });
}

void League::displayLeagueTable() const {
    std::cout << "League Table: \n";
    for (const auto& team : teams) {
        team.displayStats();
    }
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