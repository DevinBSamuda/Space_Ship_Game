#include "Enemy.h"

void Enemy::initVariables()
{
    this->pointCount = rand() % 8 + 3;
    this->type = 0;
    this->speed = static_cast<float>(this->pointCount / 3);
    this->hpMax = static_cast<int>(this->pointCount);
    this->hp = this->hpMax;
    this->damage = this->pointCount;
    this->points = this->pointCount;
}

void Enemy::initShape()
{
    this->shape.setRadius(this->pointCount * 5);
    this->shape.setPointCount(rand() % 8 + 3);
    this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
}

// constructor/destructor
Enemy::Enemy(float pos_x, float pos_y)
{
    this->initVariables();
    this->initShape();

    this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{

    return this->shape.getGlobalBounds();
}

const int &Enemy::getPoints() const
{
    return this->points;
}

const int &Enemy::getDamage() const
{
    return this->damage;
}

// Functions
void Enemy::update()
{
    // moves enemy down
    this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
