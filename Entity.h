#pragma once
#include "SFMLBase.h"
#include "Types.h"
#include "Math.h"
constexpr auto moveSpeed = 150.0f;

class Entity;
struct EntityData
{
	sf::Vector2f entityPos;
	sf::Vector2f velocity;
	Entity* pEnt;
};

class Entity : public sf::Sprite
{
	EntType entType;
	sf::Vector2f velocity;
	float timeToDie = 15.0f;
	Entity* pTarget = nullptr;
	//sf::RectangleShape streak;
	sf::VertexArray streakVerts;
	float timeToClean = 0.1f;
	bool streakCleaned = false;
public:
	Entity(EntType entType);
	Entity(EntType entType, TextureID texID);
	EntType getType();
	void applyTexture(TextureID texID);
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f v);
	void updateTimeToDie(sf::Time* pDT);
	float getTimeToDie();
	void setTarget(Entity* pTarget);
	Entity* getTarget();
	/*void setLength(float length);
	sf::RectangleShape* getStreak();*/
	void adjustStreak(sf::Vector2f enemyPos);
	sf::VertexArray& getVerts();
	void cleanStreak();
	bool getCleaned();
	void updateTimeToClean(sf::Time* pDT);
	float getTimeToClean();
};