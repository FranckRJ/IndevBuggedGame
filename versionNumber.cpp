#include "versionNumber.hpp"

versionNumberClass::versionNumberClass(std::initializer_list<unsigned int> listOfVersionNumbers)
    : versionNumbers(listOfVersionNumbers)
{
}

versionNumberClass::versionNumberClass(std::string versionNumbersAsStr)
{
    // TODO
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
