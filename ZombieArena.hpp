#pragma once
#include "Zombie.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "Pickup.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace sf;

// The game will always be in one of four states
enum class State
{
    PAUSED, LEVELING_UP,
    GAME_OVER, PLAYING
};

typedef struct s_sounds
{
    SoundBuffer hitBuffer;
    Sound hit;
    SoundBuffer splatBuffer;
    Sound splat;
    SoundBuffer shootBuffer;
    Sound shoot;
    SoundBuffer reloadBuffer;
    Sound reload;
    SoundBuffer reloadFailedBuffer;
    Sound reloadFailed;
    SoundBuffer powerupBuffer;
    Sound powerup;
    SoundBuffer pickupBuffer;
    Sound pickup;
} t_sound;

typedef struct s_texts
{
    Font font;
    Text paused;
    Text gameOver;
    Text levelUp;
    std::stringstream levelUpStream;
    Text ammo;
    Text score;
    Text hiscore;
    std::stringstream s;
    Text zombiesRemaining;
    Text waveNumber;
}t_texts;

typedef struct s_stat
{
    int hiScore = 0;
    int currentBullet = 0;
    int bulletsSpare = 24;
    int bulletsInClip = 6;
    int clipSize = 6;
    int fireRate = 1;
    int wave = 0;
    int score = 0;
    int numZombies = 0;
    int numZombiesAlive = 0;
    int framesSinceLastHUDUpdate = 0;
    const int fpsMeasurementFrameInterval = 1000;
}t_stat;

typedef struct s_sprite
{
    Sprite crosshair;
    Sprite gameOver;
    Sprite ammoIcon;
    RectangleShape healthBar;

} t_sprite;

typedef struct s_texture
{
    Texture background;
    Texture crosshair;
    Texture gameOver;
    Texture ammoIcon;
} t_texture;

typedef struct s_time
{
    Time gameTimeTotal;
    Time lastPressed;
}t_time;

int createBackground(VertexArray& rVA, IntRect arena);
void load_audio_files(t_sound& sounds);
void load_text_files(t_texts& texts, int hiScore);
void loadHUDTexure(t_texture& texture, t_sprite& sprite);
int	get_hiscore();
Zombie* createHorde(int numZombies, IntRect arena);
void handleEvents(Event& event, State& state, Clock& clock, Player* player, t_sound& sounds, t_stat& stat);
void handleMove(Player* player, t_stat& stat, t_sound& sounds, Bullet bullets[], t_time& time, Vector2f mouseWorldPosition);
bool handleLevelUp(Event event, t_stat& stat, Player* player, State& state, Pickup* healthPickup, Pickup* ammoPickup);
void setNewLevel(State state, t_stat& stat, IntRect& arena, Player* player, VertexArray& background,
    Vector2f resolution, Pickup& healthPickup, Pickup& ammoPickup, Sound powerup);
void hasZombieBeenShot(t_stat& stat, Zombie* zombies, Bullet bullets[], State& state, Sound splat);
void hasPlayerBeenAttacked(t_stat& stat, Zombie* zombies, Player* player, State& state, Sound& hit, Time gameTimeTotal);
void hasPlayerGotPickup(Player* player, Pickup* healthPickup, Pickup* ammoPickup, t_sound sounds, t_stat& stat);
void updateHUD(t_stat stat, t_texts& texts);
void drawGameover(RenderWindow& window, Sprite& gameOver, t_texts& texts);
void drawLevelUp(RenderWindow& window, Sprite& gameOver, Text& levelUp);