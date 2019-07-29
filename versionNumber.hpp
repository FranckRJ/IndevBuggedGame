#ifndef VERSIONNUMBER_HPP
#define VERSIONNUMBER_HPP

#include <initializer_list>
#include <string>
#include <vector>

class VersionNumber;

VersionNumber operator""_vn(const char* versionNumbersAsStr, std::size_t sizeOfStr);

class VersionNumber
{
public:
    VersionNumber(const std::initializer_list<unsigned int>& listOfVersionNumbers = {});
    VersionNumber(const std::string& versionNumbersAsStr);
    bool operator==(const VersionNumber& other) const;
    bool operator!=(const VersionNumber& other) const;
    bool operator<(const VersionNumber& other) const;
    bool operator>(const VersionNumber& other) const;
    bool operator<=(const VersionNumber& other) const;
    bool operator>=(const VersionNumber& other) const;

private:
    int spaceshipOperator(const VersionNumber& other) const;

private:
    std::vector<unsigned int> versionNumbers;
};

#endif
