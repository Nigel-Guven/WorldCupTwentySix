#ifndef SIMULATIONS_H
#define SIMULATIONS_H

#include "Team.h"

// Function declarations for the four game modes
void simulateClassicGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, int remainingPoints, bool isKnockout);
void simulateRandomGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, bool isKnockout);
void simulateFirstTo50GameMode(Team& homeTeam, Team& awayTeam, bool isKnockout);
void simulateNegativeInfluenceGameMode(Team& homeTeam, Team& awayTeam, int& team1Points, int& team2Points, bool isKnockout);

Team penaltyShootout(Team& homeTeam, Team& awayTeam);
Team penaltyShootoutSuddenDeath(Team& homeTeam, Team& awayTeam);

#endif // SIMULATIONS_H
