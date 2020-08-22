#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <SDL.h>
#include <SDL_video.h>

/*Struktura reprezentuj�ca okno wy�wietlane na ekranie*/
typedef struct gui_window GUI_Window;

struct gui_window 
{
	void* gui_window_data; //dane charakterystyczne dla ka�dego okna
	void(*WindowDraw)(GUI_Window*); //wska�nik na funkcj� prezentuj�c� dane na ekranie
	void(*WindowHandleEvent)(GUI_Window*, SDL_Event*); //obs�uga zdarze�
	void(*WindowDestroy)(GUI_Window*); //Usuni�cie okna z pami�ci
};

/*Usuwa okno z pami�ci
@param window okno do usuni�cia*/
void GUI_DestroyWindow(GUI_Window* window);

#endif