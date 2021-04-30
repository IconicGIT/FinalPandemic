#include "ModulePlayer.h"

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

	// animation idle up
	upIdleAnim.PushBack({ 147, 8, 21, 41 });
	upIdleAnim.PushBack({ 178, 8, 22, 42 });
	upIdleAnim.loop = true;
	upIdleAnim.speed = idleSpeed;

	// animation idle up-left
	upLeftIdleAnim.PushBack({ 143, 58, 32, 14 });
	upLeftIdleAnim.PushBack({ 173, 58, 20, 38 });
	upLeftIdleAnim.loop = true;
	upLeftIdleAnim.speed = idleSpeed;

	//animation idle left
	leftIdleAnim.PushBack({ 141, 102, 23, 41 });
	leftIdleAnim.PushBack({ 171, 102, 21, 40 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = idleSpeed;
	
	//animation idle down-left
	downLeftIdleAnim.PushBack({ 138, 149, 20, 41 });
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
		hitFromUpAnim.speed = 0.1f;

		//left
		hitFromLeftAnim.PushBack({ 420, 437, 23, 40 });
		hitFromLeftAnim.loop = false;
		hitFromLeftAnim.speed = 0.1f;

		//down
		hitFromDownAnim.PushBack({ 456, 436, 24, 39 });
		hitFromDownAnim.loop = false;
		hitFromDownAnim.speed = 0.1f;

		//right
		hitFromRightAnim.PushBack({ 457, 393, 23, 40 });
		hitFromRightAnim.loop = false;
		hitFromRightAnim.speed = 0.1f;

	//rolling when damaged
	rollAnim.PushBack({ 150, 384, 27, 26 });
	rollAnim.PushBack({ 181, 382, 29, 27 });
	rollAnim.loop = false;
	rollAnim.speed = 0.1f;

	// Death Animations

	deathFromLeftAnim.PushBack({ 216, 448, 24, 35 });
	deathFromLeftAnim.PushBack({ 245, 450, 23, 35 });
	deathFromLeftAnim.PushBack({ 272, 452, 31, 35 });
	deathFromLeftAnim.PushBack({ 305, 457, 37, 31 });
	deathFromLeftAnim.loop = false;
	deathFromLeftAnim.speed = 0.2f;

	deathFromRightAnim.PushBack({ 10, 397, 26, 41 });
	deathFromRightAnim.PushBack({ 41, 394, 26, 41 });
	deathFromRightAnim.PushBack({ 73, 392, 28, 41 });
	deathFromRightAnim.PushBack({ 111, 383, 35, 51 });
	deathFromRightAnim.loop = false;
	deathFromRightAnim.speed = 0.2f;

	deathFromUpAnim.PushBack({ 5, 443, 23, 38 });
	deathFromUpAnim.PushBack({ 36, 440, 48, 41 });
	deathFromUpAnim.PushBack({ 87, 437, 30, 41 });
	deathFromUpAnim.PushBack({ 125, 437, 30, 41 });
	deathFromUpAnim.loop = false;
	deathFromUpAnim.speed = 0.2f;

	deathFromDownAnim.PushBack({ 212, 394, 28, 45 });
	deathFromDownAnim.PushBack({ 247, 396, 43, 47 });
	deathFromDownAnim.PushBack({ 294, 405, 22, 37 });
	deathFromDownAnim.PushBack({ 321, 406, 27, 26 });
	deathFromDownAnim.PushBack({ 359, 396, 40, 46 });
	deathFromDownAnim.loop = false;
	deathFromDownAnim.speed = 0.05f;



	// Move Animations

	upAnim.PushBack({ 12, 7, 13, 42 });
	upAnim.PushBack({ 44, 7, 13, 42 });
	upAnim.PushBack({ 76, 7, 13, 42 });
	upAnim.PushBack({ 108, 7, 13, 42 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	upLeftAnim.PushBack({ 8, 54, 26, 42 });
	upLeftAnim.PushBack({ 39, 54, 26, 42 });
	upLeftAnim.PushBack({ 70, 54, 26, 42 });
	upLeftAnim.PushBack({ 103, 54, 26, 42 });
	upLeftAnim.loop = true;
	upLeftAnim.speed = 0.1f;
	
	leftAnim.PushBack({ 6, 103, 31, 41 });
	leftAnim.PushBack({ 39, 103, 31, 41 });
	leftAnim.PushBack({ 72, 103, 31, 41 });
	leftAnim.PushBack({ 103, 103, 31, 41 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	downLeftAnim.PushBack({ 11, 149, 25, 39 });
	downLeftAnim.PushBack({ 44, 149, 25, 39 });
	downLeftAnim.PushBack({ 77, 149, 25, 39 });
	downLeftAnim.PushBack({ 108, 149, 25, 39 });
	downLeftAnim.loop = true;
	downLeftAnim.speed = 0.1f;

	downAnim.PushBack({ 17, 194, 17, 40 });
	downAnim.PushBack({ 49, 194, 17, 40 });
	downAnim.PushBack({ 80, 194, 17, 40 });
	downAnim.PushBack({ 113, 194, 17, 40 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;
	
	downRightAnim.PushBack({ 12, 240, 25, 39 });
	downRightAnim.PushBack({ 44, 240, 25, 39 });
	downRightAnim.PushBack({ 72, 240, 25, 39 });
	downRightAnim.PushBack({ 108, 240, 25, 39 });
	downRightAnim.loop = true;
	downRightAnim.speed = 0.1f;

	rightAnim.PushBack({ 8, 285, 31, 38 });
	rightAnim.PushBack({ 43, 285, 27, 41 });
	rightAnim.PushBack({ 71, 285, 30, 36 });
	rightAnim.PushBack({ 108, 285, 26, 36 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	upRightAnim.PushBack({ 8, 332, 26, 42 });
	upRightAnim.PushBack({ 40, 332, 26, 42 });
	upRightAnim.PushBack({ 68, 332, 26, 42 });
	upRightAnim.PushBack({ 103, 332, 26, 42 });
	upRightAnim.loop = true;
	upRightAnim.speed = 0.1f;

	

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/character_sprites.png");
	currentAnimation = &downIdleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 150;
	position.y = 120;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

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

	keyUp    = App->input->keys[SDL_SCANCODE_W];
	keyLeft  = App->input->keys[SDL_SCANCODE_A];
	keyDown  = App->input->keys[SDL_SCANCODE_S];
	keyRight = App->input->keys[SDL_SCANCODE_D];






	// Move the player in all posible direction 
	// 
	//AXIS MOVEMENT
	if ((keyUp == KEY_STATE::KEY_IDLE)
		&& (keyLeft == KEY_STATE::KEY_REPEAT)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& (keyRight == KEY_STATE::KEY_IDLE))
	{
		position.x -= speed;

		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
		lastHorizontalKey = keyLeft;
		lastVerticalKey = KEY_STATE::KEY_IDLE;
	}

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
		lastHorizontalKey = keyRight;
		lastVerticalKey = KEY_STATE::KEY_IDLE;
	}

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
		lastHorizontalKey = KEY_STATE::KEY_IDLE;
		lastVerticalKey = keyUp;
	}

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
		lastHorizontalKey = KEY_STATE::KEY_IDLE;
		lastVerticalKey = keyDown;
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
		lastHorizontalKey = keyLeft;
		lastVerticalKey = keyUp;
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
		lastHorizontalKey = keyLeft;
		lastVerticalKey = keyDown;
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
		lastHorizontalKey = keyRight;
		lastVerticalKey = keyDown;
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
		lastHorizontalKey = keyRight;
		lastVerticalKey = keyUp;
	}




	//if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	//{
	//	position.x += speed;
	//
	//	if (currentAnimation != &rightAnim)
	//	{
	//		rightAnim.Reset();
	//		currentAnimation = &rightAnim;
	//	}
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	//{
	//	position.y += speed;
	//
	//	if (currentAnimation != &downAnim)
	//	{
	//		downAnim.Reset();
	//		currentAnimation = &downAnim;
	//	}
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	//{
	//	position.y -= speed;
	//
	//	if (currentAnimation != &upAnim)
	//	{
	//		upAnim.Reset();
	//		currentAnimation = &upAnim;
	//	}
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	//{
	//	position.y -= speed;
	//	position.x += speed;
	//
	//	if (currentAnimation != &upRightAnim)
	//	{
	//		upRightAnim.Reset();
	//		currentAnimation = &upRightAnim;
	//	}
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	//{
	//	position.y -= speed;
	//	position.x -= speed;
	//
	//	if (currentAnimation != &upLeftAnim)
	//	{
	//		upLeftAnim.Reset();
	//		currentAnimation = &upLeftAnim;
	//	}
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	//{
	//	position.y += speed;
	//	position.x -= speed;
	//
	//	if (currentAnimation != &downLeftAnim)
	//	{
	//		downLeftAnim.Reset();
	//		currentAnimation = &downLeftAnim;
	//	}
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	//{
	//	position.y += speed;
	//	position.x += speed;
	//
	//	if (currentAnimation != &downRightAnim)
	//	{
	//		downRightAnim.Reset();
	//		currentAnimation = &downRightAnim;
	//	}
	//}



	////////////////////////////////////////////////
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}
	////////////////////////////////////////////////

	// Idle Animations 

	//AXIS MOVEMENT
	if (   !(keyUp == KEY_STATE::KEY_REPEAT)
		&& (keyLeft == KEY_STATE::KEY_IDLE)
		&& !(keyDown == KEY_STATE::KEY_REPEAT)
		&& !(keyRight == KEY_STATE::KEY_REPEAT)
		)
	{
		leftIdleAnim.Reset();
		currentAnimation = &leftIdleAnim;
	}

	if (   !(keyUp == KEY_STATE::KEY_REPEAT)
		&& !(keyLeft == KEY_STATE::KEY_REPEAT)
		&& !(keyDown == KEY_STATE::KEY_REPEAT)
		&& (keyRight == KEY_STATE::KEY_IDLE)
		)
	{
		rightIdleAnim.Reset();
		currentAnimation = &rightIdleAnim;
	}

	if (   (keyUp == KEY_STATE::KEY_IDLE)
		&& !(keyLeft == KEY_STATE::KEY_REPEAT)
		&& !(keyDown == KEY_STATE::KEY_REPEAT)
		&& !(keyRight == KEY_STATE::KEY_REPEAT)
		)
	{
		upIdleAnim.Reset();
		currentAnimation = &upIdleAnim;
	}

	if (   !(keyUp == KEY_STATE::KEY_REPEAT)
		&& !(keyLeft == KEY_STATE::KEY_REPEAT)
		&& (keyDown == KEY_STATE::KEY_IDLE)
		&& !(keyRight == KEY_STATE::KEY_REPEAT)
		)
	{
		downIdleAnim.Reset();
		currentAnimation = &downIdleAnim;
	}
	 //DIAGONAL AXIS MOVEMENT
	
	 //up left
	if ((App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_UP) && (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_UP))
	{
		upLeftIdleAnim.Reset();
		currentAnimation = &upLeftIdleAnim;
	}


	//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)
	//{
	//	downIdleAnim.Reset();
	//	currentAnimation = &downIdleAnim;
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	//	|| App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	//{
	//	downRightIdleAnim.Reset();
	//	currentAnimation = &downRightIdleAnim;
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	//{
	//	rightIdleAnim.Reset();
	//	currentAnimation = &rightIdleAnim;
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
	//	&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	//{
	//	upRightIdleAnim.Reset();
	//	currentAnimation = &upRightIdleAnim;
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
	//{
	//	upIdleAnim.Reset();
	//	currentAnimation = &upIdleAnim;
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
	//	&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	//{
	//	upLeftIdleAnim.Reset();
	//	currentAnimation = &upLeftIdleAnim;
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	//{
	//	leftIdleAnim.Reset();
	//	currentAnimation = &leftIdleAnim;
	//}
	//
	//if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	//	&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	//{
	//	downLeftIdleAnim.Reset();
	//	currentAnimation = &downLeftIdleAnim;
	//}

	// Hit Animations  // Need enemy Particles or Player Life lower

	//if (ModulePlayer::OnCollision(Collider * Collider::Type::PLAYER, Collider * Collider::Type::ENEMY_SHOT))
	//{
	//
	//}

	// Death Animations

	if (destroyed == true)
	{
		// Diferentes orientaciones de la animacion de muerte.
	}


	
	////////////////////////////////////////////
	collider->SetPos(position.x, position.y);

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
		App->render->Blit(texture, position.x, position.y, &rect,0);
	}

	App->fonts->BlitText(20, 20,scoreFont, "Test Text");

	return UpdateResult::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::NONE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::NONE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::NONE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::NONE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
	}
}