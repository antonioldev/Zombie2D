#include "ZombieArena.hpp"
//#include "Player.hpp"
//#include "TextureHolder.hpp"
//#include "Bullet.hpp"
//#include "Pickup.hpp"

//Load audio files
void load_audio_files(t_sound& sounds)
{
	sounds.hitBuffer.loadFromFile("sound/hit.wav");
	sounds.hit.setBuffer(sounds.hitBuffer);
	sounds.splatBuffer.loadFromFile("sound/splat.wav");
	sounds.splat.setBuffer(sounds.splatBuffer);
	sounds.shootBuffer.loadFromFile("sound/shoot.wav");
	sounds.shoot.setBuffer(sounds.shootBuffer);
	sounds.reloadBuffer.loadFromFile("sound/reload.wav");
	sounds.reload.setBuffer(sounds.reloadBuffer);
	sounds.reloadFailedBuffer.loadFromFile("sound/reload_failed.wav");
	sounds.reloadFailed.setBuffer(sounds.reloadFailedBuffer);
	sounds.powerupBuffer.loadFromFile("sound/powerup.wav");
	sounds.powerup.setBuffer(sounds.powerupBuffer);
	sounds.pickupBuffer.loadFromFile("sound/pickup.wav");
	sounds.pickup.setBuffer(sounds.pickupBuffer);
}

//Load text for HUD files
void load_text_files(t_texts& texts, int hiScore)
{
	// Load the font
	texts.font.loadFromFile("fonts/zombiecontrol.ttf");
	// Paused
	texts.paused.setFont(texts.font);
	texts.paused.setCharacterSize(155);
	texts.paused.setFillColor(Color::White);
	texts.paused.setPosition(400, 400);
	texts.paused.setString("Press Enter \nto continue");
	// Game Over
	texts.gameOver.setFont(texts.font);
	texts.gameOver.setCharacterSize(125);
	texts.gameOver.setFillColor(Color::White);
	texts.gameOver.setPosition(250, 850);
	texts.gameOver.setString("Press Enter to play");
	// LEVELING up
	texts.levelUp.setFont(texts.font);
	texts.levelUp.setCharacterSize(80);
	texts.levelUp.setFillColor(Color::White);
	texts.levelUp.setPosition(150, 250);
	texts.levelUpStream <<
		"1- Increased rate of fire" <<
		"\n2- Increased clip size(next reload)" <<
		"\n3- Increased max health" <<
		"\n4- Increased run speed" <<
		"\n5- More and better health pickups" <<
		"\n6- More and better ammo pickups";
	texts.levelUp.setString(texts.levelUpStream.str());
	// Ammo
	texts.ammo.setFont(texts.font);
	texts.ammo.setCharacterSize(55);
	texts.ammo.setFillColor(Color::White);
	texts.ammo.setPosition(200, 980);
	// Score
	texts.score.setFont(texts.font);
	texts.score.setCharacterSize(55);
	texts.score.setFillColor(Color::White);
	texts.score.setPosition(20, 0);
	// Hi Score
	texts.hiscore.setFont(texts.font);
	texts.hiscore.setCharacterSize(55);
	texts.hiscore.setFillColor(Color::White);
	texts.hiscore.setPosition(1400, 0);
	texts.s << "Hi Score:" << hiScore;
	texts.hiscore.setString(texts.s.str());
	// Zombies remaining
	texts.zombiesRemaining.setFont(texts.font);
	texts.zombiesRemaining.setCharacterSize(55);
	texts.zombiesRemaining.setFillColor(Color::White);
	texts.zombiesRemaining.setPosition(1500, 980);
	texts.zombiesRemaining.setString("Zombies: 100");
	// Wave number
	texts.waveNumber.setFont(texts.font);
	texts.waveNumber.setCharacterSize(55);
	texts.waveNumber.setFillColor(Color::White);
	texts.waveNumber.setPosition(1250, 980);
	texts.waveNumber.setString("Wave: 0");
}

// Load the high score from a text file
int	get_hiscore()
{
	int hiScore = 0;
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		// >> Reads the data
		inputFile >> hiScore;
		inputFile.close();
	}
	return hiScore;
}

void loadHUDTexure(t_texture& texture, t_sprite& sprite)
{
	texture.background = TextureHolder::GetTexture("graphics/background_sheet.png");
	texture.crosshair = TextureHolder::GetTexture("graphics/crosshair.png");
	texture.gameOver = TextureHolder::GetTexture("graphics/background.png");
	texture.ammoIcon = TextureHolder::GetTexture("graphics/ammo_icon.png");

	sprite.crosshair.setTexture(texture.crosshair);
	sprite.crosshair.setOrigin(25, 25);
	sprite.gameOver.setTexture(texture.gameOver);
	sprite.gameOver.setPosition(0, 0);
	sprite.ammoIcon.setTexture(texture.ammoIcon);
	sprite.ammoIcon.setPosition(20, 980);
	sprite.healthBar.setFillColor(Color::Red);
	sprite.healthBar.setPosition(450, 980);
}