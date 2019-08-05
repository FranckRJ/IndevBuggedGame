#ifndef VERSIONNUMBER_HPP
#define VERSIONNUMBER_HPP

#include <initializer_list>
#include <string>
#include <vector>

class VersionNumber
{
public:
    VersionNumber(std::initializer_list<int> pVersionNumbers = {});
    VersionNumber(const std::string& pVersionNumbersAsStr);

    int spaceshipOperator(const VersionNumber& pOther) const;

private:
    std::vector<int> mVersionNumbers;
};

VersionNumber operator""_vn(const char* pVersionNumbersAsStr, std::size_t pSizeOfStr);

bool operator==(const VersionNumber& pLhs, const VersionNumber& pRhs);
bool operator!=(const VersionNumber& pLhs, const VersionNumber& pRhs);
bool operator<(const VersionNumber& pLhs, const VersionNumber& pRhs);
bool operator>(const VersionNumber& pLhs, const VersionNumber& pRhs);
bool operator<=(const VersionNumber& pLhs, const VersionNumber& pRhs);
bool operator>=(const VersionNumber& pLhs, const VersionNumber& pRhs);

#endif
