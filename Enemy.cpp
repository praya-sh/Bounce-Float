#include "stdafx.h"
#include "Enemy.h"

void Enemy::initShape()
{
	tex.loadFromFile("Assets/Enemy/FB007.png");
	
	this->shape.setRadius(rand() % 20 + 50);
	shape.setTexture(&tex);
	
	
}

void Enemy::initVariables()
{
	hp = 10;
	hpMax = 0;
	damage = 1;
}

Enemy::Enemy(float pos_x,float pos_y)
{
	this->initShape();
	this->initVariables();
	shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Enemy::update()
{
	
	shape.move(-20.f, 0.f);
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
