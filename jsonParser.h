#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Team.h"

class JSONParser {
public:
    std::unordered_map<std::string, int> parseJsonFile(const std::string& filename);
};

#endif