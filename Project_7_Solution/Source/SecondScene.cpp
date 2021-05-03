#include "SecondScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
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

	bTexture = App->textures->Load("Assets/Sprites/back_scene2.png");
	App->audio->PlayMusic("Assets/Music/introTitle.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult SecondScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}
	
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult SecondScene::PostUpdate()
{
	// Draw everything
	SDL_Rect bhouse;
	bhouse.x = 0;
	bhouse.y = 0;
	bhouse.w = 484;
	bhouse.h = 845;

	App->render->Blit(bTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}

bool SecondScene::CleanUp() {

	//SDL_free(bgTexture);

	return true;
}