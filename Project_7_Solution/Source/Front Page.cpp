#include "FrontPage.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

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
	App->audio->PlayMusic("Assets/Music/Mission1.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult FrontPage::Update()
{
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult FrontPage::PostUpdate()
{
	// Draw everything

	App->render->Blit(bTexture, 0, 0, NULL);

	return UpdateResult::UPDATE_CONTINUE;
}

bool FrontPage::CleanUp() {

	//SDL_free(bgTexture);

	return true;
}