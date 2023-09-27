#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Bullet
{

private:
    sf::Sprite shape;
    sf::Texture *texture;

    sf::Vector2f direction;
    float movementSpeed;

    // Private functions
    void initTexture();
    void initSprite();

public:
    Bullet();
    Bullet(sf::Texture *texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
    virtual ~Bullet();

    // Accessors
    const sf::FloatRect getBounds() const;

    // Functions
    void update();
    void render(sf::RenderTarget *target);
};

#endif // !BULLET_H
