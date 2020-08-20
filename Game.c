#include "Game.h"

void InitializeTheChessboard(chessboard Chessboard)
{
	for (int i = 1; i < SIZE-1; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			Chessboard[i][j] = EMPTY; //puste pola
		}
	}

	for (int j = 0; j < SIZE; j++)
	{
		Chessboard[1][j] = PAWN_WHITE;//bia³e pionki
		Chessboard[6][j] = PAWN_BLACK;//czarne pionki
	}
	//pozosta³e bia³e figury
	Chessboard[0][0] = ROOK_WHITE;
	Chessboard[0][1] = KNIGHT_WHITE;
	Chessboard[0][2] = BISHOP_WHITE;
	Chessboard[0][3] = QUEEN_WHITE;
	Chessboard[0][4] = KING_WHITE;
	Chessboard[0][5] = BISHOP_WHITE;
	Chessboard[0][6] = KNIGHT_WHITE;
	Chessboard[0][7] = ROOK_WHITE;

	//pozosta³e czarne figury
	Chessboard[7][0] = ROOK_BLACK;
	Chessboard[7][1] = KNIGHT_BLACK;
	Chessboard[7][2] = BISHOP_BLACK;
	Chessboard[7][3] = QUEEN_BLACK;
	Chessboard[7][4] = KING_BLACK;
	Chessboard[7][5] = BISHOP_BLACK;
	Chessboard[7][6] = KNIGHT_BLACK;
	Chessboard[7][7] = ROOK_BLACK;
}

Game* CreateGame()
{
	Game* new_game = (Game*)malloc(sizeof(Game));
	if (new_game==NULL) //Jeœli nie uda³o siê zarezerwowaæ pamiêci.
		return NULL;
	new_game->BlackCheck = false;
	new_game->WhiteCheck = false;
	new_game->HasGameEnded = false;
	new_game->CurrentPlayer = white;
	InitializeTheChessboard(new_game->Chessboard); /*Ustawienie pocz¹tkowe na szachownicy*/
	return new_game;
}

void DestroyGame(Game* new_game)
{
	if (new_game == NULL)
		return;
	free(new_game);
}

void PrintChessboard(Game* new_game)
{
	printf("---------------------------------\n");

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("|%3d", new_game->Chessboard[i][j]);
		}
		printf("|\n");
		printf("---------------------------------\n");
	}
	printf("%d", new_game->Chessboard[1][7]);
}

bool IsEmpty(Square* to, Game* new_game)
{
	if (new_game->Chessboard[to->row][to->column] == EMPTY)
		return true;
	return false;
}

bool IsEnemy(Square* to, Square* from, Game* new_game)
{
	if (new_game->Chessboard[from->row][from->column] * new_game->Chessboard[to->row][to->column] < 0)//jeœli iloczyn dwóch liczb jest mniejszy od zera, to znaczy ¿e s¹ ró¿nych znaków
		return true;
	return false;
}

void PawnMove(chessboard Chessboard, Square* from, bool tab[SIZE][SIZE])
{
	if (Chessboard[from->row + 1][from->column + 1] == EMPTY)
	{
		tab[from->row + 1][from->column] = true;
		if ((Chessboard[from->row][from->column] == 1) && (Chessboard[from->row + 2][from->column] == EMPTY))
		{
			tab[from->row + 2][from->column] = true;
		}
	}
	//Zbicia po skosie (jeœli stoi tam bierka przeciwnika)
	if (Chessboard[from->row + 1][from->column + 1] < 0)
		tab[from->row + 1][from->column + 1] = true;
	if (Chessboard[from->row + 1][from->column - 1] < 0)
		tab[from->row + 1][from->column - 1] = true;
}

