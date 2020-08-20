#include <stdio.h>
#include "History.h"
#include "Game.h"

int main()
{
    putchar('l');
    Game* new_game = CreateGame();
    PrintChessboard(new_game);
    bool tab[8][8] = { {0} };
    GetAllMoves(new_game->Chessboard, tab);
    PrintBoolTab(tab);
    PrintChessboard(new_game);
        return 0;
}