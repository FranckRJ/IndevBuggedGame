#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

struct ParticleInfo
{
    bool attractedByGravity = true;
    int verticalVelocity = 0;
    int horizontalVelocity = 0;
    float lifeTime = 0.f;
    int lostAlphaSpeed = 255;
};

class Particle
{
public:
    Particle(ParticleInfo pParticleInfo, sf::Color pParticleColor, sf::Vector2f pParticleSize, sf::Vector2i pVelocity,
             sf::Vector2f pBasePosition);

    void update();
    void draw(sf::RenderWindow& window) const;

    bool isDead() const;

private:
    sf::RectangleShape mSprite;
    sf::Clock mTimer;
    ParticleInfo mInfoForParticle;
    bool mIsDead = false;
};

#endif
