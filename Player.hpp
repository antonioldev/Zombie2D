#pragma once

#include <SFML/Graphics.hpp>


class Player {
	private:
		const float START_SPEED = 200;
		const float START_HEALTH = 100;
		sf::Vector2f _position; //position of the payer
		sf::Sprite _sprite;

		sf::Texture _texture;
		sf::Vector2f _resolution; //screen resolution
		sf::IntRect _arena; //size of current arena
		int _tileSize; //size of each tile of the arena
		bool _upPressed;
		bool _downPressed;
		bool _leftPressed;
		bool _rightPressed;
		int _health; // health of the player
		int _maxHealth; // maximum health of the player
		sf::Time _lastHit; //when was player last hit
		float _speed; // spped in pixel per seconds

	public:
		Player();
		void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);
		void resetPlayerStat();
		bool hit(sf::Time timeHit);
		sf::Time getLastHitTime();
		sf::FloatRect getPosition();
		sf::Vector2f getCenter();
		float getRotation();
		sf::Sprite getSprite();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void stopUp();
		void stopDown();
		void stopLeft();
		void stopRight();
		void update(float elapsedTime, sf::Vector2i mousePosition);
		void upgradeSpeed();
		void upgradeHealth();
		void increaseHealthLevel(int amount);
		int getHealth();
};