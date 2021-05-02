#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Application.h"
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"

#define PLAYER_LIFE 10

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	UpdateResult Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	UpdateResult PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	fPoint position;

	fPoint GetPlayerPosition() const {

		return position;
	}

	//Camera
	SDL_Rect camera;

	//Margin of movement
	int horizontalMargin = 45;
	int verticalMargin = 250;
	
	// The speed in which we move the player (pixels per frame)
	int speed = 2;
	int diagonalSpeed = 1;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations

	// Idle Animations
	Animation upIdleAnim;
	Animation upRightIdleAnim;
	Animation rightIdleAnim;
	Animation downRightIdleAnim;
	Animation downIdleAnim;
	Animation downLeftIdleAnim;
	Animation upLeftIdleAnim;
	Animation leftIdleAnim;
	
	// Move Animations
	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation downRightAnim;
	Animation upRightAnim;
	Animation downLeftAnim;
	Animation upLeftAnim;

	// Damage Animations
	Animation  hitFromUpAnim;
	Animation  hitFromLeftAnim;
	Animation  hitFromDownAnim;
	Animation  hitFromRightAnim;

	Animation  rollAnim; // Character fly

	// Death Animations
	Animation  deathFromLeftAnim;
	Animation  deathFromRightAnim;
	Animation  deathFromUpAnim;
	Animation  deathFromDownAnim;



	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	int playerLife = PLAYER_LIFE;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint exitCountdown = 120;

	// Sound effects indices
	uint laserFx = 0;
	uint explosionFx = 0;

	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	//player keys
	KEY_STATE keyUp;
	KEY_STATE keyLeft;
	KEY_STATE keyDown;
	KEY_STATE keyRight;

	KEY_STATE lastHorizontalKey;
	KEY_STATE lastVerticalKey;
	int lastDirection;
};

#endif //!__MODULE_PLAYER_H__