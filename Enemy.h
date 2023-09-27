#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Enemy
{
private:
    unsigned pointCount;
    sf::CircleShape shape;
    int type;
    float speed;
    int hp;
    int hpMax;
    int damage;
    int points;

    // Private functions
    void initVariables();
    void initShape();

public:
    Enemy(float pos_x, float pos_y);
    virtual ~Enemy();

    // Accessors
    const sf::FloatRect getBounds() const;
    const int &getPoints() const;
    const int &getDamage() const;

    // Functions
    void update();
    void render(sf::RenderTarget *target);
};

#endif // !Enemy_H