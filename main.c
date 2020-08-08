#include <stdio.h>
#include "History.h"
#include "Game.h"
int main(int argc, char* argv[])
{
	Game* new_game = CreateGame();
	PrintChessboard(new_game);
	Square a = { 1,1 };
	Square b = { 2,2};
	if (RookMove(new_game, &a, &b))
		printf("Ojojo");
	else printf("INVALID");
}