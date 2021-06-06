#include "ThirdScene.h"
#include <stdio.h>
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

ThirdScene::ThirdScene(bool startEnabled) : Module(startEnabled)
{

}

ThirdScene::~ThirdScene()
{

}

// Load assets
bool ThirdScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;
	
	creditFX = App->audio->LoadFx("Assets/Fx/credit.wav");

	bTexture = App->textures->Load("Assets/Sprites/background_scene3.png");
	char lookupTable1[] = { "0123456789abcdefghijklmnopqrstuvwxyz                       " };
	
	texture = App->textures->Load("Assets/Sprites/insert_coin2.png");
	texture2 = App->textures->Load("Assets/Sprites/credit.png");
	creditsFont = App->fonts->Load("Assets/Fonts/bomb_score_font_small.png", lookupTable1, 2);
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

UpdateResult ThirdScene::Update()
{
	
	if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)&&(App->fade->credits>0))
	{
		App->fade->FadeToBlack(this, (Module*)App->scene, 90);
	}
	if (App->input->keys[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN)
	{
		if (App->fade->credits < 10)
		{
			App->fade->credits++;
			App->audio->PlayFx(creditFX);

		}
		
	}

	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult ThirdScene::PostUpdate()
{
	// Draw everything
	SDL_Rect bcoin;
	bcoin.x = 0;
	bcoin.y = 0;
	bcoin.w = 224;
	bcoin.h = 384;

	App->render->Blit(bTexture, 0, 0, &bcoin);
	
	sprintf_s(txtCredits, "%2d", App->fade->credits);
	
	App->render->Blit(texture, 40, 216, false);
	App->fonts->BlitText(15, 370, creditsFont, txtCredits);
	App->render->Blit(texture2, 45, 367, false);
	return UpdateResult::UPDATE_CONTINUE;
}

bool ThirdScene::CleanUp() {

	SDL_free(bTexture);

	return true;
}