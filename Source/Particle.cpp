#include "Particle.h"

#include "Collider.h"
#include "Enemy_Soldier.h"
#include "ModuleParticles.h"
#include "Application.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
	direction = 0;
	id = 0;
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed),
										frameCount(p.frameCount), lifetime(p.lifetime), id(p.id), direction(p.direction)
{

}

Particle::~Particle()
{
	if (collider != nullptr && collider->pendingToDelete == false && collider->rect.x != NULL)
  		collider->pendingToDelete = true;
} 

bool Particle::Update()
 {
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime) {
				ret = false;

				switch (id)
				{

				case 0:

					App->particles->AddParticle(App->particles->BulletEnd, 0, position.x - 3, position.y - 3, 0, Collider::NONE);

					break;

				case 1:

					App->particles->AddParticle(App->particles->BulletEnd, 0, position.x - 3, position.y - 3, 0, Collider::NONE);

					break;

				case 2:

					App->particles->AddParticle(App->particles->BulletEnd, 0, position.x - 3, position.y - 3, 0, Collider::NONE);

					break;
				default:


					break;
				}
			}

		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished())
			ret = false;

		switch (id) {

		case 0: //player bullet

			switch (direction) {

			case 1:

				position.y -= speed.y;
				position.x += 0;

				break;

			case 2:

				position.y -= speed.y;
				position.x -= speed.x;

				break;

			case 3:

				position.y -= 0;
				position.x -= speed.x;

				break;

			case 4:

				position.y += speed.y;
				position.x -= speed.x;

				break;

			case 5:

				position.y += speed.y;
				position.x -= 0;

				break;

			case 6:

				position.y += speed.y;
				position.x += speed.x;

				break;

			case 7:

				position.y += 0;
				position.x += speed.x;

				break;

			case 8:

				position.y -= speed.y;
				position.x += speed.x;

				break;

			}

			break;

		case 1: // Enemy Bullet

			if (direction == 1)
			{
				counter = 0;
				_speedy = 0.0f;
				_speedx = 0.0f;

				if (counter == 0)
				{
					//_speedy = speed.y * App->enemies->ENEMY_SOLDIER->resultY;
					//_speedx = speed.x * App->enemies->ENEMY_SOLDIER->resultX;

					counter++;
				}
				else
				{
					position.y += _speedy;
					position.x += _speedx;
				}
				
			}
		case 2: // Enemy Bullet

			switch(direction)
			{

			case 0:

				position.y += 0;
				position.x += speed.x;

				break;

			case 1:

				position.y -= speed.y / 2;
				position.x += speed.x;

				break;

			case 2:

				position.y -= speed.y;
				position.x += speed.x;

				break;

			case 3:
				position.y -= speed.y;
				position.x += speed.x / 2;

				break;

			case 4:

				position.y -= speed.y;
				position.x -= 0;

				break;

			case 5:

				position.y -= speed.y / 2;
				position.x -= speed.x;

				break;

			case 6:

				position.y -= speed.y;
				position.x -= speed.x;

				break;

			case 7:

				position.y -= speed.y / 2;
				position.x -= speed.x;

				break;

			case 8:

				position.y -= 0;
				position.x -= speed.x;

				break;

			case 9:

				position.y += speed.y / 2;
				position.x -= speed.x;

				break;

			case 10:

				position.y -= speed.y;
				position.x += speed.x;

				break;

			case 11:

				position.y += speed.y / 2;
				position.x += speed.x;

				break;

			case 12:

				position.y += speed.y;
				position.x += 0;

				break;

			case 13:

				position.y += speed.y / 2;
				position.x += speed.x;

				break;

			case 14:

				position.y += speed.y;
				position.x += speed.x;

				break;

			case 15:

				position.y += speed.y / 2;
				position.x += speed.x;

				break;

			default:

				break;
			}

			default:

				position += speed;

			break;
		}

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}
else {
	
}

	return ret;
}