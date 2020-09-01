/**@FILE*/
#ifndef HISTORY_H
#define HISTORY_H
#include <stdlib.h>
#include<stdbool.h>
#include<stdio.h>

 /**Struktura reprezentuj¹ca pole na szachownicy*/
typedef struct square
{
    int row, column;
}Square;

/**Struktura u¿yta do zapisu przebiegu rozgrywki. Lista jednokierunkowa.*/
typedef struct history
{
    struct history* pNext; //kolejny element listy
    Square from; //pole z którego wykonywany jest ruch
    Square to; //pole na które wykonywany jest ruch
    int KilledPiece; //Jeœli podczas wykonania ruchu zosta³a zbita bierka, to tutaj zostaje zapisana jej wartoœæ, w przeciwnym wypadku 0
    bool blackCheck;//czy czarny król jest w szachu
    bool whiteCheck;//Czy bia³y król jest w szachu
}HistoryElement;

/**Funkcja dodaje nowy element, zawieraj¹cy informacjê o ruchu wykonanym przez gracza, na pocz¹tek listy.
@param from pole z którego wykonywany jest ruch
@param to pole na które wykonywany jest ruch
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej
@param KilledPiece figura która zosta³a zbita podczas ruchu, omyœlnie 0
@return true je¿eli element zosta³ dodany poprawnie, w przeciwnym wypadku false
@warning Funkcja alokuje pamiêæ!*/
bool AddAnElement(Square from, Square to, HistoryElement** pHead, int KilledPiece);

/**Pomocnicza funkcja wypisuj¹ca elementy listy na ekranie (od pierwszego elementu).
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej*/
void PrintOnTheScreen (HistoryElement *pHead);

/**Funkcja usuwa pierwszy element listy jednokierunkowej (funkcja potrzebna przy cofaniu ruchu)
@param pHead wskaŸnik na pierwszy element listy jednokierunkowej*/
void RemoveFirstElement(HistoryElement** pHead);

/**Usuwa listê jednokierunkow¹ iteracyjnie od pocz¹tku
@param pHead wskaŸnik na pierwszy element listy jednokierunkowej*/
void RemoveFormMemory(HistoryElement **pHead);
#endif