#pragma once
#include <vector>
#include "Entity.h"
#include "LinkedList.h"
#include "Player.h"
#include "Math.h"
class EntityManager
{
	static EntityManager* pEntMgr;
	LinkedList<Entity> enemies;
	LinkedList<Entity> streaks;
public:
	//std::vector<Entity> vEntites;
	static EntityManager* Get();
	Entity* createEntity(EntType entityType, EntityData& entityData);
	void draw(sf::RenderWindow& wnd);
	void update(sf::Time dt, Player& player);
	LinkedList<Entity>& getStreaks();
};

