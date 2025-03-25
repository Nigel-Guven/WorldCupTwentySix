#include "KnockoutRound.h"
#include <cstdlib>
#include <ctime>
#include "Match.h"  
#include <iostream>

// Constructor
KnockoutRound::KnockoutRound(Team t1, Team t2)
    : team1(t1), team2(t2), left(nullptr), right(nullptr), winner(t1) {}

// Simulate the knockout match between team1 and team2
void KnockoutRound::startMatch() {
    winner = startKnockoutMatch(team1, team2);  // Simulate the match and assign the winner
}

KnockoutRound* buildKnockoutTree(std::vector<Team>& teams) {
    // Handle case where number of teams is not a power of 2 by adding "byes"
    std::vector<Team> adjustedTeams = teams;

    std::cout << "Adjusted Teams: " << std::endl;
    for (const auto& team : adjustedTeams) {
        std::cout << team.getName() << " - " << team.getRankingPoints() << " points" << std::endl;
    }

    std::vector<KnockoutRound*> nextRoundNodes;
    int roundNumber = 1;  // Start with Round 1

    // Create the first round of matches
    std::cout << "\nRound " << roundNumber << " matches:\n" << std::endl;

    // Create the first round of matches
    for (size_t i = 0; i < adjustedTeams.size(); i += 2) {
        // Ensure that we're not out of bounds
        if (i + 1 < adjustedTeams.size()) {
            std::cout << "Creating match: " << adjustedTeams[i].getName()
                << " vs " << adjustedTeams[i + 1].getName() << std::endl;
            KnockoutRound* matchNode = new KnockoutRound(adjustedTeams[i], adjustedTeams[i + 1]);
            matchNode->startMatch(); // Simulate the match and assign the winner
            nextRoundNodes.push_back(matchNode);
        }
        else {
            std::cout << "Skipping team: " << adjustedTeams[i].getName() << " (odd number of teams)" << std::endl;
        }
    }

    // Continue creating subsequent rounds until there is one winner
    while (nextRoundNodes.size() > 1) {
        roundNumber++;
        std::vector<KnockoutRound*> nextLevelNodes;

        std::cout << "\nRound " << roundNumber << " matches:\n" << std::endl;

        for (size_t i = 0; i < nextRoundNodes.size(); i += 2) {
            if (i + 1 < nextRoundNodes.size()) {
                std::cout << "Creating match between: "
                    << nextRoundNodes[i]->winner.getName() << " vs "
                    << nextRoundNodes[i + 1]->winner.getName() << std::endl;
                KnockoutRound* matchNode = new KnockoutRound(nextRoundNodes[i]->winner, nextRoundNodes[i + 1]->winner);
                matchNode->startMatch(); // Simulate the match and assign the winner
                nextLevelNodes.push_back(matchNode);
            }
            else {
                std::cout << "Skipping match due to odd number of teams, passing through: "
                    << nextRoundNodes[i]->winner.getName() << std::endl;
                nextLevelNodes.push_back(nextRoundNodes[i]);
            }
        }
        nextRoundNodes = nextLevelNodes;
    }

    // Start the final match for the winner
    std::cout << "\nFinal Round:\n" << std::endl;
    nextRoundNodes[0]->startMatch();  // Simulate the final match
    std::cout << "Final winner: " << nextRoundNodes[0]->winner.getName() << std::endl;

    // Return the final match node (the winner)
    return nextRoundNodes[0];
}
