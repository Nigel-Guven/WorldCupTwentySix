#include "XMLParser.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

XMLParser::XMLParser(const string& filename) : filename(filename) {}

string XMLParser::extractValue(const string& xmlLine, const string& tagName) {
    size_t startPos = xmlLine.find("<" + tagName + ">");
    if (startPos == string::npos) return "";
    startPos += tagName.length() + 2; // Skip opening tag

    size_t endPos = xmlLine.find("</" + tagName + ">", startPos);
    if (endPos == string::npos) return "";

    return xmlLine.substr(startPos, endPos - startPos);
}

std::vector<Team> XMLParser::parseXML() {
    ifstream file(filename);  // Open the XML file
    if (!file) {
        cout << "Error: Could not open file!" << endl;
        return {};  // Return an empty vector in case of an error
    }

    string line;
    bool insideTeam = false;
    string teamName, teamPoints;
    std::vector<Team> teams;  // Vector to store the teams

    while (getline(file, line)) {
        // Search for <team> element, i.e. start of a new team
        if (line.find("<team>") != string::npos) {
            insideTeam = true;
            continue;
        }

        // Extract team name
        if (insideTeam && line.find("<name>") != string::npos) {
            teamName = extractValue(line, "name");
        }

        // Extract team points
        if (insideTeam && line.find("<points>") != string::npos) {
            teamPoints = extractValue(line, "points");
        }

        // If we've found both the team name and points, store the team in the vector
        if (!teamName.empty() && !teamPoints.empty()) {
            teams.push_back(Team(teamName, stoi(teamPoints)));  // Create a Team object and add it to the vector
            insideTeam = false;  // Reset for the next team
            teamName.clear();
            teamPoints.clear();
        }
    }

    file.close();  // Close the file
    return teams;  // Return the list of teams
}