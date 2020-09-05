/**@FILE*/
#ifndef HISTORY_H
#define HISTORY_H
#include <stdlib.h>
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
    struct history* pNext; //kolejny element listy
    Square from; //pole z kt�rego wykonywany jest ruch
    Square to; //pole na kt�re wykonywany jest ruch
}HistoryElement;

/**Funkcja dodaje nowy element, zawieraj�cy informacj� o ruchu wykonanym przez gracza, na pocz�tek listy.
@param from pole z kt�rego wykonywany jest ruch
@param to pole na kt�re wykonywany jest ruch
@param pHead wska�nik na pocz�tek listy jednokierunkowej*/
void AddAnElement(Square from, Square to, HistoryElement** pHead);

/**Pomocnicza funkcja wypisuj�ca elementy listy na ekranie (od pierwszego elementu).
@param pHead wska�nik na pocz�tek listy jednokierunkowej*/
void PrintOnTheScreen (HistoryElement *pHead);

/**Usuwa list� jednokierunkow� iteracyjnie od pocz�tku
@param pHead wska�nik na pierwszy element listy jednokierunkowej*/
void RemoveFormMemory(HistoryElement **pHead);
#endif