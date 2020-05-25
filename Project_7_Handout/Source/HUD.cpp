#include "HUD.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

#include <stdio.h>

#include "SDL/include/SDL_scancode.h"

HUD::HUD(bool startEnabled) : Module(startEnabled) {
	
}

HUD::~HUD(){
	CleanUp();
}

bool HUD::Start()
{
	bool ret = true;

	scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);
	scoreFont2 = App->fonts->Load("Assets/Fonts/rtype_font3.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 2);

	score = &App->player->score;

	return ret;
}

update_status HUD::PostUpdate()
{
	sprintf_s(scoreText, 10, "%7d", *score);

	App->fonts->BlitText(10, 10, scoreFont, scoreText);

	return update_status::UPDATE_CONTINUE;
}

bool HUD::CleanUp()
{
	App->fonts->UnLoad(scoreFont);
	App->fonts->UnLoad(scoreFont2);
	return true;
}
