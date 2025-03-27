#ifndef KNOCKOUT_TOURNAMENT_H
#define KNOCKOUT_TOURNAMENT_H

#include "team.h"
#include <vector>

struct KnockoutRound {
    Team team1;
    Team team2;
    KnockoutRound* left;
    KnockoutRound* right;
    Team winner;
    Team loser;

    KnockoutRound(Team t1, Team t2);
    void startMatch();
};

KnockoutRound* buildKnockoutTree(std::vector<Team>& teams);
std::vector<Team> buildMultipleKnockoutTrees(std::vector<Team>& teams);
std::vector<std::vector<Team>> splitKnockoutTeamsIntoSubsets(const std::vector<Team>& teams, int n);

#endif