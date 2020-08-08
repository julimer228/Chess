/**@FILE*/
#ifndef GAME_H
#define GAME_H
//#include "History.h"
#include<stdbool.h>
#include<stdio.h>
#include "History.h"

/**Definicje*/

/**Liczba pól w wierszu (kolumnie) szachownicy*/
#define SIZE 8
/**Reprezentacja pustego pola*/
#define EMPTY 0
/**Reprezentacja białych figur*/
#define PAWN_WHITE 1//pion
#define ROOK_WHITE 2//wieża
#define BISHOP_WHITE 3//goniec
#define KNIGHT_WHITE 4 //skoczek
#define QUEEN_WHITE 5 //hetman
#define KING_WHITE 6 //król
/**Reprezentacja czarnych figur*/
#define PAWN_BLACK -1 //pion
#define ROOK_BLACK -2 //wieża
#define BISHOP_BLACK -3 //goniec
#define KNIGHT_BLACK -4 //skoczek
#define QUEEN_BLACK -5 //hetman
#define KING_BLACK -6 //król

/**Kolor gracza*/
typedef enum players_t
{
    white,//gracz biały
    black //gracz czarny

}Player;

/**Szachownica*/
typedef int chessboard[SIZE][SIZE];

/**Typy pól na szachownicy ze względu na możliwość wykonania ruchu*/
typedef enum squaretype
{
    valid, //pole dozwolone
    invalid, //pole niedozwolone
    killed, //pole dozwolone, nastąpi zbicie figury przeciwnika
    threatened, //pole niedozwolone, król aktualnego gracza będzie w szachu
    killed_and_threatened,//pole niedozwolone, możliwe zbicie, jednak król aktualnego gracza będzie w szachu
    king_threatened,//pole dozwolone, król przeciwnika jest w szachu
}SquareType;

/**Szachownica zawierająca pola w raz z typami możliwych ruchów do wykonania*/
typedef SquareType BoardWithTypes[SIZE][SIZE];

/**Struktura reprezentująca grę*/
typedef struct game
{
    Player CurrentPlayer; //aktualny gracz
    chessboard Chessboard; //szachownica
    bool WhiteCheck; //czy biały król jest w szachu
    bool BlackCheck; // czy czarny król jest w szachu
    HistoryElement* pHead; //wskaźnik na początek listy jednokierunkowej do której zapisywany jest przebieg rozgrywki

}Game;

/**Typ zawierający błędy jakie mogą wystąpić podczas rozgrywki*/
typedef enum moveinfo
{
    INVALID_MOVE, //ruch jest poprawny
    VALID_MOVE, //ruch jest niepoprawny
    INVALID_MOVE_ACTUAL_KING_IS_IN_DANGER, //ruch jest niepoprawny, król aktualnego gracza byłby w szachu
    VALID_MOVE_OPPONENT_KING_IS_IN_DANGER //ruch
}MoveInfo;

/**PROTOTYPY FUNKCJI/

/**Funkcja zapisuje ustawienie początkowe figur na szachownicy
@param Chessboard szachownica na której będą rozkładane figury
*/
void InitializeTheChessboard(chessboard Chessboard);

/**Funkcja tworząca nową grę
@warning Funkcja alokuje pamięć!*/
Game* CreateGame();

/**Funkcja usuwająca grę z pamięci
@param new_game wskaźnik na zakończoną partię*/
void DestroyGame(Game* new_game);

/**Funkcja drukująca szachownicę na ekranie konsoli
@param new_game aktualnie rozgrywana gra.*/
void PrintChessboard(Game* new_game);

/**Funkcja sprawdza czy pole na które ma zostać przesunięta figura jest puste
@param to pole na które ma zostać przesunięta figura
@param new_game aktualnie rozgrywana partia
@return true jeśli pole jest puste, false jeśli pole jest zajęte*/
bool IsEmpty(Square* to, Game* new_game);

/**Funkcja sprawdza czy pole na które ma zostać przesunięta figura zajmuje figura przeciwnika (nastąpi zbicie)
@param from pole z którego ma nastąpić ruch
@param to pole na które ma zostać przesunięta figura
@return true, jeśli pole jest zajęte przez figurę przeciwnika, w przeciwnym wypadku false*/
bool IsEnemy(Square* to, Square* from, Game* new_game);

/**Funkcja odpowiadająca za ruch pionka
@param new_geme aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param to pole na które figura ma zostać przesunięta
@return true jeśli ruch jest możliwy do wykonania, false jeśli ruch nie jest możliwy*/
bool PawnMove(Game* new_game, Square *from, Square *to);

/**Funkcja sprawdzająca czy ruch skoczka jest poprawny
@param new_geme aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param to pole na które figura ma zostać przesunięta
@return true jeśli ruch jest możliwy do wykonania, false jeśli ruch nie jest możliwy*/
bool RookMove(Game* new_game, Square *from, Square *to);

/**Funkcja sprawdzająca czy ruch wieży jest poprawny
@param new_geme aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param to pole na które figura ma zostać przesunięta
@return true jeśli ruch jest możliwy do wykonania, false jeśli ruch nie jest możliwy*/
bool KnightMove(Game* new_game, Square *from, Square *to);

/**Funkcja odpowiadająca za ruch gońca
@param new_geme aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param to pole na które figura ma zostać przesunięta
@return true jeśli ruch jest możliwy do wykonania, false jeśli ruch nie jest możliwy*/
bool BishopMove(Game* new_game, Square *from, Square *to);

/**Funkcja sprawdzająca czy ruch hetmana jest poprawny
@param new_geme aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param to pole na które figura ma zostać przesunięta
@return true jeśli ruch jest możliwy do wykonania, false jeśli ruch nie jest możliwy*/
bool QueenMove(Game* new_game, Square *from, Square *to);

/**Funkcja sprawdzająca czy ruch króla jest poprawny
@param new_geme aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param to pole na które figura ma zostać przesunięta
@return true jeśli ruch jest możliwy do wykonania, false jeśli ruch nie jest możliwy*/
bool KingMove(Game* new_game, Square from, Square to);

/**Funkcja przesuwająca figurę
@param from pole z którego następuje ruch
@param to pole na które przesuwana jest figura
@param new_game aktualnie rozgrywana partia*/
void Move(Square* from, Square* to, Game* new_game);

/**Funkcja odpowiadająca za promocję piona, jeśli pion znajduje się w pierwszym lub ostatnim wierszu
szachownicy, zostaje zamieniony w hetmana. W przeciwnym wypadku funkcja nie robi nic.
@param new_game aktualnie rozgrywana gra
@param to pole na które został przesunięty pionek*/
void PawnPromotion(Game* new_game, Square* to);

/*Funkcja rozpoznaje jaka figura znajduje się na polu i sprawdza, czy ruch może zostać wykonany.
@param new_game aktualnie rozgrywana partia
@param from pole z którego ma zostać wykonany ruch
@param to pole na które ma zostać przesunięta figura
@return informacja o ruchu*/
MoveInfo GetMove(Game* new_game, Square* from, Square* to);

/*Sprawdza, czy król aktualnego gracza jest w szachu*/
bool IsActualPlayerKingInDanger();

/*Sprawdza, czy król przeciwnika jest w szachu*/
bool IsOpponentKingInDanger();

/*Ustawia ole odpowiedniego gracza w szachu*/
void SetCheckState(Game* new_game);
#endif

 
