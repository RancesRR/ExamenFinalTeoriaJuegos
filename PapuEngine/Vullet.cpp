#include "Vullet.h"
#include "ResourceManager.h"

Vullet::Vullet(std::string texture, glm::vec2 position)
				:_texture(texture),_position(position)
{
	_textureID = ResourceManager::getTexture(_texture).id;
}

void Vullet::draw(SpriteBacth& spritebatch) {
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	ColorRGBA  color;
	color.set(255, 255, 0, 255);
	glm::vec4 destRect(_position.x, _position.y, 20, 35);
	spritebatch.draw(destRect, uvRect, _textureID, 0.0f, color);
}

void Vullet::update(float deltaTime) {
	_elapsed += deltaTime;
	_position.y += 5;
}

bool Vullet::outside() {
	if (_position.y > 800)return true;
	return false;
}



bool Vullet::collision(int _X, int _Y) {
	if (_X + 40 >= _position.x && _X <= _position.x && _Y >= _position.y && _Y - 20 <= _position.y)return true;
	return false;
}

Vullet::~Vullet()
{
}
