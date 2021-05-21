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

	//Map Limit Colliders
	playerWall[0] = bottomCol = App->collisions->AddCollider({ 0, 3070, 768, 2 }, Collider::Type::WALL);
	playerWall[1] = App->collisions->AddCollider({ 0, 0, 2, 3072 }, Collider::Type::WALL);
	playerWall[2] = App->collisions->AddCollider({ 0, 0, 768, 2 }, Collider::Type::WALL);
	playerWall[3] = App->collisions->AddCollider({ 766, 0, 2, 3072 }, Collider::Type::WALL);

	//Bridge Colliders
	playerWall[4] = App->collisions->AddCollider({ 79, 366, 12, 276 }, Collider::Type::WALL);
	playerWall[5] = App->collisions->AddCollider({ 0, 407, 86, 84 }, Collider::Type::WALL);
	playerWall[6] = App->collisions->AddCollider({ 197, 365, 12, 259 }, Collider::Type::WALL);
	playerWall[7] = App->collisions->AddCollider({ 205, 407, 563, 57 }, Collider::Type::WALL);
	playerWall[8] = App->collisions->AddCollider({ 207, 520, 561, 55 }, Collider::Type::WALL);
	playerWall[9] = App->collisions->AddCollider({ 216, 568, 99, 17 }, Collider::Type::WALL);
	playerWall[10] = App->collisions->AddCollider({ 346, 567, 96, 19 }, Collider::Type::WALL);
	playerWall[11] = App->collisions->AddCollider({ 472, 564, 102, 20 }, Collider::Type::WALL);
	playerWall[12] = App->collisions->AddCollider({ 598, 566, 104, 20 }, Collider::Type::WALL);
	playerWall[13] = App->collisions->AddCollider({ 730, 568, 38, 18 }, Collider::Type::WALL);
	playerWall[14] = App->collisions->AddCollider({ 0, 526, 55, 50 }, Collider::Type::WALL);
	playerWall[15] = App->collisions->AddCollider({ 52, 528, 36, 48 }, Collider::Type::WALL);

	//Structure Colliders
	playerWall[16] = App->collisions->AddCollider({ 0, 608, 87, 30 }, Collider::Type::WALL);
	playerWall[17] = App->collisions->AddCollider({ 206, 592, 57, 31 }, Collider::Type::WALL);
	playerWall[18] = App->collisions->AddCollider({ 258, 606, 21, 31 }, Collider::Type::WALL);
	playerWall[19] = App->collisions->AddCollider({ 271, 620, 22, 29 }, Collider::Type::WALL);
	playerWall[20] = App->collisions->AddCollider({ 286, 634, 24, 33 }, Collider::Type::WALL);
	playerWall[21] = App->collisions->AddCollider({ 300, 647, 21, 35 }, Collider::Type::WALL);
	playerWall[22] = App->collisions->AddCollider({ 313, 658, 25, 36 }, Collider::Type::WALL);
	playerWall[23] = App->collisions->AddCollider({ 332, 672, 17, 37 }, Collider::Type::WALL);
	playerWall[24] = App->collisions->AddCollider({ 344, 688, 19, 31 }, Collider::Type::WALL);
	playerWall[25] = App->collisions->AddCollider({ 356, 692, 28, 27 }, Collider::Type::WALL);
	playerWall[26] = App->collisions->AddCollider({ 372, 640, 79, 101 }, Collider::Type::WALL);
	playerWall[27] = App->collisions->AddCollider({ 449, 709, 13, 36 }, Collider::Type::WALL);
	playerWall[28] = App->collisions->AddCollider({ 392, 741, 35, 27 }, Collider::Type::WALL);
	playerWall[29] = App->collisions->AddCollider({ 421, 740, 28, 6 }, Collider::Type::WALL);
	playerWall[30] = App->collisions->AddCollider({ 0, 784, 271, 52 }, Collider::Type::WALL);
	playerWall[31] = App->collisions->AddCollider({ 368, 819, 400, 17 }, Collider::Type::WALL);
	playerWall[32] = App->collisions->AddCollider({ 388, 806, 147, 17 }, Collider::Type::WALL);
	playerWall[33] = App->collisions->AddCollider({ 405, 797, 125, 13 }, Collider::Type::WALL);
	playerWall[34] = App->collisions->AddCollider({ 426, 786, 100, 12 }, Collider::Type::WALL);
	playerWall[35] = App->collisions->AddCollider({ 569, 783, 199, 23 }, Collider::Type::WALL);
	playerWall[36] = App->collisions->AddCollider({ 575, 828, 118, 86 }, Collider::Type::WALL);
	playerWall[37] = App->collisions->AddCollider({ 594, 909, 27, 19 }, Collider::Type::WALL);
	playerWall[38] = App->collisions->AddCollider({ 561, 805, 23, 18 }, Collider::Type::WALL);
	playerWall[39] = App->collisions->AddCollider({ 64, 977, 339, 51 }, Collider::Type::WALL);
	playerWall[40] = App->collisions->AddCollider({ 395, 983, 33, 45 }, Collider::Type::WALL);
	playerWall[41] = App->collisions->AddCollider({ 414, 986, 28, 42 }, Collider::Type::WALL);
	playerWall[42] = App->collisions->AddCollider({ 435, 992, 24, 36 }, Collider::Type::WALL);
	playerWall[43] = App->collisions->AddCollider({ 453, 1006, 27, 22 }, Collider::Type::WALL);
	playerWall[44] = App->collisions->AddCollider({ 64, 977, 8, 273 }, Collider::Type::WALL);
	playerWall[45] = App->collisions->AddCollider({ 68, 1153, 21, 51 }, Collider::Type::WALL);
	playerWall[46] = App->collisions->AddCollider({ 85, 1173, 16, 31 }, Collider::Type::WALL);
	playerWall[47] = App->collisions->AddCollider({ 98, 1194, 7, 9 }, Collider::Type::WALL);
	playerWall[48] = App->collisions->AddCollider({ 0, 1231, 112, 53 }, Collider::Type::WALL);
	playerWall[49] = App->collisions->AddCollider({ 106, 1237, 34, 47 }, Collider::Type::WALL);
	playerWall[50] = App->collisions->AddCollider({ 136, 1247, 29, 37 }, Collider::Type::WALL);
	playerWall[51] = App->collisions->AddCollider({ 157, 1252, 25, 32 }, Collider::Type::WALL);
	playerWall[52] = App->collisions->AddCollider({ 177, 1266, 16, 18 }, Collider::Type::WALL);
	playerWall[53] = App->collisions->AddCollider({ 96, 1042, 100, 108 }, Collider::Type::WALL);
	playerWall[54] = App->collisions->AddCollider({ 660, 1042, 108, 49 }, Collider::Type::WALL);
	playerWall[55] = App->collisions->AddCollider({ 628, 1045, 42, 46 }, Collider::Type::WALL);
	playerWall[56] = App->collisions->AddCollider({ 604, 1056, 30, 36 }, Collider::Type::WALL);
	playerWall[57] = App->collisions->AddCollider({ 593, 1063, 20, 29 }, Collider::Type::WALL);
	playerWall[58] = App->collisions->AddCollider({ 613, 1051, 13, 6 }, Collider::Type::WALL);
	playerWall[59] = App->collisions->AddCollider({ 576, 1068, 21, 24 }, Collider::Type::WALL);
	playerWall[60] = App->collisions->AddCollider({ 720, 1083, 8, 149 }, Collider::Type::WALL);
	playerWall[61] = App->collisions->AddCollider({ 412, 1201, 356, 51 }, Collider::Type::WALL);
	playerWall[62] = App->collisions->AddCollider({ 379, 1206, 38, 46 }, Collider::Type::WALL);
	playerWall[63] = App->collisions->AddCollider({ 356, 1215, 28, 37 }, Collider::Type::WALL);
	playerWall[64] = App->collisions->AddCollider({ 341, 1227, 20, 26 }, Collider::Type::WALL);

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