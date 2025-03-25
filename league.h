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

    void sortTeams();

    Team processKnockoutFromXMLFile(const std::string& fileName);
    Team processKnockoutFromLeague(League league);

      
    void displayLeagueTable() const;
    
    

private:
    std::vector<Team> teams;
};

#endif