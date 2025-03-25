#ifndef LEAGUE_H
#define LEAGUE_H

#include <vector>
#include "Team.h"

class League {
public:
    League();  // Constructor

    void addTeam(const Team& team);  // Add a team to the league
    void sortTeams();  // Sort teams by league points and ranking points
    Team processKnockoutFromXMLFile(const std::string& fileName);
    Team processKnockoutFromLeague(League league);
    int simulateKnockoutMatch(int team1Index, int team2Index);
    int penaltyShootout(Team& homeTeam, int team1Index, Team& awayTeam, int team2Index);
    void simulateGroupMatch(int team1Index, int team2Index);  // Simulate a match between two teams
    void displayLeagueTable() const;  // Display the current league standings
    Team& getTeamByIndex(int index);

    std::vector<Team>& getTeams(); // Getter for the list of teams

private:
    std::vector<Team> teams;  // List of teams in the league
};

#endif // LEAGUE_H