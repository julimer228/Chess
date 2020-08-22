#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include <SDL.h>
#include <SDL_video.h>
/*-Namiastka klasy- za pomoc¹ wskaŸnika na funkcjê mo¿na zaszczepiæ w jêzyku strukturalnym, jakim jest C pewne obiektowe w³aœciwoœci-*/
/*Struktura reprezentuj¹ca wid¿et (przyciski i inne elementy graficznego interfejsu u¿ytkownika)*/
typedef struct gui_widget GUI_Widget;

struct gui_widget 
{
	void(*WidgetDraw)(GUI_Widget*, SDL_Renderer*);//wskaŸnik na funkcjê rysuj¹c¹ wid¿et
	void(*WidgetHandleEvent)(GUI_Widget*, SDL_Event*);//wskaŸnik na funkcjê obs³uguj¹c¹ zdarzenie zwi¹zane z wid¿etem
	void(*WidgetDestroy)(GUI_Widget*);//wskaŸnik na funkcjê usuwaj¹c¹ wid¿et z pamiêci
	void* gui_widget_data;//wskaŸnik na dane charakterystyczne dla danego wid¿etu
};

void destroyWidget(GUI_Widget* widget);

#endif
