#include "FrontPage.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "SDL_mixer/include/SDL_mixer.h"

FrontPage::FrontPage(bool startEnabled) : Module(startEnabled)
{

}

FrontPage::~FrontPage()
{

}

// Load assets
bool FrontPage::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bTexture = App->textures->Load("Assets/Sprites/front_page.png");
	//bMusic = Mix_LoadMUS("Assets/Music/Opening.ogg");
	App->audio->PlayMusic("Assets/Music/Opening.ogg");




	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult FrontPage::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->firstScene, 90);
		
	}
	if (App->input->keys[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 30);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult FrontPage::PostUpdate()
{
	// Draw everything

	SDL_Rect bfront;
	bfront.x = 0;
	bfront.y = 0;
	bfront.w = 224;
	bfront.h = 384;

	App->render->Blit(bTexture, 0, 0, &bfront);

	return UpdateResult::UPDATE_CONTINUE;
}

bool FrontPage::CleanUp() {

	//SDL_free(bgTexture);

	return true;
}