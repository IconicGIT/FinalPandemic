#include "FourthScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

FourthScene::FourthScene(bool startEnabled) : Module(startEnabled)
{

}

FourthScene::~FourthScene()
{

}

// Load assets
bool FourthScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bTexture = App->textures->Load("Assets/Sprites/background_scene4.png");


	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult FourthScene::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult FourthScene::PostUpdate()
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

bool FourthScene::CleanUp() {

	//SDL_free(bgTexture);

	return true;
}