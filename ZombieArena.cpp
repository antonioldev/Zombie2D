
#include "ZombieArena.hpp"

using namespace sf;

int main()
{
	TextureHolder holder; // Here is the instance of TextureHolder
	State state = State::GAME_OVER;
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width; //getWindowResolution(resolution);
	resolution.y = VideoMode::getDesktopMode().height;
	RenderWindow window(VideoMode(resolution.x, resolution.y), // create an SFML window
		"Zombie Arena", Style::Fullscreen);
	window.setMouseCursorVisible(false); // Hide the mouse pointer and replace it with crosshair
	View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));
	View hudView(sf::FloatRect(0, 0, 1920, 1080)); // Create a view for the HUD
	Clock clock;
	Vector2f mouseWorldPosition; // Where is the mouse in relation to world coordinates
	Vector2i mouseScreenPosition;
	IntRect arena; // The boundaries of the arena
	VertexArray background; // Create the background

	t_gameObj gameObj;
	loadGameObj(gameObj); //Allcoate memory for all game objects
	t_time time;
	t_stat stat;
	stat.hiScore = get_hiscore();
	t_texts texts;
	load_text_files(texts, stat.hiScore);
	t_sound sounds;
	load_audio_files(sounds);
	t_texture texture;
	t_sprite sprite;
	loadHUDTexure(texture, sprite);

	// The main game loop
	while (window.isOpen())
	{
		Event event; // Handle events by polling
		while (window.pollEvent(event))
			handleEvents(event, state, clock, gameObj.player, sounds, stat);
		if (Keyboard::isKeyPressed(Keyboard::Escape)) // Handle the player quitting
			window.close();
		if (state == State::PLAYING) // Handle WASD while playing
			handleMove(gameObj.player, stat, sounds, gameObj.bullets, time, mouseWorldPosition);
		if (state == State::LEVELING_UP) // Handle the LEVELING up state
		{
			if (handleLevelUp(event, stat, gameObj.player, state, gameObj.healthPickup, gameObj.ammoPickup) == State::PLAYING)
			{
				setNewLevel(state, stat, arena, gameObj.player, background, resolution,
					gameObj.healthPickup, gameObj.ammoPickup, sounds.powerup);
				delete[] gameObj.zombies;
				gameObj.zombies = createHorde(stat.numZombies, arena);
				clock.restart(); // Reset clock so there isn't a frame jump
			}
		}
//		****************
//		UPDATE THE FRAME
//		****************
		if (state == State::PLAYING)
		{
			Time dt = clock.restart(); // Update the delta time
			time.gameTimeTotal += dt; // Update the total game time
			float dtAsSeconds = dt.asSeconds();
			mouseWorldPosition = window.mapPixelToCoords(Mouse::getPosition(), mainView);
			sprite.crosshair.setPosition(mouseWorldPosition);
			gameObj.player->update(dtAsSeconds, Mouse::getPosition()); // Update the player
			mainView.setCenter(gameObj.player->getCenter()); // Make the view centre the around player
			for (int i = 0; i < stat.numZombies; i++) // Loop through each Zombie and update them
				if (gameObj.zombies[i].isAlive())
					gameObj.zombies[i].update(dt.asSeconds(), gameObj.player->getCenter());
			for (int i = 0; i < 100; i++) // Update any bullets that are in-flight
				if (gameObj.bullets[i].isInFlight())
					gameObj.bullets[i].update(dtAsSeconds);
			gameObj.healthPickup->update(dtAsSeconds);
			gameObj.ammoPickup->update(dtAsSeconds);
			hasZombieBeenShot(stat, gameObj.zombies, gameObj.bullets, state, sounds.splat);
			hasPlayerBeenAttacked(stat, gameObj.zombies, gameObj.player, state, sounds.hit, time.gameTimeTotal);
			hasPlayerGotPickup(gameObj.player, gameObj.healthPickup, gameObj.ammoPickup, sounds, stat);
			sprite.healthBar.setSize(Vector2f(gameObj.player->getHealth() * 3, 50)); // size up the health bar
			stat.framesSinceLastHUDUpdate++;
			if (stat.framesSinceLastHUDUpdate > stat.fpsMeasurementFrameInterval)
			{
				updateHUD(stat, texts);
				stat.framesSinceLastHUDUpdate = 0;
			}
		}
//		**************
//		Draw the scene
//		**************
		if (state == State::PLAYING)
		{
			window.clear();
			window.setView(mainView);
			drawMainView(window, sprite, stat, background, texture.background, gameObj);
			window.setView(hudView);
			drawHudView(window, sprite, texts);
		}
		else if (state == State::LEVELING_UP)
			drawLevelUp(window, sprite.gameOver, texts.levelUp);
		else if (state == State::PAUSED)
			window.draw(texts.paused);
		else if (state == State::GAME_OVER)
			drawGameover(window, sprite.gameOver, texts);
		window.display();

	}
	freeMemory(gameObj);
	return 0;
}
