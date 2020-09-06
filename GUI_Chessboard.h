/**@FILE*/
#ifndef GUI_CHESSBOARD_H
#define GUI_CHESSBOARD_H
#include "Game.h"
#include "GUI_HelpForSDL.h"
#include "History.h"
/**D³ugoœæ krawêdzi pola szachownicy*/
#define GUI_SQUARE 90

/**Definujemy wspó³rzêdne lewego górnego rogu szachownicy - od tego punktu zaczniemy rysowanie*/
#define START_X 20
#define START_Y 20

/**Struktura odpowiedzialna za graficzne przedstawienie szachownicy*/
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
	SDL_Rect location;// po³o¿enie szachownicy w oknie

}GUI_Chessboard;

/**Funkcja wyœwietlaj¹ca wiadomoœæ na ekranie który z graczy zwyciê¿y³ lub informacjê o remisie. Zwraca informacjê, czy gra zosta³a zakoñczona.
@param Chessboard szachownica
@return false jeœli gra nie zosta³a zakoñczona lub true jeœli gra zosta³a zakoñczona*/
bool GUI_EndOfGame(GUI_Chessboard* Chessboard);


/**Funkcja podœwietla pole na którym stoi król na kolor czerwony je¿eli król aktualnego gracza jest w szachu
@param guichessboard szachownica
@param renderer render*/
void GUI_ColorKingSquareWhenCheck(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja wyœwietla okienko z informacj¹ czy król aktualnego gracza jest w szachu
@param Chessboard szachownica*/
void UpdateTheChessboard(GUI_Chessboard* Chessboard);

/**Funkcja zwracaj¹ca wybrany kwadrat szachownicy
@param i numer wiersza
@param j numer kolumny
@return pole znajduj¹ce siê w i-tym wierszu i j-otej kolumnie*/
SDL_Rect GUI_ChessboardGetSquare(int i, int j);

/**Funkcja obs³uguje klikniêcie lewym przyciskiem myszy w pole na szachownicy
@param guichessboard szachownica
@param i numer wiersza w którym znajduje siê pole
@param j numer kolumny w której znajduje siê pole*/
void GUI_MouseButtonLeftClick(GUI_Chessboard* guichessboard, int i, int j);

/**Funkcja obs³uguje klikniêcie prawym przyciskiem myszy w pole na szachownicy
Zostaje wype³niona tabilca dozwolonych ruchów, je¿eli klikniêto w³aœciwe pole.
@param guichessboard szachownica
@param i numer wiersza w którym znajduje siê pole
@param j numer kolumny w której znajduje siê pole*/
void GUI_MouseButtonRightClick(GUI_Chessboard* guichessboard, int i, int j);

/**Funkcja koloruje kwadraty ze wzglêdu na rodzaj ruchu jaki mo¿e zostaæ wykonany poprawnie wybran¹ figur¹
@param guichessboard szachownica
@param renderer render*/
void GUI_ColorTheMoveSquares(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja koloruje wybrane pole
@param guichessboard szachownica
@param renderer render*/
void GUI_ColorChosenSquare(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja rysuj¹ca pust¹ szachownicê
@param guichessboard szachownica
@param renderer render*/
void GUI_DrawEmptyChessboard(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);



/**Funkcja tworz¹ca szachownicê, je¿eli nie uda³o siê poprawnie zaalokowaæ struktury funkcja zwraca NULL
@param renderer render
@param location po³o¿enie szachownicy
@param game struktura gry
@return utworzona szachownica lub NULL w przypadku, gdy nie uda³o siê poprawnie utworzyæ szachownicy*/
GUI_Chessboard* GUI_CreateChessboard(SDL_Renderer* renderer,SDL_Rect location ,Game* game);

/**Funkcja rysuje figury w odpowiednich miejscach na szachownicy
@param guichessboard szachownica
@param renderer render*/
void GUI_DrawPieces(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);

/**Funkcja usuwaj¹ca szachownicê z pamiêci komputera
@param guichessboard szachownica*/
void GUI_DestroyChessboard(GUI_Chessboard* guichessboard);

/**Funkcja obs³uguj¹ca zdarzenia zwi¹zane z szachownic¹
@param guichessboard szachownica
@param event zdarzenie do obs³u¿enia*/
void GUI_handleChessboardEvent(GUI_Chessboard* guichessboard, SDL_Event* event);

/**Funkcja prezentuj¹ca szachownicê na ekranie
@param guichessboard szachownica
@param renderer render*/
void GUI_DrawChessboard(GUI_Chessboard* guichessboard, SDL_Renderer* renderer);
#endif