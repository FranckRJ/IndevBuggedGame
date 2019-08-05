#include <stdexcept>
#include <utility>

#include "versionNumber.hpp"

VersionNumber::VersionNumber(std::initializer_list<int> pVersionNumbers) : mVersionNumbers{std::move(pVersionNumbers)}
{
    for (const auto& number : mVersionNumbers)
    {
        if (number < 0)
        {
            throw std::invalid_argument{"invalid version number"};
        }
    }
}

VersionNumber::VersionNumber(const std::string& pVersionNumbersAsStr)
{
    auto dotIdx = std::string::npos;
    auto startIdx = std::string::size_type{0};
    auto nbOfDigitsInNumber = std::size_t{0};
    auto newNumber = 0;

    while (startIdx < pVersionNumbersAsStr.size())
    {
        dotIdx = pVersionNumbersAsStr.find('.', startIdx);
        dotIdx = (dotIdx == std::string::npos ? pVersionNumbersAsStr.size() : dotIdx);
        newNumber = std::stoi(pVersionNumbersAsStr.substr(startIdx, dotIdx - startIdx), &nbOfDigitsInNumber);

        if (nbOfDigitsInNumber != (dotIdx - startIdx) || newNumber < 0)
        {
            throw std::invalid_argument{"invalid version number"};
        }

        mVersionNumbers.emplace_back(newNumber);
        startIdx = dotIdx + 1;
    }
}

VersionNumber operator""_vn(const char* pVersionNumbersAsStr, std::size_t pSizeOfStr)
{
    return VersionNumber{std::string{pVersionNumbersAsStr, pSizeOfStr}};
}

int VersionNumber::spaceshipOperator(const VersionNumber& pOther) const
{
    auto thisCurrNumIte = mVersionNumbers.cbegin();
    auto otherCurrNumIte = pOther.mVersionNumbers.cbegin();

    while (thisCurrNumIte != mVersionNumbers.cend() || otherCurrNumIte != pOther.mVersionNumbers.cend())
    {
        auto thisCurrNum = (thisCurrNumIte == mVersionNumbers.cend() ? 0 : *thisCurrNumIte);
        auto otherCurrNum = (otherCurrNumIte == pOther.mVersionNumbers.cend() ? 0 : *otherCurrNumIte);

        if (thisCurrNum != otherCurrNum)
        {
            return (thisCurrNum < otherCurrNum ? -1 : 1);
        }

        if (thisCurrNumIte != mVersionNumbers.cend())
        {
            ++thisCurrNumIte;
        }
        if (otherCurrNumIte != pOther.mVersionNumbers.cend())
        {
            ++otherCurrNumIte;
        }
    }

    return 0;
}

bool operator==(const VersionNumber& pLhs, const VersionNumber& pRhs)
{
    return (pLhs.spaceshipOperator(pRhs) == 0);
}

bool operator!=(const VersionNumber& pLhs, const VersionNumber& pRhs)
{
    return (pLhs.spaceshipOperator(pRhs) != 0);
}

bool operator<(const VersionNumber& pLhs, const VersionNumber& pRhs)
{
    return (pLhs.spaceshipOperator(pRhs) < 0);
}

bool operator>(const VersionNumber& pLhs, const VersionNumber& pRhs)
{
    return (pLhs.spaceshipOperator(pRhs) > 0);
}

bool operator<=(const VersionNumber& pLhs, const VersionNumber& pRhs)
{
    return (pLhs.spaceshipOperator(pRhs) <= 0);
}

bool operator>=(const VersionNumber& pLhs, const VersionNumber& pRhs)
{
    return (pLhs.spaceshipOperator(pRhs) >= 0);
}
