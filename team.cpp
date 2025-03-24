#include "Team.h"
#include <iostream>

Team::Team(std::string name, int rankingPoints)
    : name(name), rankingPoints(rankingPoints), wins(0), draws(0), losses(0), leaguePoints(0) {}

void Team::addWin() {
    wins++;
    leaguePoints += 3; // 3 points for a win
}

void Team::addDraw() {
    draws++;
    leaguePoints += 1; // 1 point for a draw
}

void Team::addLoss() {
    losses++;
    // No points for a loss
}

void Team::resetStats() {
    wins = 0;
    draws = 0;
    losses = 0;
    leaguePoints = 0;
}

void Team::displayStats() const {
    std::cout << name 
        << ", League Points: " << leaguePoints
        << ", Wins: " << wins
        << ", Draws: " << draws
        << ", Losses: " << losses << std::endl;
}

std::string Team::getName() const {
    std::cout << name << std::endl;
    return name;
}

int Team::getRankingPoints() const {
    return rankingPoints;
}

int Team::getLeaguePoints() const {
    return leaguePoints;
}

int Team::getWins() const {
    return wins;
}

int Team::getDraws() const {
    return draws;
}

int Team::getLosses() const {
    return losses;
}
