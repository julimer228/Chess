#include "History.h"

Square* CreateNewSquare(int row, int column)
{
	Square* new_square = (Square*)malloc(sizeof(Square));
	if (new_square != NULL)
	{
		new_square->row = row;
		new_square->column = column;
	}
	return new_square;
}

void RemoveSquare(Square** square_t)
{
	free(*square_t);
	square_t = NULL;
}

bool IsOnTheChessboard(Square* boardsquare)
{
	if (boardsquare->column >= 0 && boardsquare->column < 8 && boardsquare->row < 8 && boardsquare->row >= 0)
		return true;
	return false;
}

bool AddAnElement(Square **from, Square **to, HistoryElement** pHead)
{
	HistoryElement* element_t = (HistoryElement*)malloc(sizeof(HistoryElement));
	element_t->from = *from;
	element_t->to = *to;
	element_t->pNext = *pHead;
	*pHead = element_t;
}

void PrintOnTheScreen(HistoryElement *pHead)
{
	if (pHead)
	{
		HistoryElement* t = pHead;
		while (t!=NULL)
		{
			printf("%i %d %d %d\n", t->from->row, t->from->column, t->to->row, t->to->column);
			t = t->pNext;
		}
	}
}

void RemoveFormMemory(HistoryElement** pHead)
{
	HistoryElement* element_t = *pHead;
	while (*pHead)
	{
		*pHead = (*pHead)->pNext;
	//	printf("Deleting %d\n", element_t->from->column); //Pomocnicze wyœwietlanie usuwanych elementów na ekran
		free((*pHead)->to);
		free((*pHead)->from);
		free(element_t);
		element_t= *pHead;
	}
	
}
