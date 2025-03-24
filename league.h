#ifndef LEAGUE_H
#define LEAGUE_H

#include <vector>
#include "Team.h"

class League {
public:
    League();  // Constructor

    void addTeam(const Team& team);  // Add a team to the league
    void sortTeams();  // Sort teams by league points and ranking points
    void simulateMatch(int team1Index, int team2Index);  // Simulate a match between two teams
    void displayLeagueTable() const;  // Display the current league standings

    std::vector<Team>& getTeams(); // Getter for the list of teams

private:
    std::vector<Team> teams;  // List of teams in the league
};

#endif // LEAGUE_H