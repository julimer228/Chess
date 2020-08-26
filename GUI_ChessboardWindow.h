#ifndef GUI_CHESSBOARDWINDOW_H
#define GUI_CHESSBOARDWINDOW_H
#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>
#include <stdbool.h>
#include "GUI_Button.h"
#include "GUI_HelpForSDL.h"
#include "GUI_Chessboard.h"
#include "GUI_Window.h"

/*Struktura odpowiedzialna za okno z szachownic¹*/
typedef struct guigamewindow_t
{
	SDL_Window* window;
	SDL_Renderer* render
		GUI_Widget* widget;
	SDL_Texture* background;
	Game* game;
	bool menu_save;
}GUI_ChessboardWindow;

GUI_Window* GUI_CreateChessboardWindow(SDL_Window* chessboardwindow, SDL_Renderer* rend, Game* game);
void GUI_DrawChessboardWindow(GUI_Window* chessboardwindow);
void GUI_DestroyChessboardWindow(GUI_Window* chessboardwindow);
void GUI_HandleChessboardEvent(GUI_Window* chessboardwindow);
#endif
