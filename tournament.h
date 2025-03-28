// Tournament.h
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "League.h"

class Tournament {
public:
    Tournament(League& league);
    void runRoundRobin(bool resetStats);  // Run the round-robin tournament
    void runSingleRound(bool resetStats);

private:
    League& league;
};

#endif // TOURNAMENT_H
