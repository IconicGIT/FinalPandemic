#include "Boss1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include <math.h>
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include <time.h>

#include <math.h>
Enemy_Boss01::Enemy_Boss01(int x, int y) : Enemy(x, y)
{
	float AnimSpeed = 0.05f;
	
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
	collider = App->collisions->AddCollider({ 0, 0, 24, 40 }, Collider::Type::ENEMY, (Module*)App->enemies);


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
		}

		

		pushTimer = pushTimerReference;
	}
	else {
		pushTimer--;
	}

	if (currentAnim == &BossShootingAnim) {

		if (movement == MovementStage::SHOOT)
		{
			if (shootTimer <= 0) {

				int bulletType = iRandomRange(0, 1);



				switch (bulletType)
				{

				case 0:
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 19, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 21, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 23, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 24, position.y + 107, Collider::ENEMY_SHOT);

					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 99, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 101, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 103, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 105, position.y + 107, Collider::ENEMY_SHOT);

					break;
				case 1:
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 19, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 22, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 23, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletL, 0, position.x + 25, position.y + 107, Collider::ENEMY_SHOT);

					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 99, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 102, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 103, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(App->particles->Boss1BulletR, 0, position.x + 105, position.y + 107, Collider::ENEMY_SHOT);

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
		else if (movement == MovementStage::MOVE)
		{

			int bulletLifeShortener = 2;
			Particle bullets[2];
			bullets[0] = App->particles->Boss1BulletL;
			bullets[1] = App->particles->Boss1BulletR;

			if (shootTimer <= 0) {

				int bulletType = iRandomRange(0, 1);

				bullets[0].lifetime -= bulletLifeShortener;
				bullets[1].lifetime -= bulletLifeShortener;


				switch (bulletType)
				{

				case 0:

					App->particles->AddParticle(bullets[0], 0, position.x + 19, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[0], 0, position.x + 21, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[0], 0, position.x + 23, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[0], 0, position.x + 24, position.y + 107, Collider::ENEMY_SHOT);

					App->particles->AddParticle(bullets[1], 0, position.x + 99, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[1], 0, position.x + 101, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[1], 0, position.x + 103, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[1], 0, position.x + 105, position.y + 107, Collider::ENEMY_SHOT);

					break;
				case 1:
					App->particles->AddParticle(bullets[0], 0, position.x + 19, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[0], 0, position.x + 22, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[0], 0, position.x + 23, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[0], 0, position.x + 25, position.y + 107, Collider::ENEMY_SHOT);

					App->particles->AddParticle(bullets[1], 0, position.x + 99, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[1], 0, position.x + 102, position.y + 107, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[1], 0, position.x + 103, position.y + 106, Collider::ENEMY_SHOT);
					App->particles->AddParticle(bullets[1], 0, position.x + 105, position.y + 107, Collider::ENEMY_SHOT);

					break;

				default:
					break;
				}
				shootTimer = shootTimerReference;
				bulletLifeShortener += 2;
			}
			else {
				shootTimer--;
			}

		}
	}

	LOG("stage: %i", movement);

	//LOG(" x: %f, y: %f", position.x, position.y);
	
	if (movement != MovementStage::ENTRANCE) a++;

	path.Update();
	position.x = spawnPos.x + path.GetRelativePosition().x;
	

	position.y = spawnPos.y + path.GetRelativePosition().y + bobbingAmplitude * sin((double)a * 0.05f);
	
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
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

