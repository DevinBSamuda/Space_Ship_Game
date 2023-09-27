#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>

class Player
{
private:
    sf::Sprite sprite;
    sf::Texture texture;

    float movementSpeed;
    float attackCooldown;
    float attackCooldownMax;

    int hp;
    int hpMax;

    // Private functions
    void initVariables();
    void initTexture();
    void initSprite();

public:
    Player();
    virtual ~Player();

    // Accessors
    const sf::Vector2f &getPos() const;
    const sf::FloatRect getBounds() const;
    const int &getHp() const;
    const int &getHpMax() const;

    // Modifiers (shows overloading)
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);

    // Functions
    void move(const float dirX, const float dirY);
    bool canAttack();

    void updateAttack();
    void update();
    void render(sf::RenderTarget &target);
};

#endif // !PLAYER_H