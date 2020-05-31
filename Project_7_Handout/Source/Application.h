#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class SceneIntro;
class SceneShop;
class SceneWin;
class ModuleScene;
class ModuleScene2;
class SceneGameover;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;
class HUD;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	Module* GetActualScene();

	void SetActualScene(Module* scene);

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	Module* actual = nullptr;

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	SceneIntro* sceneIntro = nullptr;
	SceneShop* sceneShop = nullptr;
	SceneWin* sceneWin = nullptr;
	SceneGameover* sceneGameover = nullptr;

	ModuleScene* level1 = nullptr;
	ModuleScene2* level2 = nullptr;


	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	HUD* hud = nullptr;
	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__