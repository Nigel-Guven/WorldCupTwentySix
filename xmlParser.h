#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <vector>
#include <string>
#include "Team.h"  // Make sure Team.h is included here

class XMLParser {
public:
    // Constructor declaration (only here in the header)
    XMLParser(const std::string& filename);  // Don't define it here, just declare it
    
    // Method declaration
    std::vector<Team> parseXML();
    std::vector<Team> parsePlayoffXML();

private:
    // Other private members and methods
    std::string extractValue(const std::string& xmlLine, const std::string& tagName);
    std::string trim(const std::string& str);

    std::string filename;
};


#endif // XMLPARSER_H
