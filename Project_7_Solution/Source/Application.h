#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 14

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class FirstScene;
class SceneIntro;
class ModuleScene;
class ModuleParticles;
class ModuleCollisions;
class ModuleFadeToBlack;
class ModuleEnemies;
class ModuleRender;
class ModuleFonts;

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

	FirstScene* firstScene = nullptr;
	SceneIntro* sceneIntro = nullptr;
	ModuleScene* scene = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleFadeToBlack* fade = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__