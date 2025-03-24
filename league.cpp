#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "League.h"

League::League() {}

void League::addTeam(const Team& team) {
    teams.push_back(team);  // Add the team to the list of teams
}

void League::sortTeams() {
    // Sort teams by league points (descending order), then by ranking points
    std::sort(teams.begin(), teams.end(), [](const Team& a, const Team& b) {
        if (a.getLeaguePoints() == b.getLeaguePoints())
            return a.getRankingPoints() > b.getRankingPoints();
        return a.getLeaguePoints() > b.getLeaguePoints();
        });
}

void League::simulateMatch(int team1Index, int team2Index) {
    Team& homeTeam = teams[team1Index];
    Team& awayTeam = teams[team2Index];

    // Logic to simulate match based on ranking points (for simplicity, using random values)
    int team1Points = homeTeam.getRankingPoints() + 5;
    int team2Points = awayTeam.getRankingPoints();
    int totalPoints = 100;
    int remainingPoints = totalPoints - (team1Points + team2Points);

    int gameMode = std::rand() % 4;

    if (gameMode == 0) 
    {
        // Classic Game Mode

        for (int i = 0; i < remainingPoints; ++i) {
            bool team1GetsPoint = std::rand() % 2 == 0;
            if (team1GetsPoint) {
                team1Points++;
            }
            else {
                team2Points++;
            }
        }

        if (team1Points > team2Points) {
            homeTeam.addWin();
            awayTeam.addLoss();
        }
        else if (team2Points > team1Points) {
            awayTeam.addWin();
            homeTeam.addLoss();
        }
        else {
            homeTeam.addDraw();
            awayTeam.addDraw();
        }
    }
    else if (gameMode == 1) {
        // Random Number Based Game Mode

        int homeWinChance = team1Points;
        int awayWinChance = 100 - team2Points;
        int drawChanceStart = team1Points + 1;
        
        int randomNumber = std::rand() % 100 + 1;

        if (randomNumber >= drawChanceStart && randomNumber <= team2Points) {
            homeTeam.addDraw();
            awayTeam.addDraw();
        }
        else if (randomNumber <= homeWinChance) {
            homeTeam.addWin();
            awayTeam.addLoss();
        }
        else {
            awayTeam.addWin();
            homeTeam.addLoss();
        }     
    }
    else if (gameMode == 2) {
        // First to 50 - Based on Classic but both teams are equal

        int homeTeamScore = 0;
        int awayTeamScore = 0;

        while (homeTeamScore < 50 && awayTeamScore < 50) {
            bool team1GetsPoint = std::rand() % 2 == 0;
            if (team1GetsPoint) {
                homeTeamScore++;
            }
            else {
                awayTeamScore++;
            }
        }

        // Check the winner or draw
        if (homeTeamScore >= 50 && (homeTeamScore - awayTeamScore > 4)) {
            homeTeam.addWin();
            awayTeam.addLoss();
        }
        else if (awayTeamScore >= 50 && (awayTeamScore - homeTeamScore > 4)) {
            awayTeam.addWin();
            homeTeam.addLoss();
        }
        else {
            // If the difference is 4 or less, it is a draw
            homeTeam.addDraw();
            awayTeam.addDraw();
        }
    }
    else if (gameMode == 3) {
        // Negative Influence Game Mode - Account for injuries, red cards, poor performance etc.

        bool homeTeamInjury = std::rand() % 100 < 6;  // 20% chance for an injury
        bool awayTeamInjury = std::rand() % 100 < 6;  // 20% chance for an injury

        bool homeTeamRedCard = std::rand() % 100 < 7;  // 20% chance for a red card
        bool awayTeamRedCard = std::rand() % 100 < 7;  // 20% chance for a red card

        int team1PointsNegativeMode = homeTeam.getRankingPoints() + 5;
        int team2PointsNegativeMode = awayTeam.getRankingPoints();

        if (homeTeamInjury) {
            team1PointsNegativeMode -= 3; // Deduct 3 points for an injury/red card
        }

        if (awayTeamInjury) {
            team2PointsNegativeMode -= 3; // Deduct 3 points for an injury/red card
        }

        if (homeTeamRedCard) {
            team1PointsNegativeMode -= 7; // Deduct 3 points for an injury/red card
        }

        if (awayTeamRedCard) {
            team2PointsNegativeMode -= 7; // Deduct 3 points for an injury/red card
        }

        
        int totalPointsNegativeMode = 100;
        int remainingPointsNegativeMode = totalPointsNegativeMode - (team1PointsNegativeMode + team2PointsNegativeMode);

        for (int i = 0; i < remainingPointsNegativeMode; ++i) {
            bool team1GetsPoint = std::rand() % 2 == 0;
            if (team1GetsPoint) {
                team1PointsNegativeMode++;
            }
            else {
                team2PointsNegativeMode++;
            }
        }

        if (team1PointsNegativeMode > team2PointsNegativeMode) {
            homeTeam.addWin();
            awayTeam.addLoss();
        }
        else if (team2PointsNegativeMode > team1PointsNegativeMode) {
            awayTeam.addWin();
            homeTeam.addLoss();
        }
        else {
            homeTeam.addDraw();
            awayTeam.addDraw();
        }
  
    }
}

void League::displayLeagueTable() const {
    std::cout << "League Table: \n";
    for (const auto& team : teams) {
        team.displayStats();  // Display each team's statistics
    }
}

std::vector<Team>& League::getTeams() {
    return teams;
}
