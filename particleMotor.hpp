#ifndef PARTICLEMOTOR_HPP
#define PARTICLEMOTOR_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "particle.hpp"

class ParticleMotor
{
public:
    void update();
    void draw(sf::RenderWindow& window);
    void addParticle(sf::Vector2f atThisPosition, int particleSpeed);

private:
    std::list<std::unique_ptr<Particle>> listOfParticle;
};

#endif
