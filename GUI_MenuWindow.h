#ifndef GUI_MENUWINDOW_H
#define GUI_MENUWINDOW_H

#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include "GUI_Button.h"
#include "GUI_HelpForSDL.h"
#include "GUI_Window.h"

/*Okno menu start*/

typedef struct gui_menu_window 
{
	SDL_Window* window; //okno
	SDL_Renderer* renderer; //render
	GUI_Widget* widgettab[3]; // nowa gra, pomoc, wyjœcie z programu
	SDL_Texture* background; //tekstura z t³em
} GUI_MenuWindow;

GUI_Window* GUI_MenuWindowCreate(SDL_Window* window, SDL_Renderer* render);
void GUI_MenuWindowDraw(GUI_Window* window);
void GUI_MenuWindowDestroy(GUI_Window* window);
void GUI_MenuWindowHandleEvent(GUI_Window* window, SDL_Event* event);

#endif