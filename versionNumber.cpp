#include <stdexcept>
#include <utility>

#include "versionNumber.hpp"

VersionNumber::VersionNumber(std::initializer_list<int> listOfVersionNumbers)
    : versionNumbers{std::move(listOfVersionNumbers)}
{
    for (const auto& number : versionNumbers)
    {
        if (number < 0)
        {
            throw std::invalid_argument{"invalid version number"};
        }
    }
}

VersionNumber::VersionNumber(const std::string& versionNumbersAsStr)
{
    auto dotIdx = std::string::npos;
    auto startIdx = std::string::size_type{0};
    auto nbOfDigitsInNumber = std::size_t{0};
    auto newNumber = 0;

    while (startIdx < versionNumbersAsStr.size())
    {
        dotIdx = versionNumbersAsStr.find('.', startIdx);
        dotIdx = (dotIdx == std::string::npos ? versionNumbersAsStr.size() : dotIdx);
        newNumber = std::stoi(versionNumbersAsStr.substr(startIdx, dotIdx - startIdx), &nbOfDigitsInNumber);

        if (nbOfDigitsInNumber != (dotIdx - startIdx) || newNumber < 0)
        {
            throw std::invalid_argument{"invalid version number"};
        }

        versionNumbers.emplace_back(newNumber);
        startIdx = dotIdx + 1;
    }
}

VersionNumber operator""_vn(const char* versionNumbersAsStr, std::size_t sizeOfStr)
{
    return VersionNumber{std::string{versionNumbersAsStr, sizeOfStr}};
}

int VersionNumber::spaceshipOperator(const VersionNumber& other) const
{
    auto thisCurrNumIte = versionNumbers.cbegin();
    auto otherCurrNumIte = other.versionNumbers.cbegin();

    while (thisCurrNumIte != versionNumbers.cend() || otherCurrNumIte != other.versionNumbers.cend())
    {
        auto thisCurrNum = (thisCurrNumIte == versionNumbers.cend() ? 0 : *thisCurrNumIte);
        auto otherCurrNum = (otherCurrNumIte == other.versionNumbers.cend() ? 0 : *otherCurrNumIte);

        if (thisCurrNum != otherCurrNum)
        {
            return (thisCurrNum < otherCurrNum ? -1 : 1);
        }

        if (thisCurrNumIte != versionNumbers.cend())
        {
            ++thisCurrNumIte;
        }
        if (otherCurrNumIte != other.versionNumbers.cend())
        {
            ++otherCurrNumIte;
        }
    }

    return 0;
}

bool operator==(const VersionNumber& lhs, const VersionNumber& rhs)
{
    return (lhs.spaceshipOperator(rhs) == 0);
}

bool operator!=(const VersionNumber& lhs, const VersionNumber& rhs)
{
    return (lhs.spaceshipOperator(rhs) != 0);
}

bool operator<(const VersionNumber& lhs, const VersionNumber& rhs)
{
    return (lhs.spaceshipOperator(rhs) < 0);
}

bool operator>(const VersionNumber& lhs, const VersionNumber& rhs)
{
    return (lhs.spaceshipOperator(rhs) > 0);
}

bool operator<=(const VersionNumber& lhs, const VersionNumber& rhs)
{
    return (lhs.spaceshipOperator(rhs) <= 0);
}

bool operator>=(const VersionNumber& lhs, const VersionNumber& rhs)
{
    return (lhs.spaceshipOperator(rhs) >= 0);
}
