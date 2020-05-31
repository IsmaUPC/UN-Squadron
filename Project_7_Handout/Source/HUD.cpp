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
	
																																						//720 x 224
	scoreFont = App->fonts->Load("Assets/Fonts/FontY.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,им?!*$%&()+-/:;<=>@__     ", 5,720,224);
	scoreFont2 = App->fonts->Load("Assets/Fonts/FontG.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5, 720, 224);
	
																																						//276 x 86
	hudfont = App->fonts->Load("Assets/hud/hud_font2.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,0123456789им?!*$%&()+-/:;<=>@__     ", 5,235,75);

	hudTexture = App->textures->Load("Assets/hud/hud.png");

	info.money = App->player->getMoney();
	info.score = App->player->getScore();
	info.level = App->player->getLevel();
	info.pow = App->player->getPow();
	info.total = App->player->getTotal();
	info.lives = App->player->getLives();
	
	return ret;
}

update_status HUD::PostUpdate(){

	App->render->Blit(hudTexture, 0,0, NULL, 0,false);

	sprintf_s(moneyText, 10, "%7d", *info.money);
	sprintf_s(scoreText, 10, "%7d", *info.score);
	sprintf_s(levelText, 5, "%3d", *info.level);
	sprintf_s(powText, 5, "%3d", *info.pow);
	sprintf_s(totalText, 5, "%3d", *info.total);
	sprintf_s(livesText, 5, "%3d", *info.lives);

	App->fonts->BlitText(20, 61, hudfont, scoreText);

	App->fonts->BlitText(262, 61, hudfont, moneyText);

	App->fonts->BlitText(322, 30, hudfont, levelText);

	App->fonts->BlitText(390, 61, hudfont, powText);

	App->fonts->BlitText(447, 61, hudfont, totalText);

	App->fonts->BlitText(54,412, hudfont, livesText);

	return update_status::UPDATE_CONTINUE;

}

bool HUD::CleanUp()
{
	
	App->fonts->UnLoad(scoreFont);
	App->fonts->UnLoad(scoreFont2);
	App->fonts->UnLoad(hudfont);


	App->textures->Unload(hudTexture);

	return true;
}
