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

	App->collisions->AddCollider({ 0, 384, 224, 1 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 768, 224, 1 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1152, 224, 1 }, Collider::Type::WALL);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult SecondScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->thirdScene, 90);
	}

	if (timer == timerReference) 
	{
		timer = 0;
	}

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

	//SDL_free(bgTexture);

	return true;
}

void movement(int speed, int frames)
{
	if (frames > 0)
	{
		App->render->camera.y += speed;
		frames--;
	}
	else
	{
		frames = 0;
		speed = 0;
	}
}
