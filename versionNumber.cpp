#include <stdexcept>

#include "versionNumber.hpp"

versionNumberClass operator""_vn(const char* versionNumbersAsStr, std::size_t sizeOfStr)
{
    return versionNumberClass(std::string(versionNumbersAsStr, sizeOfStr));
}

versionNumberClass::versionNumberClass(const std::initializer_list<unsigned int>& listOfVersionNumbers)
    : versionNumbers(listOfVersionNumbers)
{
}

versionNumberClass::versionNumberClass(const std::string& versionNumbersAsStr)
{
    std::string::size_type dotIdx;
    std::string::size_type startIdx = 0;
    std::string::size_type nbOfDigitsInNumber;
    int newNumber;

    do
    {
        dotIdx = versionNumbersAsStr.find('.', startIdx);
        nbOfDigitsInNumber = std::string::npos;
        newNumber = std::stoi(versionNumbersAsStr.substr(startIdx, dotIdx - startIdx), &nbOfDigitsInNumber);

        if (nbOfDigitsInNumber != (dotIdx - startIdx) && newNumber < 0)
        {
            throw std::invalid_argument("invalid version number");
        }

        versionNumbers.push_back(static_cast<unsigned int>(newNumber));
        startIdx = dotIdx + 1;
    } while (dotIdx != std::string::npos);
}

bool versionNumberClass::operator==(const versionNumberClass& other) const
{
    return (spaceshipOperator(other) == 0);
}

bool versionNumberClass::operator!=(const versionNumberClass& other) const
{
    return (spaceshipOperator(other) != 0);
}

bool versionNumberClass::operator<(const versionNumberClass& other) const
{
    return (spaceshipOperator(other) < 0);
}

bool versionNumberClass::operator>(const versionNumberClass& other) const
{
    return (spaceshipOperator(other) > 0);
}

bool versionNumberClass::operator<=(const versionNumberClass& other) const
{
    return (spaceshipOperator(other) <= 0);
}

bool versionNumberClass::operator>=(const versionNumberClass& other) const
{
    return (spaceshipOperator(other) >= 0);
}

int versionNumberClass::spaceshipOperator(const versionNumberClass& other) const
{
    auto thisCurrNumIte = versionNumbers.cbegin();
    auto otherCurrNumIte = other.versionNumbers.cbegin();

    while (thisCurrNumIte != versionNumbers.end() || otherCurrNumIte != other.versionNumbers.end())
    {
        unsigned int thisCurrNum = (thisCurrNumIte == versionNumbers.end() ? 0 : *thisCurrNumIte);
        unsigned int otherCurrNum = (otherCurrNumIte == other.versionNumbers.end() ? 0 : *otherCurrNumIte);

        if (thisCurrNum != otherCurrNum)
        {
            return (thisCurrNum < otherCurrNum ? -1 : 1);
        }

        if (thisCurrNumIte != versionNumbers.end())
        {
            ++thisCurrNumIte;
        }
        if (otherCurrNumIte != other.versionNumbers.end())
        {
            ++otherCurrNumIte;
        }
    }

    return 0;
}
