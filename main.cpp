
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "XMLParser.h"
#include "League.h"
#include "Tournament.h"
#include "KnockoutRound.h"

int main() {
    
    //Generate Random Seed

    std::srand(std::time(0));

    XMLParser groupAParser("oceania_knockout_round.xml");
    std::vector<Team> groupATeams = groupAParser.parseXML();


    KnockoutRound* firstOceaniaRound = buildKnockoutTree(groupATeams);

    std::cout << firstOceaniaRound->winner.getName();

    return 0;
}

