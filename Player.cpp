#include "Player.h"
#include "World.h"
Player::Player()                     
	:
	Entity(EntType::ET_Player)
{
	playerSpray.setPointCount(3);
	playerSpray.setPoint(0, { 0, 0 });
	playerSpray.setPoint(1, { -25, -75 });
	playerSpray.setPoint(2, { 25, -75 });
	playerSpray.setFillColor(sf::Color::Cyan);
}

void Player::update(sf::Vector2f deltaPos)
{
	checkWall(deltaPos);
	checkStreaks(deltaPos);
	sprayStreaks();
	this->move(deltaPos);
	playerSpray.setPosition(getPosition());	
}

//hardcoded again..
void Player::checkWall(sf::Vector2f &deltaPos) {
	if (this->getPosition().x <= 200 + this->getLocalBounds().width / 2 && deltaPos.x < 0)
		deltaPos.x = 0;
	else if (this->getPosition().x >= 1000 - this->getLocalBounds().width / 2 && deltaPos.x > 0)
		deltaPos.x = 0;
	if (this->getPosition().y <= 150 + this->getLocalBounds().height / 2 && deltaPos.y < 0)
		deltaPos.y = 0;
	else if (this->getPosition().y >= 750 - this->getLocalBounds().height / 2 && deltaPos.y > 0)
		deltaPos.y = 0;
}

struct StreakCollision
{
	bool bCollided;
	sf::Vector2f* deltaPos;
	Player* player;
};

float sign(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(sf::Vector2f pt, sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}
/*
double det = A1*B2 - A2*B1
if(det == 0){
//Lines are parallel
}else{
double x = (B2*C1 - B1*C2)/det
double y = (A1*C2 - A2*C1)/det
}
*/
sf::Vector2f LinesIntersect(sf::Vector2f i1, sf::Vector2f i2, sf::Vector2f j1, sf::Vector2f j2)
{
	float A1 = i2.y - i1.y;
	float B1 = i1.x - i2.x;
	float C1 = A1 * i1.x + B1 * i1.y;

	float A2 = j2.y - j1.y;
	float B2 = j1.x - j2.x;
	float C2 = A2 * j1.x + B2 * j1.y;

	auto det = A1 * B2 - A2 * B1;
	if (det < 0.0000001)
	{
		return {0,0};
	}
	else
	{
		sf::Vector2f result;
		result.x = (B2 * C1 - B1 * C2) / det;
		result.y = (A1 * C2 - A1 * C1) / det;
		return result;
	}
}

void checkCollision(Node<Entity>* pNode, void* pCollisionInfo)
{
	auto pInfo = reinterpret_cast<StreakCollision*>(pCollisionInfo);
	if (pInfo->bCollided)
		return;
	auto pPlayer = pInfo->player;
	auto pStreak = pNode->pElement;
	auto streakVerts = pStreak->getVerts();
	auto newPos = pPlayer->getPosition() + *pInfo->deltaPos;
	sf::Vector2f vertPos[] = {
		streakVerts[0].position,
		streakVerts[1].position,
		streakVerts[2].position,
		//streakVerts[3].position
	};
	auto bbox = pPlayer->getLocalBounds();
	sf::Vector2f hs = { bbox.width / 2, bbox.height / 2 };
	sf::Vector2f tr = { newPos.x + hs.x, newPos.y - hs.y };
	sf::Vector2f tl = { newPos.x - hs.x, newPos.y - hs.y };
	sf::Vector2f br = { newPos.x + hs.x, newPos.y + hs.y };
	sf::Vector2f bl = { newPos.x - hs.x, newPos.y + hs.y };
	if (PointInTriangle(tr, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		
		return;
	}

	if (PointInTriangle(tl, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		return;
	}

	if (PointInTriangle(br, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		return;
	}

	if (PointInTriangle(bl, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		return;
	}
}

void checkCollisionSpray(Node<Entity>* pNode, void* pCollisionInfo)
{
	auto pInfo = reinterpret_cast<StreakCollision*>(pCollisionInfo);
	auto pPlayer = pInfo->player;
	if (!pPlayer->getSprayStatus())
		return;
	auto pStreak = pNode->pElement;
	auto streakVerts = pStreak->getVerts();
	//auto newPos = pPlayer->getPosition() + *pInfo->deltaPos;
	sf::Vector2f vertPos[] = {
		streakVerts[0].position,
		streakVerts[1].position,
		streakVerts[2].position,
		//streakVerts[3].position
	};

	auto spray = pPlayer->getSpray();
	auto sprayTransform = spray.getTransform();
	auto sprayPos = spray.getPosition();
		
	auto p1 = spray.getPoint(0);
	//p1 += pPlayer->getPosition();
	p1 = sprayTransform.transformPoint(p1);
	auto p2 = spray.getPoint(1);
	p2 = sprayTransform.transformPoint(p2);
	auto p3 = spray.getPoint(2);
	p3 = sprayTransform.transformPoint(p3);
	
	Polygon poly1{ {p1.x, p1.y}, {p2.x, p2.y}, {p3.x, p3.y} };
	Polygon poly2{ 
		{vertPos[1].x, vertPos[1].y}, 
		{vertPos[0].x, vertPos[0].y}, 
		{vertPos[2].x, vertPos[2].y} };
	std::deque<Polygon> out;
	boost::geometry::intersection(poly1, poly2, out);
	if (out.size())
	{
		pStreak->cleanStreak();
		pInfo->bCollided;
		//printf("clean\n");
		return;
	}
}

void Player::checkStreaks(sf::Vector2f& deltaPos)
{
	auto pEnts = EntityManager::Get();
	auto streaks = pEnts->getStreaks();
	StreakCollision sc;
	sc.bCollided = false;
	sc.deltaPos = &deltaPos;
	sc.player = this;
	streaks.forEach(checkCollision, &sc);
	if (sc.bCollided)
		this->die();
}

void Player::sprayStreaks()
{
	auto pEnts = EntityManager::Get();
	auto streaks = pEnts->getStreaks();
	StreakCollision sc;
	sc.bCollided = false;
	sc.player = this;
	streaks.forEach(checkCollisionSpray, &sc);
}

void Player::updateSpray(float sprayAngle)
{
	playerSpray.setRotation(sprayAngle);
	isSpraying = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Player::draw(sf::RenderWindow& wnd)
{
	if(isSpraying)
		wnd.draw(playerSpray);
	wnd.draw(*this);
}

void Player::die()
{
	alive = false;
}

bool Player::isAlive()
{
	return alive;
}

bool Player::getSprayStatus()
{
	return isSpraying;
}

sf::ConvexShape& Player::getSpray()
{
	return playerSpray;
}
