#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <windows.h>

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);
void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

enum class update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ----------------
typedef unsigned int uint;

// Window Configuration -----------

//SCREEN_HEIGHT 440
#define SCREEN_WIDTH 503

//#define SCREEN_WIDTH 503
#define SCREEN_HEIGHT 440

#define SCREEN_SIZE 1
#define SCREEN_SPEED 1
#define WIN_FULLSCREEN 0

#define SPAWN_MARGIN 50

#define PLAYER_WIDTH 68
#define PLAYER_HEIGHT 22

//poner 1 para pantalla completa, 0 para tamaño real
#define FULL_SCREEN 0

#define WIN_FULLSCREEN_DESKTOP FULL_SCREEN
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define VSYNC 1
#define PI 3.141592

static int VOLUME_GAME = 180 ;

#endif // __GLOBALS_H__