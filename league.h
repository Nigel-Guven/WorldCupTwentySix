#ifndef LEAGUE_H
#define LEAGUE_H

#include <vector>
#include "Team.h"

class League {
public:
    League();

    void addTeam(const Team& team);

    std::vector<Team>& getTeams();
    Team& getTeamByIndex(int index);

    void removeTeams(int n);

    //League createLeagueFromXMLFile(const std::string& fileName);
    void sortTeamsByLeaguePoints();
    void sortTeamsByRankingPoints();

    void displayLeagueTable() const;
    void displayLeagueTeamAndRank() const;
    
    

private:
    std::vector<Team> teams;
};

#endif