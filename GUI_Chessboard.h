/**@FILE*/
#ifndef GUI_CHESSBOARD_H
#define GUI_CHESSBOARD_H
#include "Game.h"
#include "GUI_HelpForSDL.h"
#include "History.h"
/**D�ugo�� kraw�dzi pola szachownicy*/
#define GUI_SQUARE 90

/**Definujemy wsp�rz�dne lewego g�rnego rogu szachownicy - od tego punktu zaczniemy rysowanie*/
#define START_X 20
#define START_Y 20

/**Struktura odpowiedzialna za graficzne przedstawienie szachownicy*/
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
	SDL_Rect location;// po�o�enie szachownicy w oknie

}GUI_Chessboard;

/**Funkcja wy�wietlaj�ca wiadomo�� na ekranie kt�ry z graczy zwyci�y� lub informacj� o remisie. Zwraca informacj�, czy gra zosta�a zako�czona.
@param Chessboard szachownica
@return false je�li gra nie zosta�a zako�czona lub true je�li gra zosta�a zako�czona*/
bool GUI_EndOfGame(GUI_Chessboard* Chessboard);


/**Funkcja pod�wietla pole na kt�rym stoi kr�l na kolor czerwony je�eli kr�l aktualnego gracza jest w szachu
@param guichessboard szachownica
@param renderer render*/
void GUI_ColorKingSquareWhenCheck(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja wy�wietla okienko z informacj� czy kr�l aktualnego gracza jest w szachu
@param Chessboard szachownica*/
void UpdateTheChessboard(GUI_Chessboard* Chessboard);

/**Funkcja zwracaj�ca wybrany kwadrat szachownicy
@param i numer wiersza
@param j numer kolumny
@return pole znajduj�ce si� w i-tym wierszu i j-otej kolumnie*/
SDL_Rect GUI_ChessboardGetSquare(int i, int j);

/**Funkcja obs�uguje klikni�cie lewym przyciskiem myszy w pole na szachownicy
@param guichessboard szachownica
@param i numer wiersza w kt�rym znajduje si� pole
@param j numer kolumny w kt�rej znajduje si� pole*/
void GUI_MouseButtonLeftClick(GUI_Chessboard* guichessboard, int i, int j);

/**Funkcja obs�uguje klikni�cie prawym przyciskiem myszy w pole na szachownicy
Zostaje wype�niona tabilca dozwolonych ruch�w, je�eli klikni�to w�a�ciwe pole.
@param guichessboard szachownica
@param i numer wiersza w kt�rym znajduje si� pole
@param j numer kolumny w kt�rej znajduje si� pole*/
void GUI_MouseButtonRightClick(GUI_Chessboard* guichessboard, int i, int j);

/**Funkcja koloruje kwadraty ze wzgl�du na rodzaj ruchu jaki mo�e zosta� wykonany poprawnie wybran� figur�
@param guichessboard szachownica
@param renderer render*/
void GUI_ColorTheMoveSquares(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja koloruje wybrane pole
@param guichessboard szachownica
@param renderer render*/
void GUI_ColorChosenSquare(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja rysuj�ca pust� szachownic�
@param guichessboard szachownica
@param renderer render*/
void GUI_DrawEmptyChessboard(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);



/**Funkcja tworz�ca szachownic�, je�eli nie uda�o si� poprawnie zaalokowa� struktury funkcja zwraca NULL
@param renderer render
@param location po�o�enie szachownicy
@param game struktura gry
@return utworzona szachownica lub NULL w przypadku, gdy nie uda�o si� poprawnie utworzy� szachownicy*/
GUI_Chessboard* GUI_CreateChessboard(SDL_Renderer* renderer,SDL_Rect location ,Game* game);

/**Funkcja rysuje figury w odpowiednich miejscach na szachownicy
@param guichessboard szachownica
@param renderer render*/
void GUI_DrawPieces(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja usuwaj�ca szachownic� z pami�ci komputera
@param guichessboard szachownica*/
void GUI_DestroyChessboard(GUI_Chessboard* guichessboard);

/**Funkcja obs�uguj�ca zdarzenia zwi�zane z szachownic�
@param guichessboard szachownica
@param event zdarzenie do obs�u�enia*/
void GUI_handleChessboardEvent(GUI_Chessboard* guichessboard, SDL_Event* event);

/**Funkcja prezentuj�ca szachownic� na ekranie
@param guichessboard szachownica
@param renderer render*/
void GUI_DrawChessboard(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);
#endif