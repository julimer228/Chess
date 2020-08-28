/**@FILE*/
#ifndef GUI_HELPFORSDL_H
#define GUI_HELPFORSDL_H
#include <SDL.h>
#include "Game.h"
#include "GUI_Window.h"

/*Wysokoœæ i szerokoœæ okien*/
#define WINDOW_W 1024
#define WINDOW_H 768

/*Wymiary du¿ych przycisków*/
#define BUTTON_H 72
#define BUTTON_W 343

/*Wymiary przycisku powrotu do menu g³ównego*/
#define BUTTON_BACK_H 54
#define BUTTON_BACK_W 226

/*---WYMAGA DOPRACOWANIA!!!---*/
/**Typ wyliczeniowy okreœlaj¹cy zdarzenia jakie mog¹ mieæ miejsce ze strony u¿ytkownika*/
typedef enum gui_user_event
{
	USER_EVENT_PLAY, //Naciœniêcie przycisku play
	USER_EVENT_HELP, //Naciœniêcie przycisku help
	USER_EVENT_EXIT, //Naciœniêcie przycisku exit
	USER_EVENT_BACK_TO_MENU_WINDOW, //Naciœniêcie przycisku back
	USER_EVENT_OK	//Naciœniêcie przycisku ok
}GUI_UserEvent;

/**Funkcja rozpoczynaj¹ca pracê z bibliotek¹ SDL2*/
bool GUI_InitializeSDL2();

void GUI_UserEventPush(GUI_UserEvent userevent, void* a, void* b);

/**Funkcja koñcz¹ca pracê z bibliotek¹ SDL2*/
void GUI_QuitSDL2();

/*Funkcja wyœwietlaj¹ca informacjê na ekranie (messagebox)
@param header tytu³ okna
@param info informacja wyœwietlana w oknie*/
void GUI_Messagebox(const char*header, const char*info);


/*Funkcja wczytuj¹ca teksturê z pliku BMP
@param render mechanizm renderuj¹cy
@param path œcie¿ka do pliku z tekstur¹
@return wczytana tekstura lub NULL w przypadku gdy nie uda³o siê wczytaæ tekstury*/
SDL_Texture* GUI_TextureBMP(SDL_Renderer* render, char* path);

/*Funkcja wczytuj¹ca teksturê z pliku BMP, zmienia kolor t³a na przeŸroczysty
@param render mechanizm rnderuj¹cy
@param path œcie¿ka do pliku z tekstur¹
@param red iloœæ czerwieni w kolorze t³a
@param green iloœæ zieleni w kolorze t³a
@param blue iloœæ niebieskiego w kolorze t³a
@param return wczytana tekstura lub NULL w przypadku gdy nie uda³o siê wczytaæ tekstury*/
SDL_Texture* GUI_TextureBMPWithoutBackground(SDL_Renderer* render, char* path, Uint8 red, Uint8 green, Uint8 blue);

/*Funkcja rysuje teksturê w miejscu okreœlonym wspó³rzêdnymi x i y o okreœlonych wymiarach
@param texture tekstura któr¹ chcemy narysowaæ
@param renender render do którego rysujemy
@param x wspó³rzêdna x po³o¿enia
@param y wspó³rzêdna y po³o¿enia
@param w szerokoœæ tekstury
@param h wysokoœæ tekstury*/
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h);
#endif
