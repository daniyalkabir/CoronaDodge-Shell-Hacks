#include "Game.h"

int main()
{
	Game game;
	game.load();
	game.run();
	//	auto dMove = moveSpeed * dt;
//	sf::Vector2f deltaPos = player.getPosition() - enemy1.getPosition();
//	deltaPos /= sqrt((deltaPos.x * deltaPos.x) + (deltaPos.y * deltaPos.y));
//	enemy1.move({ deltaPos.x * dMove, deltaPos.y * dMove });
	
	return 0;
}