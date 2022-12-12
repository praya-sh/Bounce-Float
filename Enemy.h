#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::CircleShape shape;
	sf::Texture tex;
	int hp;
	int hpMax;
	int damage;

	void initShape();
	void initVariables();

public:
	Enemy(float pos_x, float pos_y);
	~Enemy();

	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget& target);
};

