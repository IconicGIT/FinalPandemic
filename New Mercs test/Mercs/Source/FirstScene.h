#ifndef __FIRSTSCENE_H__
#define __FIRSTSCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class FirstScene : public Module
{
public:
	// Constructor
	FirstScene(bool startEnabled);

	// Destructor
	~FirstScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	bool CleanUp() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	UpdateResult Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	UpdateResult PostUpdate() override;

	int counter = 1;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* hTexture = nullptr;
	SDL_Texture* text1 = nullptr;
	SDL_Texture* text2 = nullptr;
	SDL_Texture* text3 = nullptr;
	SDL_Texture* text4 = nullptr;
	SDL_Texture* text5 = nullptr;

	SDL_Rect textBlack;


	float blackAlpha;
	float blackMultiplier;
	float angle;
	bool fade;
	
	int timerReference;
	int timer;
};

#endif	// __FIRSTSCENE_H__