#include "Entity.h"
#include "TextureManager.h"

Entity::Entity(EntType entType)
{
	streakVerts = sf::VertexArray(sf::Triangles, 3);
	this->entType = entType;
}

Entity::Entity(EntType entType, TextureID texID)
{
	auto texMan = TextureManager::Get();
	setTexture(texMan->getTexture(texID));
	setColor(sf::Color::Green);
	this->entType = entType;
}

EntType Entity::getType()
{
	return entType;
}

void Entity::applyTexture(TextureID texID)
{
	auto texMan = TextureManager::Get();
	setTexture(texMan->getTexture(texID));
}

sf::Vector2f Entity::getVelocity() {
	return velocity;
}

void Entity::setVelocity(sf::Vector2f v) {
	velocity = v;
}

void Entity::updateTimeToDie(sf::Time* pDT)
{
	timeToDie -= pDT->asSeconds();
}

float Entity::getTimeToDie()
{
	return timeToDie;
}

void Entity::setTarget(Entity* pTarget)
{
	this->pTarget = pTarget;
}

Entity* Entity::getTarget()
{
	return pTarget;
}

void Entity::adjustStreak(sf::Vector2f enemyPos)
{
	auto start = enemyPos;
	auto end = getPosition();
	auto delta = end - start;
	auto dist = Math::GetDistance(end, start);
	delta /= dist;
	if (delta.x < 2)
		delta.x = 2;
	if (delta.y < 2)
		delta.y = 2;

	//streakVerts[0].position = { start.x - delta.x * 5.0f, start.y + delta.y * 5.0f };
	streakVerts[0].position = { start.x, start.y};
	//streakVerts[1].position = { start.x + delta.x * 5.0f, start.y - delta.y * 5.0f };
	streakVerts[1].position = { end.x + delta.x * 25.0f, end.y - delta.y * 25.0f };
	streakVerts[2].position = { end.x - delta.x * 25.0f, end.y + delta.y * 25.0f };

	auto streakColor = sf::Color::Green;
	streakColor.a = 127;

	streakVerts[0].color = streakColor;
	//streakVerts[1].color = streakColor;
	streakVerts[1].color = streakColor;
	streakVerts[2].color = streakColor;
}

sf::VertexArray& Entity::getVerts()
{
	return streakVerts;
}

void Entity::cleanStreak()
{
	streakCleaned = true;
}

bool Entity::getCleaned()
{
	return streakCleaned;
}

void Entity::updateTimeToClean(sf::Time* pDT)
{
	timeToClean -= pDT->asSeconds();
}

float Entity::getTimeToClean()
{
	return timeToClean;
}
