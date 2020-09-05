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

/*void SaveToFile(HistoryElement* pHead)
{
	FILE* fp; 
		char move[7];
		move[0] = pHead->from.column + 'A';
		move[1] = pHead->from.row + '1';
		move[2] = '-';
		move[3] = '>';
		move[4] = pHead->to.column + 'A';
		move[5] = pHead->to.row + '1';
		move[6] = '\0';
	printf("%s", move);
	if ((fp = fopen("test.txt", "w")) == NULL) {
		printf("Error in file game_history.txt \n");
		exit(1);
	}
	fprintf(fp, "%s", move); 
	fclose(fp); 
	return 0;
}*/

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
