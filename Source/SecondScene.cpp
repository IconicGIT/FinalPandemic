#include "SecondScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SecondScene::SecondScene(bool startEnabled) : Module(startEnabled)
{

}

SecondScene::~SecondScene()
{

}

// Load assets
bool SecondScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bTexture = App->textures->Load("Assets/Sprites/scene2.png");
	App->audio->PlayMusic("", 1.0f); //Change

	//App->collisions->AddCollider({ 0, 384, 224, 1 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 0, 768, 224, 1 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 0, 1152, 224, 1 }, Collider::Type::WALL);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	timer = timerReference;

	return ret;
}

UpdateResult SecondScene::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->thirdScene, 30);
	}

	if (timer <= 0) 
	{
		if (counter < 2) {
			timerReference = 500;
			timer = timerReference;
			speed = 6;
			frames = 128;
			counter++;
		}
		else {

			App->fade->FadeToBlack(this, (Module*)App->thirdScene, 90);

		}
	}

	timer--;
	Movement(speed, frames);

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SecondScene::PostUpdate()
{
	// Draw everything

	App->render->Blit(bTexture, 0, 0, NULL);

	App->collisions->DebugDraw();

	return UpdateResult::UPDATE_CONTINUE;
}

bool SecondScene::CleanUp() {

	SDL_free(bTexture);

	return true;
}

void SecondScene::Movement(int &speed, int &frames)
{
	if (frames > 0)
	{
		App->render->camera.y += speed;
		frames--;
	}
	else
	{
		
		speed = 0;
	}
}
