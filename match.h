#ifndef MATCH_H
#define MATCH_H

#include "Team.h";

void startGroupMatch(int team1Index, int team2Index);
Team startKnockoutMatch(Team& homeTeam, Team& awayTeam);

#endif