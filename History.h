/**@FILE*/
#ifndef HISTORY_H
#define HISTORY_H
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
    struct history* pNext;
    Square *from;
    Square *to;
}HistoryElement;

/**Funkcja alokuje pamiêæ dla struktury Square i nadaje jej polom zadane wartoœci
@param row wiersz w którym znajduje siê pole
@param column kolumna w której znajduje siê pole
@return wskaŸnik na nowo utworzon¹ strukturê, jeœli struktura nie zosta³a poprawnie zaalokowana w pamiêci, wskaŸnik ma wartoœæ NULL
@waring funkcja alokuje pamiêæ*/
Square* CreateNewSquare(int row, int column);

/**Funkcja usuwaj¹ca dynamicznie zaalokowan¹ strukturê quare z pamiêci
@param suare_t*/
void Remove

/**Funkcja sprawdza czy pole znajduje siê na szachownicy
@param boardsquare pole które chcemy sprawdziæ
@return true jeœli pole znajduje siê na szachownicy, w przeciwnym wypadku false.*/
bool IsOnTheChessboard(Square* boardsquare);

/**Funkcja dodaje nowy element, zawieraj¹cy informacjê o ruchu wykonanym przez gracza, na pocz¹tek listy.
@param from pole z którego wykonywany jest ruch
@param to pole na które wykonywany jest ruch
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej
@return true je¿eli element zosta³ dodany poprawnie, w przeciwnym wypadku false
@warning Funkcja alokuje pamiêæ!*/
bool AddAnElement(Square **from, Square **to, HistoryElement** pHead);

/**Saves the game history to the file
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej
@param FileName nazwa pliku do którego ma zostaæ zapisany przebieg rozgrywki
@return true je¿eli historia rozgrywki zosta³a zapisana poprawnie w przeciwnym wypadku false*/
bool SaveToFile();

/**Pomocnicza funkcja wypisuj¹ca elementy listy na ekranie (od pierwszego elementu).
@param pHead wskaŸnik na pocz¹tek listy jednokierunkowej*/
void PrintOnTheScreen (HistoryElement *pHead);

/**Usuwa listê jednokierunkow¹ iteracyjnie od pocz¹tku
@param pHead wskaŸnik na pierwszy element listy jednokierunkowej*/
void RemoveFormMemory(HistoryElement **pHead);
#endif