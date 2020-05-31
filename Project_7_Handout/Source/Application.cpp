#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "SceneShop.h"
#include "SceneWin.h"
#include "ModuleScene.h"
#include "ModuleScene2.h"
#include "SceneGameover.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "HUD.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"


Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen
	modules[0] = window = new ModuleWindow(true);
	modules[1] = input = new ModuleInput(true);
	modules[2] = textures = new ModuleTextures(true);
	modules[3] = audio = new ModuleAudio(true);

	modules[4] = sceneIntro = new SceneIntro(true);
	modules[5] = sceneShop = new SceneShop(false);
	modules[6] = level1 = new ModuleScene(false);
	modules[7] = level2 = new ModuleScene2(false);

	modules[8] = sceneGameover = new SceneGameover(false);
	modules[9] = sceneWin = new SceneWin(false);

	modules[10] = particles = new ModuleParticles(true);
	modules[11] = enemies = new ModuleEnemies(false);	//Enemies start disabled
	modules[12] = player = new ModulePlayer(false);		//Player starts disabled	

	modules[13] = hud = new HUD(false);
	modules[14] = collisions = new ModuleCollisions(true);
	modules[15] = fade = new ModuleFadeToBlack(true);
	modules[16] = fonts = new ModuleFonts(true);
	modules[17] = render = new ModuleRender(true);



}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Module* Application::GetActualScene(){

	return actual;
}

void Application::SetActualScene(Module* scene)
{
	actual = scene;
}

update_status Application::Update()
{
	update_status ret = update_status::UPDATE_CONTINUE;
	
	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i) 
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : update_status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == update_status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : update_status::UPDATE_CONTINUE;

	return ret;
}
 


bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;


	return ret;
}
