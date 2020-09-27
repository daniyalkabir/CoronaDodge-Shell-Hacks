#include "Game.h"

Game::Game()
	:
	wnd(sf::VideoMode(WndWidth, WndHeight), WndTitle)
{
}

void Game::load()
{
	auto texMan = TextureManager::Get();

	// entity textures
	texMan->addTexture(TexID::Enemy, TexFile::Enemy);
	texMan->addTexture(TexID::PlayerNorth, TexFile::PlayerWest);
	
	loadFonts();
	getHighScore();
	
	// item textures

	// sounds??
	
	world.setWindow(&wnd);
	world.init();
}

void Game::loadFonts() {
	auto wSize = wnd.getSize();

	//Score font
	if (!fontScore.loadFromFile("assets/score_font.ttf"))
		throw "Failed to load font.";
	textScore.setFont(fontScore);
	textScore.setCharacterSize(40);
	textScore.setFillColor(sf::Color::Black);
	auto textLocalBounds = textScore.getLocalBounds();
	textScore.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height / 2 });
	textScore.setPosition((float)wSize.x * .65f, (float)wSize.y * .85f);

	//Loss font
	if (!someFont.loadFromFile("assets/main_font.ttf"))
		printf("Failed to load font!!!");
	textLost.setFont(someFont);
	textLost.setString("Game Over!");
	textLost.setCharacterSize(128);
	textLocalBounds = textLost.getLocalBounds();
	textLost.setOrigin({ textLocalBounds.width / 2, textLocalBounds.height / 2 });
	textLost.setPosition({ (float)wSize.x / 2, (float)wSize.y / 4 });
	textLost.setFillColor(sf::Color::Green);
	textLost.setOutlineColor(sf::Color::Black);
	textLost.setOutlineThickness(4.0f);
}

void Game::run()
{
	while (isRunning)
	{
		sf::Event event;
		sf::Time dt = clock.restart();
		while (wnd.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
				wnd.close();
			}
		}
		update(dt);
		wnd.clear(sf::Color::White);
		render(wnd);
		wnd.display();
	}
}

void Game::handleInput(sf::Time dt)
{
	sf::Vector2f playerVel;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) playerVel.y -= moveSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) playerVel.y += moveSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) playerVel.x -= moveSpeed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) playerVel.x += moveSpeed;

	if (abs(playerVel.x) + abs(playerVel.y) > moveSpeed)
	{
		playerVel *= 0.75f;
	}
	world.updatePlayerPos(playerVel * dt.asSeconds());
	//player.move(playerVel * dt.asSeconds());
}

void Game::update(sf::Time dt)
{
	handleInput(dt);
	auto player = world.getPlayer();
	if (player.isAlive())
	{
		updateScore(dt);
		world.update(dt);
	}

	else {
		if (score > highScore) {
			highScore = score;
			writeHighScore();
		}
	}



	// world.update(dt);
	//updateAudio?
	
}

void Game::render(sf::RenderWindow& wnd)
{
	// ui

	world.draw();
	auto player = world.getPlayer();
	if (!player.isAlive()) {
		wnd.draw(textLost);
	}
	drawScore(wnd);
}

void Game::drawScore(sf::RenderWindow& wnd) {
	textScore.setString("Score: " + std::to_string(score) + "\n" + "High Score: " + std::to_string(highScore));
	wnd.draw(textScore);
}

void Game::updateScore(sf::Time dt) {
	if (scoreCount <= 0) {
		score += 5;
		scoreCount = 3.f;
	}
	else
		scoreCount -= dt.asSeconds();
}

void Game::getHighScore() {
	std::ifstream infile;
	infile.open("assets/high_score.txt");
	if (!infile.is_open()) {
		throw "Could not open file";
	}
	infile >> highScore;
	infile.close();
}

void Game::writeHighScore() {
	std::ofstream outfile;
	outfile.open("assets/high_score.txt");
	if (!outfile.is_open()) {
		throw "Could not open file";
	}
	outfile << highScore;
	outfile.close();
}