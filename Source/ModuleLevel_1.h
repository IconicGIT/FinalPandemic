#ifndef __MODULE_LEVEL_1_H__
#define __MODULE_LEVEL_1_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;

class ModuleLevel_1 : public Module
{
public:
	//Constructor
	ModuleLevel_1(bool startEnabled);

	//Destructor
	~ModuleLevel_1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* bg2Texture = nullptr;
	SDL_Texture* tTexture = nullptr;

	Collider* bottomCol;
	Collider* playerWall[100] = { nullptr };
	Collider* bulletWall[100] = { nullptr };

	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;

	uint32_t startTime;

	uint32_t currentTime;
	int counterMusic;
	int repetition;
	bool afterStart = false;

	int levelTimerReference = 300 * 60;
	int levelTimer = levelTimerReference;

	//rock animation
	SDL_Rect brock;
	Collider* rockTrigger;
	bool rockAnimActivate;
	fPoint rockPos;
	int dustTimerReference = 3;
	int dustTimer = dustTimerReference;

	double elapsedTime; // Convert to seconds.

	int RandomRange(int value01, int values02);
};

#endif