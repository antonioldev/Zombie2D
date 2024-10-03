#include "ZombieArena.hpp"

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

void drawMainView(RenderWindow& window, t_sprite& sprite, t_stat& stat, VertexArray background, 
	Texture& bg, t_gameObj& gameObj)
{
	
	window.draw(background, &bg);
	for (int i = 0; i < stat.numZombies; i++)
	{
		window.draw(gameObj.zombies[i].getSprite());
	}
	for (int i = 0; i < 100; i++)
	{
		if (gameObj.bullets[i].isInFlight())
			window.draw(gameObj.bullets[i].getShape());
	}
	if (gameObj.ammoPickup->isSpawned())
		window.draw(gameObj.ammoPickup->getSprite());
	if (gameObj.healthPickup->isSpawned())
		window.draw(gameObj.healthPickup->getSprite());
	window.draw(sprite.crosshair);
	window.draw(gameObj.player->getSprite());
	
}

// Draw all the HUD elements
void drawHudView(RenderWindow& window, t_sprite& sprite, t_texts& texts)
{
	window.draw(sprite.ammoIcon);
	window.draw(texts.ammo);
	window.draw(texts.score);
	window.draw(texts.hiscore);
	window.draw(sprite.healthBar);
	window.draw(texts.waveNumber);
	window.draw(texts.zombiesRemaining);
}

void freeMemory(t_gameObj& gameObj)
{
	delete[] gameObj.zombies;
	delete[] gameObj.bullets;
	delete gameObj.healthPickup;
	delete gameObj.ammoPickup;
	delete gameObj.player;
}