#include "particle.hpp"
#include "global.hpp"

Particle::Particle(ParticleInfo pParticleInfo, sf::Color pParticleColor, sf::Vector2f pParticleSize,
                   sf::Vector2i pVelocity, sf::Vector2f pBasePosition)
    : mInfoForParticle{pParticleInfo}
{
    mTimer.restart();
    mInfoForParticle.horizontalVelocity += pVelocity.x;
    mInfoForParticle.verticalVelocity += pVelocity.y;
    mSprite.setSize(pParticleSize);
    mSprite.setFillColor(pParticleColor);
    mSprite.setPosition(pBasePosition);
}

void Particle::update()
{
    if (mTimer.getElapsedTime().asSeconds() > mInfoForParticle.lifeTime)
    {
        auto newColor = mSprite.getFillColor();

        if (newColor.a <= mInfoForParticle.lostAlphaSpeed)
        {
            mIsDead = true;
        }
        else
        {
            newColor.a -= mInfoForParticle.lostAlphaSpeed;
            mSprite.setFillColor(newColor);
        }
    }

    mSprite.move(mInfoForParticle.horizontalVelocity, mInfoForParticle.verticalVelocity);

    if (mInfoForParticle.attractedByGravity)
    {
        mInfoForParticle.verticalVelocity += GRAVITY;
    }
}

void Particle::draw(sf::RenderWindow& window) const
{
    window.draw(mSprite);
}

bool Particle::isDead() const
{
    return mIsDead;
}
