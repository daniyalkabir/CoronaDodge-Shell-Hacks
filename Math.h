#pragma once
#include <SFML/System/Vector2.hpp>
#include <cmath>
namespace Math
{
	float CalcAngle(sf::Vector2f dest, sf::Vector2f origin);
	float GetDistance(sf::Vector2f dest, sf::Vector2f origin);
}