#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <SDL.h>
#include <SDL_video.h>

/*Struktura reprezentuj¹ca okno wyœwietlane na ekranie*/
typedef struct gui_window GUI_Window;

struct gui_window 
{
	void* gui_window_data; //dane charakterystyczne dla ka¿dego okna
	void(*WindowDraw)(GUI_Window*); //wskaŸnik na funkcjê prezentuj¹c¹ dane na ekranie
	void(*WindowHandleEvent)(GUI_Window*, SDL_Event*); //obs³uga zdarzeñ
	void(*WindowDestroy)(GUI_Window*); //Usuniêcie okna z pamiêci
};

/*Usuwa okno z pamiêci
@param window okno do usuniêcia*/
void GUI_DestroyWindow(GUI_Window* window);

#endif