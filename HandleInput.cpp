
#include "ZombieArena.hpp"
//#include "Player.hpp"
//#include "TextureHolder.hpp"
//#include "Bullet.hpp"
//#include "Pickup.hpp"

void handleEvents(Event& event, State& state, Clock& clock, Player* player, t_sound& sounds, t_stat& stat)
{
	if (event.type == Event::KeyPressed)
	{
		// Pause a game while playing
		if (event.key.code == Keyboard::Return &&
			state == State::PLAYING)
		{
			state = State::PAUSED;
		}
		// Restart while paused
		else if (event.key.code == Keyboard::Return &&
			state == State::PAUSED)
		{
			state = State::PLAYING;
			// Reset the clock so there isn't a frame jump
			clock.restart();
		}
		// Start a new game while in GAME_OVER state
		else if (event.key.code == Keyboard::Return &&
			state == State::GAME_OVER)
		{
			state = State::LEVELING_UP;
			stat.wave = 0;
			stat.score = 0;
			// Prepare the gun and ammo for next game
			stat.currentBullet = 0;
			stat.bulletsSpare = 24;
			stat.bulletsInClip = 6;
			stat.clipSize = 6;
			stat.fireRate = 1;
			// Reset the player's stats
			player->resetPlayerStats();

		}
	}
}

void handleMove(Player* player, t_stat& stat, t_sound& sounds, Bullet bullets[], t_time& time, Vector2f mouseWorldPosition)
{
	static bool isReloading = false;
	// Handle the pressing and releasing of WASD keys
	if (Keyboard::isKeyPressed(Keyboard::W))
		player->moveUp();
	else
		player->stopUp();
	if (Keyboard::isKeyPressed(Keyboard::S))
		player->moveDown();
	else
		player->stopDown();
	if (Keyboard::isKeyPressed(Keyboard::A))
		player->moveLeft();
	else
		player->stopLeft();
	if (Keyboard::isKeyPressed(Keyboard::D))
		player->moveRight();
	else
		player->stopRight();

	// Fire a bullet
	if (Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (time.gameTimeTotal.asMilliseconds()
			- time.lastPressed.asMilliseconds()
			> 1000 / stat.fireRate && stat.bulletsInClip > 0)
		{
			bullets[stat.currentBullet].shoot(
				player->getCenter().x, player->getCenter().y,
				mouseWorldPosition.x, mouseWorldPosition.y);
			stat.currentBullet++;
			if (stat.currentBullet > 99)
				stat.currentBullet = 0;
			time.lastPressed = time.gameTimeTotal;
			sounds.shoot.play();
			stat.bulletsInClip--;
		}
	}
	// Reloading
	if (Mouse::isButtonPressed(sf::Mouse::Right) && !isReloading)
	{
		isReloading = true;
		if (stat.bulletsSpare >= stat.clipSize)
		{
			stat.bulletsInClip = stat.clipSize;
			stat.bulletsSpare -= stat.clipSize;
			sounds.reload.play();
		}
		else if (stat.bulletsSpare > 0)
		{
			stat.bulletsInClip = stat.bulletsSpare;
			stat.bulletsSpare = 0;
			sounds.reload.play();
		}
		else
		{
			sounds.reloadFailed.play();
		}
	}
	else if (!Mouse::isButtonPressed(sf::Mouse::Right))
		isReloading = false;
}

State handleLevelUp(Event event, t_stat& stat, Player* player, State& state, Pickup* healthPickup, Pickup* ammoPickup)
{
	// Handle the player LEVELING up
	if (event.key.code == Keyboard::Num1)
	{
		stat.fireRate++;
		state = State::PLAYING;
	}
	else if (event.key.code == Keyboard::Num2)
	{
		stat.clipSize += stat.clipSize;
		state = State::PLAYING;
	}
	else if (event.key.code == Keyboard::Num3)
	{
		player->upgradeHealth();
		state = State::PLAYING;
	}
	else if (event.key.code == Keyboard::Num4)
	{
		player->upgradeSpeed();
		state = State::PLAYING;
	}
	else if (event.key.code == Keyboard::Num5)
	{
		healthPickup->upgrade();
		state = State::PLAYING;
	}
	else if (event.key.code == Keyboard::Num6)
	{
		ammoPickup->upgrade();
		state = State::PLAYING;
	}
	return state;
}

void setNewLevel(State state, t_stat& stat, IntRect& arena, Player* player, VertexArray& background,
	Vector2f resolution, Pickup* healthPickup, Pickup* ammoPickup, Sound powerup)
{

	if (state == State::PLAYING)
	{
		stat.wave++;
		arena.width = 500 * stat.wave;
		arena.height = 500 * stat.wave;
		arena.left = 0;
		arena.top = 0;
		int tileSize = createBackground(background, arena);
		// Spawn the player in middle of the arena
		player->spawn(arena, resolution, tileSize);
		// Create a horde of zombies
		// Configure the pick-ups
		healthPickup->setArena(arena);
		ammoPickup->setArena(arena);

		stat.numZombies = 5 * stat.wave;
		//// Delete the previously allocated memory (if it exists)
		//delete[] zombies;
		//zombies = createHorde(numZombies, arena);
		stat.numZombiesAlive = stat.numZombies;
		powerup.play();
		
	}
}