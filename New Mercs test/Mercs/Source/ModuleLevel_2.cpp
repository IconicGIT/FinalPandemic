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
	playerWall[116] = App->collisions->AddCollider({ 260, 1647, 60, 77 }, Collider::Type::WALL);
	playerWall[117] = App->collisions->AddCollider({ 306, 1600, 25, 137 }, Collider::Type::WALL);
	playerWall[118] = App->collisions->AddCollider({ 324, 1610, 21, 47 }, Collider::Type::WALL);
	playerWall[119] = App->collisions->AddCollider({ 341, 1615, 17, 39 }, Collider::Type::WALL);
	playerWall[120] = App->collisions->AddCollider({ 354, 1618, 15, 39 }, Collider::Type::WALL);
	playerWall[121] = App->collisions->AddCollider({ 365, 1622, 20, 32 }, Collider::Type::WALL);
	playerWall[122] = App->collisions->AddCollider({ 379, 1628, 20, 28 }, Collider::Type::WALL);
	playerWall[123] = App->collisions->AddCollider({ 389, 1634, 25, 28 }, Collider::Type::WALL);
	playerWall[124] = App->collisions->AddCollider({ 406, 1640, 32, 29 }, Collider::Type::WALL);
	playerWall[125] = App->collisions->AddCollider({ 425, 1645, 33, 29 }, Collider::Type::WALL);
	playerWall[126] = App->collisions->AddCollider({ 445, 1659, 18, 57 }, Collider::Type::WALL);
	playerWall[127] = App->collisions->AddCollider({ 456, 1675, 13, 53 }, Collider::Type::WALL);
	playerWall[128] = App->collisions->AddCollider({ 465, 1696, 9, 50 }, Collider::Type::WALL);
	playerWall[129] = App->collisions->AddCollider({ 474, 1720, 6, 140 }, Collider::Type::WALL);
	playerWall[130] = App->collisions->AddCollider({ 429, 1849, 45, 18 }, Collider::Type::WALL);
	playerWall[131] = App->collisions->AddCollider({ 413, 1857, 52, 19 }, Collider::Type::WALL);
	playerWall[132] = App->collisions->AddCollider({ 396, 1862, 60, 23 }, Collider::Type::WALL);
	playerWall[133] = App->collisions->AddCollider({ 393, 1875, 55, 15 }, Collider::Type::WALL);
	playerWall[134] = App->collisions->AddCollider({ 385, 1882, 56, 17 }, Collider::Type::WALL);
	playerWall[135] = App->collisions->AddCollider({ 375, 1896, 56, 16 }, Collider::Type::WALL);
	playerWall[136] = App->collisions->AddCollider({ 376, 1909, 49, 14 }, Collider::Type::WALL);
	playerWall[137] = App->collisions->AddCollider({ 362, 1920, 49, 12 }, Collider::Type::WALL);
	playerWall[138] = App->collisions->AddCollider({ 356, 1930, 44, 11 }, Collider::Type::WALL);
	playerWall[139] = App->collisions->AddCollider({ 352, 1938, 40, 11 }, Collider::Type::WALL);
	playerWall[140] = App->collisions->AddCollider({ 350, 1940, 34, 31 }, Collider::Type::WALL);
	playerWall[141] = App->collisions->AddCollider({ 345, 1965, 31, 12 }, Collider::Type::WALL);
	playerWall[142] = App->collisions->AddCollider({ 329, 1972, 37, 12 }, Collider::Type::WALL);
	playerWall[143] = App->collisions->AddCollider({ 314, 1981, 32, 10 }, Collider::Type::WALL);
	playerWall[144] = App->collisions->AddCollider({ 304, 1989, 30, 13 }, Collider::Type::WALL);
	playerWall[145] = App->collisions->AddCollider({ 295, 2000, 22, 11 }, Collider::Type::WALL);
	playerWall[146] = App->collisions->AddCollider({ 262, 2007, 45, 13 }, Collider::Type::WALL);
	playerWall[147] = App->collisions->AddCollider({ 250, 2019, 33, 14 }, Collider::Type::WALL);
	playerWall[148] = App->collisions->AddCollider({ 230, 2033, 30, 13 }, Collider::Type::WALL);
	playerWall[149] = App->collisions->AddCollider({ 221, 2040, 25, 13 }, Collider::Type::WALL);
	playerWall[150] = App->collisions->AddCollider({ 205, 2047, 37, 15 }, Collider::Type::WALL);
	playerWall[151] = App->collisions->AddCollider({ 172, 2050, 37, 30 }, Collider::Type::WALL);
	playerWall[152] = App->collisions->AddCollider({ 166, 2073, 26, 37 }, Collider::Type::WALL);
	playerWall[153] = App->collisions->AddCollider({ 153, 2105, 21, 77 }, Collider::Type::WALL);
	playerWall[154] = App->collisions->AddCollider({ 171, 2144, 21, 32 }, Collider::Type::WALL);
	playerWall[155] = App->collisions->AddCollider({ 137, 2173, 30, 18 }, Collider::Type::WALL);
	playerWall[156] = App->collisions->AddCollider({ 129, 2188, 28, 10 }, Collider::Type::WALL);
	playerWall[157] = App->collisions->AddCollider({ 123, 2195, 27, 12 }, Collider::Type::WALL);
	playerWall[158] = App->collisions->AddCollider({ 113, 2203, 25, 12 }, Collider::Type::WALL);
	playerWall[159] = App->collisions->AddCollider({ 97, 2208, 38, 15 }, Collider::Type::WALL);
	playerWall[160] = App->collisions->AddCollider({ 80, 2199, 40, 15 }, Collider::Type::WALL);
	playerWall[161] = App->collisions->AddCollider({ 61, 2193, 45, 15 }, Collider::Type::WALL);
	playerWall[162] = App->collisions->AddCollider({ 48, 2159, 34, 44 }, Collider::Type::WALL);
	playerWall[163] = App->collisions->AddCollider({ 0, 2167, 32, 53 }, Collider::Type::WALL);
	playerWall[164] = App->collisions->AddCollider({ 0, 2162, 60, 14 }, Collider::Type::WALL);
	playerWall[165] = App->collisions->AddCollider({ 346, 2393, 422, 87 }, Collider::Type::WALL);
	playerWall[166] = App->collisions->AddCollider({ 304, 2261, 69, 168 }, Collider::Type::WALL);
	playerWall[167] = App->collisions->AddCollider({ 307, 2412, 64, 26 }, Collider::Type::WALL);
	playerWall[168] = App->collisions->AddCollider({ 315, 2419, 62, 24 }, Collider::Type::WALL);
	playerWall[169] = App->collisions->AddCollider({ 340, 2460, 17, 15 }, Collider::Type::WALL);
	playerWall[170] = App->collisions->AddCollider({ 704, 2334, 64, 738 }, Collider::Type::WALL);
	playerWall[171] = App->collisions->AddCollider({ 402, 2479, 8, 101 }, Collider::Type::WALL);
	playerWall[172] = App->collisions->AddCollider({ 305, 2256, 37, 11 }, Collider::Type::WALL);
	playerWall[173] = App->collisions->AddCollider({ 306, 2250, 36, 9 }, Collider::Type::WALL);
	playerWall[174] = App->collisions->AddCollider({ 307, 2238, 35, 10 }, Collider::Type::WALL);
	playerWall[175] = App->collisions->AddCollider({ 312, 2228, 27, 12 }, Collider::Type::WALL);
	playerWall[176] = App->collisions->AddCollider({ 316, 2218, 27, 11 }, Collider::Type::WALL);
	playerWall[177] = App->collisions->AddCollider({ 322, 2209, 25, 10 }, Collider::Type::WALL);
	playerWall[178] = App->collisions->AddCollider({ 328, 2202, 24, 10 }, Collider::Type::WALL);
	playerWall[179] = App->collisions->AddCollider({ 333, 2195, 51, 10 }, Collider::Type::WALL);
	playerWall[180] = App->collisions->AddCollider({ 369, 2203, 23, 11 }, Collider::Type::WALL);
	playerWall[181] = App->collisions->AddCollider({ 376, 2212, 23, 16 }, Collider::Type::WALL);
	playerWall[182] = App->collisions->AddCollider({ 388, 2220, 27, 15 }, Collider::Type::WALL);
	playerWall[183] = App->collisions->AddCollider({ 409, 2203, 13, 25 }, Collider::Type::WALL);
	playerWall[184] = App->collisions->AddCollider({ 413, 2177, 29, 45 }, Collider::Type::WALL);
	playerWall[185] = App->collisions->AddCollider({ 432, 2182, 33, 31 }, Collider::Type::WALL);
	playerWall[186] = App->collisions->AddCollider({ 444, 2187, 70, 17 }, Collider::Type::WALL);
	playerWall[187] = App->collisions->AddCollider({ 504, 2077, 32, 135 }, Collider::Type::WALL);
	playerWall[188] = App->collisions->AddCollider({ 501, 2071, 59, 9 }, Collider::Type::WALL);
	playerWall[189] = App->collisions->AddCollider({ 506, 2063, 66, 13 }, Collider::Type::WALL);
	playerWall[190] = App->collisions->AddCollider({ 511, 2028, 62, 38 }, Collider::Type::WALL);
	playerWall[191] = App->collisions->AddCollider({ 515, 2021, 62, 13 }, Collider::Type::WALL);
	playerWall[192] = App->collisions->AddCollider({ 518, 2017, 61, 8 }, Collider::Type::WALL);
	playerWall[193] = App->collisions->AddCollider({ 522, 1988, 85, 36 }, Collider::Type::WALL);
	playerWall[194] = App->collisions->AddCollider({ 524, 1980, 53, 17 }, Collider::Type::WALL);
	playerWall[195] = App->collisions->AddCollider({ 527, 1970, 32, 12 }, Collider::Type::WALL);
	playerWall[196] = App->collisions->AddCollider({ 530, 1964, 25, 7 }, Collider::Type::WALL);
	playerWall[197] = App->collisions->AddCollider({ 532, 1952, 18, 15 }, Collider::Type::WALL);
	playerWall[198] = App->collisions->AddCollider({ 592, 1881, 44, 14 }, Collider::Type::WALL);
	playerWall[199] = App->collisions->AddCollider({ 588, 1896, 62, 19 }, Collider::Type::WALL);
	playerWall[200] = App->collisions->AddCollider({ 582, 1913, 52, 22 }, Collider::Type::WALL);
	playerWall[201] = App->collisions->AddCollider({ 576, 1932, 30, 31 }, Collider::Type::WALL);
	playerWall[202] = App->collisions->AddCollider({ 570, 1953, 32, 33 }, Collider::Type::WALL);
	playerWall[203] = App->collisions->AddCollider({ 564, 1986, 32, 32 }, Collider::Type::WALL);
	playerWall[204] = App->collisions->AddCollider({ 336, 2384, 53, 88 }, Collider::Type::WALL);

	//Entrance Colliders
	playerWall[205] = App->collisions->AddCollider({ 328, 2592, 382, 25 }, Collider::Type::WALL);
	playerWall[206] = App->collisions->AddCollider({ 500, 2723, 13, 349 }, Collider::Type::WALL);
	playerWall[207] = App->collisions->AddCollider({ 472, 2821, 53, 35 }, Collider::Type::WALL);
	playerWall[208] = App->collisions->AddCollider({ 472, 2948, 60, 36 }, Collider::Type::WALL);
	playerWall[209] = App->collisions->AddCollider({ 306, 2904, 26, 168 }, Collider::Type::WALL);
	playerWall[210] = App->collisions->AddCollider({ 0, 2752, 173, 32 }, Collider::Type::WALL);

	playerWall[211] = App->collisions->AddCollider({ 333, 2614, 40, 12 }, Collider::Type::WALL);
	playerWall[212] = App->collisions->AddCollider({ 340, 2621, 40, 12 }, Collider::Type::WALL);
	playerWall[213] = App->collisions->AddCollider({ 347, 2628, 40, 12 }, Collider::Type::WALL);
	playerWall[214] = App->collisions->AddCollider({ 355, 2636, 40, 12 }, Collider::Type::WALL);
	playerWall[215] = App->collisions->AddCollider({ 362, 2645, 40, 12 }, Collider::Type::WALL);
	playerWall[216] = App->collisions->AddCollider({ 370, 2653, 40, 12 }, Collider::Type::WALL);
	playerWall[217] = App->collisions->AddCollider({ 378, 2661, 40, 12 }, Collider::Type::WALL);
	playerWall[218] = App->collisions->AddCollider({ 386, 2669, 40, 12 }, Collider::Type::WALL);
	playerWall[219] = App->collisions->AddCollider({ 397, 2678, 40, 12 }, Collider::Type::WALL);
	playerWall[220] = App->collisions->AddCollider({ 392, 2690, 40, 12 }, Collider::Type::WALL);
	playerWall[221] = App->collisions->AddCollider({ 396, 2700, 40, 12 }, Collider::Type::WALL);
	playerWall[222] = App->collisions->AddCollider({ 403, 2705, 40, 12 }, Collider::Type::WALL);
	playerWall[223] = App->collisions->AddCollider({ 427, 2711, 40, 12 }, Collider::Type::WALL);
	playerWall[224] = App->collisions->AddCollider({ 434, 2719, 40, 12 }, Collider::Type::WALL);
	playerWall[225] = App->collisions->AddCollider({ 447, 2730, 40, 12 }, Collider::Type::WALL);
	playerWall[226] = App->collisions->AddCollider({ 441, 2742, 40, 12 }, Collider::Type::WALL);
	playerWall[227] = App->collisions->AddCollider({ 446, 2751, 40, 12 }, Collider::Type::WALL);
	playerWall[228] = App->collisions->AddCollider({ 471, 2756, 40, 12 }, Collider::Type::WALL);
	playerWall[229] = App->collisions->AddCollider({ 482, 2765, 40, 12 }, Collider::Type::WALL);
	playerWall[230] = App->collisions->AddCollider({ 493, 2773, 40, 12 }, Collider::Type::WALL);

	playerWall[231] = App->collisions->AddCollider({ 131, 2758, 40, 12 }, Collider::Type::WALL);
	playerWall[232] = App->collisions->AddCollider({ 138, 2764, 40, 12 }, Collider::Type::WALL);
	playerWall[233] = App->collisions->AddCollider({ 145, 2771, 40, 12 }, Collider::Type::WALL);
	playerWall[234] = App->collisions->AddCollider({ 152, 2777, 40, 12 }, Collider::Type::WALL);
	playerWall[235] = App->collisions->AddCollider({ 169, 2781, 40, 12 }, Collider::Type::WALL);
	playerWall[236] = App->collisions->AddCollider({ 176, 2787, 40, 12 }, Collider::Type::WALL);
	playerWall[237] = App->collisions->AddCollider({ 181, 2793, 40, 12 }, Collider::Type::WALL);
	playerWall[237] = App->collisions->AddCollider({ 181, 2805, 40, 12 }, Collider::Type::WALL);
	playerWall[238] = App->collisions->AddCollider({ 186, 2812, 40, 12 }, Collider::Type::WALL);
	playerWall[239] = App->collisions->AddCollider({ 192, 2818, 40, 12 }, Collider::Type::WALL);
	playerWall[240] = App->collisions->AddCollider({ 199, 2825, 40, 12 }, Collider::Type::WALL);
	playerWall[241] = App->collisions->AddCollider({ 216, 2831, 40, 12 }, Collider::Type::WALL);
	playerWall[242] = App->collisions->AddCollider({ 223, 2835, 40, 12 }, Collider::Type::WALL);
	playerWall[243] = App->collisions->AddCollider({ 229, 2842, 40, 12 }, Collider::Type::WALL);
	playerWall[244] = App->collisions->AddCollider({ 229, 2854, 40, 12 }, Collider::Type::WALL);
	playerWall[245] = App->collisions->AddCollider({ 235, 2861, 40, 12 }, Collider::Type::WALL);
	playerWall[246] = App->collisions->AddCollider({ 242, 2867, 40, 12 }, Collider::Type::WALL);
	playerWall[247] = App->collisions->AddCollider({ 247, 2876, 40, 12 }, Collider::Type::WALL);
	playerWall[248] = App->collisions->AddCollider({ 252, 2884, 40, 12 }, Collider::Type::WALL);
	playerWall[249] = App->collisions->AddCollider({ 265, 2890, 40, 12 }, Collider::Type::WALL);
	playerWall[250] = App->collisions->AddCollider({ 273, 2897, 40, 12 }, Collider::Type::WALL);
	playerWall[250] = App->collisions->AddCollider({ 282, 2904, 40, 12 }, Collider::Type::WALL);

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