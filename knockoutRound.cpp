#include "knockoutRound.h"
#include <cstdlib>
#include <ctime>
#include "match.h"  

// Constructor
KnockoutRound::KnockoutRound(Team& t1, Team& t2)
    : team1(t1), team2(t2), left(nullptr), right(nullptr), winner(t1) {}

// Simulate the knockout match between team1 and team2
void KnockoutRound::startMatch() {
    winner = startKnockoutMatch(team1, team2);  // Simulate the match and assign the winner
}

// Build the knockout tree
KnockoutRound* buildKnockoutTree(std::vector<Team>& teams) {
    if (teams.size() == 1) {
        // Only one team, return it as the root of the tree (final winner)
        return new KnockoutRound(teams[0], teams[0]);  // Pass references to the same team
    }

    std::vector<KnockoutRound*> nextRoundNodes;
    for (size_t i = 0; i < teams.size(); i += 2) {
        if (i + 1 < teams.size()) {
            // Create match nodes with team references
            KnockoutRound* matchNode = new KnockoutRound(teams[i], teams[i + 1]);
            nextRoundNodes.push_back(matchNode);
        }
    }

    while (nextRoundNodes.size() > 1) {
        std::vector<KnockoutRound*> nextLevelNodes;
        for (size_t i = 0; i < nextRoundNodes.size(); i += 2) {
            if (i + 1 < nextRoundNodes.size()) {
                // Create new match nodes with winner references from previous rounds
                KnockoutRound* matchNode = new KnockoutRound(nextRoundNodes[i]->winner, nextRoundNodes[i + 1]->winner);
                nextLevelNodes.push_back(matchNode);
            }
        }
        nextRoundNodes = nextLevelNodes;
    }

    // Start the final match for the winner
    nextRoundNodes[0]->startMatch();  // This will simulate the last match
    // Return the final match node (the winner)
    return nextRoundNodes[0];
}