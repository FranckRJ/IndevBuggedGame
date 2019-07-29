#include "particle.hpp"
#include "global.hpp"

Particle::Particle()
{
    isDead = false;
    timer.restart();
}

Particle::Particle(ParticleInfo newParticleInfo, sf::Color particleColor, sf::Vector2f particleSize,
                   sf::Vector2i velocity, sf::Vector2f basePosition)
    : Particle()
{
    infoForParticle = newParticleInfo;
    infoForParticle.horizontalVelocity += velocity.x;
    infoForParticle.verticalVelocity += velocity.y;
    sprite.setSize(particleSize);
    sprite.setFillColor(particleColor);
    sprite.setPosition(basePosition);
}

void Particle::update()
{
    if (timer.getElapsedTime().asSeconds() > infoForParticle.lifeTime)
    {
        sf::Color newColor = sprite.getFillColor();

        if (newColor.a <= infoForParticle.lostAlphaSpeed)
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

    if (infoForParticle.attractedByGravity)
    {
        infoForParticle.verticalVelocity += GRAVITY;
    }
}

void Particle::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

bool Particle::getIsDead()
{
    return isDead;
}