void RookMove(chessboard Chessboard, Square* from, bool tab[SIZE][SIZE])
{
	for (int i = 1; from->row + i < SIZE; i++)
	{
		if (Chessboard[from->row + i][from->column] > 0)
			break;
		if (Chessboard[from->row + i][from->column] < 0)
		{
			tab[from->row + i][from->column] = true;
			break;
		}
		if (Chessboard[from->row + i][from->column] == EMPTY)
			tab[from->row + i][from->column] = true;
	}
	for (int i = 1; from->row - i >=0; i++)
	{
		if (Chessboard[from->row - i][from->column] > 0)
			break;
		if (Chessboard[from->row - i][from->column] < 0)
		{
			tab[from->row - i][from->column] = true;
			break;
		}
		if (Chessboard[from->row - i][from->column] == EMPTY)
			tab[from->row - i][from->column] = true;
	}
	for (int i = 1; from->column + i < SIZE; i++)
	{
		if (Chessboard[from->row][from->column+i] > 0)
			break;
		if (Chessboard[from->row][from->column+i] < 0)
		{
			tab[from->row][from->column+i] = true;
			break;
		}
		if (Chessboard[from->row][from->column+i] == EMPTY)
			tab[from->row][from->column+i] = true;
	}
	for (int i = 1; from->column - i >= 0; i++)
	{
		if (Chessboard[from->row][from->column-i] > 0)
			break;
		if (Chessboard[from->row][from->column-i] < 0)
		{
			tab[from->row][from->column-i] = true;
			break;
		}
		if (Chessboard[from->row][from->column-i] == EMPTY)
			tab[from->row][from->column-i] = true;
	}
}

void KnightMove(chessboard Chessboard, Square* from, bool tab[SIZE][SIZE])
{
	if((from->row+1<SIZE)&&(from->column+2<SIZE)&&((Chessboard[from->row+1][from->column+2]==EMPTY)||(Chessboard[from->row+1][from->column+2]<0))) 
	tab[from->row+1][from->column+2] = true;
	if((from->row-1>=0)&&(from->column-2>=0) && ((Chessboard[from->row - 1][from->column - 2] == EMPTY) || (Chessboard[from->row - 1][from->column - 2] < 0)))
	tab[from->row-1][from->column-2] = true;
	if ((from->row + 1 <SIZE) && (from->column - 2 >= 0) && ((Chessboard[from->row + 1][from->column - 2] == EMPTY) || (Chessboard[from->row + 1][from->column - 2] < 0)))
	tab[from->row+1][from->column-2] = true;
	if ((from->row - 1 >= 0) && (from->column+2 <SIZE) && ((Chessboard[from->row -1][from->column + 2] == EMPTY) || (Chessboard[from->row - 1][from->column + 2] < 0)))
	tab[from->row-1][from->column+2] = true;
	if ((from->row + 2<SIZE) && (from->column +1 <SIZE) && ((Chessboard[from->row + 2][from->column + 1] == EMPTY) || (Chessboard[from->row + 2][from->column + 1] < 0)))
	tab[from->row+2][from->column+1] = true;
	if ((from->row +2 <SIZE) && (from->column - 1 >= 0) && ((Chessboard[from->row + 2][from->column -1] == EMPTY) || (Chessboard[from->row + 2][from->column -1] < 0)))
	tab[from->row+2][from->column-1] = true;
	if ((from->row - 2 >= 0) && (from->column +1 <SIZE ) && ((Chessboard[from->row -2][from->column + 1] == EMPTY) || (Chessboard[from->row -2][from->column + 1] < 0)))
	tab[from->row-2][from->column+1] = true; 
	if ((from->row - 2 >= 0) && (from->column - 1 >= 0) && ((Chessboard[from->row -2][from->column -1] == EMPTY) || (Chessboard[from->row -2][from->column-1] < 0)))
	tab[from->row-2][from->column-1] = true;
}

