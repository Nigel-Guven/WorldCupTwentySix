#ifndef TEAM_H
#define TEAM_H

#include <string>

class Team {
public:
    // Constructor
    Team(std::string name, int rankingPoints);

    // Methods for match results
    void addWin();
    void addDraw();
    void addLoss();

    void resetStats();

    void updateLeaguePoints(); // Update league points (based on match results)

    // Display team information
    void displayStats() const;

    // Getters for team information
    std::string getName() const;
    int getRankingPoints() const;
    int getLeaguePoints() const;
    int getWins() const;
    int getDraws() const;
    int getLosses() const;

private:
    std::string name;
    int rankingPoints;  // Ranking points (based on strength or initial ranking)
    int wins;
    int draws;
    int losses;
    int leaguePoints;   // Points accumulated in league (win = 3, draw = 1, loss = 0)
};

#endif // TEAM_H
