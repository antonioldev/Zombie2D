#include "ZombieArena.hpp"
//#include "Player.hpp"
//#include "TextureHolder.hpp"
//#include "Bullet.hpp"
//#include "Pickup.hpp"

void drawGameover(RenderWindow& window, Sprite& gameOver, t_texts& texts)
{
	window.draw(gameOver);
	window.draw(texts.gameOver);
	window.draw(texts.score);
	window.draw(texts.hiscore);
}

void drawLevelUp(RenderWindow& window, Sprite& gameOver, Text& levelUp)
{
	window.draw(gameOver);
	window.draw(levelUp);
}

//void drawPlaying(RenderWindow& window, t_sprite& sprite, Player &player, Zombie* zombies,
//	Bullet* bullets, t_texts& texts, t_stat& stat, VertexArray background, View& mainView, View& hudView,
//	Texture& bg, Pickup& healthPickup, Pickup& ammoPickup)
//{
//	window.clear();
//	// set the mainView to be displayed in the window
//	// And draw everything related to it
//	window.setView(mainView);
//	// Draw the background
//	window.draw(background, &bg);
//	// Draw the zombies
//	for (int i = 0; i < stat.numZombies; i++)
//	{
//		window.draw(zombies[i].getSprite());
//	}
//	for (int i = 0; i < 100; i++)
//	{
//		if (bullets[i].isInFlight())
//			window.draw(bullets[i].getShape());
//	}
//	// Draw the pick-ups, if currently spawned
//	if (ammoPickup.isSpawned())
//		window.draw(ammoPickup.getSprite());
//	if (healthPickup.isSpawned())
//		window.draw(healthPickup.getSprite());
//	//Draw the crosshair
//	window.draw(sprite.crosshair);
//	// Draw the player
//	window.draw(player.getSprite());
//	// Switch to the HUD view
//	window.setView(hudView);
//	// Draw all the HUD elements
//	window.draw(sprite.ammoIcon);
//	window.draw(texts.ammo);
//	window.draw(texts.score);
//	window.draw(texts.hiscore);
//	window.draw(sprite.healthBar);
//	window.draw(texts.waveNumber);
//	window.draw(texts.zombiesRemaining);
//}