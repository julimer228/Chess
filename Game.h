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
/**Rodzaje możliwych ruchów na szachownicy*/
typedef enum movetab_t
{
    MOVE_IS_INVALID,//ruch niepoprawny
    MOVE_VALID_KILLED_DANGER,//ruch poprawny, nastąpi zbicie, figura będzie stała na polu zgrożonym zbiciem
    MOVE_VALID_KILLED,//Ruch poprawny, nastąpiło zbicie
    MOVE_VALID_DANGER,//Ruch poprawny figura stoi na polu zagrożonym zbiciem
    MOVE_INVALID_KING_DANGER,//Ruch niepoprawny król byłby w szachu
    MOVE_VALID//Poprawny ruch
}MoveTab;

typedef MoveTab movetab[SIZE][SIZE];

/**Informacje o przebiegu gry*/
typedef enum message_t {
    MS_INVALID_MOVE,//Ruch jest niepoprawny
    MS_SUCESS_MOVE,//Ruch poprawny
    MS_INVALID_MOVE_KING_IN_DANGER,//Ruch jest niepoprawny król byłby w szachu
    MS_VALID_MOVE_KILLED,//Ruch poprawny nastąpiło zbicie
    MS_VALID_MOVE_DANGER_KILLED,//Ruch poprawny nastąpiło zbicie, pionek znajduje się na zagrożonym polu
    MS_INVALID_SQUARE,//Niepoprawne pole
    MS_INVALID_PIECE,//Niepoprawna figura
    MS_GAME_ERROR,//Struktura reprezentująca grę nie istnieje lub została niepoprawnie zaalokowana
    GAME_UNDO_NO_HISTORY,
    GAME_UNDO_SUCCESS,
    MS_GAME_SUCCESS//sukces
} Message;


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

/*Funkcja pobiera dozwolone ruchy dla figury dowolnego koloru
@param Chessboard szachownica
@param tab tablica dozwolonych ruchów
@param from pole z którego ma zostać wykonany ruch*/
void GetValidMoves(chessboard Chessboard, bool tab[SIZE][SIZE], Square from);

/*Funkcja przypisuje każdemu polu rodzaj ruchu jaki może zostać wykonany
@param game aktualnie rozgrywana partia
@param tab tablica dozwolonych ruchów
@param sq pole z którego ma zostać wykonany ruch
@param Move_Tab tablica z rodzajami ruchów jakie mogą zostać wykonane z pola from*/
void FillTheMoveTab(Game* game, bool tab[SIZE][SIZE], Square sq, movetab Move_Tab);

/*Funkcja sprawdza czy ruch jest poprawny (na podstawie tablicy z rodzajami ruchów)
@param moveType rodzaj ruchu przypisany do pola
@return true jeśli ruch jest poprawny false jeśli ruch jest niepoprawny*/
bool IsAValidMove(MoveTab moveType);

/**Główna funkcja sprawdzająca czy ruch podany przez gracza jest poprawny
@param game aktualnie rozgrywana partia
@param from pole z którego ma zostać wykonany ruch
@param to pole na które ma zostać wykonany ruch
@return wiadomość o błędzie lub o rodzaju wykonanego ruchu*/
Message SetMove(Game* game, Square* from, Square* to);
#endif

 
