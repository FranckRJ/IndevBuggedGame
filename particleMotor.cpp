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

void ParticleMotor::addParticle(sf::Vector2f pAtThisPosition, sf::Vector2f pWithThisRelativeMargin, int pParticleSpeed)
{
    const auto particleSize = 10.f;
    auto addVerticalVelocity = mRandomVelocityChange(Global::fast_random);
    auto addHorizontalVelocity = mRandomVelocityChange(Global::fast_random);

    mListOfParticle.emplace_back(
        ParticleManager::createParticle("NORMAL_PARTICLE", sf::Color::Blue, sf::Vector2f{particleSize, particleSize},
                                        sf::Vector2i{pParticleSpeed + addHorizontalVelocity, addVerticalVelocity},
                                        sf::Vector2f{pAtThisPosition.x + (pWithThisRelativeMargin.x * particleSize),
                                                     pAtThisPosition.y + (pWithThisRelativeMargin.y * particleSize)}));
}
