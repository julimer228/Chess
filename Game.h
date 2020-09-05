/**@FILE*/
#ifndef GAME_H
#define GAME_H
#include <stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#include "History.h"

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
    bool IsSaved;//informacja o tym czy gra została poprawnie zapisana
    char file_name[50];//nazwa pliku do którego zostanie zapisany przebieg partii, po zakończeniu gry

    Square From;//Poprzednie pole z którego był wykonywany ruch
    Square To;//Poprzednie pole na które był wykonywany ruch
    int piece_killed;//Informacja jaka figura została zbita w poprzednim ruchu
    bool whitecheck_t;//Informacja, czy w poprzednim ruchu biały król był w szachu
    bool blackcheck_t;//Informacja, czy w poprzednim ruchu czarny król był w szachu
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
/**Szachownica, której pola są wypełniane typami możliwych ruchów*/
typedef MoveTab movetab[SIZE][SIZE];

/**Informacje o tym jaki ruch został wykonany*/
typedef enum message_t {
    MS_INVALID_MOVE,//Ruch jest niepoprawny
    MS_SUCESS_MOVE,//Ruch poprawny
    MS_INVALID_MOVE_KING_IN_DANGER,//Ruch jest niepoprawny król byłby w szachu
    MS_SUCESS_MOVE_KILLED,//Ruch poprawny nastąpiło zbicie
    MS_INVALID_SQUARE,//Niepoprawne pole
    MS_INVALID_PIECE,//Niepoprawna figura
    MS_GAME_SUCCESS//sukces
} Message;

/**Informacja o tym czy gra została zakończona i z jakim rezultatem*/
typedef enum endofgame_t
{
    CONTINUE,
    OPPONENT_PLAYER_WINNER,
    DRAW
}EndOfGame_MS;

/**Funkcja zapisuje ustawienie początkowe figur na szachownicy
@param Chessboard szachownica na której będą rozkładane figury*/
void InitializeTheChessboard(chessboard Chessboard);

/**Funkcja sprawdza czy pole znajduje się na szachownicy
@param sq pole które chcemy sprawdzić
@return true, jeśli pole znajduje się na szachownicy w przeciwnym wypadku false*/
bool IsSquareOnTheChessboard(Square sq);

/**Funkcja sprawdza na które pola z pola from można wykonać ruch pionkiem. Jeśli ruch jest możliwy zapisuje wartość true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z którego ma zostać wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruchów*/
void PawnMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdza na które pole z pola from można wykonać ruch wieżą. Jeśli ruch jest możliwy zapisuje wartość true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z którego ma zostać wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruchów*/
void RookMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdza na które pole z pola from można wykonać ruch skoczkiem. Jeśli ruch jest możliwy zapisuje wartość true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z którego ma zostać wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruchów*/
void KnightMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdza na które pole z pola from można wykonać ruch gońcem. Jeśli ruch jest możliwy zapisuje wartość true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z którego ma zostać wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruchów*/
void BishopMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdza na które pole z pola from można wykonać ruch hetmanem. Jeśli ruch jest możliwy zapisuje wartość true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z którego ma zostać wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruchów*/
void QueenMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE]);

/**Funkcja sprawdza na które pole z pola from można wykonać ruch królem. Jeśli ruch jest możliwy zapisuje wartość true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z którego ma zostać wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruchów*/
void KingMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE]);

/**Zapisuje w tablicy tab wszystkie możliwe ruchy białej bierki stojącej na polu from
@param Chessboard szachownica
@param tab tablica dozwolonych ruchów
@param from pole z którego ma zostać wykonany ruch*/
void GetMovesOfTheWhitePiece(chessboard Chessboard, bool tab[SIZE][SIZE], Square from);


/**Funkcja zapisuje wszystkie możliwe ruchy bierek białego gracza
@param Chessboard szachownica
@param tab tablica dozwolonych ruchów*/
void GetAllMovesOfTheWhitePlayer(chessboard Chessboard, bool tab[SIZE][SIZE]);

