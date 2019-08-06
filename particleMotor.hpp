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
    void draw(sf::RenderWindow& pWindow);
    void addParticle(sf::Vector2f pAtThisPosition, int pParticleSpeed);

private:
    std::list<std::unique_ptr<Particle>> mListOfParticle;
};

#endif
