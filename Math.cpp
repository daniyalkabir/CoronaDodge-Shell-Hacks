#include "Math.h"

float Math::CalcAngle(sf::Vector2f dest, sf::Vector2f origin)
{
	sf::Vector2f delta = dest - origin;
	return (atan2f(delta.y, delta.x) * 180.0f / 3.14f) + 90.0f;
}

float Math::GetDistance(sf::Vector2f dest, sf::Vector2f origin)
{
	auto dx = dest.x - origin.x;
	auto dy = dest.y - origin.y;
	return sqrt(dx * dx + dy * dy);
}