/**Funkcja obraca szachownicę o 180 stopni i zamienia kolor bierek na przeciwny. Dzięki temu można używać funkcji definiujących ruchy figur
również dla czarnego gracza
@param Chessboar szachownica którą obracamy*/
void TurnTheBoardChangeColor(chessboard Chessboard);

/**Funkcja obraca tablicę możliwych ruchów o 180 stopni
@param tab tablica dozwolonych ruchów (bool)*/
void TurnTheValidMovesTab(bool tab[SIZE][SIZE]);

/**Funkcja zwraca pole na którym stoi czarny król
@param Chessboard szachownica
@return pole na którym znajduje się król, jeśli pola nie znaleziono zwraca pole o niedozwolonych współrzędnych (-1,-1)*/
Square FindTheBlackKing(chessboard Chessboard);

/**Funkcja sprawdza czy czarny król jest w szachu. Odnajduje czarnego króla na szachownicy, wypełnia dwuwymiarową tablicę
tab wszystkimi dozwolonymi ruchami białego gracza. Sprawdza czy biały gracz może wykonać ruch na pole zajmowane przez króla.
@param Chessboard szachownica
@return true jeśli czarny król jest w szachu w przeciwnym wypadku false*/
bool IsBlackKingChecked(chessboard Chessboard);

/**Funkcja sprawdza, czy czarna bierka jest zagrożona zbiciem przez białego gracza, działa analogicznie do funkcji
wykrywającej szach czarnego króla.
@param Chessboard szachownica
@param black_square pole na którym stoi czarna bierka
@return true jeśli czarna bierka jest zagrożona zbiciem przez białego gracza w przeciwnym wypadku false*/
bool BlackPieceInDanger(chessboard Chessboard, Square black_square);

/**Funkcja pozwalająca kolejnemu graczowi wykonać ruch (zmienia kolor aktualnego gracza i obraca planszę o 180 stopni)
@param game struktura reprezentująca grę*/
void PrepareForNextPlayerTurn(Game* game);

/**Funkcja sprawdza czy figura dowolnego gracza stojąca na polu sq jest zagrożona zbiciem przez figurę przciwnika
@param Chessboard szachownica
@param sq pole na którym stoi figura
@return true, jeśli figura jest zagrożona false jeśli nie jest zagrożona*/
bool IsPieceInDanger(chessboard Chessboard, Square sq);

/**Funkcja cofa ostatni ruch jaki został wykonany (funkcja potrzebna do sprawdzenia czy po wykonaniu ruchu król będzie w szachu, 
lub figura będzie stała na polu zagrożonym zbiciem).
@param game struktura reprezentująca grę*/
void DeleteLastMove(Game* game);

/**Funkcja sprawdza czy ruch powoduje, że król jest zagrożony przez figurę przeciwnika lub dowolna figura jest zagrożona zbiciem
@param game struktura reprezentująca grę
@param from pole z którego ma zostać wykonany ruch
@param to pole na które ma zostać wwykonany ruch
@param KingInDanger pole informujące czy król byłby w szachu
@param PieceInDanger pole informujące czy bierka byłaby zagrożona zbiciem*/
void CheckIfPieceOrKingWillBeInDanger(Game* game, Square from, Square to, bool* KingInDanger, bool* PieceInDanger);

/**Funkcja która wypełnia szachownicę typami możliwych ruchów jakie może wykonać figura stojąca na polu sq
(nie wymaga tablicy dozwolonych ruchów (bool tab) jako argumentu).
@param game struktura reprezentująca grę
@param Move_Tab tablica dwuwymiarowa z rodzajami ruchów
@param sq pole z którego ma zostać wykonany ruch*/
void FillTheMoveTabHelper(Game* game, movetab Move_tab, Square sq);

/**Funkcja tworząca nową grę
@return wskaźnik na nowo utworzoną grę*/
Game* CreateGame();

/**Funkcja usuwająca grę z pamięci
@param game gra która ma zostać usunięta*/
void DestroyGame(Game* game);

