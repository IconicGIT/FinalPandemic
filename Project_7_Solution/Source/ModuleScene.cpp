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

	bgTexture = App->textures->Load("Assets/Sprites/background_ingame.png");
	//App->audio->PlayMusic("Assets/stage_1.ogg", 1.0f);

	tTexture = App->textures->Load("Assets/Sprites/moving_and_chaging_tiles.png");

	//Bottomside collider
	App->collisions->AddCollider({ 475, 1534, 608, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 475, -15, 768, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1083, 398, 160, 15 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 460, 0, 15, 1534 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1083, 398, 15, 1136 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1243, 0, 15, 398 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 1003, 164, 282, 42 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 877, 197, 145, 42 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 755, 181, 125, 44 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 734, 217, 39, 46 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 705, 232, 31, 36 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 674, 215, 37, 39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 650, 261, 36, 34 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 630, 266, 33, 39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 612, 273, 29, 43 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 586, 284, 35, 47 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 553, 293, 40, 53 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 529, 345, 46, 73 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 511, 415, 42, 39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 483, 437, 35, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 467, 468, 38, 147 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 529, 590, 66, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 505, 609, 41, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 522, 696, 45, 93 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 509, 787, 30, 102 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 528, 878, 45, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 556, 904, 42, 23 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 599, 922, 54, 41 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 653, 944, 48, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 684, 962, 43, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 695, 986, 99, 53 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 793, 1011, 40, 74 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 706, 1078, 86, 51 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 675, 1110, 40, 34 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 585, 1132, 102, 33 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 525, 1166, 86, 25 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 484, 1193, 56, 24 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 462, 1215, 36, 276 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 479, 1478, 399, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 867, 1278, 73, 219 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 819, 1254, 62, 31 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 773, 1239, 55, 21 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 751, 1223, 73, 16 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 791, 1175, 34, 47 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 830, 1143, 52, 34 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 881, 1133, 85, 39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 921, 1109, 60, 39 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 962, 1082, 75, 38 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1033, 973, 54, 129 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1005, 922, 72, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 948, 904, 65, 45 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 912, 849, 48, 67 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 873, 812, 63, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 773, 786, 102, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 725, 760, 50, 31 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 701, 714, 38, 46 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 705, 647, 49, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 747, 630, 50, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 797, 666, 40, 36 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 832, 603, 28, 67 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 838, 532, 23, 72 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 807, 489, 47, 41 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 777, 465, 40, 45 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 756, 407, 33, 56 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 715, 358, 56, 48 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 727, 343, 22, 15 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 744, 320, 83, 37 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 801, 295, 70, 26 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 851, 265, 166, 32 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 1000, 285, 71, 45 }, Collider::Type::WALL);
	App->collisions->AddCollider({1055, 328, 202, 82 }, Collider::Type::WALL);

	App->audio->PlayMusic("Assets/Music/Mission1.ogg", 1.0f);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 535, 1360);
	

	
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 600, 80);


	App->render->camera.x = 475 * SCREEN_SIZE;
	App->render->camera.y = 1149 * SCREEN_SIZE;

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

	SDL_Rect btree;
	btree.x = 417;
	btree.y = 294;
	btree.w = 89;
	btree.h = 160;

	App->render->Blit(tTexture, 813, 910, &btree);
	App->render->Blit(tTexture, 877, 926, &btree);
	App->render->Blit(tTexture, 845, 958, &btree);
	App->render->Blit(tTexture, 813, 974, &btree);
	App->render->Blit(tTexture, 781, 974, &btree);

	SDL_Rect brock;
	brock.x = 284;
	brock.y = 7;
	brock.w = 127;
	brock.h = 213;

	App->render->Blit(tTexture, 768, 487, &brock);

	App->collisions->DebugDraw();

	return UpdateResult::UPDATE_CONTINUE;
}