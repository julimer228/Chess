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
	Chessboard[0][6] = KING_WHITE;
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

bool KnightMove(Game* new_game, Square *from, Square *to)
{
	if (abs(from->row - to->row) == 2 && abs(from->column - to->column) == 1)
		return true;
	if (abs(from->row - to->row) == 1 && abs(from->column - to->column) == 2)
		return true;
	
	return false;
}

bool BishopMove(Game* new_game, Square *from, Square *to)
{
	if (abs(from->column - to->column) == abs(from->row - to->row))
	{
		if ((from->row > to->row) && (from->column < to->column))//ruch w kierunku prawego górnego rogu
		{
			for (int i = 1; i < abs(from->column - to->column); i++)
			{
				if (new_game->Chessboard[from->row-i][from->column+i] != EMPTY)
					return false;
				return true;
			}
		}
		if ((from->row > to->row) && (from->column < to->column))	//ruch w kierunku lewego górnego rogu
		{
			for (int i = 1; i < abs(from->column - to->column); i++)
			{
				if (new_game->Chessboard[from->row-i][from->column-i] != EMPTY)
					return false;
				return true;
			}
		}
		if ((from->row > to->row) && (from->column < to->column))	//ruch w kierunku prawego dolnego rogu
		{
			for (int i = 1; i < abs(from->column - to->column); i++)
			{
				if (new_game->Chessboard[from->row+i][from->column+i] != EMPTY)
					return false;
				return true;
			}
		}
		if ((from->row > to->row) && (from->column < to->column))	//ruch w kierunku lewego dolnego rogu
		{
			for (int i = 1; i < abs(from->column - to->column); i++)
			{
				if (new_game->Chessboard[from->row+i][from->column-i] != EMPTY)
					return false;
				return true;
			}
		}
	}
	return false;
}

bool QueenMove(Game* new_game, Square *from, Square *to)
{
	
	if (BishopMove(new_game, from, to))//Je¿eli ruch nastêpuje po skosie (odpowiada ruchowi goña)
		return true;
	if (RookMove(new_game, from, to))//Je¿eli ruch nastêpuje po prostej (odpowiada ruchowi wie¿y)
		return true;
	return false;
}

bool KingMove(Game* new_game, Square *from, Square *to)
{
	if ((from->row == to->row) && abs((from->column - to->column) == 1))
		return true;

}

void Move(Square* from, Square* to, Game* new_game)
{
	new_game->Chessboard[to->row][to->column] = new_game->Chessboard[from->row][from->column];
	new_game->Chessboard[from->row][from->column] = EMPTY;
}

void PawnPromotion(Game* new_game, Square* to)
{
	if (to->row == 7)
	{
		new_game->Chessboard[to->row][to->column] = QUEEN_WHITE;
		return;
	} 
	if (to->row == 0)
	{
		new_game->Chessboard[to->row][to->column] = QUEEN_BLACK;
		return;
	}
}

MoveInfo GetMove(Game* new_game, Square* to, Square* from)
{
	bool isvalid = false;
	switch (new_game->Chessboard[from->row][from->column])
	{
	case 1:
	{
	     isvalid=PawnMove(new_game, from, to);
	}
	case 2:
	{
		isvalid=RookMove(new_game, from, to);
	}
	case 3:
	{
		isvalid=KnightMove(new_game, from, to);
	}
	case 4:
	{
		isvalid=BishopMove(new_game, from, to);
	}
	case 5:
	{
		isvalid=QueenMove(new_game, from, to);
	}
	case 6:
	{
		isvalid=KingMove(new_game, from, to);
	}
	default:
		break;
	}
	if (isvalid)
	{
		//SprawdŸ czy po wykonaniu ruchu mój król jest w szachu, jeœli jest zwróæ informacjê ¿e ruch nie jest prawid³owy.
		if (false)
			return INVALID_MOVE_ACTUAL_KING_IS_IN_DANGER;
		//Wykonaj ruch.
		if (true)
		{
			//SetCheckState(new_game);
			return VALID_MOVE_OPPONENT_KING_IS_IN_DANGER;
		}
			return VALID_MOVE;
		//Je¿eli król przeciwnika jest w szachu zmieñ pole struktury gra->czarny_szach na true i zwróæ wiadomoœæ MoveInfo.
		//Je¿eli nie to zwróæ odpowiednie MoveInfo

	}
	return INVALID_MOVE;
	//Ruch by³ nieprawid³owy

}

bool RookMove(Game* new_game, Square *from, Square *to)
{
	if (from->row == to->row) //ruch w kierunku poziomym (ten sam wiersz)
	{
		if (from->column < to->column)//ruch w prawo
		{
			for (int i = 1; i+from->column < to->column; i++)
			{
				if (new_game->Chessboard[from->row][from->column + i] != EMPTY)
					return false;
			}
			return true;
		}
		else //ruch w lewo
		{
			for (int i = 1; i+to->column < from->column; i++)
			{
				if (new_game->Chessboard[to->row][to->column + i] != EMPTY)
					return false;
			}
			return true;
		}
	}
	if (from->column == to->column) //ruch w kierunku pionowym (ta sama kolumna)
	{
		if (from->row > to->row)//ruch w dó³
		{
			for (int i = 1; i+from->row < to->row; i++)
			{
				if (new_game->Chessboard[from->row+i][from->column] != EMPTY)
					return false;
			}
			return true;
		}
		else //ruch w górê
		{
			for (int i = 1; i+to->row < from->row; i++)
			{
				if (new_game->Chessboard[to->row+i][to->column] != EMPTY)
					return false;
			}
			return true;
		}
	}
	return false;
}

bool PawnMove(Game* new_game, Square *from, Square *to)
{
	if (new_game->Chessboard[from->row][from->column] == 1)
	{
		if ((from->row == 1) && (to->row == 3) && (to->column == from->column) && (new_game->Chessboard[from->row + 1][from->column] == EMPTY))
			return true; //pierwszy ruch bia³ego pionka na szachownicy (mo¿na przesun¹æ siê dwa pola do przodu)
		if (from->row == to->row - 1)
			return true; //przesuniêcie piona w dó³
		if ((from->row == to->row - 1) && (abs(from->column - to->column) == 1) && new_game->Chessboard[to->row][to->column] < 0)
			return true; //zbicie po skosie
	}
	if (new_game->Chessboard[from->row][from->column] == -1)
	{
		if((from->row == 6) && (to->row == 4) && (to->column == from->column)&&(new_game->Chessboard[from->row-1][from->column]==EMPTY))
			return true; //pierwszy ruch czarnego pionka na szachownicy (mo¿na przesun¹æ siê dwa pola do przodu)
		if (from->row == to->row + 1)
			return true; //przesuniêcie piona w górê
		if ((from->row == to->row + 1) && (abs(from->column - to->column) == 1) && new_game->Chessboard[to->row][to->column] > 0)
			return true; //zbicie po skosie
	}
	return false;

}

