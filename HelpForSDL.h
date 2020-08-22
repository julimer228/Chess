/**@FILE*/
#ifndef HELP_FOR_SDL_H
#define HELP_FOR_SDL_H
#include <SDL.h>
#include "Game.h"

/*Wysoko�� i szeroko�� okien*/
#define GUI_WINDOW_W 1024
#define GUI_WINDOW_H 768

/*Wymiary du�ych przycisk�w*/
#define GUI_BUTTON_H 72
#define GUI_BUTTON_W 343

/*Wymiary ma�ych przycisk�w*/
#define GUI_BUTTON_SMALL_H 54
#define GUI_BUTTON_SMALL_W 226

/*---WYMAGA DOPRACOWANIA!!!---*/
/**Typ wyliczeniowy okre�laj�cy zdarzenia jakie mog� mie� miejsce ze strony u�ytkownika*/
typedef enum gui_user_event
{
	GUI_USER_EVENT_PLAY, //Naci�ni�cie przycisku play
	GUI_USER_EVENT_HELP, //Naci�ni�cie przycisku help
	GUI_USER_EVENT_EXIT, //Naci�ni�cie przycisku exit
	GUI_USER_EVENT_BACK, //Naci�ni�cie przycisku back
	GUI_USER_EVENT_OK	//Naci�ni�cie przycisku ok
}GUI_User_Event;

/**Funkcja rozpoczynaj�ca prac� z bibliotek� SDL2*/
bool InitializeSDL2();

/**Funkcja ko�cz�ca prac� z bibliotek� SDL2*/
void QuitSDL2();

#endif
