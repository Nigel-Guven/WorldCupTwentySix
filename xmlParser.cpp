#include "XMLParser.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Tournament.h"  // Assuming Tournament class is in this file

using namespace std;

// Constructor definition (only in the .cpp file)
XMLParser::XMLParser(const string& filename) : filename(filename) {}

string XMLParser::extractValue(const string& xmlLine, const string& tagName) {
    size_t startPos = xmlLine.find("<" + tagName + ">");
    if (startPos == string::npos) return "";
    startPos += tagName.length() + 2; // Skip opening tag

    size_t endPos = xmlLine.find("</" + tagName + ">", startPos);
    if (endPos == string::npos) return "";

    return xmlLine.substr(startPos, endPos - startPos);
}

// Other methods' definitions follow as usual
std::vector<Team> XMLParser::parseXML() {
    ifstream file(filename);  // Open the XML file
    if (!file) {
        cerr << "Error: Could not open file: " << filename << endl;
        return {};  // Return an empty vector in case of an error
    }

    string line;
    bool insideTeam = false;
    string teamName, teamPoints;
    std::vector<Team> teams;  // Vector to store the teams

    while (getline(file, line)) {
        // Trim line before processing (optional, depends on XML format)
        line = trim(line);

        // Skip empty lines or lines that don't contain relevant data
        if (line.empty()) continue;

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
            try {
                teams.push_back(Team(teamName, stoi(teamPoints)));  // Create a Team object and add it to the vector
            }
            catch (const std::invalid_argument& e) {
                cerr << "Invalid points format for team " << teamName << ": " << teamPoints << endl;
                cerr << "Exception: " << e.what() << endl;  // Log the exception message
            }
            catch (const std::out_of_range& e) {
                cerr << "Points value out of range for team " << teamName << ": " << teamPoints << endl;
                cerr << "Exception: " << e.what() << endl;  // Log the exception message
            }
            insideTeam = false;  // Reset for the next team
            teamName.clear();
            teamPoints.clear();
        }
    }

    file.close();  // Close the file
    return teams;  // Return the list of teams
}

std::vector<Team> XMLParser::parsePlayoffXML() {
    ifstream file(filename);  // Open the XML file
    if (!file) {
        cerr << "Error: Could not open file: " << filename << endl;
        return {};  // Return an empty vector in case of an error
    }

    string line;
    vector<Team> teams;  // Vector to store the teams

    while (getline(file, line)) {
        // Trim line before processing (optional, depends on XML format)
        line = trim(line);

        // Skip empty lines or lines that don't contain relevant data
        if (line.empty()) continue;

        // Extract team names from <name> tags
        if (line.find("<name>") != string::npos) {
            string teamName = extractValue(line, "name");
            if (!teamName.empty()) {
                teams.push_back(Team(teamName, 0));  // Add the team to the vector
            }
        }
    }

    file.close();  // Close the file
    return teams;  // Return the list of teams
}


string XMLParser::trim(const string& str) {
    const auto start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";  // No non-whitespace characters
    const auto end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
}
