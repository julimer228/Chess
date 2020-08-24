#include <stdio.h>
#include "GUI_MenuWindow.h"
int main(int argc, char* argv[])
{
	SDL_Window* sdl_window=SDL_CreateWindow("Chess",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 1000, 700, SDL_WINDOW_SHOWN);
	SDL_Renderer* new_renderer=SDL_CreateRenderer(sdl_window,-1, NULL);
	GUI_Window* new_menuwindow = GUI_MenuWindowCreate(sdl_window, new_renderer);
	GUI_MenuWindowDraw(new_menuwindow);
	SDL_Delay(3000);
}