void BishopMove(chessboard Chessboard, Square* from, bool tab[SIZE][SIZE])
{
	bool first_enemy = true; //Sprawdzamy czy ju¿ jakiœ pionek by³ zbity (nie mo¿emy kilku figur w jednym ruchu)
	for (int i = 1; ((i + from->row )< SIZE)&&((from->column+i)<SIZE); i++)
	{
		if (Chessboard[from->row + i][from->column + i] > 0)//Jeœli na przek¹tnej znajduje siê bia³a figura, to nie mo¿emy stan¹æ na tym polu, nie mo¿emy go tak¿e "przeskoczyæ"
			break;
			if(((Chessboard[from->row+i][from->column+i] == EMPTY) || (Chessboard[from->row+i][from->column+i] < 0))&& (first_enemy == true))
			{
				if (Chessboard[from->row+i][from->column+i] < 0)//Jeœli na przek¹tnej znajduje siê czarna figura, to mo¿emy j¹ zbiæ i stan¹æ na zajmowanym przez ni¹ polu, ale nie mo¿emy iœæ dalej
					first_enemy = false;
				tab[from->row+i][from->column+i] = true;
			}
		
	}
	first_enemy = true;
	for (int i = 1; (from->row-i)>=0 && (from->column - i) >= 0; i++)
	{
		if (Chessboard[from->row - i][from->column - i] > 0)
			break;
		if (((Chessboard[from->row - i][from->column - i] == EMPTY) || (Chessboard[from->row - i][from->column - i] < 0)) && (first_enemy == true))
		{
			if (Chessboard[from->row - i][from->column - i] < 0)
				first_enemy = false;
			tab[from->row - i][from->column - i] = true;
		}

	}
	first_enemy = true;
	for (int i = 1; (from->row-i) >=0 && (from->column + i) < SIZE; i++)
	{
		if (Chessboard[from->row - i][from->column + i] > 0)
			break;
		if (((Chessboard[from->row - i][from->column + i] == EMPTY) || (Chessboard[from->row - i][from->column + i] < 0)) && (first_enemy == true))
		{
			if (Chessboard[from->row - i][from->column + i] < 0)
				first_enemy = false;
			tab[from->row - i][from->column + i] = true;
		}

	}
	first_enemy = true;
	for (int i = 1; ((i + from->row) < SIZE) && ((from->column - i) >= 0); i++)
	{
		if (Chessboard[from->row + i][from->column - i] > 0)
			break;
		if (((Chessboard[from->row + i][from->column - i] == EMPTY) || (Chessboard[from->row + i][from->column - i] < 0)) && (first_enemy == true))
		{
			if (Chessboard[from->row + i][from->column - i] < 0)
				first_enemy = false;
			tab[from->row + i][from->column - i] = true;
		}

	}
}

void QueenMove(chessboard Chessboard, Square* from, bool tab[SIZE][SIZE])
{
	BishopMove(Chessboard, from, tab);
	RookMove(Chessboard, from, tab);
}

void KingMove(chessboard Chessboard, Square* from, bool tab[SIZE][SIZE])
{
	if (from->row + 1 < SIZE)
	{
		if (from->column + 1 < SIZE&&((Chessboard[from->row+1][from->column+1]==EMPTY)||(Chessboard[from->row+1][from->column+1]<0)))
		{
			tab[from->row+1][from->column + 1] = true;
		}
		if (from->column - 1 >= 0 && ((Chessboard[from->row + 1][from->column - 1] == EMPTY) || (Chessboard[from->row + 1][from->column - 1] < 0)))
		{
			tab[from->row+1][from->column - 1] = true;
		}
		if (Chessboard[from->row + 1][from->column] == EMPTY || Chessboard[from->row + 1][from->column] < 0)
		{
			tab[from->row + 1][from->column] = true;
		}
	}
	if (from->row - 1 >= 0)
	{
		if (from->column + 1 < SIZE && ((Chessboard[from->row - 1][from->column + 1] == EMPTY) || (Chessboard[from->row - 1][from->column + 1] < 0)))
		{
			tab[from->row-1][from->column + 1] = true;
		}
		if (from->column - 1 >= 0 && ((Chessboard[from->row - 1][from->column - 1] == EMPTY) || (Chessboard[from->row - 1][from->column - 1] < 0)))
		{
			tab[from->row-1][from->column - 1] = true;
		}
		if (Chessboard[from->row - 1][from->column] == EMPTY || Chessboard[from->row - 1][from->column] < 0)
		{
			tab[from->row - 1][from->column] = true;
		}
	}
	if (from->column + 1 < SIZE && ((Chessboard[from->row][from->column + 1] == EMPTY) || (Chessboard[from->row][from->column + 1] < 0)))
	{
		tab[from->row][from->column + 1] = true;
	}
	if (from->column - 1 >= 0 && ((Chessboard[from->row][from->column - 1] == EMPTY) || (Chessboard[from->row][from->column - 1] < 0)))
	{
		tab[from->row][from->column - 1] = true;
	}
	
}
	

