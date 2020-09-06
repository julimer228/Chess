#include "History.h"

void AddAnElement(Square from, Square to, HistoryElement** pHead)
{
	HistoryElement* element_t = (HistoryElement*)malloc(sizeof(HistoryElement));

	element_t->from = from;
	element_t->to = to;
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
			printf("%i %d %d %d\n", t->from.row, t->from.column, t->to.row, t->to.column);
		
			t = t->pNext;
		}
	}
}

void SaveToFile(HistoryElement* pHead)
{
	FILE* fp; 
	if ((fp = fopen("History.txt", "w")) == NULL) {
		printf("Error in file History.txt \n");
		return;
	}
	HistoryElement* t = pHead;
	while (t)
	{
		char move[8];
		move[0] = t->from.column + 'A';
		move[1] = t->from.row + '1';
		move[2] = '-';
		move[3] = '>';
		move[4] = t->to.column + 'A';
		move[5] = t->to.row + '1';
		move[6] = '\n';
		move[7] = '\0';
		printf("%s", move);
		fprintf(fp, "%s", move);
		t = t->pNext;
	}
	fclose(fp); 

}

static void RemoveFirstElement(HistoryElement** pHead)
{
	if ((*pHead) != NULL)
	{
		HistoryElement* p = (*pHead);
		(*pHead) = (*pHead)->pNext;
		free(p);
	}
}

void RemoveFormMemory(HistoryElement** pHead)
{
	while ((*pHead) != NULL)
		RemoveFirstElement(pHead);
}
