#include "History.h"

bool AddAnElement(Square from, Square to, HistoryElement** pHead, int KilledPiece)
{
	HistoryElement* element_t = (HistoryElement*)malloc(sizeof(HistoryElement));
	element_t->from = from;
	element_t->to = to;
	element_t->pNext = *pHead;
	element_t->KilledPiece = KilledPiece;
	*pHead = element_t;
}

void PrintOnTheScreen(HistoryElement *pHead)
{
	if (pHead)
	{
		HistoryElement* t = pHead;
		while (t!=NULL)
		{
			printf("%i %d %d %d\n", t->from.row, t->from.column, t->to.row, t->to.column);
			t = t->pNext;
		}
	}
}

void RemoveFirstElement(HistoryElement** pHead)
{
	if ((*pHead) == NULL)
	{
		printf("History list was empty!");
		return;
	}
	HistoryElement* p = (*pHead);
	(*pHead) = (*pHead)->pNext;
	free(p);
}

void RemoveFormMemory(HistoryElement** pHead)
{
	while ((*pHead) != NULL)
		RemoveFirstElement(pHead);
}
