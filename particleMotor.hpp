#ifndef PARTICLEMOTOR_HPP
#define PARTICLEMOTOR_HPP

#include <memory>
#include <list>
#include <SFML/Graphics.hpp>

#include "particle.hpp"

class particleMotorClass
{
public:
    void update();
    void draw(sf::RenderWindow& window);
    void addParticle(sf::Vector2f atThisPosition, int particleSpeed);
private:
    std::list<std::unique_ptr<particleClass>> listOfParticle;
};

#endif
