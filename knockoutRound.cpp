#include "KnockoutRound.h"
#include <cstdlib>
#include <ctime>
#include "Match.h"  
#include <iostream>
#include <algorithm>
#include <random>

// Constructor
KnockoutRound::KnockoutRound(Team t1, Team t2)
    : team1(t1), team2(t2), left(nullptr), right(nullptr), winner(t1), loser(t2) {}

// Simulate the knockout match between team1 and team2
void KnockoutRound::startMatch() {
    winner = startKnockoutMatch(team1, team2);

    if (winner.getName() == team1.getName())
        loser = team2;
    else
        loser = team1;
}

KnockoutRound* buildKnockoutTree(std::vector<Team>& teams) {

    std::vector<Team> adjustedTeams = teams;

    std::vector<KnockoutRound*> nextRoundNodes;
    int roundNumber = 1;  

    for (size_t i = 0; i < adjustedTeams.size(); i += 2) {
        if (i + 1 < adjustedTeams.size()) 
        {
            KnockoutRound* matchNode = new KnockoutRound(adjustedTeams[i], adjustedTeams[i + 1]);
            matchNode->startMatch();
            nextRoundNodes.push_back(matchNode);
        }
    }

    while (nextRoundNodes.size() > 1) {
        roundNumber++;
        std::vector<KnockoutRound*> nextLevelNodes;

        std::cout << "\nRound " << roundNumber << " matches:\n" << std::endl;

        for (size_t i = 0; i < nextRoundNodes.size(); i += 2) {
            if (i + 1 < nextRoundNodes.size()) {

                KnockoutRound* matchNode = new KnockoutRound(nextRoundNodes[i]->winner, nextRoundNodes[i + 1]->winner);
                matchNode->startMatch();
                nextLevelNodes.push_back(matchNode);
            }
            else 
            {
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

std::vector<Team> buildMultipleKnockoutTrees(std::vector<Team>& teams) {
    std::vector<Team> multipleKnockoutRoundWinners;

    std::vector<std::vector<Team>> groups;

    for (int i = 0; i < 4; ++i) {
        std::vector<Team> group(teams.begin() + i * 4, teams.begin() + (i + 1) * 4);
        groups.push_back(group);
    }

    std::srand(static_cast<unsigned int>(std::time(0)));  // Seed random number generator
    std::random_shuffle(groups.begin(), groups.end());

    for (int i = 0; i < groups.size(); ++i) {

        std::vector<Team> uefaSecondRoundPathTeams;
        std::random_shuffle(groups[i].begin(), groups[i].end());

        for (int j = 0; j < 4; ++j) {
            uefaSecondRoundPathTeams.push_back(groups[j].at(i));

            std::cout << "Assigned team to knockout path: " << groups[j].at(i).getName() << std::endl;
        }

        KnockoutRound* uefaSecondRoundPath = buildKnockoutTree(uefaSecondRoundPathTeams);
        multipleKnockoutRoundWinners.push_back(uefaSecondRoundPath->winner);
        std::cout << "Knockout round winner: " << uefaSecondRoundPath->winner.getName() << std::endl;
    }

    return multipleKnockoutRoundWinners;
}

std::vector<std::vector<Team>> splitKnockoutTeamsIntoSubsets(const std::vector<Team>& teams, int n) {

    if (n <= 0 || n > teams.size()) {
        throw std::invalid_argument("Invalid number of subsets (n).");
    }

    int subsetSize = teams.size() / n;
    int remainder = teams.size() % n;

    std::vector<std::vector<Team>> subsets;

    int index = 0;

    for (int i = 0; i < n; ++i) {

        int currentSubsetSize = subsetSize + (i < remainder ? 1 : 0);

        std::vector<Team> subset;
        for (int j = 0; j < currentSubsetSize; ++j) {
            subset.push_back(teams[index++]);
        }

        subsets.push_back(subset);
    }

    return subsets;
}