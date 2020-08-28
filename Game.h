/**@FILE*/
#ifndef GAME_H
#define GAME_H
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

/**Struktura reprezentująca grę*/
typedef struct game_t
{
    Player CurrentPlayer; //aktualny gracz
    chessboard Chessboard; //szachownica
    bool WhiteCheck; //czy biały król jest w szachu
    bool BlackCheck; // czy czarny król jest w szachu
    bool HasGameEnded;//zawiera informację, czy gra została zakończona
    HistoryElement* pHead; //wskaźnik na początek listy jednokierunkowej do której zapisywany jest przebieg rozgrywki
    char file_name[50];//nazwa pliku do którego zostanie zapisany przebieg partii, po zakończeniu gry
}Game;

typedef enum moveinformation
{
    INVALID_SQUARE,
    INVALID_PIECE,
    INVALID_MOVE,
    KING_IN_DANGER,
    KING_STILL_IN_DANGER,
    VALID_KING_DANGER,
    VALID_MOVE
}MoveInformation;
/*-------------------------PROTOTYPY FUNKCJI--------------------------------*/

/**Funkcja zapisuje ustawienie początkowe figur na szachownicy
@param Chessboard szachownica na której będą rozkładane figury
*/
//static void InitializeTheChessboard(chessboard Chessboard);

/**Funkcja tworząca nową grę
@warning Funkcja alokuje pamięć!*/
Game* CreateGame();

/**Funkcja usuwająca grę z pamięci
@param new_game wskaźnik na zakończoną partię*/
void DestroyGame(Game* new_game);

/**Funkcja zmieniająca kolor aktualnego gracza
@param new_game aktualnie rozgrywana partia*/
void SwitchPlayers(Game* new_game);

/**Funkcja sprawdza czy król białego lub czarnego gracza znajduje się w szachu
@param Chessboard szachownica
@param player gracz*/
bool IsKingChecked(chessboard* Chessboard, Player player);

/*Funkcja wykonuje ruch bierki i zamienia graczy, dodaje element do historii, sprawdza czy któryś król jest w szachu
@param game aktualnie rozgrywana partia
@param from pole z którego przesuwamy bierkę
@param to pole na które przesuwamy bierkę*/
void MakeAMove(Game* game, Square* from, Square* To);

/*Funkcja sprawdza czy król aktualnego gracza znajduje się w szachu
@param game aktualnie rozgrywana partia*/
bool IsActualPlayerInCheck(Game* game);

/*Funkcja pobiera dozwolone ruchy dla figury aktualnego gracza na danym polu
@param Chessboard szachownica
@param tab tablica dozwolonych ruchów
@param from pole z którego ma zostać wykonany ruch*/
void GetValidMoves(chessboard Chessboard, bool tab[SIZE][SIZE], Square* from);

/**Funkcja drukująca szachownicę na ekranie konsoli
@param new_game aktualnie rozgrywana gra.*/
//void PrintChessboard(Game* new_game);

/**Funkcja sprawdza czy pole na które ma zostać przesunięta figura jest puste
@param to pole na które ma zostać przesunięta figura
@param new_game aktualnie rozgrywana partia
@return true jeśli pole jest puste, false jeśli pole jest zajęte*/
//bool IsEmpty(Square* to, Game* new_game);

/**Funkcja sprawdza czy pole na które ma zostać przesunięta figura zajmuje figura przeciwnika (nastąpi zbicie)
@param from pole z którego ma nastąpić ruch
@param to pole na które ma zostać przesunięta figura
@return true, jeśli pole jest zajęte przez figurę przeciwnika, w przeciwnym wypadku false*/
//bool IsEnemy(Square* to, Square* from, Game* new_game);

/*--------------FUNKCJE ODPOWIEDZIALNE ZA RUCHY FIGUR------------------------*/
/* Funkcje działają dla figur białego gracza, aby zastosować je dla czarnego */ 
/* gracza należy odwrócić planszę, oraz zamienić kolory figur                */
/*---------------------------------------------------------------------------*/

