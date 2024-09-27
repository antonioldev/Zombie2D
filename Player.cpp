#include "Player.hpp"

//Constructor for player object
Player::Player()
	:	_speed(START_SPEED),
		_health(START_HEALTH),
		_maxHealth(START_HEALTH),
		_texture(),
		_sprite()
{
	_texture.loadFromFile("graphics/player.png");
	_sprite.setTexture(_texture);
	//Set the orig to the center for smooth rotation
	_sprite.setOrigin(25, 25);
}

//Spawn of the player on the arena
void Player::spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize)
{
	_position.x = arena.width / 2;
	_position.y = arena.height / 2;
	
	//copy the details of the arena to the player's arena
	_arena.left = arena.left;
	_arena.width = arena.width;
	_arena.top = arena.top;
	_arena.height = arena.height;

	//remember how big the tiles are in the arena
	_tileSize = tileSize;

	//remember the resolution
	_resolution.x = resolution.x;
	_resolution.y = resolution.y;
}

//Cal at the end of each game
void Player::resetPlayerStat()
{
	_speed = START_SPEED;
	_health = START_HEALTH;
	_maxHealth = START_HEALTH;
}

//Handle the player get hit
bool Player::hit(sf::Time timeHit)
{
	if ((timeHit.asMilliseconds() - _lastHit.asMilliseconds()) > 200)
	{
		_lastHit = timeHit;
		_health -= 10;
		return true;
	}
	else
		return false;
}

//Return last time the player got hit
sf::Time Player::getLastHitTime()
{
	return _lastHit;
}

//Where the player is on the map
sf::FloatRect Player::getPosition()
{
	return _sprite.getGlobalBounds();
}

//Wher is the center of the player
sf::Vector2f Player::getCenter()
{
	return _position;
}

//What angle the player is facing
float Player::getRotation()
{
	return _sprite.getRotation();
}

//Return a copy of the player's sprite 
sf::Sprite Player::getSprite()
{
	return _sprite;
}

//Move the player up
void Player::moveUp()
{
	_upPressed = true;
}

void Player::stopUp()
{
	_upPressed = false;
}

//Move the player down
void Player::moveDown()
{
	_downPressed = true;
}

void Player::stopDown()
{
	_downPressed = false;
}

//Move the player left
void Player::moveLeft()

{
	_leftPressed = true;
}

void Player::stopLeft()

{
	_leftPressed = false;
}

//Move the player right
void Player::moveRight()

{
	_rightPressed = true;
}

void Player::stopRight()

{
	_rightPressed = false;
}

//Call at each frame to update the windown
void Player::update(float elapsedTime, sf::Vector2i mousePosition)
{
	if (_upPressed)
		_position.y -= _speed * elapsedTime;
	if (_downPressed)
		_position.y += _speed * elapsedTime;
	if (_leftPressed)
		_position.x -= _speed * elapsedTime;
	if (_rightPressed)
		_position.x += _speed * elapsedTime;
	_sprite.setPosition(_position);

	//keep player in the arena
	if (_position.x > (_arena.width - _tileSize))
		_position.x = _arena.width - _tileSize;
	if (_position.x < (_arena.width + _tileSize))
		_position.x = _arena.width + _tileSize;

	if (_position.y > (_arena.height - _tileSize))
		_position.y = _arena.height - _tileSize;
	if (_position.y < (_arena.height + _tileSize))
		_position.y = _arena.height + _tileSize;

	//calculate the angle of the player
	float angle = (atan2(mousePosition.y - _resolution.y / 2,
		mousePosition.x - _resolution.x / 2) * 180) / 3.141;
	_sprite.setRotation(angle);
}

//Increase the player speed
void Player::upgradeSpeed()
{
	_speed += (START_SPEED * 0.2);
}

//Increase the player health
void Player::upgradeHealth()
{
	_maxHealth += (START_HEALTH * 0.2);
}

//Increase the max' health the player can have
void Player::increaseHealthLevel(int amount)
{
	_health += amount;
	if (_health > _maxHealth)
		_health = _maxHealth;
}

//Return the player health value
int Player::getHealth()
{
	return _health;
}