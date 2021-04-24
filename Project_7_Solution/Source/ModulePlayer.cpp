#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	// idle animations - just one sprite

	upIdleAnim.PushBack({ 66, 1, 32, 14 });
	upIdleAnim.PushBack({ 66, 1, 32, 14 });
	upIdleAnim.loop = true;
	upIdleAnim.speed = 0.1f;

	upRightIdleAnim.PushBack({ 66, 1, 32, 14 });
	upRightIdleAnim.PushBack({ 66, 1, 32, 14 });
	upRightIdleAnim.loop = true;
	upRightIdleAnim.speed = 0.1f;

	rightIdleAnim.PushBack({ 66, 1, 32, 14 });
	rightIdleAnim.PushBack({ 66, 1, 32, 14 });
	rightIdleAnim.loop = true;
	rightIdleAnim.speed = 0.1f;

	downRightIdleAnim.PushBack({ 66, 1, 32, 14 });
	downRightIdleAnim.PushBack({ 66, 1, 32, 14 });
	downRightIdleAnim.loop = true;
	downRightIdleAnim.speed = 0.1f;

	downIdleAnim.PushBack({ 66, 1, 32, 14 });
	downIdleAnim.PushBack({ 66, 1, 32, 14 });
	downIdleAnim.loop = true;
	downIdleAnim.speed = 0.1f;

	downLeftIdleAnim.PushBack({ 66, 1, 32, 14 });
	downLeftIdleAnim.PushBack({ 66, 1, 32, 14 });
	downLeftIdleAnim.loop = true;
	downLeftIdleAnim.speed = 0.1f;

	leftIdleAnim.PushBack({ 66, 1, 32, 14 });
	leftIdleAnim.PushBack({ 66, 1, 32, 14 });
	leftIdleAnim.loop = true;
	leftIdleAnim.speed = 0.1f;

	upLeftIdleAnim.PushBack({ 66, 1, 32, 14 });
	upLeftIdleAnim.PushBack({ 66, 1, 32, 14 });
	upLeftIdleAnim.loop = true;
	upLeftIdleAnim.speed = 0.1f;


	// Hit Animations
	
	bulletHitAnim.PushBack({ 66, 1, 32, 14 });
	bulletHitAnim.PushBack({ 66, 1, 32, 14 });
	upLeftIdleAnim.loop = false;
	upLeftIdleAnim.speed = 0.1f;

	explosionHitAnim.PushBack({ 66, 1, 32, 14 });
	explosionHitAnim.PushBack({ 66, 1, 32, 14 });
	upLeftIdleAnim.loop = false;
	upLeftIdleAnim.speed = 0.1f;

	// Death Animations 

	deathUpLeftAnim.PushBack({ 66, 1, 32, 14 });
	deathUpLeftAnim.PushBack({ 66, 1, 32, 14 });
	deathUpLeftAnim.loop = false;
	deathUpLeftAnim.speed = 0.1f;

	deathUpRightAnim.PushBack({ 66, 1, 32, 14 });
	deathUpRightAnim.PushBack({ 66, 1, 32, 14 });
	deathUpRightAnim.loop = false;
	deathUpRightAnim.speed = 0.1f;


	deathDownLeftAnim.PushBack({ 66, 1, 32, 14 });
	deathDownLeftAnim.PushBack({ 66, 1, 32, 14 });
	deathDownLeftAnim.loop = false;
	deathDownLeftAnim.speed = 0.1f;


	deathDownRightAnim.PushBack({ 66, 1, 32, 14 });
	deathDownRightAnim.PushBack({ 66, 1, 32, 14 });
	deathDownRightAnim.loop = false;
	deathDownRightAnim.speed = 0.1f;



	// Move Animations

	upAnim.PushBack({ 100, 1, 32, 14 });
	upAnim.PushBack({ 132, 0, 32, 14 });
	upAnim.loop = true;
	upAnim.speed = 0.1f;


	downAnim.PushBack({ 33, 1, 32, 14 });
	downAnim.PushBack({ 0, 1, 32, 14 });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	
	leftAnim.PushBack({ 33, 1, 32, 14 });
	leftAnim.PushBack({ 0, 1, 32, 14 });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	
	rightAnim.PushBack({ 33, 1, 32, 14 });
	rightAnim.PushBack({ 0, 1, 32, 14 });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	
	upLeftAnim.PushBack({ 33, 1, 32, 14 });
	upLeftAnim.PushBack({ 0, 1, 32, 14 });
	upLeftAnim.loop = true;
	upLeftAnim.speed = 0.1f;

	
	upRightAnim.PushBack({ 33, 1, 32, 14 });
	upRightAnim.PushBack({ 0, 1, 32, 14 });
	upRightAnim.loop = true;
	upRightAnim.speed = 0.1f;

	
	downLeftAnim.PushBack({ 33, 1, 32, 14 });
	downLeftAnim.PushBack({ 0, 1, 32, 14 });
	downLeftAnim.loop = true;
	downLeftAnim.speed = 0.1f;

	
	downRightAnim.PushBack({ 33, 1, 32, 14 });
	downRightAnim.PushBack({ 0, 1, 32, 14 });
	downRightAnim.loop = true;
	downRightAnim.speed = 0.1f;

	

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/ship.png");
	currentAnimation = &downIdleAnim;

	laserFx = App->audio->LoadFx("Assets/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/explosion.wav");

	position.x = 150;
	position.y = 120;

	collider = App->collisions->AddCollider({ position.x, position.y, 32, 16 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{
	////////////////////////////////////////////////////////
	// Moving the player with the camera scroll
	//App->player->position.x += 0;
	////////////////////////////////////////////////////////


	// Move the player in all posible direction 

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;

		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;

		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;

		if (currentAnimation != &downAnim)
		{
			downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;

		if (currentAnimation != &upAnim)
		{
			upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		position.x += speed;

		if (currentAnimation != &upRightAnim)
		{
			upRightAnim.Reset();
			currentAnimation = &upRightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
		position.x -= speed;

		if (currentAnimation != &upLeftAnim)
		{
			upLeftAnim.Reset();
			currentAnimation = &upLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		position.x -= speed;

		if (currentAnimation != &downLeftAnim)
		{
			downLeftAnim.Reset();
			currentAnimation = &downLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
		position.x += speed;

		if (currentAnimation != &downRightAnim)
		{
			downRightAnim.Reset();
			currentAnimation = &downRightAnim;
		}
	}



	////////////////////////////////////////////////
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		App->audio->PlayFx(laserFx);
	}
	////////////////////////////////////////////////

	// Idle Animations 

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)
	{
		downIdleAnim.Reset();
		currentAnimation = &downIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		|| App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	{
		downRightIdleAnim.Reset();
		currentAnimation = &downRightIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	{
		rightIdleAnim.Reset();
		currentAnimation = &rightIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
	{
		upRightIdleAnim.Reset();
		currentAnimation = &upRightIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
	{
		upIdleAnim.Reset();
		currentAnimation = &upIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	{
		upLeftIdleAnim.Reset();
		currentAnimation = &upLeftIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	{
		leftIdleAnim.Reset();
		currentAnimation = &leftIdleAnim;
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	{
		downLeftIdleAnim.Reset();
		currentAnimation = &downLeftIdleAnim;
	}

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
			return update_status::UPDATE_STOP;
	}
	
	////////////////////////////////////////////
	
	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (destroyed != true)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect,0);
	}

	return update_status::UPDATE_CONTINUE;
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