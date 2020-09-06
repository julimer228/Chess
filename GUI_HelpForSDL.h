/**@file*/
#ifndef GUI_HELPFORSDL_H
#define GUI_HELPFORSDL_H
#include <SDL.h>
#include <SDL_video.h>
#include "Game.h"



#define WINDOW_W 1024
#define WINDOW_H 768

/**Funkcja wyœwietlaj¹ca informacjê na ekranie (messagebox)
@param header tytu³ okna
@param info informacja wyœwietlana w oknie*/
void GUI_Messagebox(const char*header, const char*info);

/**Funkcja wczytuj¹ca teksturê z pliku BMP
@param render render
@param path œcie¿ka do pliku z tekstur¹
@return wczytana tekstura lub NULL w przypadku gdy nie uda³o siê wczytaæ tekstury*/
SDL_Texture* GUI_TextureBMP(SDL_Renderer* render, char* path);

/**Funkcja wczytuj¹ca teksturê z pliku BMP, zmienia kolor t³a na przeŸroczysty
@param render render
@param path œcie¿ka do pliku z tekstur¹
@param red iloœæ czerwieni w kolorze t³a
@param green iloœæ zieleni w kolorze t³a
@param blue iloœæ niebieskiego w kolorze t³a
@param return wczytana tekstura lub NULL w przypadku gdy nie uda³o siê wczytaæ tekstury*/
SDL_Texture* GUI_TextureBMPWithoutBackground(SDL_Renderer* render, char* path, Uint8 red, Uint8 green, Uint8 blue);

/**Funkcja Rozpoczyna pracê z bibliotek¹ SDL, jeœli wyst¹pi³ b³¹d funkcja wypisuje na ekranie konsoli informacjê o b³êdzie
@return true, jeœli uda³o siê poprawnie zainicjowaæ bibliotekê, w przeciwnym wypadku false*/
bool InitSDL2();

/**Funkcja tworzy okno i sprawdza czy zosta³o poprawnie utworzone
@return okno biblioteki lub NULL jeœli nie uda³o siê utworzyæ okna*/
SDL_Window* CreateAWindow();

/**Funkcja tworzy render biblioteki i sprawdza czy zosta³ poprawnie utworzony
@return render lub NULL jeœli nie zosta³ poprawnie utworzony*/
SDL_Renderer* CreateARenderer(SDL_Window*window);

#endif
