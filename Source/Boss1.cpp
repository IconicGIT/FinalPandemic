#include "Boss1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include <math.h>
#include "ModuleParticles.h"

#include "ModuleLevel_1.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include <time.h>

#include <math.h>

Enemy_Boss01::Enemy_Boss01(int x, int y) : Enemy(x, y)
{
	float AnimSpeed = 0.05f;
	bossShotFX = App->audio->LoadFx("Assets/Fx/gun_shot02.2.wav");
	bossDefeatedFX = App->audio->LoadFx("Assets/Fx/explosion_03.wav");
	App->audio->PlayMusic("Assets/Music/boss_repeat.ogg", 1.0f);

	BossIdleAnim.PushBack({ 0,0,128,158 });

	BossShootingAnim.PushBack({ 0,0,128,158 });
	BossShootingAnim.PushBack({ 128,0,128,158 });
	BossShootingAnim.PushBack({ 0,0,128,158 });
	BossShootingAnim.PushBack({ 256,0,128,158 });
	BossShootingAnim.loop = true;
	BossShootingAnim.speed = 0.3f;

	
	
	// Death animation



	// Collider

	currentAnim = &BossIdleAnim;
	collider = App->collisions->AddCollider({ (int)position.x + 10, (int)position.y + 5, 128, 120 }, Collider::Type::ENEMY, (Module*)App->enemies);
	lifeBar = { 384,0,21,12 };

	timeAlive = 1000;
	inmortal = true;
	movement = MovementStage::ENTRANCE;

	pivot = { 1050,30 };
	pushTimerReference = 5*50 + 50;
	pushTimer = pushTimerReference;
	path.loop = false;
	path.PushBack({ 0,0.3f }, 1);
	shootWhileMoving = false;
	shootTimerReference = 4;
	srand(time(0));
	bobbingAmplitude = 0.2f;

	lifePoints = 300;

	particleTimerReference = 4;
	particleTimer = particleTimerReference;

	counter++;
}

