#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "FrontPage.h"
#include "FirstScene.h"
#include "SecondScene.h"
#include "ThirdScene.h"
#include "FifthScene.h"
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModulePowerUps.h"
#include "ModuleObstacle.h"


#include "SDL/include/SDL.h"
#include "Globals.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = fonts = new ModuleFonts(true);
	modules[4] = audio = new ModuleAudio(true);

	modules[5] = frontPage = new FrontPage(true);
	modules[6] = firstScene = new FirstScene(false);
	modules[7] = secondScene = new SecondScene(false);
	modules[8] = thirdScene = new ThirdScene(false);
	modules[9] = fifthScene = new FifthScene(false);
	modules[10] = scene = new ModuleLevel_1(false);
	modules[11] = scene_2 = new ModuleLevel_2(false);							//Gameplay scene starts disabled
	modules[12] = player = new ModulePlayer(false);								//Player starts disabled
	modules[13] = enemies = new ModuleEnemies(false);							//Enemies start disabled
	modules[14] = powerUps = new ModulePowerUps(true);
	modules[15] = particles = new ModuleParticles(true);
	modules[16] = obstacles = new ModuleObstacle(true);

	modules[17] = collisions = new ModuleCollisions(true);
	modules[18] = fade = new ModuleFadeToBlack(true);
	
	modules[19] = render = new ModuleRender(true);
	
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		// WARNING: When deleting a pointer, set it to nullptr afterwards
		// It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

UpdateResult Application::Update()
{
	init = SDL_GetTicks();

	UpdateResult ret = UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UpdateResult::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UpdateResult::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UpdateResult::UPDATE_CONTINUE;

	end = SDL_GetTicks();

	long elapsedTime = (float)(end - init);
	(float)SDL_GetPerformanceFrequency();

	//LOG("Current FPS: %f", (1000.0f / elapsedTime)); 
	SDL_Delay(fabs(floor((long)16.666f - elapsedTime)));

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
