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

    KnockoutRound(Team t1, Team t2);
    void startMatch();  // Function to start the knockout match
};

KnockoutRound* buildKnockoutTree(std::vector<Team>& teams);

#endif  // KNOCKOUT_TOURNAMENT_H