#ifndef GUI_CHESSBOARD_H
#define GUI_CHESSBOARD_H
#include "GUI_Widget.h"
#include "Game.h"
#include "GUI_HelpForSDL.h"

//Rozmiar pola na szachownicy
#define GUI_SQUARE 90

//Definujemy wspó³rzêdne lewego górnego rogu szachownicy - od tego punktu zaczniemy rysowanie
#define START_X 20
#define START_Y 20

//Struktura odpowiedzialna za graficzne przedstawienie szachownicy
typedef struct guichessboard_t
{
	Game* game; //Informacje zwi¹zane z rozgrywk¹

	movetab Move_Tab;//Szachownica z rodzajami ruchów

	Square from;//Pole z którego ma zostaæ wykonany ruch
	Square Moves; //Pole na które ma zostaæ wykonany ruch

	//Tekstury bia³ych figur
	SDL_Texture* Pawn_white_tx;
	SDL_Texture* Rook_white_tx;
	SDL_Texture* Knight_white_tx;
	SDL_Texture* Bishop_white_tx;
	SDL_Texture* Queen_white_tx;
	SDL_Texture* King_white_tx;

	//Tekstury czarnych figur
	SDL_Texture* Pawn_black_tx;
	SDL_Texture* Rook_black_tx;
	SDL_Texture* Bishop_black_tx;
	SDL_Texture* Knight_black_tx;
	SDL_Texture* Queen_black_tx;
	SDL_Texture* King_black_tx;

	SDL_Renderer* renderer; //render
	SDL_Rect location;// po³o¿enie wid¿etu szachownicy w oknie
	void(*ChessboardAction)(void); //WskaŸnik na funkcjê obs³uguj¹c¹ akcje zwi¹zane z szachownic¹

}GUI_Chessboard;

//-----FUNKCJE-----//

/*Funkcja tworz¹ca wid¿et szachownicy, je¿eli nie uda³o siê poprawnie zaalokowaæ struktury funkcja zwraca NULL
@param renderer render
@param location po³o¿enie szachownicy
@param ChessboardAction funkcja obs³uguj¹ca akcje zwi¹zane z szachownic¹
@param game struktura zawieraj¹ca informacje o rozgrywce
@return utworzony wid¿et lub NULL w przypadku, gdy nie uda³o siê poprawnie utworzyæ szachownicy*/
GUI_Widget* GUI_CreateChessboard(SDL_Renderer* renderer,SDL_Rect location,void(*ChessboardAction)(void),Game* game);

/*Funkcja usuwaj¹ca szachownicê z pamiêci komputera
@param widget szachownica*/
void GUI_DestroyChessboard(GUI_Widget* widget);

/*Funkcja obs³uguj¹ca zdarzenia zwi¹zane z szachownic¹
@param widget szachownica
@param event zdarzenie do obs³u¿enia*/
void GUI_handleChessboardEvent(GUI_Widget* widget, SDL_Event* event);

/*Funkcja prezentuj¹ca szachownicê na ekranie
@param widget szachownica
@param renderer render*/
void GUI_DrawChessboard(GUI_Widget* widget, SDL_Renderer* renderer);


#endif