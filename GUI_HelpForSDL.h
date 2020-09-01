/**@FILE*/
#ifndef GUI_HELPFORSDL_H
#define GUI_HELPFORSDL_H
#include <SDL.h>
#include "Game.h"
#include "GUI_Window.h"

/*Wysoko�� i szeroko�� okien*/
#define WINDOW_W 1024
#define WINDOW_H 768

/*Wymiary du�ych przycisk�w*/
#define BUTTON_H 72
#define BUTTON_W 343

/*Wymiary przycisku powrotu do menu g��wnego*/
#define BUTTON_BACK_H 54
#define BUTTON_BACK_W 226

/*---WYMAGA DOPRACOWANIA!!!---*/
/**Typ wyliczeniowy okre�laj�cy zdarzenia jakie mog� mie� miejsce ze strony u�ytkownika*/
typedef enum gui_user_event
{
	USER_EVENT_PLAY, //Naci�ni�cie przycisku play
	USER_EVENT_HELP, //Naci�ni�cie przycisku help
	USER_EVENT_EXIT, //Naci�ni�cie przycisku exit
	USER_EVENT_BACK_TO_MENU_WINDOW, //Naci�ni�cie przycisku back
	USER_EVENT_OK,	//Naci�ni�cie przycisku ok
	USER_EVENT_MESSAGE//Wy�wietlenie okienka z wiadomo�ci�
}GUI_UserEvent;

/**Funkcja wykorzystana do obs�ugi zdarze� od u�ytkownika
@param userevent zdarzenie od u�ytkownika
@param a
@param b*/
void GUI_UserEventPush(GUI_UserEvent userevent, void* a, void* b);

/*Funkcja wy�wietlaj�ca informacj� na ekranie (messagebox)
@param header tytu� okna
@param info informacja wy�wietlana w oknie*/
void GUI_Messagebox(const char*header, const char*info);


/*Funkcja wczytuj�ca tekstur� z pliku BMP
@param render mechanizm renderuj�cy
@param path �cie�ka do pliku z tekstur�
@return wczytana tekstura lub NULL w przypadku gdy nie uda�o si� wczyta� tekstury*/
SDL_Texture* GUI_TextureBMP(SDL_Renderer* render, char* path);

/*Funkcja wczytuj�ca tekstur� z pliku BMP, zmienia kolor t�a na prze�roczysty
@param render mechanizm rnderuj�cy
@param path �cie�ka do pliku z tekstur�
@param red ilo�� czerwieni w kolorze t�a
@param green ilo�� zieleni w kolorze t�a
@param blue ilo�� niebieskiego w kolorze t�a
@param return wczytana tekstura lub NULL w przypadku gdy nie uda�o si� wczyta� tekstury*/
SDL_Texture* GUI_TextureBMPWithoutBackground(SDL_Renderer* render, char* path, Uint8 red, Uint8 green, Uint8 blue);

#endif
