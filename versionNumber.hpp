#ifndef VERSIONNUMBER_HPP
#define VERSIONNUMBER_HPP

#include <initializer_list>
#include <string>
#include <vector>

class versionNumberClass;

versionNumberClass operator""_vn(const char* versionNumbersAsStr, std::size_t sizeOfStr);

class versionNumberClass
{
public:
    versionNumberClass(const std::initializer_list<unsigned int>& listOfVersionNumbers = {});
    versionNumberClass(const std::string& versionNumbersAsStr);
    bool operator==(const versionNumberClass& other) const;
    bool operator!=(const versionNumberClass& other) const;
    bool operator<(const versionNumberClass& other) const;
    bool operator>(const versionNumberClass& other) const;
    bool operator<=(const versionNumberClass& other) const;
    bool operator>=(const versionNumberClass& other) const;

private:
    int spaceshipOperator(const versionNumberClass& other) const;

private:
    std::vector<unsigned int> versionNumbers;
};

#endif // VERSIONNUMBER_HPP
