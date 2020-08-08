#include "History.h"

bool IsOnTheChessboard(Square* boardsquare)
{
	if (boardsquare->column >= 0 && boardsquare->column < 8 && boardsquare->row < 8 && boardsquare->row >= 0)
		return true;
	return false;
}

bool AddAnElement(Square **from, Square **to, HistoryElement** pHead)
{
	HistoryElement* new_element = (HistoryElement*)malloc(sizeof(HistoryElement));
	new_element->from = *from;
	new_element->to = *to;
	new_element->pNext = *pHead;
	*pHead = new_element;
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

bool RemoveFormMemory(HistoryElement *pHead)
{
	if (pHead)
		RemoveFormMemory(pHead->pNext);
	free(pHead);
	printf("Usunieto\n");
}
