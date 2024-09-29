#pragma once
#include "Zombie.hpp"
#include <SFML/Graphics.hpp>
using namespace sf;

// The game will always be in one of four states
enum class State {
	PAUSED, LEVELING_UP,
	GAME_OVER, PLAYING
};

int createBackground(VertexArray& rVA, IntRect arena);
Zombie* createHorde(int numZombies, IntRect arena);
