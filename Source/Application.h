#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class FrontPage;
class FirstScene;
class SecondScene;
class ThirdScene;
class FifthScene;
class ModuleLevel_1;
class ModuleLevel_2;
class ModuleParticles;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleEnemies;
class ModuleRender;
class ModuleFonts;
class ModulePowerUps;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	UpdateResult Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	FrontPage* frontPage = nullptr;
	FirstScene* firstScene = nullptr;
	SecondScene* secondScene = nullptr;
	ThirdScene* thirdScene = nullptr;
	FifthScene* fifthScene = nullptr;
	ModuleLevel_1* scene = nullptr;
	ModuleLevel_2* scene_2 = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;
	ModulePowerUps* powerUps = nullptr;

	ModuleFadeToBlack* fade = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;

	float limitFrames = 20;
	float init;
	float end;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__