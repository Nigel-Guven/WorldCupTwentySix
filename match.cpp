#include "league.h"
#include "match.h"
#include "simulations.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void startGroupMatch(int team1Index, int team2Index, League& league) {
    Team& homeTeam = league.getTeams()[team1Index];
    Team& awayTeam = league.getTeams()[team2Index];

    int team1Points = homeTeam.getRankingPoints() + 5;
    int team2Points = awayTeam.getRankingPoints();
    int totalPoints = 100;
    int remainingPoints = totalPoints - (team1Points + team2Points);

    int gameMode = std::rand() % 4;

    switch (gameMode) {
    case 0:
        simulateClassicGameMode(homeTeam, awayTeam, team1Points, team2Points, remainingPoints, false);
        break;
    case 1:
        simulateRandomGameMode(homeTeam, awayTeam, team1Points, team2Points, false);
        break;
    case 2:
        simulateFirstTo50GameMode(homeTeam, awayTeam, false);
        break;
    case 3:
        simulateNegativeInfluenceGameMode(homeTeam, awayTeam, team1Points, team2Points, false);
        break;
    }
}

Team startKnockoutMatch(Team& homeTeam, Team& awayTeam) {

    int team1Points = homeTeam.getRankingPoints() + 5;
    int team2Points = awayTeam.getRankingPoints();
    int totalPoints = 100;
    int remainingPoints = totalPoints - (team1Points + team2Points);
    int gameMode = std::rand() % 4;

    switch (gameMode) {
    case 0:
        simulateClassicGameMode(homeTeam, awayTeam, team1Points, team2Points, remainingPoints, true);
        break;
    case 1:
        simulateRandomGameMode(homeTeam, awayTeam, team1Points, team2Points, true);
        break;
    case 2:
        simulateFirstTo50GameMode(homeTeam, awayTeam, true);
        break;
    case 3:
        simulateNegativeInfluenceGameMode(homeTeam, awayTeam, team1Points, team2Points, true);
        break;
    }

    return (team1Points > team2Points) ? homeTeam : awayTeam;
}