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
    void draw(sf::RenderWindow& pWindow) const;
    void addParticle(sf::Vector2f pAtThisPosition, int pParticleSpeed);

private:
    std::uniform_int_distribution<int> mRandomAddVerticalVelocity{-4, 0};
    std::uniform_int_distribution<int> mRandomAddHorizontalVelocity{-2, 2};
    std::list<std::unique_ptr<Particle>> mListOfParticle;
};

#endif
