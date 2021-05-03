#include "ModulePlayer.h"

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
	currentAnimation = &downIdleAnim;

	//Add audio -> remember unload
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	bombFx = App->audio->LoadFx("Assets/Fx/explosion.wav");



	position.x = 550.0f;
	position.y = 1400.0f;

	lastDirection = 5;

	//collBox = App->collisions->AddCollider({ (int)position.x, (int)position.y, playerWidth, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	//hitBox = App->collisions->AddCollider({ (int)position.x, (int)position.y + 15, 25, 25}, Collider::Type::PLAYER_HITBOX, this);
	hitBox = App->collisions->AddCollider({ (int)position.x, (int)position.y, playerWidth, playerHeight }, Collider::Type::PLAYER_HITBOX, this);

	colBoxUp		= App->collisions->AddCollider({ (int)position.x, (int)position.y - speed, playerWidth, speed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxUpLeft	= App->collisions->AddCollider({ (int)position.x - diagonalSpeed, (int)position.y - diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxLeft		= App->collisions->AddCollider({ (int)position.x - speed, (int)position.y, speed, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDownLeft	= App->collisions->AddCollider({ (int)position.x - diagonalSpeed, (int)position.y + playerHeight + diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDown		= App->collisions->AddCollider({ (int)position.x, (int)position.y + playerHeight, playerWidth, speed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxDownRight = App->collisions->AddCollider({ (int)position.x + playerWidth, (int)position.y + playerHeight, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxRight		= App->collisions->AddCollider({ (int)position.x + playerWidth, (int)position.y, speed, playerHeight }, Collider::Type::PLAYER_COLLBOX, this);
	colBoxUpRight	= App->collisions->AddCollider({ (int)position.x, (int)position.y - diagonalSpeed, diagonalSpeed, diagonalSpeed }, Collider::Type::PLAYER_COLLBOX, this);


	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font3.png", lookupTable,2);


	
	return ret;

}

UpdateResult ModulePlayer::Update()
{
	////////////////////////////////////////////////////////
	// Moving the player with the camera scroll
	//App->player->position.x += 0;
	////////////////////////////////////////////////////////

	if (maxColliders == 0) maxColliders = App->collisions->GetMaxColliders();

	LOG("getting wall colliders: ")

		//for (int i = 0; i < maxColliders; i++)
		//{
		//
		//	LOG("getting wall colliderssss: ")
		//	if (App->collisions->colliders[i] != NULL 
		//		&& App->collisions->colliders[i]->type == Collider::Type::WALL
		//		&& wallArr[i].w != 0)
		//	{
		//	
		//		wallArr[i] = App->collisions->colliders[i]->rect;
		//		//LOG("collider i% x: i%", i, wallArr[i].x);
		//	
		//	}
		//	else {
		//	
		//		wallArr[i] = { -1,-1,-1,-1 };
		//	
		//	}
		//}

	keyUp    = App->input->keys[SDL_SCANCODE_W];
	keyLeft  = App->input->keys[SDL_SCANCODE_A];
	keyDown  = App->input->keys[SDL_SCANCODE_S];
	keyRight = App->input->keys[SDL_SCANCODE_D];

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
		bool move = true;

		for (int i = 0; i < 100; i++) 
		{
			if (position.x - speed < wallArr[i].x + wallArr[i].w) {
				move = false;
			}
			
		}
		if (move) position.x -= speed;

		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
		
		lastDirection = 3;
	}

	//right
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_REPEAT))
	{
		position.x += speed;

		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
		lastDirection = 7;
	}

	//Up
	if ((keyUp == KEY_STATE::KEY_REPEAT)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		position.y -= speed;

		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
		lastDirection = 1;
	}

	//Down
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_REPEAT)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		position.y += speed;

		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
		lastDirection = 5;
	}

	//DIAGONAL AXIS MOVEMENT
	
	//up-left
	if ((keyUp == KEY_STATE::KEY_REPEAT) 
		&& (keyLeft == KEY_STATE::KEY_REPEAT)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		position.x -= diagonalSpeed;
		position.y -= diagonalSpeed;

		if (currentAnimation != &upLeftAnim)
		{
			upLeftAnim.Reset();
			currentAnimation = &upLeftAnim;
		}
		lastDirection = 2;
	}

	//down-left
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_REPEAT)
		&& (keyDown == KEY_STATE::KEY_REPEAT)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		position.x -= diagonalSpeed;
		position.y += diagonalSpeed;

		if (currentAnimation != &downLeftAnim)
		{
			downLeftAnim.Reset();
			currentAnimation = &downLeftAnim;
		}

		lastDirection = 4;
	}

	//down-right
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_REPEAT)
		&& (keyRight == KEY_STATE::KEY_REPEAT))
	{
		position.x += diagonalSpeed;
		position.y += diagonalSpeed;

		if (currentAnimation != &downRightAnim)
		{
			downRightAnim.Reset();
			currentAnimation = &downRightAnim;
		}

		lastDirection = 6;
	}

	//up-right
	if ((keyUp == KEY_STATE::KEY_REPEAT)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_REPEAT))
	{
		position.x += diagonalSpeed;
		position.y -= diagonalSpeed;

		if (currentAnimation != &upRightAnim)
		{
			upRightAnim.Reset();
			currentAnimation = &upRightAnim;
		}
		lastDirection = 8;
	}

	//if (keyLeft == KEY_STATE::KEY_REPEAT) {
	//
	//	if (App->render->camera.x / SCREEN_SIZE > 475) {
	//
	//		if (lastDirection % 2 == 0)
	//		{
	//			if (position.x < (App->render->camera.x / SCREEN_SIZE + horizontalMargin)
	//				&& ((App->render->camera.x / SCREEN_SIZE - diagonalSpeed > 475))) App->render->camera.x -= diagonalSpeed * SCREEN_SIZE;
	//
	//		}
	//		else
	//		{
	//			if (position.x < (App->render->camera.x / SCREEN_SIZE + horizontalMargin)
	//				&& ((App->render->camera.x / SCREEN_SIZE - speed > 475))) App->render->camera.x -= speed * SCREEN_SIZE;
	//
	//		}
	//
	//	}
	//	else {
	//		while (App->render->camera.x / SCREEN_SIZE != 475) {
	//			App->render->camera.x--;
	//		}
	//	}
	//}

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

	//474

	if (App->render->camera.y <= 1156 * SCREEN_SIZE) {

		if (lastDirection % 2 == 0)
		{
			if (position.y <= (App->render->camera.y / SCREEN_SIZE + verticalMargin)) App->render->camera.y -= diagonalSpeed * SCREEN_SIZE;
		}
		else
		{
			if (position.y < (App->render->camera.y / SCREEN_SIZE + verticalMargin)) App->render->camera.y -= speed * SCREEN_SIZE;
		}
	}

	



	



	////////////////////////////////////////////////
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->PlayerBullet,0, position.x, position.y,lastDirection, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}
	////////////////////////////////////////////////

	// Idle Animations 

	//AXIS MOVEMENT
	
	
	 //DIAGONAL AXIS MOVEMENT


	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE)
		) {

		switch (lastDirection) {

		case 1:

			if (currentAnimation != &upIdleAnim) {
				upIdleAnim.Reset();
				currentAnimation = &upIdleAnim;
			}

			break;

		case 2:
			if (currentAnimation != &upLeftIdleAnim) {
				upLeftIdleAnim.Reset();
				currentAnimation = &upLeftIdleAnim;
			}
			break;

		case 3:
			if (currentAnimation != &leftIdleAnim) {
				leftIdleAnim.Reset();
				currentAnimation = &leftIdleAnim;
			}
			break;

		case 4:
			if (currentAnimation != &downLeftIdleAnim) {

				downLeftIdleAnim.Reset();
				currentAnimation = &downLeftIdleAnim;
			}
			break;

		case 5:
			if (currentAnimation != &downIdleAnim) {

				downIdleAnim.Reset();
				currentAnimation = &downIdleAnim;
			}
			break;

		case 6:
			if (currentAnimation != &downRightIdleAnim) {

				downRightIdleAnim.Reset();
				currentAnimation = &downRightIdleAnim;
			}
			break;

		case 7:
			if (currentAnimation != &rightIdleAnim) {

				rightIdleAnim.Reset();
				currentAnimation = &rightIdleAnim;
			}
			break;

		case 8:

			if (currentAnimation != &upRightIdleAnim) {

				upRightIdleAnim.Reset();
				currentAnimation = &upRightIdleAnim;
			}
			break;

		}


	}

	

	// Death Animations

	if (destroyed == true)
	{
		switch (lastDirection)
		{
		case 1:
			if (currentAnimation != &deathFromUpAnim) {

				deathFromUpAnim.Reset();
				currentAnimation = &deathFromUpAnim;
			}
			
			break;

		case 2:
			if (currentAnimation != &deathFromUpAnim) {

				deathFromUpAnim.Reset();
				currentAnimation = &deathFromUpAnim;
			}
			break;

		case 3:
			if (currentAnimation != &deathFromLeftAnim) {

				deathFromLeftAnim.Reset();
				currentAnimation = &deathFromLeftAnim;
			}
			break;

		case 4:
			if (currentAnimation != &deathFromLeftAnim) {

				deathFromLeftAnim.Reset();
				currentAnimation = &deathFromLeftAnim;
			}
			break;

		case 5:
			if (currentAnimation != &deathFromDownAnim) {

				deathFromDownAnim.Reset();
				currentAnimation = &deathFromDownAnim;
			}
			break;

		case 6:
			if (currentAnimation != &deathFromDownAnim) {

				deathFromDownAnim.Reset();
				currentAnimation = &deathFromDownAnim;
			}
			break;

		case 7:
			if (currentAnimation != &deathFromRightAnim) {

				deathFromRightAnim.Reset();
				currentAnimation = &deathFromRightAnim;
			}
			break;

		case 8:
			if (currentAnimation != &deathFromRightAnim) {

				deathFromRightAnim.Reset();
				currentAnimation = &deathFromRightAnim;
			}
			break;


		}
	}


	
	////////////////////////////////////////////
	hitBox->SetPos(position.x, position.y);
	
	colBoxUp		->SetPos(position.x, position.y - speed);
	colBoxUpLeft	->SetPos(position.x - diagonalSpeed, position.y - diagonalSpeed);
	colBoxLeft		->SetPos(position.x - speed, position.y);
	colBoxDownLeft	->SetPos(position.x - diagonalSpeed, position.y + playerHeight);
	colBoxDown		->SetPos(position.x, position.y + playerHeight);
	colBoxDownRight	->SetPos(position.x + playerWidth, position.y + playerHeight);
	colBoxRight		->SetPos(position.x + playerWidth, position.y);
	colBoxUpRight	->SetPos(position.x + playerWidth, position.y - diagonalSpeed);

	currentAnimation->Update();

	if (destroyed)
	{
		exitCountdown--;
		if (exitCountdown <= 0)
			return UpdateResult::UPDATE_STOP;
	}
	
	////////////////////////////////////////////
	
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ModulePlayer::PostUpdate()
{
	if (destroyed != true)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect,1);
	}

	App->fonts->BlitText(20, 20,scoreFont,scoreText);

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == hitBox && destroyed == false)
	{
		
	}

	
}




