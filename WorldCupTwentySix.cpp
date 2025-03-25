
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "XMLParser.h"
#include "League.h"
#include "Tournament.h"

void processGroup(const std::string& fileName);

int main() {
    
    //Generate Random Seed

    std::srand(std::time(0));

    /*
        South America
    */ 
    
    std::cout << "Starting South America Tournament...\n";
    processGroup("south_america.xml");
    

    /*
        Africa
    */
    const std::vector<std::string> africaGroups = {
        "africa_group_a.xml",
        "africa_group_b.xml",
        "africa_group_c.xml",
        "africa_group_d.xml",
        "africa_group_e.xml",
        "africa_group_f.xml",
        "africa_group_g.xml",
        "africa_group_h.xml",
        "africa_group_i.xml"
    };
    
    for (const auto& group : africaGroups) {
        std::cout << "Starting Tournament for " << group << "...\n";
        processGroup(group);
    }

    /*
        Europe
    */

    /*
        North America
    */

    /*
        Oceania
    */



    /*
        Asia
    */

    return 0;
}

void processGroup(const std::string& fileName) {
    XMLParser parser(fileName);
    std::vector<Team> teams = parser.parseXML();

    if (teams.empty()) {
        std::cout << "No teams parsed from " << fileName << std::endl;
        return;
    }

    League league;
    for (const auto& team : teams) {
        league.addTeam(team);
    }

    Tournament tournament(league);
    tournament.runRoundRobin();
}
