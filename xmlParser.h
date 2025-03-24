#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <vector>
#include "Team.h"
#include <string>

class XMLParser {
public:
    XMLParser(const std::string& filename);  // Constructor to initialize the file name
    std::vector<Team> parseXML();  // Method to parse the XML and return a list of teams

private:
    std::string filename;  // File name for the XML file
    std::string extractValue(const std::string& xmlLine, const std::string& tagName);  // Helper method to extract tag values
};

#endif // XMLPARSER_H