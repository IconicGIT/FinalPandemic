#include "FifthScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

FifthScene::FifthScene(bool startEnabled) : Module(startEnabled)
{

}

FifthScene::~FifthScene()
{

}

// Load assets
bool FifthScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bTexture = App->textures->Load("Assets/Sprites/background_scene5.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult FifthScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_2, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult FifthScene::PostUpdate()
{
	// Draw everything
	SDL_Rect bcoin;
	bcoin.x = 0;
	bcoin.y = 0;
	bcoin.w = 224;
	bcoin.h = 384;

	App->render->Blit(bTexture, 0, 0, &bcoin);

	return UpdateResult::UPDATE_CONTINUE;
}

bool FifthScene::CleanUp() {

	//SDL_free(bgTexture);

	return true;
}