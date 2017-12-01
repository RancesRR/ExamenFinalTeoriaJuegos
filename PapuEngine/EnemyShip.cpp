#include "EnemyShip.h"



EnemyShip::EnemyShip(float agent_width, float agent_height, glm::vec2 position, std::string texture)
	:Ship(agent_width,agent_height,position,texture),_elapsed(0)
{
	
}

void EnemyShip::update(float deltaTime) {
	_elapsed += deltaTime;
	_position.y -= 5;
}

bool EnemyShip::outside() {
	if (_position.y < 20) return true;
	return false;
}


bool EnemyShip::colision(Vullet* bullet) {
	if (bullet->collision(_position.x,_position.y))return true;
	return false;
}

EnemyShip::~EnemyShip()
{
}
