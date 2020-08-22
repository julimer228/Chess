#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <SDL.h>
#include <SDL_video.h>
/*-Namiastka klasy- za pomoc� wska�nika na funkcj� mo�na zaszczepi� w j�zyku strukturalnym, jakim jest C pewne obiektowe w�a�ciwo�ci-*/
/*Struktura reprezentuj�ca wid�et (przyciski i inne elementy graficznego interfejsu u�ytkownika)*/
typedef struct gui_widget GUI_Widget;

struct gui_widget 
{
	void(*WidgetDraw)(GUI_Widget*, SDL_Renderer*);//wska�nik na funkcj� rysuj�c� wid�et
	void(*WidgetHandleEvent)(GUI_Widget*, SDL_Event*);//wska�nik na funkcj� obs�uguj�c� zdarzenie zwi�zane z wid�etem
	void(*WidgetDestroy)(GUI_Widget*);//wska�nik na funkcj� usuwaj�c� wid�et z pami�ci
	void* gui_widget_data;//wska�nik na dane charakterystyczne dla danego wid�etu
};

void destroyWidget(GUI_Widget* widget);

#endif
