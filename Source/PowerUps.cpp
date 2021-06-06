#include "PowerUps.h"
#include "Collider.h"
#include "Enemy_Soldier.h"
#include "Application.h"
#include "ModulePowerUps.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "Collider.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

PowerUp::PowerUp()
{
	position.SetToZero();
	id = 0;
}

PowerUp::PowerUp(const PowerUp& p) : anim(p.anim), position(p.position),
frameCount(p.frameCount), lifetime(p.lifetime), id(p.id)
{

}

PowerUp::~PowerUp()
{
	//if (collider != nullptr)
	//{
	//	collider->pendingToDelete = true;
	//}

}

bool PowerUp::Update()
{
	bool ret = true;
	frameCount++;

	if (!isAlive && frameCount >= 0)
		isAlive = true;
	/*
	if (isAlive)
	{
		anim.Update();

		switch (id)
		{
		case 0:
			App->player->score += 1000;
			//Medal1.collider->pendingToDelete = true;
			break;
		case 1:
			App->player->score += 2500;//
			//Medal2.collider->pendingToDelete = true;
			break;
		case 2:
			App->player->score += 5000;//
			//Medal3.collider->pendingToDelete = true;
			break;
		case 3:
			App->player->weaponType = 2;
			//MachineGun.collider->pendingToDelete = true;
			break;
		case 4:
			App->player->weaponType = 3;
			//FlameThrower.collider->pendingToDelete = true;
			break;
		case 5:
			App->player->weaponType = 1;
			//Shotgun.collider->pendingToDelete = true;
			break;
		case 6:
			App->player->weaponType = 4;
			//GrenadeLouncher.collider->pendingToDelete = true;
			break;
		case 7:
			App->player->bombs++;
			//Bomb.collider->pendingToDelete = true;
			break;
		case 8:
			App->player->weaponLevel++;
			//Pow.collider->pendingToDelete = true;
			break;
		case 9:
			App->player->playerLife += 2;
			App->player->playerMaximumLife += 2;

			if (App->player->playerLife > App->player->playerMaximumLife)
			{
				App->player->playerLife = App->player->playerMaximumLife;
			}
			break;
		case 10:
			App->player->playerLife += 4;//

			if (App->player->playerLife > App->player->playerMaximumLife)
			{
				App->player->playerLife = App->player->playerMaximumLife;
			}
			break;
		case 11:
			App->player->playerLife += 2;//

			if (App->player->playerLife > App->player->playerMaximumLife)
			{
				App->player->playerLife = App->player->playerMaximumLife;
			}
			break;
		case 12:
			App->player->score += 500;
			break;
			
		case 13:
			App->player->score += 2000;
			break;
		case 14:
			App->player->score += 3000;
			break;
		case 15:
			App->player->score += 5000;
			break;
		}
		*/
		
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}

		else if (anim.HasFinished())
			ret = false;

		

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);

		return ret;



}
	
	
