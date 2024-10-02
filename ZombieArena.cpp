
#include "ZombieArena.hpp"
#include "Player.hpp"
#include "TextureHolder.hpp"
#include "Bullet.hpp"
#include "Pickup.hpp"


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

	// Health bar
	/*RectangleShape healthBar;*/
	/*healthBar.setFillColor(Color::Red);
	healthBar.setPosition(450, 980);*/

	Player* player = new Player();
	//Player player; // Create an instance of the Player class
	Zombie* zombies = nullptr; // Prepare for a horde of zombies
	Bullet* bullets = new Bullet[100]; //Prepare a set of bulltes
	Pickup* healthPickup = new Pickup(1); // Dynamic allocation
	Pickup* ammoPickup = new Pickup(2);
	
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
			handleEvents(event, state, clock, player, sounds, stat);
		if (Keyboard::isKeyPressed(Keyboard::Escape)) // Handle the player quitting
			window.close();
		if (state == State::PLAYING) // Handle WASD while playing
			handleMove(player, stat, sounds, bullets, time, mouseWorldPosition);
		if (state == State::LEVELING_UP) // Handle the LEVELING up state
		{
			if (handleLevelUp(event, stat, player, state, healthPickup, ammoPickup))
			{
				setNewLevel(state, stat, arena, player, background, resolution,
					*healthPickup, *ammoPickup, sounds.powerup);
				delete[] zombies;
				zombies = createHorde(stat.numZombies, arena);
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
			mouseWorldPosition = window.mapPixelToCoords(
				Mouse::getPosition(), mainView);
			sprite.crosshair.setPosition(mouseWorldPosition);
			player->update(dtAsSeconds, Mouse::getPosition()); // Update the player
			mainView.setCenter(player->getCenter()); // Make the view centre the around player
			for (int i = 0; i < stat.numZombies; i++) // Loop through each Zombie and update them
				if (zombies[i].isAlive())
					zombies[i].update(dt.asSeconds(), player->getCenter());
			for (int i = 0; i < 100; i++) // Update any bullets that are in-flight
				if (bullets[i].isInFlight())
					bullets[i].update(dtAsSeconds);
			healthPickup->update(dtAsSeconds);
			ammoPickup->update(dtAsSeconds);
			hasZombieBeenShot(stat, zombies, bullets, state, sounds.splat);
			hasPlayerBeenAttacked(stat, zombies, player, state, sounds.hit, time.gameTimeTotal);
			hasPlayerGotPickup(player, healthPickup, ammoPickup, sounds, stat);
			sprite.healthBar.setSize(Vector2f(player->getHealth() * 3, 50)); // size up the health bar
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
			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);
			// Draw the background
			window.draw(background, &texture.background);
			// Draw the zombies
			for (int i = 0; i < stat.numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}
			for (int i = 0; i < 100; i++)
			{
				if (bullets[i].isInFlight())
					window.draw(bullets[i].getShape());
			}
			// Draw the pick-ups, if currently spawned
			if (ammoPickup->isSpawned())
				window.draw(ammoPickup->getSprite());
			if (healthPickup->isSpawned())
				window.draw(healthPickup->getSprite());
			//Draw the crosshair
			window.draw(sprite.crosshair);
			// Draw the player
			window.draw(player->getSprite());
			// Switch to the HUD view
			window.setView(hudView);
			// Draw all the HUD elements
			window.draw(sprite.ammoIcon);
			window.draw(texts.ammo);
			window.draw(texts.score);
			window.draw(texts.hiscore);
			window.draw(sprite.healthBar);
			window.draw(texts.waveNumber);
			window.draw(texts.zombiesRemaining);


			
		}

		if (state == State::LEVELING_UP)
			drawLevelUp(window, sprite.gameOver, texts.levelUp);
		if (state == State::PAUSED)
			window.draw(texts.paused);
		if (state == State::GAME_OVER)
			drawGameover(window, sprite.gameOver, texts);
		window.display();

	}
	delete[] zombies;
	delete[] bullets;
	delete healthPickup;
	delete ammoPickup;
	delete player;
	return 0;
}
