#include "ZombieArena.hpp"
//#include "Player.hpp"
//#include "TextureHolder.hpp"
//#include "Bullet.hpp"
//#include "Pickup.hpp"

// Collision detection zombie/bullet
void hasZombieBeenShot(t_stat& stat, Zombie* zombies, Bullet bullets[], State& state, Sound splat)
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < stat.numZombies; j++)
		{
			if (bullets[i].isInFlight() &&
				zombies[j].isAlive())
			{
				if (bullets[i].getPosition().intersects
				(zombies[j].getPosition()))
				{
					// Stop the bullet
					bullets[i].stop();
					// Register the hit and see if it was a kill
					if (zombies[j].hit())
					{
						// Not just a hit but a kill too
						stat.score += 10;
						if (stat.score >= stat.hiScore)
						{
							stat.hiScore = stat.score;
						}
						stat.numZombiesAlive--;
						// When all the zombies are dead (again)
						if (stat.numZombiesAlive == 0) {
							state = State::LEVELING_UP;
						}
						splat.play();
					}
				}
			}
		}
	}
}

// Collision detection zombie/player
void hasPlayerBeenAttacked(t_stat& stat, Zombie* zombies, Player* player, State& state, Sound& hit, Time gameTimeTotal)
{
	for (int i = 0; i < stat.numZombies; i++)
	{
		if (player->getPosition().intersects
		(zombies[i].getPosition()) && zombies[i].isAlive())
		{
			if (player->hit(gameTimeTotal))
			{
				hit.play();
			}
			if (player->getHealth() <= 0)
			{
				state = State::GAME_OVER;
				std::ofstream outputFile("gamedata/scores.txt");
				// << writes the data
				outputFile << stat.hiScore;
				outputFile.close();

			}
		}
	}
}

// Has the player get pickup
void  hasPlayerGotPickup(Player* player, Pickup* healthPickup, Pickup* ammoPickup, t_sound sounds, t_stat& stat)
{
	if (player->getPosition().intersects(healthPickup->getPosition()) && healthPickup->isSpawned())
	{
		player->increaseHealthLevel(healthPickup->gotIt());
		sounds.pickup.play();
	}
	// Has the player touched ammo pickup
	if (player->getPosition().intersects(ammoPickup->getPosition()) && ammoPickup->isSpawned())
	{
		stat.bulletsSpare += ammoPickup->gotIt();
		sounds.reload.play();
	}
}

// Update game HUD text
void updateHUD(t_stat stat, t_texts& texts)
{
	std::stringstream ssAmmo;
	std::stringstream ssScore;
	std::stringstream ssHiScore;
	std::stringstream ssWave;
	std::stringstream ssZombiesAlive;
	// Update the ammo text
	ssAmmo << stat.bulletsInClip << "/" << stat.bulletsSpare;
	texts.ammo.setString(ssAmmo.str());
	// Update the score text
	ssScore << "Score:" << stat.score;
	texts.score.setString(ssScore.str());
	// Update the high score text
	ssHiScore << "Hi Score:" << stat.hiScore;
	texts.hiscore.setString(ssHiScore.str());
	// Update the wave
	ssWave << "Wave:" << stat.wave;
	texts.waveNumber.setString(ssWave.str());
	// Update the high score text
	ssZombiesAlive << "Zombies:" << stat.numZombiesAlive;
	texts.zombiesRemaining.setString(ssZombiesAlive.str());
	
}