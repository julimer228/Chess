#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "GUI_Widget.h"
#include <SDL.h>
#include <SDL_video.h>

/*Struktura reprezentuj¹ca przycisk*/

typedef struct gui_button {
	SDL_Renderer* renderer; //render
	SDL_Texture* texture; //tekstura
	SDL_Rect location; //po³o¿enie przycisku
	void(*ButtonAction)(void); //wskaŸnik na funkcjê, która zostanie wywo³ana po naciœniêciu przycisku
} GUI_Button;

/*Funkcja tworz¹ca przycisk
@param renderer render
@param imagepath œcie¿ka do pliku z tekstur¹
@param location po³o¿enie przycisku
@param ButtonAction akcja, która wydarzy siê po naciœniêciu przycisku
@return utworzony przycisk*/
GUI_Widget* GUI_CreateButton(SDL_Renderer* renderer,const char* imagepath, SDL_Rect location, void(*ButtonAction)(void));

/*Funkcja usuwaj¹ca przycisk z pamiêci
@param widget usuwany przycisk*/
void GUI_DestroyButton(GUI_Widget* widget);

/*Funkcja obs³uguj¹ca zdarzenia zwi¹zane z przyciskiem
@param widget przycisk
@param event zdarzenie do obs³u¿enia*/
void GUI_HandleButtonEvent(GUI_Widget* widget, SDL_Event* event);

/*Funkcja rysuj¹ca przycisk w buforze
@param widget przycisk
@param renderer render który rysuje w buforze*/
void GUI_DrawButton(GUI_Widget*widget, SDL_Renderer*renderer);

#endif 