#include "ModuleLevel_1.h"

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
#include "ModuleFadeToBlack.h"

//temporal
#include "SDL_mixer/include/SDL_mixer.h"


#define CAMERA_X_MARGIN 25
#define CAMERA_Y_MARGIN 50


ModuleLevel_1::ModuleLevel_1(bool startEnabled) : Module(startEnabled)
{

}

ModuleLevel_1::~ModuleLevel_1()
{
	

}

// Load assets
bool ModuleLevel_1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background_ingame.png");

	//App->audio->PlayMusic("Assets/stage_1.ogg", 1.0f);

	tTexture = App->textures->Load("Assets/Sprites/moving_and_chaging_tiles.png");

	////
	startTime = SDL_GetTicks();
	counterMusic = 0;
	repetition = 1;

	//Map colliders
	playerWall[0] = App->collisions->AddCollider({ 475, 1534, 608, 15 }, Collider::Type::WALL);
	playerWall[1] = App->collisions->AddCollider({ 475, -15, 768, 15 }, Collider::Type::WALL);
	playerWall[2] = App->collisions->AddCollider({ 1083, 398, 160, 15 }, Collider::Type::WALL);
	playerWall[4] = App->collisions->AddCollider({ 460, 0, 15, 1534 }, Collider::Type::WALL);
	playerWall[5] = App->collisions->AddCollider({ 1083, 398, 15, 1136 }, Collider::Type::WALL);
	playerWall[6] = App->collisions->AddCollider({ 1243, 0, 15, 398 }, Collider::Type::WALL);
	playerWall[7] = App->collisions->AddCollider({ 1003, 164, 282, 42 }, Collider::Type::WALL);
	playerWall[8] = App->collisions->AddCollider({ 877, 197, 145, 42 }, Collider::Type::WALL);
	playerWall[9] = App->collisions->AddCollider({ 755, 181, 125, 44 }, Collider::Type::WALL);
	playerWall[10] = App->collisions->AddCollider({ 734, 217, 39, 46 }, Collider::Type::WALL);
	playerWall[11] = App->collisions->AddCollider({ 705, 232, 31, 36 }, Collider::Type::WALL);
	playerWall[12] = App->collisions->AddCollider({ 668, 240, 37, 39 }, Collider::Type::WALL);
	playerWall[13] = App->collisions->AddCollider({ 650, 261, 36, 34 }, Collider::Type::WALL);
	playerWall[14] = App->collisions->AddCollider({ 630, 266, 33, 39 }, Collider::Type::WALL);
	playerWall[15] = App->collisions->AddCollider({ 612, 273, 29, 43 }, Collider::Type::WALL);
	playerWall[16] = App->collisions->AddCollider({ 586, 284, 35, 47 }, Collider::Type::WALL);
	playerWall[17] = App->collisions->AddCollider({ 553, 293, 40, 53 }, Collider::Type::WALL);
	playerWall[18] = App->collisions->AddCollider({ 529, 345, 46, 73 }, Collider::Type::WALL);
	playerWall[19] = App->collisions->AddCollider({ 511, 415, 42, 39 }, Collider::Type::WALL);
	playerWall[20] = App->collisions->AddCollider({ 483, 437, 35, 37 }, Collider::Type::WALL);
	playerWall[21] = App->collisions->AddCollider({ 467, 468, 38, 147 }, Collider::Type::WALL);
	playerWall[22] = App->collisions->AddCollider({ 529, 590, 66, 50 }, Collider::Type::WALL);
	playerWall[23] = App->collisions->AddCollider({ 505, 609, 41, 90 }, Collider::Type::WALL);
	playerWall[24] = App->collisions->AddCollider({ 522, 696, 45, 93 }, Collider::Type::WALL);
	playerWall[25] = App->collisions->AddCollider({ 509, 787, 30, 102 }, Collider::Type::WALL);
	playerWall[26] = App->collisions->AddCollider({ 528, 878, 45, 32 }, Collider::Type::WALL);
	playerWall[27] = App->collisions->AddCollider({ 556, 904, 42, 23 }, Collider::Type::WALL);
	playerWall[28] = App->collisions->AddCollider({ 599, 922, 54, 41 }, Collider::Type::WALL);
	playerWall[29] = App->collisions->AddCollider({ 653, 944, 48, 32 }, Collider::Type::WALL);
	playerWall[30] = App->collisions->AddCollider({ 684, 962, 43, 40 }, Collider::Type::WALL);
	playerWall[31] = App->collisions->AddCollider({ 695, 986, 99, 53 }, Collider::Type::WALL);
	playerWall[32] = App->collisions->AddCollider({ 793, 1011, 40, 74 }, Collider::Type::WALL);
	playerWall[33] = App->collisions->AddCollider({ 706, 1078, 86, 51 }, Collider::Type::WALL);
	playerWall[34] = App->collisions->AddCollider({ 675, 1110, 40, 34 }, Collider::Type::WALL);
	playerWall[35] = App->collisions->AddCollider({ 475, 1177, 68, 73 }, Collider::Type::WALL);
	playerWall[36] = App->collisions->AddCollider({ 536, 1171, 66, 57 }, Collider::Type::WALL);
	playerWall[37] = App->collisions->AddCollider({ 586, 1166, 58, 49 }, Collider::Type::WALL);
	playerWall[38] = App->collisions->AddCollider({ 628, 1136, 57, 60 }, Collider::Type::WALL);
	playerWall[39] = bottomCol = App->collisions->AddCollider({ 479, 1488, 800, 70 }, Collider::Type::WALL);
	playerWall[40] = App->collisions->AddCollider({ 867, 1278, 73, 219 }, Collider::Type::WALL);
	playerWall[41] = App->collisions->AddCollider({ 819, 1254, 62, 31 }, Collider::Type::WALL);
	playerWall[42] = App->collisions->AddCollider({ 773, 1239, 55, 21 }, Collider::Type::WALL);
	playerWall[43] = App->collisions->AddCollider({ 751, 1223, 73, 16 }, Collider::Type::WALL);
	playerWall[44] = App->collisions->AddCollider({ 791, 1175, 34, 47 }, Collider::Type::WALL);
	playerWall[45] = App->collisions->AddCollider({ 830, 1143, 52, 34 }, Collider::Type::WALL);
	playerWall[46] = App->collisions->AddCollider({ 881, 1133, 85, 39 }, Collider::Type::WALL);
	playerWall[47] = App->collisions->AddCollider({ 921, 1109, 60, 39 }, Collider::Type::WALL);
	playerWall[48] = App->collisions->AddCollider({ 962, 1082, 75, 38 }, Collider::Type::WALL);
	playerWall[49] = App->collisions->AddCollider({ 1033, 973, 54, 129 }, Collider::Type::WALL);
	playerWall[50] = App->collisions->AddCollider({ 1005, 922, 72, 50 }, Collider::Type::WALL);
	playerWall[51] = App->collisions->AddCollider({ 948, 904, 65, 45 }, Collider::Type::WALL);
	playerWall[52] = App->collisions->AddCollider({ 912, 849, 48, 67 }, Collider::Type::WALL);
	playerWall[53] = App->collisions->AddCollider({ 873, 812, 63, 37 }, Collider::Type::WALL);
	playerWall[54] = App->collisions->AddCollider({ 773, 786, 102, 37 }, Collider::Type::WALL);
	playerWall[55] = App->collisions->AddCollider({ 725, 760, 50, 31 }, Collider::Type::WALL);
	playerWall[56] = App->collisions->AddCollider({ 701, 714, 38, 46 }, Collider::Type::WALL);
	playerWall[57] = App->collisions->AddCollider({ 705, 647, 49, 70 }, Collider::Type::WALL);
	playerWall[58] = App->collisions->AddCollider({ 747, 630, 50, 50 }, Collider::Type::WALL);
	playerWall[59] = App->collisions->AddCollider({ 797, 666, 40, 36 }, Collider::Type::WALL);
	playerWall[60] = App->collisions->AddCollider({ 832, 603, 28, 67 }, Collider::Type::WALL);
	playerWall[61] = App->collisions->AddCollider({ 838, 532, 23, 72 }, Collider::Type::WALL);
	playerWall[62] = App->collisions->AddCollider({ 807, 489, 47, 41 }, Collider::Type::WALL);
	playerWall[63] = App->collisions->AddCollider({ 777, 465, 40, 45 }, Collider::Type::WALL);
	playerWall[64] = App->collisions->AddCollider({ 756, 407, 33, 56 }, Collider::Type::WALL);
	playerWall[65] = App->collisions->AddCollider({ 715, 358, 56, 48 }, Collider::Type::WALL);
	playerWall[66] = App->collisions->AddCollider({ 727, 343, 22, 15 }, Collider::Type::WALL);
	playerWall[67] = App->collisions->AddCollider({ 744, 320, 83, 37 }, Collider::Type::WALL);
	playerWall[68] = App->collisions->AddCollider({ 801, 295, 70, 26 }, Collider::Type::WALL);
	playerWall[69] = App->collisions->AddCollider({ 851, 265, 166, 32 }, Collider::Type::WALL);
	playerWall[70] = App->collisions->AddCollider({ 1000, 285, 71, 45 }, Collider::Type::WALL);
	playerWall[71] = App->collisions->AddCollider({1055, 328, 202, 82 }, Collider::Type::WALL);
	playerWall[72] = App->collisions->AddCollider({ 1242, 208, 16, 128 }, Collider::Type::WALL);
	playerWall[73] = App->collisions->AddCollider({ 691, 574, 102, 32 }, Collider::Type::WALL);
	playerWall[74] = App->collisions->AddCollider({ 563, 526, 102, 32 }, Collider::Type::WALL);
	playerWall[75] = App->collisions->AddCollider({ 611, 446, 102, 32 }, Collider::Type::WALL);

	//App->audio->PlayMusic("Assets/Music/mission_1.ogg", 0.0f);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 535, 1360);
	Mix_FadeOutMusic((int)(1000.0f));


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

