/**@FILE*/
#ifndef GAME_H
#define GAME_H
#include <stdlib.h>
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
/**Funkcja tworząca nową grę
@warning Funkcja alokuje pamięć!*/
Game* CreateGame();

/**Funkcja usuwająca grę z pamięci
@param new_game wskaźnik na zakończoną partię*/
void DestroyGame(Game** game);

/**Funkcja zmieniająca kolor aktualnego gracza
@param new_game aktualnie rozgrywana partia*/
void SwitchPlayers(Game* new_game);

/**Funkcja sprawdza czy król białego lub czarnego gracza znajduje się w szachu
@param Chessboard szachownica
@param player gracz*/
bool IsKingChecked(chessboard Chessboard, Player player);

/*Funkcja wykonuje ruch bierki i zamienia graczy, dodaje element do historii, sprawdza czy któryś król jest w szachu
@param game aktualnie rozgrywana partia
@param from pole z którego przesuwamy bierkę
@param to pole na które przesuwamy bierkę*/
void MakeAMove(Game* game, Square from, Square To);

/*Funkcja sprawdza czy król aktualnego gracza znajduje się w szachu
@param game aktualnie rozgrywana partia*/
bool IsActualPlayerInCheck(Game* game);

/*Funkcja zwraca kolor aktualnego gracza
@param game aktualnie rozgrywana partia
@return kolor aktualnego gracza*/
Player ColorOfActualPlayer(Game* game);

/*Funkcja zwraca kolor przeciwnego gracza
@param game aktualnie rozgrywana partia
@return kolor przeciwnego gracza*/
Player ColorOfOpponentPlayer(Game* game);

/*Funkcja sprawdzająca czy bierka należy do aktualnego gracza
@param game aktualnie rozgrywana partia
@param piece_square pole na którym stoi bierka
@return true, jeśli bierka należy do aktualnego gracza w przeciwnym wypadku false*/
bool BelongsToActualPlayer(Game* game, Square piece_square);

/*Funkcja pobiera dozwolone ruchy dla figury aktualnego gracza na danym polu
@param Chessboard szachownica
@param tab tablica dozwolonych ruchów
@param from pole z którego ma zostać wykonany ruch*/
void GetValidMoves(chessboard Chessboard, bool tab[SIZE][SIZE], Square from);

#endif

 
