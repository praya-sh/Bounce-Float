#pragma once
#include"stdafx.h"
#include "Player.h"
#include "Tile.h"
#include "Collider.h"
#include"Enemy.h"
class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	//Player* player;
	Player player;
	sf::Texture backGround;
	//sf::Sprite *backsprite;
	sf::RectangleShape backsprite;
	std::vector<Tile>tiles;
	sf::Texture tex;
	//sf::Texture* texture;

	sf::Vector2f direction;
	//Collider p1;
	sf::Clock _start;
	sf::Time curr;
	std::string time_str;

	sf::Text gameOverText;
	sf::Text startGameText;
	sf::Text gtimer;
	int score;
	sf::Text deathscore;
	sf::Font font;

	

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarback;

	std::vector<Enemy*>enemies;
	float spawnTimer;
	float spawnTimerMax; 

	void initWindow();
	void initPlayer();	
	void initEnemies();
	void initGUI();

public:
	Game();
	~Game();

	bool playerAlive();
	bool gameStart();
	void enterTiles();
	void updateGUI();
	void updatePlayer();
	void updateCollision();
	void updateEnemies();
	void update();
	void renderGUI();
	void renderPlayer();
	void render();
	sf::RenderWindow& getWindow();
};

