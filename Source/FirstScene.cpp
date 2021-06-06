#include "FirstScene.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include <math.h>

FirstScene::FirstScene(bool startEnabled) : Module(startEnabled)
{

}

FirstScene::~FirstScene()
{

}

// Load assets
bool FirstScene::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	hTexture = App->textures->Load("Assets/Sprites/house.png");
	text1 = App->textures->Load("Assets/Sprites/text1.png");
	text2 = App->textures->Load("Assets/Sprites/text2.png");
	text3 = App->textures->Load("Assets/Sprites/text3.png");
	text4 = App->textures->Load("Assets/Sprites/text4.png");
	text5 = App->textures->Load("Assets/Sprites/text5.png");
	App->audio->PlayMusic("", 1.0f); 

	
	
	textBlack = { 0,256,224,128 };
	timerReference = 500;
	timer = 0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	blackAlpha = 0;
	blackMultiplier = 0.05f;
	angle = 0;
	fade = false;
	
	
	return ret;
}

UpdateResult FirstScene::Update()
{

	if ((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN))
	{
		App->fade->FadeToBlack(this, (Module*)App->secondScene, 30);
	}


	if (timer == timerReference) {

		fade = true;
		timer = 0;
	}
	
	if (counter > 5 ) {

		App->fade->FadeToBlack(this, (Module*)App->secondScene, 90);

	}

	timer++;
	return UpdateResult::UPDATE_CONTINUE;
}

UpdateResult FirstScene::PostUpdate()
{
	// Draw everything
	SDL_Rect bhouse;
	bhouse.x = 0;
	bhouse.y = 0;
	bhouse.w = 224;
	bhouse.h = 256;

	App->render->Blit(hTexture, 0, 0, &bhouse);

	

	if ((fade == true)) 
	{
	
		angle++;
	}
	if (angle == 60)
	{
		
		fade = false;
		angle = 0;
	}

	if (angle == 31) counter++;

	//if (blackAlpha >= 254) LOG("angle: %f", angle);
	

	blackAlpha = 255 * sin(angle * blackMultiplier);

	switch (counter)
	{
	case 1:
		App->render->Blit(text1, 0, textBlack.y, &textBlack);
		break;
	case 2:
		App->render->Blit(text2, 0, textBlack.y, &textBlack);
		break;
	case 3:
		App->render->Blit(text3, 0, textBlack.y, &textBlack);
		break;
	case 4:
		App->render->Blit(text4, 0, textBlack.y, &textBlack);
		break;
	case 5:
		App->render->Blit(text5, 0, textBlack.y, &textBlack);
		break;

	}

	App->render->DrawQuad(textBlack, 0, 0, 0, blackAlpha);

	return UpdateResult::UPDATE_CONTINUE;
}

bool FirstScene::CleanUp() {

	SDL_free(hTexture);
	SDL_free(text1);
	SDL_free(text2);
	SDL_free(text3);
	SDL_free(text4);
	SDL_free(text5);

	return true;
}