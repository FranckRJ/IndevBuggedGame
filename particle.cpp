#include "particle.hpp"
#include "global.hpp"

particleClass::particleClass()
{
    isDead = false;
    timer.restart();
}

particleClass::particleClass(particleInfo newParticleInfo, sf::Color particleColor, sf::Vector2f particleSize, sf::Vector2i velocity, sf::Vector2f basePosition) : particleClass()
{
    infoForParticle = newParticleInfo;
    infoForParticle.horizontalVelocity += velocity.x;
    infoForParticle.verticalVelocity += velocity.y;
    sprite.setSize(particleSize);
    sprite.setFillColor(particleColor);
    sprite.setPosition(basePosition);
}

void particleClass::update()
{
    if(timer.getElapsedTime().asSeconds() > infoForParticle.lifeTime)
    {
        sf::Color newColor = sprite.getFillColor();

        if(newColor.a <= infoForParticle.lostAlphaSpeed)
        {
            isDead = true;
        }
        else
        {
            newColor.a -= infoForParticle.lostAlphaSpeed;
            sprite.setFillColor(newColor);
        }
    }

    sprite.move(infoForParticle.horizontalVelocity, infoForParticle.verticalVelocity);

    if(infoForParticle.attractedByGravity)
    {
        infoForParticle.verticalVelocity += GRAVITY;
    }
}

void particleClass::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool particleClass::getIsDead()
{
    return isDead;
}
