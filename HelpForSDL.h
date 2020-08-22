/**@FILE*/
#ifndef HELP_FOR_SDL_H
#define HELP_FOR_SDL_H
#include <SDL.h>
#include "Game.h"

/*Wysokoœæ i szerokoœæ okien*/
#define GUI_WINDOW_W 1024
#define GUI_WINDOW_H 768

/*Wymiary du¿ych przycisków*/
#define GUI_BUTTON_H 72
#define GUI_BUTTON_W 343

/*Wymiary ma³ych przycisków*/
#define GUI_BUTTON_SMALL_H 54
#define GUI_BUTTON_SMALL_W 226

/*---WYMAGA DOPRACOWANIA!!!---*/
/**Typ wyliczeniowy okreœlaj¹cy zdarzenia jakie mog¹ mieæ miejsce ze strony u¿ytkownika*/
typedef enum gui_user_event
{
	GUI_USER_EVENT_PLAY, //Naciœniêcie przycisku play
	GUI_USER_EVENT_HELP, //Naciœniêcie przycisku help
	GUI_USER_EVENT_EXIT, //Naciœniêcie przycisku exit
	GUI_USER_EVENT_BACK, //Naciœniêcie przycisku back
	GUI_USER_EVENT_OK	//Naciœniêcie przycisku ok
}GUI_User_Event;

/**Funkcja rozpoczynaj¹ca pracê z bibliotek¹ SDL2*/
bool InitializeSDL2();

/**Funkcja koñcz¹ca pracê z bibliotek¹ SDL2*/
void QuitSDL2();

#endif
