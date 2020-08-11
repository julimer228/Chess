#include <stdio.h>
#include "History.h"
#include "Game.h"
int main(int argc, char* argv[])
{
	Game* new_game = CreateGame();
	PrintChessboard(new_game);
	/**Square a = { 1,1 };
	Square b = { 2,2};
	if (RookMove(new_game, &a, &b))
		printf("Ojojo");
	else printf("INVALID");
	Square* a1 = (Square*)malloc(sizeof(Square));
	a1->row = 1;
	a1->column = 1;
	Square* a2 = (Square*)malloc(sizeof(Square));
	a2->row = 2;
	a2->column = 2;
	Square* a3 = (Square*)malloc(sizeof(Square));
	a3->row = 3;
	a3->column = 3;
	Square* a4 = (Square*)malloc(sizeof(Square));
	a4->row = 4;
	a4->column = 4;
	Square* a5 = (Square*)malloc(sizeof(Square));
	a5->row = 5;
	a5->column = 5;
	Square* a6 = (Square*)malloc(sizeof(Square));
	a6->row = 6;
	a6->column = 6;

	HistoryElement* pHead = NULL;

	AddAnElement(&a1,&a1,&pHead);
	AddAnElement(&a2, &a2, &pHead);
	Square *new_square=CreateNewSquare(6, 66);
	AddAnElement(&new_square, &new_square, &pHead);
	AddAnElement(&a4, &a4, &pHead);
	AddAnElement(&a5, &a5, &pHead);
	AddAnElement(&a6, &a6, &pHead);
	PrintOnTheScreen(pHead);
	RemoveFormMemory(&pHead);*/
	bool tab[SIZE][SIZE] = { {false} };
	Square* new_square = CreateNewSquare(3, 5);
	KingMove(new_game->Chessboard, new_square, tab);
	PrintBoolTab(tab);
	TurnTheBoardChangeColor(new_game->Chessboard);
	PrintChessboard(new_game);

	

}