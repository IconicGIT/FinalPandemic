#include "ModuleLevel_2.h"

#include "Application.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Globals.h"
#include "ModuleInput.h"
#include "ModuleFonts.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_timer.h"


#define CAMERA_X_MARGIN 25
#define CAMERA_Y_MARGIN 50

#define MAP_WIDTH 767
#define MAP_HEIGHT 3071

ModuleLevel_2::ModuleLevel_2(bool startEnabled) : Module(startEnabled)
{

}

ModuleLevel_2::~ModuleLevel_2()
{

}

// Load assets
bool ModuleLevel_2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background_ingame2.png");

	startTime = SDL_GetTicks();
	counterMusic = 0;
	repetition = 1;


	

	//Bottomside collider
	bottomCol = App->collisions->AddCollider({ 0, 1488, 800, 70 }, Collider::Type::WALL);
	
	//App->audio->PlayMusic("Assets/Music/mission_2.ogg", 1.0f);

	// Enemies ---
	//App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 535, 1360);




	if (App->player->IsEnabled() == 0)
	{
		App->player->Enable();
		App->player->level = 1;
	}

	if (App->enemies->IsEnabled() == 0)
	{
		App->enemies->Enable();
	}

	if (App->collisions->IsEnabled() == 0)
	{
		App->collisions->Enable();
	}

	App->player->position.x = 400;
	App->player->position.y = 3000;

	App->render->camera.x = 303 * SCREEN_SIZE;
	App->render->camera.y = MAP_HEIGHT * SCREEN_SIZE - App->render->camera.h * SCREEN_SIZE;

	return ret;
}

UpdateResult ModuleLevel_2::Update()
{
	//App->render->camera.x += 3;


	//if (App->player->position.x < (App->render->camera.x + CAMERA_X_MARGIN)) {
	//
	//	App->render->camera.x -= 10; //App->player->speed;
	//	
	//
	//} else if ((App->player->position.x + App->player->collider->rect.w) > (App->render->camera.x + App->render->camera.w - CAMERA_X_MARGIN)) {
	//
	//	App->render->camera.x += 10; // App->player->speed * 3;
	//}

	currentTime = SDL_GetTicks();
	elapsedTime = (currentTime - startTime) / 1000.0;



	if (counterMusic < 1 * repetition)
	{
		if (elapsedTime > 92 * repetition)
		{
			//App->audio->PlayMusic("Assets/Music/Mission_1_repeat.ogg", 1.0f);
			counterMusic++;
			repetition++;
		}
	}


	//render camera aread
	bottomCol->SetPos(0, 1480 - (1534 - App->render->camera.y / SCREEN_SIZE) + 384 + 32);
	App->render->DrawQuad(App->render->camera, 0, 255, 255, 100);
	App->fonts->BlitText(0, 0, App->player->scoreFont, App->player->scoreText);
	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleLevel_2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	//SDL_Rect btree;
	//btree.x = 417;
	//btree.y = 294;
	//btree.w = 89;
	//btree.h = 160;
	//
	//
	//
	//SDL_Rect brock;
	//brock.x = 284;
	//brock.y = 7;
	//brock.w = 127;
	//brock.h = 213;
	//
	//App->render->Blit(tTexture, 768, 487, &brock);

	return UpdateResult::UPDATE_CONTINUE;
}