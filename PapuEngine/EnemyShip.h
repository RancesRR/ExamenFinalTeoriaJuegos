#pragma once
#include "Ship.h"
#include "Vullet.h"
class EnemyShip : public Ship
{
private:
	float _elapsed;
public:
	EnemyShip(float agent_width, float agent_height, glm::vec2 position,std::string texture);
	void update(float deltaTime);
	bool outside();
	bool colision(Vullet* bullet);
	~EnemyShip();
};