UpdateResult ModuleLevel_1::Update()
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
		if (!afterStart)
		{
			if (elapsedTime > 85.85f * repetition)
			{
				//App->audio->PlayMusic("Assets/Music/Mission_1_repeat.ogg", 0.0f);
				counterMusic++;
				repetition++;
				afterStart = true;
			}
		}
		else
		{
			if (elapsedTime > 38.0f * repetition)
			{
				//App->audio->PlayMusic("Assets/Music/mission_1_repeat.ogg", 0.0f);
				counterMusic++;
				repetition++;
			}
		}
		
	}

	//render camera aread
	bottomCol->SetPos(479, 1480 - (1534 - App->render->camera.y / SCREEN_SIZE) + 384 + 32);
	App->render->DrawQuad(App->render->camera, 0, 255, 255, 100);
	App->fonts->BlitText(0, 0, App->player->scoreFont, App->player->scoreText);

	if (App->input->keys[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->fifthScene, 90);
		App->player->level = 1;

		for (int i = 0; i < 100; i++) {
			if (playerWall[i] != nullptr) {
				playerWall[i]->pendingToDelete = true;
			}
		}
		
	}
	return UpdateResult::UPDATE_CONTINUE;
}

// Update: draw background
UpdateResult ModuleLevel_1::PostUpdate()
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

	return UpdateResult::UPDATE_CONTINUE;
}
