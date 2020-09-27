#pragma once
#include "Entity.h"
#include <deque>
#include <boost/geometry.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/geometries/point.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>

typedef std::vector<sf::Vector2f> Polygon;

BOOST_GEOMETRY_REGISTER_POINT_2D(sf::Vector2f, float, boost::geometry::cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_LINESTRING(Polygon)

class Player : public Entity
{
	bool isSpraying;
	bool alive = true;
	sf::ConvexShape playerSpray;
public:
	Player();
	void update(sf::Vector2f deltaPos);
	void checkWall(sf::Vector2f& deltaPos);
	void checkStreaks(sf::Vector2f& deltaPos);
	void sprayStreaks();
	void updateSpray(float sprayAngle);
	void draw(sf::RenderWindow& wnd);
	void die();
	bool isAlive();
	bool getSprayStatus();
	sf::ConvexShape& getSpray();
};

