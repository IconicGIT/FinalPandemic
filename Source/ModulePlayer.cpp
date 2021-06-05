#include "ModulePlayer.h"
#include <stdio.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFonts.h"
#include "ModuleFadeToBlack.h"
#include <string>
#include "ModuleLevel_1.h"
#include "ModuleLevel_2.h"

#include "SDL/include/SDL_scancode.h"
#include <math.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	/* animation

		-> for each key detected, lastKey == that key
	
		if (rightKey == leftKey == upKey == downKey == IDLE) -> no keys are pressed
		{
			if (lastKey == rightKey && currentAnim != rightIdle)
				currentAnim = rightIdle

			if (lastKey == upKey && currentAnim != rightIdle)
				currentAnim = upIdle

			if (lastKey == downKey && currentAnim != rightIdle)
				currentAnim = downIdle

			if (lastKey == leftKey && currentAnim != rightIdle)
				currentAnim = leftIdle
		}
	*/




	// idle animations - just one sprite

	float idleSpeed = 0.01f;
	float animSpeed = 0.15f;
	float hitSpeed = 0.1f;
	float deathSpeed = 0.1f;

	// animation idle up
	upIdleAnim.PushBack({ 147, 8, 21, 41 });
	upIdleAnim.PushBack({ 178, 8, 22, 42 });
	upIdleAnim.loop = true;
	upIdleAnim.speed = idleSpeed;

	// animation idle up-left
	upLeftIdleAnim.PushBack({ 143, 58, 22, 38 });
	upLeftIdleAnim.PushBack({ 173, 58, 20, 38 });
	upLeftIdleAnim.loop = true;
	upLeftIdleAnim.speed = idleSpeed;

	//animation idle left
	leftIdleAnim.PushBack({ 141, 102, 23, 41 });
	leftIdleAnim.PushBack({ 171, 102, 21, 40 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleSpeed;
	
	//animation idle down-left
	downLeftIdleAnim.PushBack({ 138, 149, 30, 41 });
	downLeftIdleAnim.PushBack({ 172, 149, 27, 43 });
	downLeftIdleAnim.loop = true;
	downLeftIdleAnim.speed = idleSpeed;

	//animation idle down
	downIdleAnim.PushBack({ 143, 196, 24, 42 });
	downIdleAnim.PushBack({ 177, 194, 24, 43 });
	downIdleAnim.loop = true;
	downIdleAnim.speed = idleSpeed;

	//animation idle down-right
	downRightIdleAnim.PushBack({ 142,239, 20, 42 });
	downRightIdleAnim.PushBack({ 175, 239, 20, 42 });
	downRightIdleAnim.loop = true;
	downRightIdleAnim.speed = idleSpeed;

	//animation idle right 
	rightIdleAnim.PushBack({ 144, 286, 24, 41 });
	rightIdleAnim.PushBack({ 177, 287, 24, 41 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = idleSpeed;

	//animation idle up-right
	upRightIdleAnim.PushBack({ 137, 334, 24, 40 });
	upRightIdleAnim.PushBack({ 173, 334, 24, 40 });
	upRightIdleAnim.loop = true;
	upRightIdleAnim.speed = idleSpeed;


	// 456, 436, 24, 39 hit from down
	// 420, 437, 23, 40 hit from left
	// 425, 393, 22, 40 hit from up
	// 457, 393, 23, 40 hit from right


	// Hit Animations
	
		//up
		hitFromUpAnim.PushBack({ 425, 393, 22, 40 });
		hitFromUpAnim.loop = false;
		hitFromUpAnim.speed = hitSpeed;

		//left
		hitFromLeftAnim.PushBack({ 420, 437, 23, 40 });
		hitFromLeftAnim.loop = false;
		hitFromLeftAnim.speed = hitSpeed;

		//down
		hitFromDownAnim.PushBack({ 456, 436, 24, 39 });
		hitFromDownAnim.loop = false;
		hitFromDownAnim.speed = hitSpeed;

		//right
		hitFromRightAnim.PushBack({ 457, 393, 23, 40 });
		hitFromRightAnim.loop = false;
		hitFromRightAnim.speed = hitSpeed;

	//rolling when damaged
	rollAnim.PushBack({ 150, 384, 27, 26 });
	rollAnim.PushBack({ 181, 382, 29, 27 });
	rollAnim.loop = false;
	rollAnim.speed = hitSpeed;

	// Death Animations

	deathFromLeftAnim.PushBack({ 216, 448, 24, 35 });
	deathFromLeftAnim.PushBack({ 245, 450, 23, 35 });
	deathFromLeftAnim.PushBack({ 272, 452, 31, 35 });
	deathFromLeftAnim.PushBack({ 305, 457, 37, 31 });
	deathFromLeftAnim.loop = false;
	deathFromLeftAnim.speed = deathSpeed;

	deathFromRightAnim.PushBack({ 10, 397, 26, 41 });
	deathFromRightAnim.PushBack({ 41, 394, 26, 41 });
	deathFromRightAnim.PushBack({ 73, 392, 28, 41 });
	deathFromRightAnim.PushBack({ 111, 383, 35, 51 });
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = deathSpeed;

	deathFromUpAnim.PushBack({ 5, 443, 23, 38 });
	deathFromUpAnim.PushBack({ 36, 440, 48, 41 });
	deathFromUpAnim.PushBack({ 87, 437, 30, 41 });
	deathFromUpAnim.PushBack({ 125, 437, 30, 41 });
	deathFromUpAnim.loop = false;
	deathFromUpAnim.speed = deathSpeed;

	deathFromDownAnim.PushBack({ 212, 394, 28, 45 });
	deathFromDownAnim.PushBack({ 247, 396, 43, 47 });
	deathFromDownAnim.PushBack({ 294, 405, 22, 37 });
	deathFromDownAnim.PushBack({ 321, 406, 27, 26 });
	deathFromDownAnim.PushBack({ 359, 396, 40, 46 });
	deathFromDownAnim.loop = false;
	deathFromDownAnim.speed = deathSpeed;



	// Move Animations

	upAnim.PushBack({ 12, 7, 13, 42 });
	upAnim.PushBack({ 44, 7, 13, 42 });
	upAnim.PushBack({ 76, 7, 13, 42 });
	upAnim.PushBack({ 108, 7, 13, 42 });
	upAnim.loop = true;
	upAnim.speed = animSpeed;

	upLeftAnim.PushBack({ 8, 54, 26, 42 });
	upLeftAnim.PushBack({ 39, 54, 26, 42 });
	upLeftAnim.PushBack({ 70, 54, 26, 42 });
	upLeftAnim.PushBack({ 103, 54, 26, 42 });
	upLeftAnim.loop = true;
	upLeftAnim.speed = animSpeed;
	
	leftAnim.PushBack({ 6, 103, 31, 41 });
	leftAnim.PushBack({ 39, 103, 31, 41 });
	leftAnim.PushBack({ 72, 103, 31, 41 });
	leftAnim.PushBack({ 103, 103, 31, 41 });
	leftAnim.loop = true;
	leftAnim.speed = animSpeed;

	downLeftAnim.PushBack({ 11, 149, 25, 39 });
	downLeftAnim.PushBack({ 44, 149, 25, 39 });
	downLeftAnim.PushBack({ 77, 149, 25, 39 });
	downLeftAnim.PushBack({ 108, 149, 25, 39 });
	downLeftAnim.loop = true;
	downLeftAnim.speed = animSpeed;

	downAnim.PushBack({ 17, 194, 17, 40 });
	downAnim.PushBack({ 49, 194, 17, 40 });
	downAnim.PushBack({ 80, 194, 17, 40 });
	downAnim.PushBack({ 113, 194, 17, 40 });
	downAnim.loop = true;
	downAnim.speed = animSpeed;
	
	downRightAnim.PushBack({ 12, 240, 25, 39 });
	downRightAnim.PushBack({ 44, 240, 25, 39 });
	downRightAnim.PushBack({ 72, 240, 25, 39 });
	downRightAnim.PushBack({ 108, 240, 25, 39 });
	downRightAnim.loop = true;
	downRightAnim.speed = animSpeed;

	rightAnim.PushBack({ 8, 285, 31, 38 });
	rightAnim.PushBack({ 43, 285, 27, 41 });
	rightAnim.PushBack({ 71, 285, 30, 36 });
	rightAnim.PushBack({ 108, 285, 26, 36 });
	rightAnim.loop = true;
	rightAnim.speed = animSpeed;

	upRightAnim.PushBack({ 8, 332, 26, 42 });
	upRightAnim.PushBack({ 40, 332, 26, 42 });
	upRightAnim.PushBack({ 68, 332, 26, 42 });
	upRightAnim.PushBack({ 103, 332, 26, 42 });
	upRightAnim.loop = true;
	upRightAnim.speed = animSpeed;

	

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	//Add textures -> remember unload
	texture = App->textures->Load("Assets/Sprites/character_sprites.png");
	exitTexture = App->textures->Load("Assets/Sprites/quit_icon.png");
	lifeBarTexture = App->textures->Load("Assets/Sprites/player_life_bar.png");

	currentAnimation = &downIdleAnim;

	//Add audio -> remember unload
	laserFx = App->audio->LoadFx("Assets/Fx/gun_shot.wav");
	bombFx = App->audio->LoadFx("Assets/Fx/explosion_02.wav");
	deathFx = App->audio->LoadFx("Assets/Fx/player_death.wav");



	position.x = 550;
	position.y = 1400;

	lastDirection = 5;

	//collBox = App->collisions->AddCollider({ (int)position.x, (int)position.y, playerWidth, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	//hitBox = App->collisions->AddCollider({ (int)position.x, (int)position.y + 15, 25, 25}, Collider::Type::PLAYER_HITBOX, this);
	hitBox = App->collisions->AddCollider({ (int)position.x, (int)position.y + 30, playerWidth, playerHeight }, Collider::Type::PLAYER_HITBOX, this);

	colBoxUp		= App->collisions->AddCollider({ (int)position.x, (int)position.y - speed, playerWidth, speed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxUpLeft	= App->collisions->AddCollider({ (int)position.x - diagonalSpeed, (int)position.y - diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxLeft		= App->collisions->AddCollider({ (int)position.x - speed, (int)position.y, speed, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDownLeft	= App->collisions->AddCollider({ (int)position.x - diagonalSpeed, (int)position.y + playerHeight + diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDown		= App->collisions->AddCollider({ (int)position.x, (int)position.y + playerHeight, playerWidth, speed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDownRight = App->collisions->AddCollider({ (int)position.x + playerWidth, (int)position.y + playerHeight, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxRight		= App->collisions->AddCollider({ (int)position.x + playerWidth, (int)position.y, speed, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxUpRight	= App->collisions->AddCollider({ (int)position.x, (int)position.y - diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);


	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable1[] = { "0123456789abcdefghijklmnopqrstuvwxyz                       " };
	char lookupTable2[] = { "0123456789:;<=>?*abcdefghijklmnopqrstuvwxyz@çççççççççç          " };
	char lookupTable3[] = { "0123456789çççççççççççççççççççççççççççççççççççççççççççççççççççççççççççççç        " };
	char lookupTable4[] = { "çççççççççççççççç0123456789abcdefghijklmnopqrstuvwxyççççççççççççççççççççç        " };
	char lookupTable5[] = { "çççççççççççççççççççççççççççççççççççççççççççççççççççççççç0123456789çççççç        " };
	char lookupTable6[] = { "çççççççççççççççççççççççççççççççççççççççççççç0123456789          " };
	char lookupTable7[] = { "çççççççççççççççççççççççççççççççççççççççççççççççççççççççç0123456789çççççç        " };
	bombScoreFont = App->fonts->Load("Assets/Fonts/bomb_score_font_small.png", lookupTable1, 2);
	playerScoreFont = App->fonts->Load("Assets/Fonts/player_score_font.png", lookupTable2, 2);
	
	endLevelFontGreen = App->fonts->Load("Assets/Fonts/game_over_fonts_big.png", lookupTable4, 5);
	bigGreyFont = App->fonts->Load("Assets/Fonts/game_over_fonts_big.png", lookupTable5, 5);
	endLevelFontPink = App->fonts->Load("Assets/Fonts/game_over_fonts_big.png", lookupTable3, 5);

	bombCounterFont = App->fonts->Load("Assets/Fonts/player_score_font.png", lookupTable6, 2);



	
	return ret;

}

UpdateResult ModulePlayer::Update()
{

	UpdateResult ret = UpdateResult::UPDATE_CONTINUE;
	////////////////////////////////////////////////////////
	// Moving the player with the camera scroll
	//App->player->position.x += 0;
	////////////////////////////////////////////////////////

	//colUp = false;
	//colUpLeft = false;
	//colLeft = false;
	//colDownLeft = false;
	//colDown = false;
	//colDownRight = false;
	//colRight = false;
	//colUpRight = false;

	//LOG("col %i: ", collisionID);




	keyUp    = App->input->keys[SDL_SCANCODE_W];
	keyLeft  = App->input->keys[SDL_SCANCODE_A];
	keyDown  = App->input->keys[SDL_SCANCODE_S];
	keyRight = App->input->keys[SDL_SCANCODE_D];
	shoot = App->input->keys[SDL_SCANCODE_SPACE];

	
	// lastDirection
	// 
	//	1 = up
	//	2 = up-left
	//  3 = left
	//  4 = down-left
	//  5 = down
	//  6 = down-right
	//  7 = right
	// 	8 = up-right
	//

	// Move the player in all posible direction 
	// 
	//AXIS MOVEMENT
	//left

	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_REPEAT)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		lastDirection = 3;

		if (!colCheck[2])
		{
			position.x -= speed;
			SetAnimation(leftAnim);
			colCheck[2] = false;
		}
		else {
			SetAnimation(leftIdleAnim);
		}
	}

	//right
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_REPEAT))
	{
		lastDirection = 7;
		

		

		if (!colCheck[6])
		{
			position.x += speed;
			SetAnimation(rightAnim);
			colCheck[5] = false;
		}
		else {
			SetAnimation(rightIdleAnim);
		}
	}

	//Up
	if ((keyUp == KEY_STATE::KEY_REPEAT)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		lastDirection = 1;
		
		if (!colCheck[0])
		{
			SetAnimation(upAnim);
			position.y -= speed;
			colCheck[0] = false;
		}
		else {
			SetAnimation(upIdleAnim);
		}
		
	}

	//Down
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_REPEAT)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		lastDirection = 5;
		
		if (!colCheck[4])
		{
			SetAnimation(downAnim);

			position.y += speed;
			colCheck[4] = false;
		}
		else {
			SetAnimation(downIdleAnim);
		}

		
	}

	//DIAGONAL AXIS MOVEMENT
	
	//up-left
	if ((keyUp == KEY_STATE::KEY_REPEAT) 
		&& (keyLeft == KEY_STATE::KEY_REPEAT)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		lastDirection = 2;
		
		//if (!colCheck[1] && !colCheck[2] && !colCheck[0])
		//{
		//	SetAnimation(upLeftAnim);
		//
		//	position.x -= diagonalSpeed;
		//	position.y -= diagonalSpeed;
		//	colCheck[1] = false;
		//}
		//else {
		//	SetAnimation(upLeftIdleAnim);
		//}
		
		if (!colCheck[1] && !colCheck[2] && !colCheck[0])
		{
			SetAnimation(upLeftAnim);

			position.x -= diagonalSpeed;
			position.y -= diagonalSpeed;
			colCheck[1] = false;
			colCheck[2] = false;
			colCheck[0] = false;
		}
		else
		{

			if (!colCheck[1])
			{

				if (!colCheck[2]) {
					SetAnimation(leftAnim);
					position.x -= speed;
					colCheck[1] = false;
					colCheck[2] = false;

				}
				if (!colCheck[0])
				{
					SetAnimation(upAnim);
					position.y -= speed;
					colCheck[1] = false;
					colCheck[0] = false;

				}

			}
		}
		if (colCheck[1] && colCheck[2] && colCheck[0])
		{
			SetAnimation(upLeftIdleAnim);
		}

	}

	//down-left
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_REPEAT)
		&& (keyDown == KEY_STATE::KEY_REPEAT)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		lastDirection = 4;
		
		if (!colCheck[3] && !colCheck[2] && !colCheck[4])
		{
			SetAnimation(downLeftAnim);
		
			position.x -= diagonalSpeed;
			position.y += diagonalSpeed;
			colCheck[3] = false;
			colCheck[2] = false;
			colCheck[4] = false;
		}
		else 
		{

			if (!colCheck[3]) 
			{

				if (!colCheck[2]) {
					SetAnimation(leftAnim);
					position.x -= speed;
					colCheck[3] = false;
					colCheck[2] = false;

				}
				if (!colCheck[4]) 
				{
					SetAnimation(downAnim);
					position.y += speed;
					colCheck[3] = false;
					colCheck[4] = false;

				}

			}
		}
		if (colCheck[2] && colCheck[3] && colCheck[4])
		{
			SetAnimation(downLeftIdleAnim);
		}
	}

	//down-right
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_REPEAT)
		&& (keyRight == KEY_STATE::KEY_REPEAT))
	{
		lastDirection = 6;
		
		//if (!colCheck[5] && !colCheck[4] && !colCheck[6])
		//{
		//	SetAnimation(downRightAnim);
		//
		//	position.x += diagonalSpeed;
		//	position.y += diagonalSpeed;
		//	colCheck[5] = false;
		//}
		//else {
		//	SetAnimation(downRightIdleAnim);
		//}

		if (!colCheck[5] && !colCheck[4] && !colCheck[6])
		{
			SetAnimation(downRightAnim);

			position.x += diagonalSpeed;
			position.y += diagonalSpeed;
			colCheck[4] = false;
			colCheck[5] = false;
			colCheck[6] = false;
		}
		else 
		{

			if (!colCheck[5])
			{

				if (!colCheck[6]) 
				{
					SetAnimation(rightAnim);
					position.x += speed;
					colCheck[5] = false;
					colCheck[6] = false;

				}

				if (!colCheck[4]) 
				{
					SetAnimation(downAnim);
					position.y += speed;
					colCheck[5] = false;
					colCheck[6] = false;
					
				}

			}
		}
		if (colCheck[5] && colCheck[4] && colCheck[6]) 
		{
			SetAnimation(downRightIdleAnim);
		}
	}

	//up-right
	if ((keyUp == KEY_STATE::KEY_REPEAT)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_REPEAT))
	{
		lastDirection = 8;

		
		//if (!colCheck[7] && !colCheck[1] && !colCheck[6])
		//{
		//	SetAnimation(upRightAnim);
		//
		//	position.x += diagonalSpeed;
		//	position.y -= diagonalSpeed;
		//	colCheck[6] = false;
		//}
		//else {
		//	SetAnimation(upRightIdleAnim);
		//}

		if (!colCheck[7] && !colCheck[0] && !colCheck[6])
		{
			SetAnimation(upRightAnim);

			position.x += diagonalSpeed;
			position.y -= diagonalSpeed;
			colCheck[7] = false;
			colCheck[0] = false;
			colCheck[6] = false;
		}
		else
		{

			if (!colCheck[7])
			{

				if (!colCheck[6])
				{
					SetAnimation(rightAnim);
					position.x += speed;
					colCheck[7] = false;
					colCheck[6] = false;

				}

				if (!colCheck[0])
				{
					SetAnimation(upAnim);
					position.y -= speed;
					colCheck[7] = false;
					colCheck[0] = false;
					
				}

			}
		}
		if (colCheck[7] && colCheck[0] && colCheck[6])
		{
			SetAnimation(upRightIdleAnim);
		}
	}
		
	

	for (int i = 0; i < 8; i++)
	{
		colCheck[i] = false;
	}

	//camera control

	//LOG("player x: %f, y: %f", position.x, position.y);

	switch (level) {

	case 0:
			
			
			if (keyRight == KEY_STATE::KEY_REPEAT) {

				if (App->render->camera.y + App->render->camera.h > 500) {


					if (App->render->camera.x / SCREEN_SIZE + App->render->camera.w + speed < 1083)
					{

						if (lastDirection % 2 != 0)
						{
							if (position.x + playerWidth > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin) {
								App->render->camera.x += speed * SCREEN_SIZE;
							}
						}
						else
						{
							if (position.x + playerWidth > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin) {
								App->render->camera.x += diagonalSpeed * SCREEN_SIZE;
							}
						}

					}

				}
				else
				{

					if (App->render->camera.x / SCREEN_SIZE + App->render->camera.w + speed < 1242)
					{

						if (lastDirection % 2 != 0)
						{
							if (position.x + playerWidth > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin) {
								App->render->camera.x += speed * SCREEN_SIZE;
							}
						}
						else
						{
							if (position.x + playerWidth > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin) {
								App->render->camera.x += diagonalSpeed * SCREEN_SIZE;
							}
						}

					}
				}

			}

			if (keyLeft == KEY_STATE::KEY_REPEAT) {


				if (App->render->camera.x / SCREEN_SIZE - speed > 474)
				{

					if (lastDirection % 2 != 0)
					{
						if (position.x < App->render->camera.x / SCREEN_SIZE + horizontalMargin) {
							App->render->camera.x -= speed * SCREEN_SIZE;
						}
					}
					else
					{
						if (position.x < App->render->camera.x / SCREEN_SIZE + horizontalMargin) {
							App->render->camera.x -= diagonalSpeed * SCREEN_SIZE;
						}
					}

				}

			}



			if (App->render->camera.y / SCREEN_SIZE <= 1156) {

				if (lastDirection % 2 == 0)
				{
					if (position.y <= (App->render->camera.y / SCREEN_SIZE + verticalMargin) && App->render->camera.y / SCREEN_SIZE - diagonalSpeed >= 0) App->render->camera.y -= diagonalSpeed * SCREEN_SIZE;
				}
				else
				{
					if (position.y < (App->render->camera.y / SCREEN_SIZE + verticalMargin) && App->render->camera.y / SCREEN_SIZE - speed >= 0) App->render->camera.y -= speed * SCREEN_SIZE;
				}
			}

		break;

	case 1:

		
		
		if (keyRight == KEY_STATE::KEY_REPEAT) {

			


				if (App->render->camera.x / SCREEN_SIZE + App->render->camera.w + speed < 768)
				{

					if (lastDirection % 2 != 0)
					{
						if (position.x + playerWidth > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin) {
							App->render->camera.x += speed * SCREEN_SIZE;
						}
					}
					else
					{
						if (position.x + playerWidth > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin) {
							App->render->camera.x += diagonalSpeed * SCREEN_SIZE;
						}
					}

				}

			

		}

		if (keyLeft == KEY_STATE::KEY_REPEAT) {


			if (App->render->camera.x / SCREEN_SIZE - speed > 0)
			{

				if (lastDirection % 2 != 0)
				{
					if (position.x < App->render->camera.x / SCREEN_SIZE + horizontalMargin) {
						App->render->camera.x -= speed * SCREEN_SIZE;
					}
				}
				else
				{
					if (position.x < App->render->camera.x / SCREEN_SIZE + horizontalMargin) {
						App->render->camera.x -= diagonalSpeed * SCREEN_SIZE;
					}
				}

			}

		}



		if (App->render->camera.y / SCREEN_SIZE <= 3072) {

			if (lastDirection % 2 == 0)
			{
				if (position.y <= (App->render->camera.y / SCREEN_SIZE + verticalMargin) 
					&& App->render->camera.y / SCREEN_SIZE - diagonalSpeed >= 0) App->render->camera.y -= diagonalSpeed * SCREEN_SIZE;
			}
			else
			{
				if (position.y < (App->render->camera.y / SCREEN_SIZE + verticalMargin) 
					&& App->render->camera.y / SCREEN_SIZE - speed >= 0) App->render->camera.y -= speed * SCREEN_SIZE;
			}
		}

		break;

	}


	



	////////////////////////////////////////////////
	if (shoot == KEY_STATE::KEY_DOWN)
	{
		int posOffsetX = 0;
		int posOffsetY = 0;

		switch (lastDirection) {
		case 1:
			posOffsetX = 13;
			
			break;
		case 2:
			posOffsetX = 4;
			posOffsetY = 1;
			break;
		case 3:
			posOffsetX = 0;
			posOffsetY = 9;
			break;
		case 4:
			posOffsetX = PlayerWidthOffset;
			posOffsetY = 16;
			break;
		case 5:
			posOffsetX = 7;
			posOffsetY = 24;
			break;
		case 6:
			posOffsetX = 17;
			posOffsetY = 18;
			break;
		case 7:
			posOffsetX = 19;
			posOffsetY = 11;
			break;
		case 8:
			posOffsetX = 20;
			posOffsetY = 4;
			break;
		}
		for (size_t i = 0; i < 4; i++)
		{
			App->particles->AddParticle(App->particles->playerBullet1[lastDirection - 1], 0, position.x + posOffsetX, position.y + posOffsetY, lastDirection, Collider::Type::PLAYER_SHOT,i * 3);
		}
		

		
		
		App->audio->PlayFx(laserFx);
	}
	if ((App->input->keys[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)||(App->fade->credits<=0))
	{
		destroyed = true;
		//App->particles->AddParticle(App->particles->playerBullet1[lastDirection - 1], 0, position.x, position.y, lastDirection, Collider::Type::PLAYER_SHOT);
		//App->audio->PlayFx(laserFx);
	}
	if (App->input->keys[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN)
	{
		if (playerLife < 9)
		{
			App->fade->credits++;
		}
		
	}

	if (playerLife <= 0)
	{
		App->audio->PlayFx(deathFx);
		App->fade->credits--;
		playerLife = playerMaximumLife;
	}
	

	////////////////////////////////////////////////

	// Idle Animations 

	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE)
		) {

		switch (lastDirection) {

		case 1:

			
			SetAnimation(upIdleAnim);
			break;

		case 2:
			
			SetAnimation(upLeftIdleAnim);
			break;

		case 3:
			
			SetAnimation(leftIdleAnim);
			break;

		case 4:
			
			SetAnimation(downLeftIdleAnim);
			break;

		case 5:
			
			SetAnimation(downIdleAnim);
			break;

		case 6:
			
			SetAnimation(downRightIdleAnim);
			break;

		case 7:
			
			SetAnimation(rightIdleAnim);
			break;

		case 8:

			
			SetAnimation(upRightIdleAnim);
			break;

		}


	}

	

	// Death Animations

	if (destroyed == true)
	{
		switch (lastDirection)
		{
		case 1:
			
			SetAnimation(deathFromUpAnim);
			break;

		case 2:
			
			SetAnimation(deathFromUpAnim);
			break;

		case 3:
			
			SetAnimation(deathFromLeftAnim);
			break;

		case 4:
			
			SetAnimation(deathFromLeftAnim);
			break;

		case 5:
			
			SetAnimation(deathFromDownAnim);
			break;

		case 6:
			
			SetAnimation(deathFromDownAnim);
			break;

		case 7:
			
			SetAnimation(deathFromRightAnim);
			break;

		case 8:
			
			SetAnimation(deathFromRightAnim);
			break;


		}
	}


	
	////////////////////////////////////////////
	hitBox->SetPos(position.x, position.y + playerHeightOffset);
	
	colBoxUp		->SetPos(position.x, position.y - speed + playerHeightOffset);
	colBoxUpLeft	->SetPos(position.x - diagonalSpeed, position.y - diagonalSpeed + playerHeightOffset);
	colBoxLeft		->SetPos(position.x - speed, position.y + playerHeightOffset);
	colBoxDownLeft	->SetPos(position.x - diagonalSpeed, position.y + playerHeight + playerHeightOffset);
	colBoxDown		->SetPos(position.x, position.y + playerHeight + playerHeightOffset);
	colBoxDownRight	->SetPos(position.x + playerWidth, position.y + playerHeight + playerHeightOffset);
	colBoxRight		->SetPos(position.x + playerWidth, position.y + playerHeightOffset);
	colBoxUpRight	->SetPos(position.x + playerWidth, position.y - diagonalSpeed + playerHeightOffset);

	currentAnimation->Update();


	if (App->input->keys[SDL_SCANCODE_ESCAPE] == KEY_STATE::KEY_REPEAT)
	{
		exit_counter++;
	}
	else {
		exit_counter = 0;
	}
	
	if (exit_counter >= 200) {
	
		ret = UpdateResult::UPDATE_STOP;
	}
	
	//LOG("Quit time: %i", exit_counter);

	

	if (destroyed)
	{
		//exitCountdown--;
		//if (exitCountdown <= 0)
			return UpdateResult::UPDATE_STOP;
	}
	
	////////////////////////////////////////////
	
	if (App->input->keys[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN) score += 1000;
	if (App->input->keys[SDL_SCANCODE_H] == KEY_STATE::KEY_DOWN) playerLife--;

	//LOG("player live: %f", (float)playerLife / (float)playerMaximumLife * 22);

	return ret;
}

UpdateResult ModulePlayer::PostUpdate()
{

	if (destroyed != true)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		
		App->render->Blit(texture, position.x + PlayerWidthOffset, position.y, &rect,1);
	}

	// Draw UI (score) --------------------------------------

	
	sprintf_s(txtUpLeftScore, "%5d", score);
	sprintf_s(txtBombCounter, "%2d", bombs);
	sprintf_s(txtLevelTimer, "%3d", levelTime);

	

	// TODO 3: Blit the text of the score in at the bottom of the screen
	//App->fonts->BlitText(29, 1, playerScoreFont, txtPlayerScore);

	

	

	//icon and score left up
	SDL_Rect playerIconRect = { 474,493,16,21 };
	App->render->Blit(texture, 5, 0, &playerIconRect, 1, false);
	App->fonts->BlitText(38, 0, playerScoreFont, txtUpLeftScore);

	//player bombs and bomb counter
	SDL_Rect playerBombIconRect = { 186,84,14,16 };
	App->render->Blit(App->particles->texture, 6, 360, &playerBombIconRect, 1, false);
	App->fonts->BlitText(6, 376, bombCounterFont, txtBombCounter);

	//player lifebar
	SDL_Rect lifeBarRectOutline = { 216,14,25,14 };
	SDL_Rect lifeBarRectInside = { 240, 14, ((float) playerLife / (float)playerMaximumLife * 22),14 };
	
	App->render->Blit(lifeBarTexture, 21, 362, &lifeBarRectOutline, 1, false);
	App->render->Blit(lifeBarTexture, 21, 362, &lifeBarRectInside, 1, false);
	
	//level time
	App->fonts->BlitText(166, 40, bigGreyFont, txtLevelTimer);

	//quitting icon in pressing ESC
	SDL_Rect quitRect1 = { 0,0,58,16 };
	SDL_Rect quitRect2 = { 0,0,64,16 };
	SDL_Rect quitRect3 = { 0,0,70,16 };

	if (exit_counter > 0 && exit_counter < 60) {
		App->render->Blit(exitTexture, 10, 10, &quitRect1, 1,false);
	}
	if (exit_counter >= 60 && exit_counter < 120) {
		App->render->Blit(exitTexture, 10, 10, &quitRect2, 1,false);
	}
	if (exit_counter >= 120) {
		App->render->Blit(exitTexture, 10, 10, &quitRect3, 1,false);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	

	//AXIAL
	if (c1 == colBoxUp && c2->type == Collider::WALL) {
		
		colCheck[0] = true;	
		
	}



	if (c1 == colBoxLeft && c2->type == Collider::WALL) {

		colCheck[2] = true;

	}



	if (c1 == colBoxDown && c2->type == Collider::WALL) {

		colCheck[4] = true;

	}


	if (c1 == colBoxRight && c2->type == Collider::WALL) {

		colCheck[6] = true;

	}



	//DIAGONAL
	if (c1 == colBoxUpLeft && c2->type == Collider::WALL) {

		colCheck[1] = true;
	}

	if (c1 == colBoxDownLeft && c2->type == Collider::WALL) {

		colCheck[3] = true;

	}


	if (c1 == colBoxDownRight && c2->type == Collider::WALL) {

		colCheck[5] = true;

	}

	if (c1 == colBoxUpRight && c2->type == Collider::WALL) {

		colCheck[7] = true;

	}

	//rock

	if (c2 == App->scene->rockTrigger) {
		App->scene->rockAnimActivate = true;
		App->scene->rockTrigger->pendingToDelete = true;
	}
	
}
void ModulePlayer::SetAnimation(Animation &toChange) {

	if (currentAnimation != &toChange) {

		toChange.Reset();
		currentAnimation = &toChange;
	}

}



