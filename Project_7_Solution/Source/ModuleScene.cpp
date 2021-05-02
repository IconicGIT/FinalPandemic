#include "ModuleScene.h"

#include "Application.h"
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


#define CAMERA_X_MARGIN 25
#define CAMERA_Y_MARGIN 50

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/background.png");
	//App->audio->PlayMusic("Assets/stage_1.ogg", 1.0f);

	//Bottomside collider
	App->collisions->AddCollider({ 475, 1534, 608, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 475, -15, 768, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1083, 398, 160, 15 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 460, 0, 15, 1534 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1083, 398, 15, 1136 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1243, 0, 15, 398 }, Collider::Type::WALL);

	//First two columns colliders


	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 535, 1360);
	

	
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);


	App->render->camera.x = 475 * SCREEN_SIZE;
	App->render->camera.y = 1156 * SCREEN_SIZE;

	if (App->player->IsEnabled() == 0)
	{
		App->player->Enable();
	}

	if (App->enemies->IsEnabled() == 0)
	{
		App->enemies->Enable();
	}

	if (App->collisions->IsEnabled() == 0)
	{
		App->collisions->Enable();
	}

	return ret;
}

UpdateResult ModuleScene::Update()
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

	//render camera area
	App->render->DrawQuad(App->render->camera, 0, 255, 255, 100);
	App->fonts->BlitText(0, 0, App->player->scoreFont, App->player->scoreText);
	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->collisions->DebugDraw();

	return UpdateResult::UPDATE_CONTINUE;
}