#ifndef MATCH_H
#define MATCH_H

#include "Team.h";
#include "League.h";

void startGroupMatch(int team1Index, int team2Index, League& league);
Team startKnockoutMatch(Team& homeTeam, Team& awayTeam);

#endif