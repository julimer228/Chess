/**@FILE*/
#ifndef HISTORY_H
#define HISTORY_H
#include<stdbool.h>
#include<stdio.h>
 /**Struktura reprezentuj�ca pole na szachownicy*/
typedef struct square
{
    int row, column;
}Square;
/**Struktura u�yta do zapisu przebiegu rozgrywki. Lista jednokierunkowa.*/
typedef struct history
{
    struct history* pNext;
    Square from;
    Square to;
}HistoryElement;

/**Funkcja sprawdza czy pole znajduje si� na szachownicy
@param boardsquare pole kt�re chcemy sprawdzi�
@return true je�li pole znajduje si� na szachownicy, w przeciwnym wypadku false.*/
bool IsOnTheChessboard(Square* boardsquare);

/**Funkcja dodaje nowy element, zawieraj�cy informacj� o ruchu wykonanym przez gracza, na pocz�tek listy.
@param from pole z kt�rego wykonywany jest ruch
@param to pole na kt�re wykonywany jest ruch
@param pHead wska�nik na pocz�tek listy jednokierunkowej
@return true je�eli element zosta� dodany poprawnie, w przeciwnym wypadku false
@warning Funkcja alokuje pami��!*/
bool AddAnElement(Square *from, Square *to, HistoryElement* pHead);

/**Saves the game history to the file
@param pHead wska�nik na pocz�tek listy jednokierunkowej
@param FileName nazwa pliku do kt�rego ma zosta� zapisany przebieg rozgrywki
@return true je�eli historia rozgrywki zosta�a zapisana poprawnie w przeciwnym wypadku false*/
bool SaveToFile();

/**Usuwa list� jednokierunkow� rekurencyjnie od ko�ca.
@param pHead wska�nik na pierwszy element listy jednokierunkowej
@return true je�eli lista zosta�a usuni�ta poprawnie lub by�a pusta, w przeciwnym wypadku false*/
bool RemoveFormMemory();
#endif