void Enemy_Boss01::Update()
{
	////////////////////////////////////////////////////
	path.Update();
	
	//playerPosition = (fPoint)App->player->position;
	
	float pushX;
	float pushY;

	fPoint movementRangeX;
	fPoint movementRangeY;
	

	if (lifePoints <= 0 && movement != MovementStage::DEFEATED) 
	{
		path.Reset();
		movement = MovementStage::DEFEATED;
		pushTimerReference = 180;
		pushTimer = pushTimerReference;
		currentAnim = &BossIdleAnim;
	}


	if (pushTimer <= 0)
	{

		switch (movement) {
		case MovementStage::ENTRANCE:
			pushTimerReference = 2 * 60;
			
			path.PushBack({ 0, 0 }, pushTimerReference);
			currentAnim = &BossIdleAnim;
			
			bobbingAmplitude = position.y;
			shootWhileMoving = (bool)iRandomRange(0, 1);
			movement = MovementStage::MOVE;
			break;

		case MovementStage::MOVE:
			pushTimerReference = 60;
			if (shootWhileMoving) {
				currentAnim = &BossShootingAnim;

				//shoot
			}
			else {
				currentAnim = &BossIdleAnim;
			}
			
			movementRangeX = { 0.2f,0.7f };
			movementRangeY = { 0.1f,0.3f };

			if (position.x < pivot.x) {
				pushX = fRandomRange(movementRangeX.x, movementRangeX.y);
				//LOG("moving right")
			}
			if (position.x > pivot.x) {
				pushX = -fRandomRange(movementRangeX.x, movementRangeX.y);
				//LOG("moving left")
			}
			if (position.y < pivot.y) {
				pushY = fRandomRange(movementRangeY.x, movementRangeY.y);
				//LOG("moving down")
			}
			if (position.y > pivot.y) {
				pushY = -fRandomRange(movementRangeY.x, movementRangeY.y);
				//LOG("moving up")
			}

			path.PushBack({ pushX,pushY }, pushTimerReference);
			movement = MovementStage::SHOOT;
			break;

		case MovementStage::SHOOT:
			path.Reset();
			BossIdleAnim.Reset();
			currentAnim = &BossShootingAnim;


			pushTimerReference = 120;


			if (!shootWhileMoving) shootWhileMoving = (bool)iRandomRange(0, 1);
			else shootWhileMoving = false;

			path.PushBack({ 0,0 }, pushTimerReference);
			movement = MovementStage::MOVE;
			break;
		
		case MovementStage::DEFEATED:
			path.Reset();
			path.PushBack({ 0,0.3f }, pushTimerReference);

			


			break;
		
		
		
		
		}

		

		pushTimer = pushTimerReference;
	}
	else {
		pushTimer--;
	}

	if (movement == MovementStage::DEFEATED)
	{
		App->audio->PlayFx(bossDefeatedFX);
		if (particleTimer <= 0) {
			particleTimer = particleTimerReference;
			for (int i = 0; i < iRandomRange(1, 3); i++)
			{

				App->particles->AddParticle(

					App->particles->Explosion2Big,
					0,
					iRandomRange(position.x, position.x + collider->rect.w - 25),
					iRandomRange(position.y + 10, position.y + collider->rect.h + 15),
					0,
					Collider::NONE,
					iRandomRange(0, 4));


			}
		}
		else
		{
			particleTimer--;
		}
	}


	if (currentAnim == &BossShootingAnim) {

		if (movement == MovementStage::SHOOT || movement == MovementStage::MOVE)
		{
			App->audio->PlayFx(bossShotFX);
			
			if (shootTimer <= 0) {

				int bulletType = iRandomRange(0, 1);



				switch (bulletType)
				{

				case 0:
					
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 19, position.y + 106,0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 21, position.y + 107, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 23, position.y + 106, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 24, position.y + 107, 0, Collider::ENEMY_SHOT);
					
					
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 99, position.y + 106, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 101, position.y + 107, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 103, position.y + 106, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 105, position.y + 107, 0, Collider::ENEMY_SHOT);
					
					break;
				case 1:
					
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 19, position.y + 106, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 22, position.y + 107, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 23, position.y + 106, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, -1, position.x + 25, position.y + 107, 0, Collider::ENEMY_SHOT);
					
					
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 99, position.y + 106, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 102, position.y + 107, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 103, position.y + 106, 0, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, -1, position.x + 105, position.y + 107, 0, Collider::ENEMY_SHOT);
					
					break;

				default:
					break;
				}
				shootTimer = shootTimerReference;
			}
			else {
				shootTimer--;
			}

		}
	}


	if (App->player->backTimer < -60) {
		inmortal = false;
		timeAlive = 0;
		
	}



	//LOG("stage: %i", movement);

	//LOG(" x: %f, y: %f", position.x, position.y);
	
	if (movement != MovementStage::ENTRANCE && movement != MovementStage::DEFEATED) a++;

	path.Update();
	position.x = spawnPos.x + path.GetRelativePosition().x;
	

	position.y = spawnPos.y + path.GetRelativePosition().y + bobbingAmplitude * sin((double)a * 0.05f);
	collider->SetPos((int)position.x + 10, (int)position.y + 5);
	
	


	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Boss01::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));

	//show life bar

	if (lifePoints > 0) {
		App->render->Blit(texture, 184, 26, &lifeBar, 0, true);
	}
	if (lifePoints >= 20 * 3) {
		App->render->Blit(texture, 184 - 24, 26, &lifeBar, 0, true);
	}
	if (lifePoints >= 40 * 3) {
		App->render->Blit(texture, 184 - 24 * 2, 26, &lifeBar, 0, true);
	}
	if (lifePoints >= 60 * 3) {
		App->render->Blit(texture, 184 - 24 * 3, 26, &lifeBar, 0, true);
	}
	if (lifePoints >= 80 * 3) {
		App->render->Blit(texture, 184 - 24 * 4, 26, &lifeBar, 0, true);
	}

}


int Enemy_Boss01::iRandomRange(int value01, int value02) {

	if (value01 > value02) {

		int i = value01;
		value01 = value02;
		value02 = i;

	}
	return(rand() % (value02 - value01 + 1) + value01);

}

float Enemy_Boss01::fRandomRange(float value01, float value02) {

	if (value01 > value02) {

		float i = value01;
		value01 = value02;
		value02 = i;

	}
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = value02 - value01;
	float r = random * diff;
	return value01 + r;

}

void Enemy_Boss01::OnCollision(Collider* collider)
{
	//LOG("collision");

	switch (collider->type)
	{
	case Collider::PLAYER_SHOT:

		lifePoints--;
		if (collider->pendingToDelete != false) collider->pendingToDelete = true;

		break;


	default:
		break;
	}

	//App->particles->AddParticle(App->particles->explosion,App->particles->explosion.id, position.x, position.y, App->particles->explosion.direction);
	//App->audio->PlayFx(destroyedFx);
}
