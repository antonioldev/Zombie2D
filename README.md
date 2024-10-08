## Zombie Arena
In the Zombie Arena project, I built a survival shooter game where the player must fend off waves of zombies from a top-down perspective. The game features power-ups, weapon upgrades, and increasingly challenging enemy waves.
Zombie Arena was by far the most complex project, and it's where I really started applying everything I had learned. This game is a top-down shooter where the player fights off waves of zombies. I used the new keyword to create dynamic objects, and I refactored the code into different functions to make the project more modular and readable.

Key takeaways from the Zombie Arena project:

- $${\color{green}\textbf{Dynamic Object Management}}$$: Using the new keyword allowed me to dynamically allocate memory for game objects like zombies, bullets, and pickups. This was my first experience with memory management in C++, which is crucial for handling multiple objects in real time.
- $${\color{green}\textbf{Refactoring and Modularity}}$$: I took extra steps to break the main function into smaller, more manageable functions. This improved the readability and maintainability of the code, which is a vital skill as games grow in complexity.
- $${\color{green}\textbf{Advanced SFML Features}}$$: I learned how to use more complex SFML functionalities, like rendering multiple layers (backgrounds, characters, bullets, etc.) and managing sprite animations for the zombies.
- $${\color{green}\textbf{Object-Oriented Programming}}$$: I deepened my understanding of OOP by creating classes for different game objects, each with its own behavior and characteristics, making the code cleaner and easier to debug.
- $${\color{green}\textbf{AI for Enemy Behavior}}$$: I learned to create AI for enemy behavior, including pathfinding and attack patterns for the zombies.
- $${\color{green}\textbf{Managing Multiple Game Objects}}$$: I managed multiple game objects efficiently, such as the player, zombies, bullets, and power-ups.
- $${\color{green}\textbf{Scoring System}}$$: I implemented a scoring system to track the player's progress and provide feedback on their performance.
- $${\color{green}\textbf{Advanced Collision Detection}}$$: I tackled more complex collision detection and response, ensuring accurate interactions between the player, zombies, and bullets.
- $${\color{green}\textbf{Game Optimization}}$$: I applied game optimization techniques to ensure smooth gameplay, even with many active game objects.
Zombie Arena was an important project because it mimicked the structure of larger games. Managing multiple objects, handling user inputs in a more sophisticated way, and refining the game architecture were invaluable lessons.

## Game Scenes
![Zombie Screenshot](https://github.com/antonioldev/Zombie2D/blob/master/Screenshot1.png)
![Zombie Screenshot](https://github.com/antonioldev/Zombie2D/blob/master/Screenshot2.png)

## SFML Library
Throughout these projects, I used the SFML (Simple and Fast Multimedia Library).W
hich is a cross-platform library designed to provide a simple interface to various multimedia components in C++.
SFML is particularly useful for game development due to its simplicity and ease of use.

**Key Features**:
- $${\color{green}\textbf{Graphics}}$$: Rendering shapes, sprites, and text. SFML makes it easy to draw 2D graphics and handle basic animations.
- $${\color{green}\textbf{Windowing}}$$: Creating and managing game windows. SFML provides a straightforward way to create windows and handle events such as resizing and closing.
- $${\color{green}\textbf{Audio}}$$: Playing sound effects and music. SFML supports various audio formats and allows for easy playback and control of sounds.
- $${\color{green}\textbf{Input}}$$: Handling keyboard, mouse, and joystick input. SFML simplifies the process of capturing and responding to user inputs.
