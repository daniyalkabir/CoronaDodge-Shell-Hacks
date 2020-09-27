#include "World.h"
#include <cstdlib>
#include <ctime>
#include <vector>

World::World()
	:
	arena({ ArenaWidth,ArenaHeight })
{
	arena.setFillColor(sf::Color::White);
	arena.setOutlineColor(sf::Color::Black);
	arena.setOutlineThickness(2.0f);
	auto aSize = arena.getSize();
	arena.setOrigin(aSize.x / 2, aSize.y / 2);
	entities = EntityManager::Get();
}

void World::setWindow(sf::RenderWindow* pWnd)
{
	this->pWnd = pWnd;
}

void World::init()
{
	srand(unsigned int(time(0)));
	initPlayer();
}

void World::spawnEntity(sf::Time dt) {
	if (spawnVal <= 0) {
		float spawnAngle = (float)(rand() % 360);
		float spawnX = cos(spawnAngle);
		float spawnY = sin(spawnAngle);
		sf::Vector2f entPos = { spawnX * 1200 + 600, spawnY * 900 + 450 };
		//sf::Vector2f entPos = { spawnX * 800 + 600, spawnY * 600 + 450 };

		sf::Vector2f velocity;
		if (covCount == 0)
		{  //shoot towards player
			velocity = player.getPosition() - entPos;
			covCount++;
		}
		else 
		{
			sf::Vector2f target(float(rand() % 800 + 200), float(rand() % 600 + 150));
			velocity = target - entPos;
			covCount++;
			if (covCount == 5)
				covCount = 0;
		}
		velocity /= sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));


		EntityData enemyData;
		enemyData.entityPos = entPos;
		enemyData.velocity = velocity * 0.1f;
		auto pEnemy = entities->createEntity(EntType::ET_Enemy, enemyData);
		EntityData streakData;
		streakData.entityPos = entPos;
		streakData.pEnt = pEnemy;
		entities->createEntity(EntType::ET_Streak, streakData);


		spawnVal = (float)((rand() % 50 + 5) / 10.);
	}
	else 
	{
		spawnVal = spawnVal - dt.asSeconds();
	}
}

void World::updatePlayerPos(sf::Vector2f deltaPos)
{
	player.update(deltaPos);
}

const Player& World::getPlayer()
{
	return player;
}

void World::initPlayer()
{
	auto texMan = TextureManager::Get();
	player.setTexture(texMan->getTexture(TexID::PlayerNorth));
	player.setColor(sf::Color::Blue);
	auto pRect = player.getLocalBounds();
	player.setOrigin(pRect.width / 2, pRect.height / 2);
	auto wSize = pWnd->getSize();
	player.setPosition(float(wSize.x / 2), float(wSize.y / 2));
}

void World::updatePlayer()
{
	auto mousePosI = sf::Mouse::getPosition(*pWnd);
	sf::Vector2f mousePos = { (float)mousePosI.x, (float)mousePosI.y };
	auto playerBox = player.getLocalBounds();
	auto playerPos = player.getPosition();
	sf::Vector2f playerCenter = { 
		playerPos.x - playerBox.width / 2, 
		playerPos.y - playerBox.height / 2 };
	auto sprayAngle = Math::CalcAngle(mousePos, playerCenter);
	player.updateSpray(sprayAngle);
}

int bOnce = false;
void World::updateEntities(sf::Time dt) 
{
	spawnEntity(dt);
	entities->update(dt, player);
}

void World::draw()
{
	auto wSize = pWnd->getSize();
	arena.setPosition(float(wSize.x / 2), float(wSize.y / 2));
	pWnd->draw(arena);
	entities->draw(*pWnd);
	player.draw(*pWnd);
}

void World::update(sf::Time dt)
{
	updatePlayer();
	updateEntities(dt);
}