void Move(Square* from, Square* to, Game* new_game)
{
	new_game->Chessboard[to->row][to->column] = new_game->Chessboard[from->row][from->column];
	new_game->Chessboard[from->row][from->column] = EMPTY;
}

void PawnPromotion(chessboard Chessboard, Square* to)
{
	if (to->row == SIZE - 1)
		Chessboard[to->row][to->column] = 5; //zamieñ bia³ego pionka na hetmana
}


void GetMove(chessboard Chessboard, bool tab[SIZE][SIZE], Square* from)
{
	switch (Chessboard[from->row][from->column])
	{
	case PAWN_WHITE: PawnMove(Chessboard, from, tab);
		break;
	case ROOK_WHITE: RookMove(Chessboard, from, tab);
		break;
	case KNIGHT_WHITE: KnightMove(Chessboard, from, tab);
		break;
	case BISHOP_WHITE: BishopMove(Chessboard, from, tab);
		break;
	case QUEEN_WHITE: QueenMove(Chessboard, from, tab);
		break;
	case KING_WHITE: KingMove(Chessboard, from, tab);
		break;
	default:
		break;
	}
}

void GetAllMoves(chessboard Chessboard, bool tab[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Chessboard[i][j] > 0)
			{
				Square* square_t=CreateNewSquare(i, j);
				GetMove(Chessboard, tab, square_t);
				free(square_t);
			}
		}
	}
}

void TurnTheBoardChangeColor(chessboard Chessboard)
{
	for (int i = 0; i < SIZE/2; i++)//Zamiana kolorów 
	{
		for (int j = 0; j < SIZE; j++)
		{
			int t = -Chessboard[i][j];
			Chessboard[i][j] = -(Chessboard[SIZE - 1 - i][SIZE - 1 - j]);
			Chessboard[SIZE - 1 - i][SIZE - 1 - j] = t;
		}
	}
}

void TurnTheBoard(chessboard Chessboard)
{
	for (int i = 0; i < SIZE / 2; i++)//Zamiana kolorów 
	{
		for (int j = 0; j < SIZE; j++)
		{
			int t = Chessboard[i][j];
			Chessboard[i][j] =(Chessboard[SIZE - 1 - i][SIZE - 1 - j]);
			Chessboard[SIZE - 1 - i][SIZE - 1 - j] = t;
		}
	}
}

Square* FindTheBlackKing(chessboard Chessboard)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Chessboard[i][j] == KING_BLACK)
				return CreateNewSquare(i, j);
		}
	}
	return NULL;
}


bool IsBlackKingChecked(chessboard Chessboard)
{
	bool blackcheck = false;
	bool tab[SIZE][SIZE] = { {false} };
	Square *BlackKingPosition = FindTheBlackKing(Chessboard);
	GetAllMoves(Chessboard, tab);//Zapisujemy w tablicy wszystkie mo¿liwe ruchy bia³ego gracza
	if (tab[BlackKingPosition->row][BlackKingPosition->column])//Jeœli pole na którym stoi król jest polem atakowanym przez bia³¹ bierkê oznacza to ¿e czarny król jest w szachu
		blackcheck = true;
	free(BlackKingPosition);
	return blackcheck;
}

void SwitchPlayers(Game* new_game)
{
	if (new_game->CurrentPlayer == white)
		new_game->CurrentPlayer = black;
	else new_game->CurrentPlayer = white;
}

bool BelongsToCurrentPlayer(Player currentplayer, chessboard Chessboard, Square *square_)
{
	if (Chessboard[square_->row][square_->column] > 0)
		return true;
	return false;
}

void PrintBoolTab(bool tab[SIZE][SIZE])
{
	printf("\n");
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf(" %d ", tab[i][j]);
		}
		printf("\n");
	}
}


