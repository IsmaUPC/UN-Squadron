#ifndef __HUD_H__
#define __HUD_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

class HUD : public Module
{
public:

	HUD(bool startEnabled);

	~HUD();

	bool Start() override;

	update_status PostUpdate() override;

	bool CleanUp() override;

private:

	int* score = nullptr;

	int scoreFont = 0;
	int scoreFont2 = 0;
	char scoreText[10] = { "\0" };
};


#endif // !__HUD_H__

