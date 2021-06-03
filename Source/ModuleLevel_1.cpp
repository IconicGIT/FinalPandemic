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
#include "ModulePowerUps.h"

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
	srand(2);
	int randValue = rand() % 2;

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



	bulletWall[0 ] = App->collisions->AddCollider({ 471, 1182, 63, 23 }, Collider::Type::BULLET_WALL);
	bulletWall[1 ] = App->collisions->AddCollider({ 520, 1167, 80, 26 }, Collider::Type::BULLET_WALL);
	bulletWall[2 ] = App->collisions->AddCollider({ 586, 1146, 70, 27 }, Collider::Type::BULLET_WALL);
	bulletWall[3 ] = App->collisions->AddCollider({ 642, 1126, 65, 24 }, Collider::Type::BULLET_WALL);
	bulletWall[4 ] = App->collisions->AddCollider({ 697, 1103, 74, 29 }, Collider::Type::BULLET_WALL);
	bulletWall[5 ] = App->collisions->AddCollider({ 759, 1054, 39, 58 }, Collider::Type::BULLET_WALL);
	bulletWall[6 ] = App->collisions->AddCollider({ 772, 1217, 44, 15 }, Collider::Type::BULLET_WALL);
	bulletWall[7 ] = App->collisions->AddCollider({ 794, 1185, 23, 47 }, Collider::Type::BULLET_WALL);
	bulletWall[8 ] = App->collisions->AddCollider({ 811, 1214, 46, 18 }, Collider::Type::BULLET_WALL);
	bulletWall[9 ] = App->collisions->AddCollider({ 841, 1218, 48, 23 }, Collider::Type::BULLET_WALL);
	bulletWall[10] = App->collisions->AddCollider({ 870, 1223, 44, 28 }, Collider::Type::BULLET_WALL);
	bulletWall[11] = App->collisions->AddCollider({ 885, 1238, 25, 28 }, Collider::Type::BULLET_WALL);
	bulletWall[12] = App->collisions->AddCollider({ 818, 1168, 49, 19 }, Collider::Type::BULLET_WALL);
	bulletWall[13] = App->collisions->AddCollider({ 840, 1149, 61, 20 }, Collider::Type::BULLET_WALL);
	bulletWall[14] = App->collisions->AddCollider({ 877, 1138, 45, 18 }, Collider::Type::BULLET_WALL);
	bulletWall[15] = App->collisions->AddCollider({ 915, 1100, 63, 48 }, Collider::Type::BULLET_WALL);
	bulletWall[16] = App->collisions->AddCollider({ 963, 1076, 63, 31 }, Collider::Type::BULLET_WALL);
	bulletWall[17] = App->collisions->AddCollider({ 1024, 1058, 53, 29 }, Collider::Type::BULLET_WALL);
	bulletWall[18] = App->collisions->AddCollider({ 1054, 1035, 28, 27 }, Collider::Type::BULLET_WALL);
	bulletWall[19] = App->collisions->AddCollider({ 1040, 971, 34, 64 }, Collider::Type::BULLET_WALL);
	bulletWall[20] = App->collisions->AddCollider({ 1016, 941, 41, 29 }, Collider::Type::BULLET_WALL);
	bulletWall[21] = App->collisions->AddCollider({ 980, 923, 46, 25 }, Collider::Type::BULLET_WALL);
	bulletWall[22] = App->collisions->AddCollider({ 973, 900, 20, 44 }, Collider::Type::BULLET_WALL);
	bulletWall[23] = App->collisions->AddCollider({ 961, 889, 18, 45 }, Collider::Type::BULLET_WALL);

	bulletWall[24] = App->collisions->AddCollider({ 948, 867, 16, 54 }, Collider::Type::BULLET_WALL);
	bulletWall[25] = App->collisions->AddCollider({ 924, 897, 26, 17 }, Collider::Type::BULLET_WALL);
	bulletWall[26] = App->collisions->AddCollider({ 936, 847, 24, 53 }, Collider::Type::BULLET_WALL);
	bulletWall[27] = App->collisions->AddCollider({ 910, 833, 35, 28 }, Collider::Type::BULLET_WALL);
	bulletWall[28] = App->collisions->AddCollider({ 891, 822, 32, 23 }, Collider::Type::BULLET_WALL);
	bulletWall[29] = App->collisions->AddCollider({ 870, 800, 36, 36 }, Collider::Type::BULLET_WALL);
	bulletWall[30] = App->collisions->AddCollider({ 849, 788, 29, 30 }, Collider::Type::BULLET_WALL);
	bulletWall[31] = App->collisions->AddCollider({ 860, 790, 27, 38 }, Collider::Type::BULLET_WALL);
	bulletWall[32] = App->collisions->AddCollider({ 815, 783, 43, 18 }, Collider::Type::BULLET_WALL);
	bulletWall[33] = App->collisions->AddCollider({ 826, 795, 35, 15 }, Collider::Type::BULLET_WALL);
	bulletWall[34] = App->collisions->AddCollider({ 817, 741, 35, 47 }, Collider::Type::BULLET_WALL);
	bulletWall[35] = App->collisions->AddCollider({ 797, 730, 40, 17 }, Collider::Type::BULLET_WALL);
	bulletWall[36] = App->collisions->AddCollider({ 816, 667, 20, 66 }, Collider::Type::BULLET_WALL);
	bulletWall[37] = App->collisions->AddCollider({ 813, 613, 21, 55 }, Collider::Type::BULLET_WALL);
	bulletWall[38] = App->collisions->AddCollider({ 798, 601, 17, 52 }, Collider::Type::BULLET_WALL);
	bulletWall[39] = App->collisions->AddCollider({ 787, 588, 14, 44 }, Collider::Type::BULLET_WALL);
	bulletWall[40] = App->collisions->AddCollider({ 779, 573, 13, 42 }, Collider::Type::BULLET_WALL);
	bulletWall[41] = App->collisions->AddCollider({ 769, 555, 13, 45 }, Collider::Type::BULLET_WALL);
	bulletWall[42] = App->collisions->AddCollider({ 775, 509, 35, 45 }, Collider::Type::BULLET_WALL);
	bulletWall[43] = App->collisions->AddCollider({ 810, 485, 58, 26 }, Collider::Type::BULLET_WALL);
	bulletWall[44] = App->collisions->AddCollider({ 876, 471, 16, 28 }, Collider::Type::BULLET_WALL);
	bulletWall[45] = App->collisions->AddCollider({ 895, 451, 23, 22 }, Collider::Type::BULLET_WALL);
	bulletWall[46] = App->collisions->AddCollider({ 941, 424, 17, 28 }, Collider::Type::BULLET_WALL);
	bulletWall[47] = App->collisions->AddCollider({ 1006, 398, 31, 25 }, Collider::Type::BULLET_WALL);
	bulletWall[48] = App->collisions->AddCollider({ 753, 1016, 75, 43 }, Collider::Type::BULLET_WALL);
	bulletWall[49] = App->collisions->AddCollider({ 717, 987, 72, 32 }, Collider::Type::BULLET_WALL);
	bulletWall[50] = App->collisions->AddCollider({ 673, 964, 48, 30 }, Collider::Type::BULLET_WALL);
	bulletWall[51] = App->collisions->AddCollider({ 643, 943, 53, 27 }, Collider::Type::BULLET_WALL);
	bulletWall[52] = App->collisions->AddCollider({ 597, 921, 64, 28 }, Collider::Type::BULLET_WALL);
	bulletWall[53] = App->collisions->AddCollider({ 535, 902, 61, 25 }, Collider::Type::BULLET_WALL);
	bulletWall[54] = App->collisions->AddCollider({ 514, 881, 61, 27 }, Collider::Type::BULLET_WALL);
	bulletWall[55] = App->collisions->AddCollider({ 473, 857, 67, 30 }, Collider::Type::BULLET_WALL);
	bulletWall[56] = App->collisions->AddCollider({ 476, 770, 26, 88 }, Collider::Type::BULLET_WALL);
	bulletWall[57] = App->collisions->AddCollider({ 468, 762, 62, 44 }, Collider::Type::BULLET_WALL);
	bulletWall[58] = App->collisions->AddCollider({ 466, 696, 104, 92 }, Collider::Type::BULLET_WALL);
	bulletWall[59] = App->collisions->AddCollider({ 471, 645, 78, 53 }, Collider::Type::BULLET_WALL);
	bulletWall[60] = App->collisions->AddCollider({ 467, 590, 110, 43 }, Collider::Type::BULLET_WALL);
	bulletWall[61] = App->collisions->AddCollider({ 534, 631, 14, 18 }, Collider::Type::BULLET_WALL);
	bulletWall[62] = App->collisions->AddCollider({ 472, 568, 63, 36 }, Collider::Type::BULLET_WALL);
	bulletWall[63] = App->collisions->AddCollider({ 467, 449, 28, 35 }, Collider::Type::BULLET_WALL);
	bulletWall[64] = App->collisions->AddCollider({ 487, 441, 25, 34 }, Collider::Type::BULLET_WALL);
	bulletWall[65] = App->collisions->AddCollider({ 499, 431, 29, 29 }, Collider::Type::BULLET_WALL);
	bulletWall[66] = App->collisions->AddCollider({ 512, 430, 38, 22 }, Collider::Type::BULLET_WALL);
	bulletWall[67] = App->collisions->AddCollider({ 507, 404, 34, 30 }, Collider::Type::BULLET_WALL);
	bulletWall[68] = App->collisions->AddCollider({ 526, 382, 22, 37 }, Collider::Type::BULLET_WALL);
	bulletWall[69] = App->collisions->AddCollider({ 531, 378, 34, 20 }, Collider::Type::BULLET_WALL);
	bulletWall[70] = App->collisions->AddCollider({ 530, 364, 26, 19 }, Collider::Type::BULLET_WALL);
	bulletWall[71] = App->collisions->AddCollider({ 519, 311, 30, 59 }, Collider::Type::BULLET_WALL);
	bulletWall[72] = App->collisions->AddCollider({ 545, 282, 11, 35 }, Collider::Type::BULLET_WALL);
	bulletWall[73] = App->collisions->AddCollider({ 552, 267, 17, 34 }, Collider::Type::BULLET_WALL);
	bulletWall[74] = App->collisions->AddCollider({ 559, 248, 22, 32 }, Collider::Type::BULLET_WALL);
	bulletWall[75] = App->collisions->AddCollider({ 573, 206, 17, 54 }, Collider::Type::BULLET_WALL);
	bulletWall[76] = App->collisions->AddCollider({ 590, 206, 7, 41 }, Collider::Type::BULLET_WALL);
	bulletWall[77] = App->collisions->AddCollider({ 541, 160, 49, 39 }, Collider::Type::BULLET_WALL);
	bulletWall[78] = App->collisions->AddCollider({ 503, 132, 48, 46 }, Collider::Type::BULLET_WALL);
	bulletWall[79] = App->collisions->AddCollider({ 469, 123, 33, 46 }, Collider::Type::BULLET_WALL);
	bulletWall[80] = App->collisions->AddCollider({ 692, 580, 100, 20 }, Collider::Type::BULLET_WALL);
	bulletWall[81] = App->collisions->AddCollider({ 563, 532, 100, 20 }, Collider::Type::BULLET_WALL);
	bulletWall[82] = App->collisions->AddCollider({ 612, 452, 100, 20 }, Collider::Type::BULLET_WALL);
	//App->audio->PlayMusic("Assets/Music/mission_1.ogg", 0.0f);

	// PowerUps
	
	
	//App->powerUps->AddPowerUp(App->powerUps->Pow, 0, 995, 1010, Collider::Type::POWER_UP, 0);
	//App->powerUps->AddPowerUp(App->powerUps->Bomb, 0, 555, 450, Collider::Type::POWER_UP, 0);
	//App->powerUps->AddPowerUp(App->powerUps->Food3, 0, 730, 450, Collider::Type::POWER_UP, 0);

	

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 535, 1360);
	App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 540, 1360);
	App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 530, 1360);
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

	//winning condition
	if (App->input->keys[SDL_SCANCODE_I] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->fifthScene, 90);
		App->player->level = 1;

		for (int i = 0; i < 100; i++) {
			if (playerWall[i] != nullptr) {
				playerWall[i]->pendingToDelete = true;
			}
			if (bulletWall[i] != nullptr) {
				bulletWall[i]->pendingToDelete = true;
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
