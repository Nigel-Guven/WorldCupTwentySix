// Tournament.h
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include "League.h"

class Tournament {
public:
    Tournament(League& league);
    void runRoundRobin();  // Run the round-robin tournament

private:
    League& league;
};

#endif // TOURNAMENT_H
