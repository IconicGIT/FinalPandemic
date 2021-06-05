#include "Enemy_Car.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"

Enemy_Car::Enemy_Car(int x, int y) : Enemy(x, y)
{


	carDirectionRect[0] .PushBack({ 0,0,100,100 });
	carDirectionRect[1] .PushBack({ 100,0,100,100   });
	carDirectionRect[2] .PushBack({ 200,0,100,100   });
	carDirectionRect[3] .PushBack({ 300,0,100,100   });
	carDirectionRect[4] .PushBack({ 400,0,100,100   });
	carDirectionRect[5] .PushBack({ 500,0,100,100   });
							  
	carDirectionRect[6] .PushBack({ 0,100,100,100   }); 
	carDirectionRect[7] .PushBack({ 100,100,100,100 });
	carDirectionRect[8] .PushBack({ 200,100,100,100 });
	carDirectionRect[9] .PushBack({ 300,100,100,100 });
	carDirectionRect[10].PushBack({ 400,100,100,100 });
	carDirectionRect[11].PushBack({ 500,100,100,100 });
								  
	carDirectionRect[12].PushBack({ 000,200,100,100   }); 
	carDirectionRect[13].PushBack({ 100,200,100,100 });
	carDirectionRect[14].PushBack({ 200,200,100,100 });
	carDirectionRect[15].PushBack({ 300,200,100,100 });

	for (size_t i = 0; i < 16; i++)
	{
		carDirectionRect[i].loop = false;
		timeAlive = 1000;
		inmortal = true;
	}
	
	currentAnim = &carDirectionRect[0];
	SDL_Rect colboxRect = { 206,2326,73,75 };
	SDL_Rect hitboxRect = { 209,2336,67,43 };

	//colbox = App->collisions->AddCollider(colboxRect, Collider::WALL);
	//hitbox = App->collisions->AddCollider(colboxRect, Collider::ENEMY);
	
}

void Enemy_Car::Update()
{
	if (App->input->keys[SDL_SCANCODE_U] == KEY_STATE::KEY_DOWN) direction++;
	if (App->input->keys[SDL_SCANCODE_Y] == KEY_STATE::KEY_DOWN) direction--;

	if (direction >= 16) direction = 0;
	if (direction < 0) direction = 15;


	currentAnim = &carDirectionRect[direction];
	//LOG("direction: %i", direction);
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}


