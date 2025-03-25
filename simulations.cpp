#include <iostream>
#include <cstdlib>
#include "Team.h"
#include "simulations.h"

void simulateClassicGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, int remainingPoints, bool isKnockout) {
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
    else if (isKnockout) {
        penaltyShootout(homeTeam, awayTeam);
    }
    else {
        homeTeam.addDraw();
        awayTeam.addDraw();
    }
}

void simulateRandomGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, bool isKnockout) {
    int homeWinChance = team1Points;
    int awayWinChance = 100 - team2Points;

    int randomNumber = std::rand() % 100 + 1;

    if (randomNumber > awayWinChance) {
        awayTeam.addWin();
        homeTeam.addLoss();
    }
    else if (randomNumber < homeWinChance) {
        homeTeam.addWin();
        awayTeam.addLoss();
    }
    else if (isKnockout) {
        penaltyShootout(homeTeam, awayTeam);
    }
    else {      
        homeTeam.addDraw();
        awayTeam.addDraw();
    }
}

void simulateFirstTo50GameMode(Team& homeTeam, Team& awayTeam, bool isKnockout) {
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
    else if (isKnockout) {
        penaltyShootout(homeTeam, awayTeam);
    }
    else {
        // If the difference is 4 or less, it is a draw
        homeTeam.addDraw();
        awayTeam.addDraw();
    }
}

void simulateNegativeInfluenceGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, bool isKnockout) {

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
    else if (isKnockout) {
        penaltyShootout(homeTeam, awayTeam);
    }
    else {
        homeTeam.addDraw();
        awayTeam.addDraw();
    }
}

void simulate5545GameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, bool isKnockout) {
    
    int homeTeamPoints = 0;
    int awayTeamPoints = 0;

    if (team1Points > team2Points)
    {
        homeTeamPoints == 100-55;
        awayTeamPoints == 45;
    }
    else if (team2Points > team1Points)
    {
        homeTeamPoints == 100-45;
        awayTeamPoints == 55;
    }

    while ((homeTeamPoints < 100) && (awayTeamPoints < 100)) {
        bool team1GetsPoint = std::rand() % 2 == 0;
        if (team1GetsPoint) {
            homeTeamPoints++;
        }
        else {
            awayTeamPoints++;
        }
    }
    
    // Check the winner or draw
    if (homeTeamPoints >= 100) {
        homeTeam.addWin();
        awayTeam.addLoss();
    }
    else if (awayTeamPoints >= 100) {
        awayTeam.addWin();
        homeTeam.addLoss();
    }
    else if (isKnockout) {
        penaltyShootout(homeTeam, awayTeam);
    }
    else {
        // If the difference is 4 or less, it is a draw
        homeTeam.addDraw();
        awayTeam.addDraw();
    }
}

Team penaltyShootout(Team& homeTeam, Team& awayTeam) {
    int homeTeamGoals = 0, awayTeamGoals = 0;

    for (int i = 0; i < 5; ++i) {
        homeTeamGoals += (std::rand() % 100 < 80);
        awayTeamGoals += (std::rand() % 100 < 80);
    }

    if (homeTeamGoals > awayTeamGoals) {
        homeTeam.addWin();
        awayTeam.addLoss();
        return homeTeam;
    }
    else if (awayTeamGoals > homeTeamGoals) {
        awayTeam.addWin();
        homeTeam.addLoss();
        return awayTeam;
    }

    return penaltyShootoutSuddenDeath(homeTeam, awayTeam);
}

Team penaltyShootoutSuddenDeath(Team& homeTeam, Team& awayTeam) {
    int homeTeamGoals = 0, awayTeamGoals = 0;
    int round = 1;

    while (true) {
        homeTeamGoals += (std::rand() % 100 < 80);
        awayTeamGoals += (std::rand() % 100 < 80);

        if (homeTeamGoals > awayTeamGoals) {
            homeTeam.addWin();
            awayTeam.addLoss();
            return homeTeam;
        }
        else if (awayTeamGoals > homeTeamGoals) {
            awayTeam.addWin();
            homeTeam.addLoss();
            return awayTeam;
        }

        round++;
    }
}