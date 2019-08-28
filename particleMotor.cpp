#include "particleMotor.hpp"
#include "global.hpp"
#include "particleManager.hpp"
#include "utls.hpp"

void ParticleMotor::update()
{
    utls::updateRemoveErase(mListOfParticle, [](auto& particlePtr) {
        particlePtr->update();
        return particlePtr->isDead();
    });
}

void ParticleMotor::draw(sf::RenderWindow& pWindow) const
{
    for (const auto& particlePtr : mListOfParticle)
    {
        particlePtr->draw(pWindow);
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
