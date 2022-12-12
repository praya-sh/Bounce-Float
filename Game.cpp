#include "stdafx.h"
#include "Game.h"

void Game::initWindow()
{
	this->window.create(sf::VideoMode(1000, 600), "Game", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
	backGround.loadFromFile("Assets/Tileset/background.png");
	
	backsprite.setTexture(&backGround);
	backsprite.setSize(sf::Vector2f(1000.0f, 600.0f));
	/*_start = std::chrono::system_clock::now();
	time_t_start = std::chrono::system_clock::to_time_t(_start);*/
}

void Game::initPlayer()
{
	//this->player = new Player();
	//pl = *player;
	
}

void Game::initEnemies()
{
	spawnTimerMax = 25.f;
	spawnTimer = this->spawnTimerMax;
}

void Game::initGUI()
{
	font.loadFromFile("Assets/Fonts/Roboto-Regular.ttf");
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(
		window.getSize().x / 2.f- gameOverText.getGlobalBounds().width /2.f,
		window.getSize().y/2.f - gameOverText.getGlobalBounds().height / 2.f);

	startGameText.setFont(font);
	startGameText.setCharacterSize(100);
	startGameText.setFillColor(sf::Color::Red);
	startGameText.setString("Press space bar to start!");
	startGameText.setPosition(
		window.getSize().x / 2.f - startGameText.getGlobalBounds().width / 2.f,
		window.getSize().y / 2.f - startGameText.getGlobalBounds().height / 2.f);


	playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	playerHpBar.setFillColor(sf::Color::Green);
	playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));
	playerHpBarback = playerHpBar;
	playerHpBarback.setFillColor(sf::Color(25, 25, 25, 200));

	gtimer.setFont(font);
	gtimer.setCharacterSize(25);
	gtimer.setFillColor(sf::Color::Green);
	//auto curr = std::chrono::system_clock::now();
	
	//std::string _val = std::ctime(&time_t_start);
	sf::Time elasped = _start.getElapsedTime();
	score = elasped.asSeconds();
	std::string time_str = std::to_string(score);
	
	gtimer.setString(time_str);
	
	gtimer.setPosition(20.f, 45.f);
	
	deathscore.setPosition(500.f, 200.f);
	deathscore.setCharacterSize(50);

}

Game::Game()
{
	initWindow();
	initPlayer();
	initEnemies();
	initGUI();
}

Game::~Game()
{
	//delete &window;
	delete &player;
	//delete enemies;
	for (auto* i : this->enemies)
	{
		delete i;

	}
	
	
}

bool Game::playerAlive()
{
	if (player.getHP() > 0)
		return true;
	else
		return false;

}

bool Game::gameStart()
{
	/*if (ev.type == sf::Event::KeyReleased == sf::Keyboard::Enter)*/
		return true;
}

void Game::enterTiles()
{
	tex.loadFromFile("Assets/Tileset/platform.png");
	//sf::IntRect r1(0, 0, 100, 100);
	tiles.push_back(Tile(&tex, sf::Vector2f(100.0f,100.f),sf::Vector2f(100.0f,100.0f), false));
	tiles.push_back(Tile(&tex, sf::Vector2f(100.0f, 100.f), sf::Vector2f(400.0f, 100.0f), false));
	tiles.push_back(Tile(&tex, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(700.0f, 500.0f), false));
	tiles.push_back(Tile(&tex, sf::Vector2f(100.f, 100.f), sf::Vector2f(500.f, 500.f), false));
	tiles.push_back(Tile(&tex, sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 300.f), false));
	tiles.push_back(Tile(&tex, sf::Vector2f(100.f, 100.f), sf::Vector2f(400.f, 600.f), false));
	tiles.push_back(Tile(&tex, sf::Vector2f(100.f, 100.f), sf::Vector2f(900.f, 0.f), false));
	tiles.push_back(Tile(&tex, sf::Vector2f(100.f, 100.f), sf::Vector2f(600.f, 300.f), false));
	
	for (Tile& tile : tiles) {
		tile.render(window);
	}
}

void Game::updateGUI()
{
	
	float hpPercent = static_cast<float>(player.getHP()) / player.getHPmax() ;
	playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, playerHpBar.getSize().y));

	curr = _start.getElapsedTime();
	score = curr.asSeconds();
	time_str = "Time : ";
	time_str += std::to_string(score);
	gtimer.setString(time_str);
	
}

void Game::updatePlayer()
{
	//this->player->update();
	player.update();
}

void Game::updateCollision()
{
	if (this->player.getPosition().y + this->player.getGlobalBounds().height >= this->window.getSize().y)
	{
		this->player.resetVelocityY();
		this->player.setPosition(
			this->player.getPosition().x,
			this->window.getSize().y - this->player.getGlobalBounds().height
		);
	}
	if (player.getGlobalBounds().left < 0.f) {
		player.setPosition(0.f, player.getGlobalBounds().top);
	}
	if (player.getGlobalBounds().left + player.getGlobalBounds().width >= window.getSize().x) {
		player.setPosition(window.getSize().x - player.getGlobalBounds().width, player.getGlobalBounds().top);
	}
	if (player.getGlobalBounds().top < 0.f) {
		player.setPosition(player.getGlobalBounds().left, 0.f);
	}
	Collider p1 = player.GetCollider();
	for (Tile& tile : tiles) {
		if (tile.GetCollider().checkCollision(p1, direction, 1.0f)) {
			player.OnCollision(direction);
		}
	}
}

void Game::updateEnemies()
{
	spawnTimer += 1.f;
	if (spawnTimer >= spawnTimerMax) {
		enemies.push_back(new Enemy(1100.f, rand()%this->window.getSize().y+20.f));
		spawnTimer = 0.f;
	}
	for (int i = 0; i < enemies.size(); ++i) {
		enemies[i]->update();
		if (-this->enemies[i]->getBounds().left > window.getSize().x)
		{
			enemies.erase(enemies.begin() + i);
			
		}
		else if(enemies[i]->getBounds().intersects(player.getGlobalBounds()))
		{
			this->player.losehp(1);
			enemies.erase(enemies.begin() + i);
			
		}
	}
}

void Game::update()
{
	while (this->window.pollEvent(this->ev)) {
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		if (this->ev.type == sf::Event::KeyPressed && this->ev.key.code == sf::Keyboard::Escape)
			this->window.close();
		if (this->ev.type == sf::Event::KeyReleased && 
			(this->ev.key.code == sf::Keyboard::A) ||
			this->ev.key.code == sf::Keyboard::D) 
		{
			this->player.resetAnimationTimer();
		}
	}
	if (playerAlive() ) {
		this->updatePlayer();
		this->updateCollision();
		this->updateEnemies();
		this->updateGUI();	
	}
}

void Game::renderGUI()
{
	this->window.draw(playerHpBarback);
	this->window.draw(playerHpBar); 
}

void Game::renderPlayer()
{
	this->player.render(this->window);
}

void Game::render()
{
	this->window.clear();
	
	this->window.draw(backsprite);
	this->renderGUI();
	this->renderPlayer();
	this->enterTiles();
	window.draw(gtimer);

	for (auto* enemy : enemies) {
		enemy->render(window); 
	}
	
	if (player.getHP() <= 0) {
		
		window.draw(deathscore);
		window.draw(gameOverText);
	

	}

	this->window.display();
}

sf::RenderWindow& Game::getWindow()
{
	// TODO: insert return statement here
	return this->window;
}
