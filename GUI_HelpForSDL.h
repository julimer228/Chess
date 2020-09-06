/**@file*/
#ifndef GUI_HELPFORSDL_H
#define GUI_HELPFORSDL_H
#include <SDL.h>
#include <SDL_video.h>
#include "Game.h"



#define WINDOW_W 1024
#define WINDOW_H 768

/**Funkcja wy�wietlaj�ca informacj� na ekranie (messagebox)
@param header tytu� okna
@param info informacja wy�wietlana w oknie*/
void GUI_Messagebox(const char*header, const char*info);

/**Funkcja wczytuj�ca tekstur� z pliku BMP
@param render render
@param path �cie�ka do pliku z tekstur�
@return wczytana tekstura lub NULL w przypadku gdy nie uda�o si� wczyta� tekstury*/
SDL_Texture* GUI_TextureBMP(SDL_Renderer* render, char* path);

/**Funkcja wczytuj�ca tekstur� z pliku BMP, zmienia kolor t�a na prze�roczysty
@param render render
@param path �cie�ka do pliku z tekstur�
@param red ilo�� czerwieni w kolorze t�a
@param green ilo�� zieleni w kolorze t�a
@param blue ilo�� niebieskiego w kolorze t�a
@param return wczytana tekstura lub NULL w przypadku gdy nie uda�o si� wczyta� tekstury*/
SDL_Texture* GUI_TextureBMPWithoutBackground(SDL_Renderer* render, char* path, Uint8 red, Uint8 green, Uint8 blue);

/**Funkcja Rozpoczyna prac� z bibliotek� SDL, je�li wyst�pi� b��d funkcja wypisuje na ekranie konsoli informacj� o b��dzie
@return true, je�li uda�o si� poprawnie zainicjowa� bibliotek�, w przeciwnym wypadku false*/
bool InitSDL2();

/**Funkcja tworzy okno i sprawdza czy zosta�o poprawnie utworzone
@return okno biblioteki lub NULL je�li nie uda�o si� utworzy� okna*/
SDL_Window* CreateAWindow();

/**Funkcja tworzy render biblioteki i sprawdza czy zosta� poprawnie utworzony
@return render lub NULL je�li nie zosta� poprawnie utworzony*/
SDL_Renderer* CreateARenderer(SDL_Window*window);

#endif
