#ifndef VERSIONNUMBER_HPP
#define VERSIONNUMBER_HPP

#include <initializer_list>
#include <string>
#include <vector>

class VersionNumber
{
public:
    VersionNumber(std::initializer_list<int> listOfVersionNumbers = {});
    VersionNumber(const std::string& versionNumbersAsStr);
    int spaceshipOperator(const VersionNumber& other) const;

private:
    std::vector<int> versionNumbers;
};

VersionNumber operator""_vn(const char* versionNumbersAsStr, std::size_t sizeOfStr);

bool operator==(const VersionNumber& lhs, const VersionNumber& rhs);
bool operator!=(const VersionNumber& lhs, const VersionNumber& rhs);
bool operator<(const VersionNumber& lhs, const VersionNumber& rhs);
bool operator>(const VersionNumber& lhs, const VersionNumber& rhs);
bool operator<=(const VersionNumber& lhs, const VersionNumber& rhs);
bool operator>=(const VersionNumber& lhs, const VersionNumber& rhs);

#endif
