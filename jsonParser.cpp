#include "JSONParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string, int> JSONParser::parseJsonFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string jsonString((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    std::unordered_map<std::string, int> teamsPoints;

    size_t teamsStart = jsonString.find("\"teams\": [");
    if (teamsStart == std::string::npos) {
        std::cerr << "Teams array not found in the JSON file!" << std::endl;
        return teamsPoints;
    }

    size_t teamsEnd = jsonString.find("]", teamsStart);
    std::string teamsData = jsonString.substr(teamsStart + 9, teamsEnd - teamsStart - 9);  // Skip the `"teams": [` part

    std::stringstream ss(teamsData);
    std::string teamData;
    while (std::getline(ss, teamData, '}')) {
        size_t nameStart = teamData.find("\"name\": \"");
        if (nameStart == std::string::npos) continue;

        size_t nameEnd = teamData.find("\"", nameStart + 9);
        std::string teamName = teamData.substr(nameStart + 9, nameEnd - nameStart - 9);

        size_t pointsStart = teamData.find("\"points\": ");
        if (pointsStart == std::string::npos) continue;

        int teamPoints = std::stoi(teamData.substr(pointsStart + 10));

        teamsPoints[teamName] = teamPoints;
    }

    return teamsPoints;
}