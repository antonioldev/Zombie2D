
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Game.hpp"
#include "Player.hpp"

using namespace sf;

//Get the desktop resolution
void getDesktopResolution(t_game& game)
{
	game.state = State::GAME_OVER;
	game.resolution.x = VideoMode::getDesktopMode().width;
	game.resolution.y = VideoMode::getDesktopMode().height;
}

int main()
{
	t_game game;
	
	//Create a SFML window
	RenderWindow window(VideoMode(game.resolution.x, game.resolution.y),
		"Zombie Arena", Style::Fullscreen);

	//Create the SFML Views
	View mainView(FloatRect(0, 0, game.resolution.x, game.resolution.y));

	Player player;

	while (window.isOpen())
	{

	}

	return 0;
}


