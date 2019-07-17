#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <vector>

class utilitiesClass
{
public:
    static std::string readFirstString(std::string& thisString);
    static std::vector<int> readNumber(std::string& thisString, int numberOfNumber);
    static std::vector<std::string> readString(std::string& thisString, int numberOfString);
    static std::string intToString(int thisInt);
    static int stringToInt(std::string thisString);
    static double stringToDouble(std::string thisString);
    static std::string& addNewLine(std::string& thisString);
};

#endif
