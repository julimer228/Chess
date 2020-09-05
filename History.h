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
}HistoryElement;

/**Funkcja dodaje nowy element, zawieraj¹cy informacjê o ruchu wykonanym przez gracza, na pocz¹tek listy.
@param from pole z którego wykonywany jest ruch
@param to pole na które wykonywany jest ruch
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej*/
void AddAnElement(Square from, Square to, HistoryElement** pHead);

/**Pomocnicza funkcja wypisuj¹ca elementy listy na ekranie (od pierwszego elementu).
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej*/
void PrintOnTheScreen (HistoryElement *pHead);

/**Usuwa listê jednokierunkow¹ iteracyjnie od pocz¹tku
@param pHead wskaŸnik na pierwszy element listy jednokierunkowej*/
void RemoveFormMemory(HistoryElement **pHead);
#endif