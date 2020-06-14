#ifndef __SCENE_WIN_H__
#define __SCENE_WIN_H__

#include "Module.h"
#include "Animation.h"
#include"Path.h"
#include "Timer.h"

struct SDL_Texture;

class SceneWin : public Module
{
public:
	//Constructor
	SceneWin(bool startEnabled);

	//Destructor
	~SceneWin();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;
	bool CleanUp();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* winTexture = nullptr;
	Animation win_screen1 ;
	Animation win_screen2 ;
	Animation win_screen3 ;
	Animation win_screen4 ;
	Path animWin;
	Timer* fade;
	Collider* collider;
	int numFrames=0;
	Animation* currentAnim = nullptr;


};

#endif