#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "XMLParser.h"
#include "League.h"
#include "Tournament.h"
#include <random>
#include "KnockoutRound.h"

#include <windows.h>
#include <wincrypt.h>

unsigned int getTrueRandomSeed() {
    std::ifstream random_device("/dev/urandom", std::ios::binary);
    if (!random_device) {
        std::cerr << "Failed to open /dev/urandom." << std::endl;
        return 0;  // Fallback to a default value if it fails
    }

    unsigned int seed;
    random_device.read(reinterpret_cast<char*>(&seed), sizeof(seed));
    return seed;
}


int main() {
    
    unsigned int seed = getTrueRandomSeed();
    std::cout << "Truly random seed: " << seed << std::endl;

    std::srand(seed);  // Set the seed for std::rand

    int random_number = std::rand();
    std::cout << "Random number: " << random_number << std::endl;

    XMLParser groupAParser("oceania_knockout_round.xml");
    std::vector<Team> groupATeams = groupAParser.parseXML();


    KnockoutRound* firstOceaniaRound = buildKnockoutTree(groupATeams);

    Team firstOceaniaWinner = firstOceaniaRound->winner;

    std::cout << firstOceaniaWinner.getName() << std::endl;

    return 0;
}

