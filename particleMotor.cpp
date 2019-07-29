#include <cstdlib>

#include "particleManager.hpp"
#include "particleMotor.hpp"

void ParticleMotor::update()
{
    for (auto thisParticle = listOfParticle.begin(); thisParticle != listOfParticle.end();)
    {
        (*thisParticle)->update();

        if ((*thisParticle)->getIsDead())
        {
            listOfParticle.erase(thisParticle++);
            continue;
        }
        ++thisParticle;
    }
}

void ParticleMotor::draw(sf::RenderWindow& window)
{
    for (std::unique_ptr<Particle>& thisParticle : listOfParticle)
    {
        thisParticle->draw(window);
    }
}

void ParticleMotor::addParticle(sf::Vector2f atThisPosition, int particleSpeed)
{
    int addVerticalVelocity = -(rand() % 5);
    int addHorizontalVelocity = (rand() % 5) - 2;

    listOfParticle.push_back(std::unique_ptr<Particle>(ParticleManager::createParticle(
        "NORMAL_PARTICLE", sf::Color::Blue, sf::Vector2f(10, 10),
        sf::Vector2i(particleSpeed + addHorizontalVelocity, addVerticalVelocity), atThisPosition)));
}
