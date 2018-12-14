#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

struct particleInfo
{
    bool attractedByGravity;
    int verticalVelocity;
    int horizontalVelocity;
    double lifeTime;
    int lostAlphaSpeed;
};

class particleClass
{
public:
    particleClass();
    particleClass(particleInfo newParticleInfo, sf::Color particleColor, sf::Vector2f particleSize, sf::Vector2i velocity, sf::Vector2f basePosition);
    void update();
    void draw(sf::RenderWindow& window);
    bool getIsDead();
private:
    sf::RectangleShape sprite;
    sf::Clock timer;
    particleInfo infoForParticle;
    bool isDead;
};

#endif
