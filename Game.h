#pragma once
#include "World.h"
#include <fstream>
constexpr int WndWidth	= 1200;
constexpr int WndHeight = 900;
constexpr const char* WndTitle = "CoronaDodge!";

namespace TexFile
{
	constexpr const char* PlayerWest = "assets/player.bmp";
	//const char* PlayerEast = "assets/player.bmp";
	//const char* PlayerNorth = "assets/player.bmp";
	//const char* PlayerSouth = "assets/player.bmp";
	constexpr const char* Enemy = "assets/enemy.bmp";
}

class Game
{
	bool isRunning = true;
	sf::Clock clock;
	sf::RenderWindow wnd;
	sf::Font someFont;
	sf::Text textLost;
	World world;

	int score = 0;
	int highScore;
	float scoreCount = 3.f;
	sf::Text textScore;
	sf::Font fontScore;

public:
	Game();
	void load();
	void run();
private:
	void handleInput(sf::Time dt);
	void update(sf::Time dt);
	void render(sf::RenderWindow& wnd);
	void drawScore(sf::RenderWindow& wnd);
	void updateScore(sf::Time dt);
	void getHighScore();
	void writeHighScore();
	void loadFonts();
};