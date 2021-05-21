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

	//Structures Colliders
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
	playerWall[65] = App->collisions->AddCollider({ 746, 1410, 22, 51 }, Collider::Type::WALL);
	playerWall[66] = App->collisions->AddCollider({ 710, 1415, 37, 46 }, Collider::Type::WALL);
	playerWall[67] = App->collisions->AddCollider({ 693, 1423, 18, 38 }, Collider::Type::WALL);
	playerWall[68] = App->collisions->AddCollider({ 686, 1435, 8, 26 }, Collider::Type::WALL);
	playerWall[69] = App->collisions->AddCollider({ 678, 1441, 10, 20 }, Collider::Type::WALL);
	playerWall[70] = App->collisions->AddCollider({ 32, 1237, 8, 184 }, Collider::Type::WALL);
	playerWall[71] = App->collisions->AddCollider({ 0, 1409, 473, 51 }, Collider::Type::WALL);
	playerWall[72] = App->collisions->AddCollider({ 464, 1416, 30, 44 }, Collider::Type::WALL);
	playerWall[73] = App->collisions->AddCollider({ 477, 1419, 35, 41 }, Collider::Type::WALL);
	playerWall[74] = App->collisions->AddCollider({ 507, 1424, 21, 36 }, Collider::Type::WALL);
	playerWall[75] = App->collisions->AddCollider({ 525, 1437, 18, 23 }, Collider::Type::WALL);
	playerWall[76] = App->collisions->AddCollider({ 500, 1472, 80, 108 }, Collider::Type::WALL);
	playerWall[78] = App->collisions->AddCollider({ 521, 1478, 31, 22 }, Collider::Type::WALL);
	playerWall[79] = App->collisions->AddCollider({ 572, 1546, 17, 32 }, Collider::Type::WALL);
	playerWall[97] = App->collisions->AddCollider({ 525, 1580, 25, 20 }, Collider::Type::WALL);


	//Tanks Colliders
	playerWall[80] = App->collisions->AddCollider({ 183, 850, 121, 94 }, Collider::Type::WALL);
	playerWall[81] = App->collisions->AddCollider({ 544, 1108, 121, 92 }, Collider::Type::WALL);
	playerWall[83] = App->collisions->AddCollider({ 0, 1026, 57, 190 }, Collider::Type::WALL);
	playerWall[84] = App->collisions->AddCollider({ 640, 1266, 121, 94 }, Collider::Type::WALL);
	
	//Objects Colliders
	playerWall[85] = App->collisions->AddCollider({ 528, 849, 25, 41 }, Collider::Type::WALL);
	playerWall[86] = App->collisions->AddCollider({ 549, 874, 25, 15 }, Collider::Type::WALL);
	playerWall[87] = App->collisions->AddCollider({ 703, 849, 32, 29 }, Collider::Type::WALL);
	playerWall[88] = App->collisions->AddCollider({ 719, 872, 30, 17 }, Collider::Type::WALL);
	playerWall[89] = App->collisions->AddCollider({ 720, 896, 32, 29 }, Collider::Type::WALL);
	playerWall[90] = App->collisions->AddCollider({ 97, 850, 47, 41 }, Collider::Type::WALL);
	playerWall[91] = App->collisions->AddCollider({ 127, 888, 18, 14 }, Collider::Type::WALL);
	playerWall[92] = App->collisions->AddCollider({ 111, 911, 33, 32 }, Collider::Type::WALL);
	playerWall[93] = App->collisions->AddCollider({ 220, 1041, 64, 53 }, Collider::Type::WALL);
	playerWall[94] = App->collisions->AddCollider({ 220, 1088, 35, 30 }, Collider::Type::WALL);
	playerWall[95] = App->collisions->AddCollider({ 187, 1045, 36, 87 }, Collider::Type::WALL);
	playerWall[96] = App->collisions->AddCollider({ 467, 1610, 46, 16 }, Collider::Type::WALL);
	playerWall[97] = App->collisions->AddCollider({ 487, 1585, 26, 41 }, Collider::Type::WALL);

	//Plants Colliders
	playerWall[98] = App->collisions->AddCollider({ 0, 1682, 282, 89 }, Collider::Type::WALL);
	playerWall[99] = App->collisions->AddCollider({ 32, 1456, 16, 240 }, Collider::Type::WALL);
	playerWall[100] = App->collisions->AddCollider({ 72, 1667, 46, 21 }, Collider::Type::WALL);
	playerWall[101] = App->collisions->AddCollider({ 138, 1664, 40, 22 }, Collider::Type::WALL);
	playerWall[102] = App->collisions->AddCollider({ 200, 1663, 45, 22 }, Collider::Type::WALL);
	playerWall[103] = App->collisions->AddCollider({ 579, 1781, 30, 107 }, Collider::Type::WALL);
	playerWall[104] = App->collisions->AddCollider({ 589, 1769, 179, 22 }, Collider::Type::WALL);
	playerWall[105] = App->collisions->AddCollider({ 594, 1761, 50, 15 }, Collider::Type::WALL);
	playerWall[106] = App->collisions->AddCollider({ 658, 1762, 64, 9 }, Collider::Type::WALL);
	playerWall[107] = App->collisions->AddCollider({ 704, 1745, 49, 26 }, Collider::Type::WALL);
	playerWall[108] = App->collisions->AddCollider({ 750, 1757, 18, 18 }, Collider::Type::WALL);
	playerWall[109] = App->collisions->AddCollider({ 0, 2508, 80, 50 }, Collider::Type::WALL);
	playerWall[110] = App->collisions->AddCollider({ 75, 2504, 21, 23 }, Collider::Type::WALL);
	playerWall[111] = App->collisions->AddCollider({ 94, 2491, 19, 19 }, Collider::Type::WALL);
	playerWall[112] = App->collisions->AddCollider({ 101, 2239, 13, 258 }, Collider::Type::WALL);
	playerWall[113] = App->collisions->AddCollider({ 0, 2209, 48, 28 }, Collider::Type::WALL);
	playerWall[114] = App->collisions->AddCollider({ 40, 2222, 41, 19 }, Collider::Type::WALL);
	playerWall[115] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);

	//Building Colliders
	playerWall[116] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[117] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[118] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[119] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[120] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[121] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[122] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[123] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[124] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[125] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[126] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[127] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[128] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[129] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[130] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[131] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[132] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[133] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[134] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[135] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[136] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[137] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[138] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[139] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[140] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[141] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[142] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[143] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[144] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[145] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[146] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[147] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[148] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[149] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[150] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[151] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[152] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[153] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);
	playerWall[154] = App->collisions->AddCollider({ 76, 2229, 29, 11 }, Collider::Type::WALL);



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