/**Funkcja po podaniu pola startowego, z którego ma ruszyć pionek zaznacza, które pola są dozwolone.
@param Chessboard szachownica zawierająca aktualne ustawienie figur na planszy
@param from pole z którego ma natąpić ruch
@param tab tablica dwuwymiarowa zawierająca informację, na które pola można przesunąć piona*/
//void PawnMove(chessboard Chessboard, Square *from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdzająca czy ruch wieży jest poprawny
@param Chessboard aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param tab tablica dwuwymiarowa zawierająca informację, na które pola można przesunąć wieżę*/
//void RookMove(chessboard Chessboard, Square*from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdzająca czy ruch skoczka jest poprawny
@param Chessboard aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param tab tablica dwuwymiarowa zawierająca informację, na które pola można przesunąć skoczka*/
//void KnightMove(chessboard Chessboard, Square *from, bool tab[SIZE][SIZE]);

/**Funkcja odpowiadająca za ruch gońca
@param Chessboard aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param tab tablica dwuwymiarowa zawierająca informację, na które pola można przesunąć gońca*/
//void BishopMove(chessboard Chessboard, Square*from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdzająca czy ruch hetmana jest poprawny
@param Chessboard aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param tab tablica dwuwymiarowa zawierająca informację, na które pola można przesunąć hetmana*/
//void QueenMove(chessboard Chessboard, Square *from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdzająca czy ruch króla jest poprawny
@param Chessboard aktualnie rozgrywana partia
@param from pole z którego ma natąpić ruch
@param tab tablica dwuwymiarowa zawierająca informację, na które pola można przesunąć króla*/
//void KingMove(chessboard Chessboard, Square *from, bool tab[SIZE][SIZE]);

/**Funkcja odpowiadająca za promocję piona, jeśli pion znajduje się w pierwszym lub ostatnim wierszu
szachownicy, zostaje zamieniony w hetmana. W przeciwnym wypadku funkcja nie robi nic.
@param Chessboard szachownica
@param to pole na które został przesunięty pionek*/
//void PawnPromotion(chessboard Chessboard, Square* to);

/*Funkcja rozpoznaje jaka figura znajduje się na polu określa na jakie pola figura może zostać przesunięta.
@param Chessboard szachownica
@param from pole z którego ma zostać wykonany ruch
@param tab tablica dwuwymiarowa zawierająca dozwolone i niedozwolone pola*/
//void GetMove(chessboard Chessboard, bool tab[SIZE][SIZE], Square* from);

/*Funkcja zaznacza w tablicy tab wszystkie możliwe ruchy białego gracza*
@param Chessboard szachownica 
@param tab tablica dwuwymiarowa zawierająca dozwolone i niedozwolone pola*/
//void GetAllMoves(chessboard Chessboard, bool tab[SIZE][SIZE]);

/*Funkcja odwracająca Szachownicę o 180 stopni. Zamienia kolor figur na przeciwny. Pozwala używać funkcji napisanych dla białego gracza, także dla czarnego gracza.
@param Chessboard szachownica z aktualnym ustawieniem figur*/
//void TurnTheBoardChangeColor(chessboard Chessboard);

/*Funkcja odwracająca szachownicę o 180 stopni.
@param Chessboard szachownica z aktualnym ustawieniem figur*/
//void TurnTheBoard(chessboard Chessboard);

/*Funkcja zwraca pole na którym stoi czarny król
@param Chessboard
@return Square* wskaźnik na pole na którym stoi król
@warning Funkcja alokuje pamięć!*/
//Square* FindTheBlackKing(chessboard Chessboard);

/**Funkcja sprawdza czy czarny król jest w szachu
@param Chessboard
@return true jeśli król jest w szachu, false jeśli nie jest*/
//bool IsBlackKingChecked(chessboard Chessboard);

/**Funkcja sprawdza czy bierka należy do aktualnego gracza
@param currentplayer aktualny gracz
@param Chessboard szachownica z aktualnym ułożeniem figur
@param square_ pole na którym stoi figura
@return true, jeśli figura należy do aktualnego gracza, w przeciwnym wypadku false*/
//bool BelongsToCurrentPlayer(Player currentplayer, chessboard Chessboard, Square* square_);


/*-----------FUNKCJE POMOCNICZE UŻYTE DO DEBUGOWANIA PROJEKTU------------------------- */
/*Funkcja wypisuje na ekranie zawartość tablicy zawierającej możliwe do wykonania ruchy*/
//void PrintBoolTab(bool tab[SIZE][SIZE]);

#endif

 
