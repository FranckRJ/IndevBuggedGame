#include "particleMotor.hpp"
#include "global.hpp"
#include "particleManager.hpp"

void ParticleMotor::update()
{
    for (auto thisParticle = mListOfParticle.begin(); thisParticle != mListOfParticle.end();)
    {
        (*thisParticle)->update();

        if ((*thisParticle)->getIsDead())
        {
            mListOfParticle.erase(thisParticle++);
            continue;
        }
        ++thisParticle;
    }
}

void ParticleMotor::draw(sf::RenderWindow& pWindow)
{
    for (const auto& thisParticle : mListOfParticle)
    {
        thisParticle->draw(pWindow);
    }
}

void ParticleMotor::addParticle(sf::Vector2f pAtThisPosition, int pParticleSpeed)
{
    auto addVerticalVelocity = mRandomAddVerticalVelocity(Global::fast_random);
    auto addHorizontalVelocity = mRandomAddHorizontalVelocity(Global::fast_random);

    mListOfParticle.emplace_back(ParticleManager::createParticle(
        "NORMAL_PARTICLE", sf::Color::Blue, sf::Vector2f{10.f, 10.f},
        sf::Vector2i{pParticleSpeed + addHorizontalVelocity, addVerticalVelocity}, pAtThisPosition));
}
