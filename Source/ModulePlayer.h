#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Application.h"
#include "Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "ModuleInput.h"

#define PLAYER_LIFE 16
#define PLAYER_LIFES_LEFT 3

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
	int level;

	//Margin of movement
	int horizontalMargin = 45;
	int verticalMargin = 205;
	
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

	void SetAnimation(Animation &toChange);

	// The player's collider
	Collider* hitBox = nullptr;

	Collider* colBoxUp = nullptr;
	Collider* colBoxUpLeft = nullptr;
	Collider* colBoxLeft = nullptr;
	Collider* colBoxDownLeft = nullptr;
	Collider* colBoxDown = nullptr;
	Collider* colBoxDownRight = nullptr;
	Collider* colBoxRight = nullptr;
	Collider* colBoxUpRight = nullptr;

	int collisionID;

	bool colUp = false;
	bool colUpLeft = false;
	bool colLeft = false;
	bool colDownLeft = false;
	bool colDown = false;
	bool colDownRight = false;
	bool colRight = false;
	bool colUpRight = false;

	bool colCheck[8] = { false };

	// A flag to detect when the player has been destroyed
	bool destroyed = false;
	int playerLife = PLAYER_LIFE;
	int playerWidth = 24;
	int playerHeight = 16;
	int playerHeightOffset = 30;
	int PlayerWidthOffset = 2;
	int playerLifesLeft = PLAYER_LIFES_LEFT;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint exitCountdown = 120;

	// Sound effects indices
	uint laserFx = 0;
	uint damageFx = 0;
	uint deathFx = 0;
	uint bombFx = 0;
	

	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	// Weapon
	int weaponType = 0; // 0 normal, 1 shotgun, 2 machinegun, 3 flamethrower, 4 grenade launcher

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