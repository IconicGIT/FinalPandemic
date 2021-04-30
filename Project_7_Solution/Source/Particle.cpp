#include "Particle.h"

#include "Collider.h"

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
	if (collider != nullptr)
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
			if (frameCount >= lifetime)
				ret = false;
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

		}

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}