#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Player.hpp"

using namespace sf;

//State of the game
enum class State {
	PAUSED,
	LEVELING_UP,
	GAME_OVER,
	PLAYING
};

typedef struct s_game {

	State state;
	Vector2f resolution;
	Clock clock; //Clock for timing
	Time gameTimeTotal; //How long has the paying status been active
	Vector2f mouseWorldPosisiton; //Position of the mouse in relation to world cordinate
	Vector2i mouseScreenPosition; //Position of the mouse in relation to screen cordinate
	IntRect arena; //The boundaries of the arena


} t_game;