/**Funkcja zmieniająca kolor aktualnego gracza
@param game aktualnie rozgrywana partia*/
void SwitchPlayers(Game* game);

/**Funkcja sprawdza czy król białego lub czarnego gracza znajduje się w szachu
@param Chessboard szachownica
@param player kolor gracza
@return true, jeśli gracz znajduje się w szachu, w przeciwnym wypadku false*/
bool IsKingChecked(chessboard Chessboard, Player player);

/**Funkcja wykonuje ruch bierki i zamienia graczy, sprawdza czy któryś król jest w szachu
@param game struktura reprezentująca grę
@param from pole z którego przesuwamy bierkę
@param to pole na które przesuwamy bierkę*/
void MakeAMove(Game* game, Square from, Square to);

/**Funkcja sprawdza czy król aktualnego gracza znajduje się w szachu
@param game struktura reprezentująca grę*/
bool IsActualPlayerInCheck(Game* game);

/**Funkcja sprawdzająca czy bierka należy do aktualnego gracza
@param game aktualnie rozgrywana partia
@param piece_square pole na którym stoi bierka
@return true, jeśli bierka należy do aktualnego gracza w przeciwnym wypadku false*/
bool BelongsToActualPlayer(Game* game, Square piece_square);

/**Funkcja pobiera dozwolone ruchy dla figury dowolnego koloru
@param Chessboard szachownica
@param tab dwuwymiarowa tablica dozwolonych ruchów
@param from pole z którego ma zostać wykonany ruch*/
void GetValidMoves(chessboard Chessboard, bool tab[SIZE][SIZE], Square from);

/**Funkcja przypisuje każdemu polu rodzaj ruchu jaki może zostać wykonany
@param game struktura reprezentująca grę
@param tab dwuwymiarowa tablica dozwolonych ruchów
@param sq pole z którego ma zostać wykonany ruch
@param Move_Tab dwuwymiarowa tablica z rodzajami ruchów jakie mogą zostać wykonane z pola from*/
void FillTheMoveTab(Game* game, bool tab[SIZE][SIZE], Square sq, movetab Move_Tab);

/**Funkcja sprawdza czy ruch jest poprawny (na podstawie tablicy z rodzajami ruchów)
@param moveType rodzaj ruchu przypisany do pola
@return true jeśli ruch jest poprawny false jeśli ruch jest niepoprawny*/
bool IsAValidMove(MoveTab moveType);

/**Główna funkcja sprawdzająca czy ruch podany przez gracza jest poprawny, jeśli ruch jest 
poprawny to zostanie wykonany. Zwraca wiadomość o rodzaju ruchu.
@param game struktura reprezentująca grę
@param from pole z którego ma zostać wykonany ruch
@param to pole na które ma zostać wykonany ruch
@return wiadomość o błędzie lub o rodzaju wykonanego ruchu*/
Message SetMove(Game* game, Square from, Square to);

/**Funkcja sprawdza czy nastąpił koniec gry i zwraca odpowiednią informację
@param game struktura reprezentująca grę
@return informacja czy gra została zakończona wygraną jednego z graczy*/
EndOfGame_MS IsTheEndOfGame(Game* game);

/**Funkcja wypełnia tablicę typami dozwolonych ruchów, sprawdza czy została wybrana figura odpowiedniego koloru, 
oraz czy pole startowe znajduje się na szachownicy, zwraca informację czy udało się wypełnić tablicę, lub rodzaj nieprawidłowego
ruchu jaki wystąpił (np. wybór figury przeciwnika)
@param game struktura reprezentująca grę
@param from sprawdzane pole
@param Move_tab dwuwymiarowa tablica rodzajów ruchów
@return informacja o tym czy udało się wypełnić tablicę, jeśli nie udało się wypełnić tablicy zwraca informację
o tym czy została wybrana figura właściwgo koloru lub czy pole znajdowało się na szachownicy*/
Message SetMoveHelper(Game* game, Square from, movetab Move_tab);
#endif

 
