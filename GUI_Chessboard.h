#ifndef GUI_CHESSBOARD_H
#define GUI_CHESSBOARD_H
#include "GUI_Widget.h"
#include "Game.h"
#include "GUI_HelpForSDL.h"

//Rozmiar pola na szachownicy
#define GUI_SQUARE 90

//Definujemy wsp�rz�dne lewego g�rnego rogu szachownicy - od tego punktu zaczniemy rysowanie
#define START_X 20
#define START_Y 20

//Struktura odpowiedzialna za graficzne przedstawienie szachownicy
typedef struct guichessboard_t
{
	Game* game; //Informacje zwi�zane z rozgrywk�

	movetab Move_Tab;//Szachownica z rodzajami ruch�w

	Square from;//Pole z kt�rego ma zosta� wykonany ruch
	Square Moves; //Pole na kt�re ma zosta� wykonany ruch

	//Tekstury bia�ych figur
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
	SDL_Rect location;// po�o�enie wid�etu szachownicy w oknie
	void(*ChessboardAction)(void); //Wska�nik na funkcj� obs�uguj�c� akcje zwi�zane z szachownic�

}GUI_Chessboard;

//-----FUNKCJE-----//

/*Funkcja tworz�ca wid�et szachownicy, je�eli nie uda�o si� poprawnie zaalokowa� struktury funkcja zwraca NULL
@param renderer render
@param location po�o�enie szachownicy
@param ChessboardAction funkcja obs�uguj�ca akcje zwi�zane z szachownic�
@param game struktura zawieraj�ca informacje o rozgrywce
@return utworzony wid�et lub NULL w przypadku, gdy nie uda�o si� poprawnie utworzy� szachownicy*/
GUI_Widget* GUI_CreateChessboard(SDL_Renderer* renderer,SDL_Rect location,void(*ChessboardAction)(void),Game* game);

/*Funkcja usuwaj�ca szachownic� z pami�ci komputera
@param widget szachownica*/
void GUI_DestroyChessboard(GUI_Widget* widget);

/*Funkcja obs�uguj�ca zdarzenia zwi�zane z szachownic�
@param widget szachownica
@param event zdarzenie do obs�u�enia*/
void GUI_handleChessboardEvent(GUI_Widget* widget, SDL_Event* event);

/*Funkcja prezentuj�ca szachownic� na ekranie
@param widget szachownica
@param renderer render*/
void GUI_DrawChessboard(GUI_Widget* widget, SDL_Renderer* renderer);


#endif