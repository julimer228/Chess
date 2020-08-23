#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "GUI_Widget.h"
#include <SDL.h>
#include <SDL_video.h>

/*Struktura reprezentuj�ca przycisk*/

typedef struct gui_button {
	SDL_Renderer* renderer; //render
	SDL_Texture* texture; //tekstura
	SDL_Rect location; //po�o�enie przycisku
	void(*ButtonAction)(void); //wska�nik na funkcj�, kt�ra zostanie wywo�ana po naci�ni�ciu przycisku
} GUI_Button;

/*Funkcja tworz�ca przycisk
@param renderer render
@param imagepath �cie�ka do pliku z tekstur�
@param location po�o�enie przycisku
@param ButtonAction akcja, kt�ra wydarzy si� po naci�ni�ciu przycisku
@return utworzony przycisk*/
GUI_Widget* GUI_CreateButton(SDL_Renderer* renderer,const char* imagepath, SDL_Rect location, void(*ButtonAction)(void));

/*Funkcja usuwaj�ca przycisk z pami�ci
@param widget usuwany przycisk*/
void GUI_DestroyButton(GUI_Widget* widget);

/*Funkcja obs�uguj�ca zdarzenia zwi�zane z przyciskiem
@param widget przycisk
@param event zdarzenie do obs�u�enia*/
void GUI_HandleButtonEvent(GUI_Widget* widget, SDL_Event* event);

/*Funkcja rysuj�ca przycisk w buforze
@param widget przycisk
@param renderer render kt�ry rysuje w buforze*/
void GUI_DrawButton(GUI_Widget*widget, SDL_Renderer*renderer);

#endif 