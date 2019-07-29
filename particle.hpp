#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

struct ParticleInfo
{
    bool attractedByGravity;
    int verticalVelocity;
    int horizontalVelocity;
    double lifeTime;
    int lostAlphaSpeed;
};

class Particle
{
public:
    Particle();
    Particle(ParticleInfo newParticleInfo, sf::Color particleColor, sf::Vector2f particleSize, sf::Vector2i velocity,
             sf::Vector2f basePosition);
    void update();
    void draw(sf::RenderWindow& window);
    bool getIsDead();

private:
    sf::RectangleShape sprite;
    sf::Clock timer;
    ParticleInfo infoForParticle;
    bool isDead;
};

#endif
