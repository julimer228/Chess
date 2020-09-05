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
		Chessboard[1][j] = PAWN_WHITE;//bia�e pionki
		Chessboard[6][j] = PAWN_BLACK;//czarne pionki
	}
	//pozosta�e bia�e figury
	Chessboard[0][0] = ROOK_WHITE;
	Chessboard[0][1] = KNIGHT_WHITE;
	Chessboard[0][2] = BISHOP_WHITE;
	Chessboard[0][3] = QUEEN_WHITE;
	Chessboard[0][4] = KING_WHITE;
	Chessboard[0][5] = BISHOP_WHITE;
	Chessboard[0][6] = KNIGHT_WHITE;
	Chessboard[0][7] = ROOK_WHITE;

	//pozosta�e czarne figury
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
	if (new_game==NULL) //Je�li nie uda�o si� zarezerwowa� pami�ci.
		return NULL;
	new_game->BlackCheck = false;
	new_game->WhiteCheck = false;
	new_game->HasGameEnded = false;
	new_game->IsSaved = false;
	new_game->CurrentPlayer = white;
	new_game->pHead = NULL;
	//Ustawiamy pola dotycz�ce ostatniego wykonanego ruchu na warto�ci pocz�tkowe (poza szachownic�)
	new_game->From.row = -1;
	new_game->From.column = -1;
	new_game->To.column = -1;
	new_game->To.row = -1;
	new_game->blackcheck_t = false;
	new_game->whitecheck_t = false;
	new_game->piece_killed = EMPTY;
	InitializeTheChessboard(new_game->Chessboard); /*Ustawienie pocz�tkowe na szachownicy*/
	return new_game;
}

void DestroyGame(Game* game)
{
	if (game == NULL)
		return;
	RemoveFormMemory(&game->pHead);
	free(game);
}

bool IsSquareOnTheChessboard(Square sq)
{
	if (sq.column < SIZE && sq.column >= 0 && sq.row >= 0 && sq.row < SIZE)
		return true;
	return false;
}

void PawnMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	if (Chessboard[from.row + 1][from.column] == EMPTY)
	{
		tab[from.row + 1][from.column] = true;
		if ((from.row == 1) && (Chessboard[from.row + 2][from.column] == EMPTY))//Je�eli wykonujemy pierwszy ruch pionkiem to mo�emy go przesun�� o dwa pola do przodu
		{
			tab[from.row + 2][from.column] = true;
		}
	}
	//Zbicia po skosie (je�li stoi tam bierka przeciwnika)
	if (Chessboard[from.row + 1][from.column + 1] < 0)
		tab[from.row + 1][from.column + 1] = true;
	if (Chessboard[from.row + 1][from.column - 1] < 0)
		tab[from.row + 1][from.column - 1] = true;
}

void RookMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	for (int i = 1; from.row + i < SIZE; i++)
	{
		if (Chessboard[from.row + i][from.column] > 0)
			break;
		if (Chessboard[from.row + i][from.column] < 0)
		{
			tab[from.row + i][from.column] = true;
			break;
		}
		if (Chessboard[from.row + i][from.column] == EMPTY)
			tab[from.row + i][from.column] = true;
	}
	for (int i = 1; from.row - i >=0; i++)
	{
		if (Chessboard[from.row - i][from.column] > 0)
			break;
		if (Chessboard[from.row - i][from.column] < 0)
		{
			tab[from.row - i][from.column] = true;
			break;
		}
		if (Chessboard[from.row - i][from.column] == EMPTY)
			tab[from.row - i][from.column] = true;
	}
	for (int i = 1; from.column + i < SIZE; i++)
	{
		if (Chessboard[from.row][from.column+i] > 0)
			break;
		if (Chessboard[from.row][from.column+i] < 0)
		{
			tab[from.row][from.column+i] = true;
			break;
		}
		if (Chessboard[from.row][from.column+i] == EMPTY)
			tab[from.row][from.column+i] = true;
	}
	for (int i = 1; from.column - i >= 0; i++)
	{
		if (Chessboard[from.row][from.column-i] > 0)
			break;
		if (Chessboard[from.row][from.column-i] < 0)
		{
			tab[from.row][from.column-i] = true;
			break;
		}
		if (Chessboard[from.row][from.column-i] == EMPTY)
			tab[from.row][from.column-i] = true;
	}
}

void KnightMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	if((from.row+1<SIZE)&&(from.column+2<SIZE)&&((Chessboard[from.row+1][from.column+2]==EMPTY)||(Chessboard[from.row+1][from.column+2]<0))) 
	tab[from.row+1][from.column+2] = true;
	if((from.row-1>=0)&&(from.column-2>=0) && ((Chessboard[from.row - 1][from.column - 2] == EMPTY) || (Chessboard[from.row - 1][from.column - 2] < 0)))
	tab[from.row-1][from.column-2] = true;
	if ((from.row + 1 <SIZE) && (from.column - 2 >= 0) && ((Chessboard[from.row + 1][from.column - 2] == EMPTY) || (Chessboard[from.row + 1][from.column - 2] < 0)))
	tab[from.row+1][from.column-2] = true;
	if ((from.row - 1 >= 0) && (from.column+2 <SIZE) && ((Chessboard[from.row -1][from.column + 2] == EMPTY) || (Chessboard[from.row - 1][from.column + 2] < 0)))
	tab[from.row-1][from.column+2] = true;
	if ((from.row + 2<SIZE) && (from.column +1 <SIZE) && ((Chessboard[from.row + 2][from.column + 1] == EMPTY) || (Chessboard[from.row + 2][from.column + 1] < 0)))
	tab[from.row+2][from.column+1] = true;
	if ((from.row +2 <SIZE) && (from.column - 1 >= 0) && ((Chessboard[from.row + 2][from.column -1] == EMPTY) || (Chessboard[from.row + 2][from.column -1] < 0)))
	tab[from.row+2][from.column-1] = true;
	if ((from.row - 2 >= 0) && (from.column +1 <SIZE ) && ((Chessboard[from.row -2][from.column + 1] == EMPTY) || (Chessboard[from.row -2][from.column + 1] < 0)))
	tab[from.row-2][from.column+1] = true; 
	if ((from.row - 2 >= 0) && (from.column - 1 >= 0) && ((Chessboard[from.row -2][from.column -1] == EMPTY) || (Chessboard[from.row -2][from.column-1] < 0)))
	tab[from.row-2][from.column-1] = true;
}

void BishopMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	bool first_enemy = true; //Sprawdzamy czy ju� jaki� pionek by� zbity (nie mo�emy kilku figur w jednym ruchu)
	for (int i = 1; ((i + from.row )< SIZE)&&((from.column+i)<SIZE); i++)
	{
		if (Chessboard[from.row + i][from.column + i] > 0)//Je�li na przek�tnej znajduje si� bia�a figura, to nie mo�emy stan�� na tym polu, nie mo�emy go tak�e "przeskoczy�"
			break;
			if(((Chessboard[from.row+i][from.column+i] == EMPTY) || (Chessboard[from.row+i][from.column+i] < 0))&& (first_enemy == true))
			{
				if (Chessboard[from.row+i][from.column+i] < 0)//Je�li na przek�tnej znajduje si� czarna figura, to mo�emy j� zbi� i stan�� na zajmowanym przez ni� polu, ale nie mo�emy i�� dalej
					first_enemy = false;
				tab[from.row+i][from.column+i] = true;
			}
		
	}
	first_enemy = true;
	for (int i = 1; (from.row-i)>=0 && (from.column - i) >= 0; i++)
	{
		if (Chessboard[from.row - i][from.column - i] > 0)
			break;
		if (((Chessboard[from.row - i][from.column - i] == EMPTY) || (Chessboard[from.row - i][from.column - i] < 0)) && (first_enemy == true))
		{
			if (Chessboard[from.row - i][from.column - i] < 0)
				first_enemy = false;
			tab[from.row - i][from.column - i] = true;
		}

	}
	first_enemy = true;
	for (int i = 1; (from.row-i) >=0 && (from.column + i) < SIZE; i++)
	{
		if (Chessboard[from.row - i][from.column + i] > 0)
			break;
		if (((Chessboard[from.row - i][from.column + i] == EMPTY) || (Chessboard[from.row - i][from.column + i] < 0)) && (first_enemy == true))
		{
			if (Chessboard[from.row - i][from.column + i] < 0)
				first_enemy = false;
			tab[from.row - i][from.column + i] = true;
		}

	}
	first_enemy = true;
	for (int i = 1; ((i + from.row) < SIZE) && ((from.column - i) >= 0); i++)
	{
		if (Chessboard[from.row + i][from.column - i] > 0)
			break;
		if (((Chessboard[from.row + i][from.column - i] == EMPTY) || (Chessboard[from.row + i][from.column - i] < 0)) && (first_enemy == true))
		{
			if (Chessboard[from.row + i][from.column - i] < 0)
				first_enemy = false;
			tab[from.row + i][from.column - i] = true;
		}

	}
}

void QueenMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	BishopMove(Chessboard, from, tab);
	RookMove(Chessboard, from, tab);
}

void KingMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	if (from.row + 1 < SIZE)
	{
		if (from.column + 1 < SIZE&&((Chessboard[from.row+1][from.column+1]==EMPTY)||(Chessboard[from.row+1][from.column+1]<0)))
		{
			tab[from.row+1][from.column + 1] = true;
		}
		if (from.column - 1 >= 0 && ((Chessboard[from.row + 1][from.column - 1] == EMPTY) || (Chessboard[from.row + 1][from.column - 1] < 0)))
		{
			tab[from.row+1][from.column - 1] = true;
		}
		if (Chessboard[from.row + 1][from.column] == EMPTY || Chessboard[from.row + 1][from.column] < 0)
		{
			tab[from.row + 1][from.column] = true;
		}
	}
	if (from.row - 1 >= 0)
	{
		if (from.column + 1 < SIZE && ((Chessboard[from.row - 1][from.column + 1] == EMPTY) || (Chessboard[from.row - 1][from.column + 1] < 0)))
		{
			tab[from.row-1][from.column + 1] = true;
		}
		if (from.column - 1 >= 0 && ((Chessboard[from.row - 1][from.column - 1] == EMPTY) || (Chessboard[from.row - 1][from.column - 1] < 0)))
		{
			tab[from.row-1][from.column - 1] = true;
		}
		if (Chessboard[from.row - 1][from.column] == EMPTY || Chessboard[from.row - 1][from.column] < 0)
		{
			tab[from.row - 1][from.column] = true;
		}
	}
	if (from.column + 1 < SIZE && ((Chessboard[from.row][from.column + 1] == EMPTY) || (Chessboard[from.row][from.column + 1] < 0)))
	{
		tab[from.row][from.column + 1] = true;
	}
	if (from.column - 1 >= 0 && ((Chessboard[from.row][from.column - 1] == EMPTY) || (Chessboard[from.row][from.column - 1] < 0)))
	{
		tab[from.row][from.column - 1] = true;
	}
	
}

void GetMovesOfTheWhitePiece(chessboard Chessboard, bool tab[SIZE][SIZE], Square from)
{
	switch (Chessboard[from.row][from.column])
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

void GetAllMovesOfTheWhitePlayer(chessboard Chessboard, bool tab[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Chessboard[i][j] > 0)
			{
				Square square_t = { i, j }; //Tworzymy pole
				GetMovesOfTheWhitePiece(Chessboard, tab, square_t);
			}
		}
	}
}

void TurnTheBoardChangeColor(chessboard Chessboard)
{
	for (int i = 0; i < SIZE/2; i++)//Obracamy tylko do po�owy poniewa� wr�ciliby�my do tego samego ustawienia 
	{
		for (int j = 0; j < SIZE; j++)
		{
			int t = -Chessboard[i][j];
			Chessboard[i][j] = -(Chessboard[SIZE - 1 - i][SIZE - 1 - j]);
			Chessboard[SIZE - 1 - i][SIZE - 1 - j] = t;
		}
	}
}

void TurnTheValidMovesTab(bool tab[SIZE][SIZE])
{
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int t = tab[i][j];
			tab[i][j] =(tab[SIZE - 1 - i][SIZE - 1 - j]);
			tab[SIZE - 1 - i][SIZE - 1 - j] = t;
		}
	}
}

 Square FindTheBlackKing(chessboard Chessboard)
{
	Square sq = { -1,-1 };//Je�li kr�la nie znaleziono zwr�ci pole o niedozwolonych indeksach
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (Chessboard[i][j] == KING_BLACK)
			{
				sq.row = i;
				sq.column = j;
				return sq;
				
			}
		}
	}

}

bool IsBlackKingChecked(chessboard Chessboard)
{
	bool tab[SIZE][SIZE] = { {false} };//Tworzymy tablic� dozwolonych ruch�w
	Square BlackKingPosition = FindTheBlackKing(Chessboard);//Szukamy czarnego kr�la na szachownicy

	GetAllMovesOfTheWhitePlayer(Chessboard, tab);
	if (tab[BlackKingPosition.row][BlackKingPosition.column] == true)
		return true;
	return false;
}

bool BlackPieceInDanger(chessboard Chessboard, Square black_square)
{
	bool tab[SIZE][SIZE] = {{ false }};
	if (Chessboard[black_square.row][black_square.column] < 0)//Je�eli na polu stoi czarna figura
	{
		GetAllMovesOfTheWhitePlayer(Chessboard, tab);
		if (tab[black_square.row][black_square.column])
			return true;
	}
	return false;
}

void PrepareForNextPlayerTurn(Game* game)
{
	TurnTheBoardChangeColor(game->Chessboard);//Obr�t planszy
	SwitchPlayers(game);//zamiana graczy
}

bool IsPieceInDanger(chessboard Chessboard, Square sq)
{
	bool t = false;
	if (Chessboard[sq.row][sq.column] < 0)//Figura na polu sq jest czarna
		return BlackPieceInDanger(Chessboard, sq);
	//Na polu kt�re sprawdzamy stoi bia�a figura, musimy obr�ci� plansze
	if (Chessboard[sq.row][sq.column] > 0)
	{
		TurnTheBoardChangeColor(Chessboard);
		//Musimy "obr�ci�" tak�e wsp�rz�dne pola sq
		sq.row = SIZE - 1 - sq.row;
		sq.column = SIZE - 1 - sq.column;
		bool t = BlackPieceInDanger(Chessboard, sq);
		TurnTheBoardChangeColor(Chessboard);//Musimy obr�ci� plansze z powrotem
	}
		return t;
}

 void DeleteLastMove(Game* game)
{
	//Przestawiamy figur� z pola to na pole from
	game->Chessboard[game->From.row][game->From.column] = game->Chessboard[game->To.row][game->To.column];
	//Ustawiamy figur� kt�ra zosta�a zbita (lub puste pole)
	game->Chessboard[game->To.row][game->To.column] = game->piece_killed;

	//zmiana graczy;
	SwitchPlayers(game);
	//je�li w poprzednim ruchu kr�l by� w szachu
	game->BlackCheck = game->blackcheck_t;
	game->WhiteCheck = game->whitecheck_t;
}

void MakeAMove(Game* game, Square from, Square to)
{

	//Wykonanie ruchu na szachownicy
	game->piece_killed = game->Chessboard[to.row][to.column];

	game->Chessboard[to.row][to.column] = game->Chessboard[from.row][from.column];
	game->Chessboard[from.row][from.column] = EMPTY;
	
	//Zamiana graczy
	SwitchPlayers(game);

	//Zapisz informacj� o tym czy kr�l kt�rego� z graczy jest w szachu
	game->WhiteCheck = IsKingChecked(game->Chessboard, white);
	game->BlackCheck = IsKingChecked(game->Chessboard, black);

	game->blackcheck_t = game->BlackCheck;
	game->whitecheck_t = game->WhiteCheck;
	game->From = from;
	game->To = to;
	
}

void CheckIfPieceOrKingWillBeInDanger(Game* game, Square from, Square to, bool* KingInDanger, bool* PieceInDanger)
{
	MakeAMove(game, from, to);
	if (game->Chessboard[from.row][from.column] > 0)
	{
		*KingInDanger = IsKingChecked(game->Chessboard, white);
	}
	else if(game->Chessboard[from.row][from.column]<0)
	{
		*KingInDanger = IsKingChecked(game->Chessboard,black);
	}

	*PieceInDanger = IsPieceInDanger(game->Chessboard, to);
	DeleteLastMove(game);
}

void SwitchPlayers(Game* game)
{
	if (game->CurrentPlayer == white)//je�li aktualny gracz jest bia�y zmie� na czrnego
		game->CurrentPlayer = black;
	else game->CurrentPlayer = white;//aktualny gracz by� czarny, zamiana na bia�ego
}

bool IsKingChecked(chessboard Chessboard, Player player)
{
	bool check = false;
	if (player == white)
	{
		TurnTheBoardChangeColor(Chessboard);//Zmieniamy kolory figur i obracamy plansz�
		check = IsBlackKingChecked(Chessboard);//sprawdzamy czy czarny kr�l jest w szachu
		TurnTheBoardChangeColor(Chessboard);//Obracamy plansz� i zmieniamy kolor
	}
	else if(player==black)
	{
		check = IsBlackKingChecked(Chessboard);//Sprawdzamy czy czarny kr�l jest w szachu
	}
	return check;
}

bool IsActualPlayerInCheck(Game* game)
{
	if (game->CurrentPlayer == black)
		return IsKingChecked(game->Chessboard, black);
	if (game->CurrentPlayer == white)
		return IsKingChecked(game->Chessboard, white);
}

bool BelongsToActualPlayer(Game* game, Square piece_square)
{
	if (game->Chessboard[piece_square.row][piece_square.column] > 0 && game->CurrentPlayer == white)
		return true;
	if (game->Chessboard[piece_square.row][piece_square.column] < 0 && game->CurrentPlayer == black)
		return true;
	return false;
}

void GetValidMoves(chessboard Chessboard, bool tab[SIZE][SIZE], Square from)
{
	bool white_piece=false;
	if (Chessboard[from.row][from.column] > 0)
		white_piece = true;
	if (!white_piece)//Czarna figura
	{
		//Obracamy szachownic�
		TurnTheBoardChangeColor(Chessboard);
		from.row = SIZE - 1 - from.row;
		from.column = SIZE - 1 - from.column;
	}

	GetMovesOfTheWhitePiece(Chessboard, tab, from);//wype�niamy tablic� dozwolonych ruch�w

	if (!white_piece)
	{
		TurnTheBoardChangeColor(Chessboard);
		TurnTheValidMovesTab(tab);
	}
}

void FillTheMoveTab(Game* game, bool tab[SIZE][SIZE], Square sq, movetab Move_Tab)
{
	bool KingInDanger = false;
	bool PieceInDanger = false;
	bool PieceKilled=false;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (tab[i][j] == false)
				Move_Tab[i][j] = MOVE_IS_INVALID;//Je�eli pole w tablicy dozwolonych ruch�w->false to ruch jest niedozwolony
			else
			{
				if (game->Chessboard[i][j] != EMPTY)//Na polu na kt�ry chcemy przesun�� figur� stoi jaka� bierka przeciwnika
					PieceKilled = true;//Ruch spowoduje zbicie
				else PieceKilled = false;
				Square to = { i,j };
				CheckIfPieceOrKingWillBeInDanger(game, sq, to, &KingInDanger,&PieceInDanger);

				//Je�eli ruch powoduje, �e kr�l aktualnego gracza by�by zagro�ony to ruch jest niedozwolony
				if (KingInDanger)
				{
					Move_Tab[i][j] = MOVE_INVALID_KING_DANGER;//Kr�l aktualnego gracza by�by w szachu
					continue;
				}
				else if (PieceKilled && PieceInDanger)
					Move_Tab[i][j] = MOVE_VALID_KILLED_DANGER;//zbicie i figura na zagro�onym polu
				else if (PieceKilled&&(!PieceInDanger))
					Move_Tab[i][j] = MOVE_VALID_KILLED;//zbicie
				else if (PieceInDanger&&(!PieceKilled))
					Move_Tab[i][j] = MOVE_VALID_DANGER;//figura na zagro�onym polu
				else
					Move_Tab[i][j] = MOVE_VALID;//poprawny ruch


			}
		}
	}
}

bool IsAValidMove(MoveTab moveType)
{
	return(!(moveType == MOVE_IS_INVALID || moveType ==MOVE_INVALID_KING_DANGER) );		
}

void FillTheMoveTabHelper(Game* game, movetab Move_tab, Square sq)
{
	bool tab[SIZE][SIZE] = { {false} };//Tablica dozwolonych ruch�w
	GetValidMoves(game->Chessboard, tab, sq);//Wype�nij tablic� dozwolonych ruch�w
	FillTheMoveTab(game, tab, sq,Move_tab);//Wype�nij tablic� rodzajami ruch�w
}

Message SetMove(Game* game, Square from, Square to)
{
	movetab Move_tab = { {MOVE_IS_INVALID} };//Pocz�tkowa warto�� tablicy zawieraj�cej rodzaje ruch�w
	MoveTab move;

	if (IsSquareOnTheChessboard(from) == false || IsSquareOnTheChessboard(to) == false)
		return MS_INVALID_SQUARE;//Kt�re� z p�l nie znajdowa�o si� na planszy
	if (BelongsToActualPlayer(game, from)==false||game->Chessboard[from.row][from.column]==EMPTY)
		return MS_INVALID_PIECE;//Gracz wybra� figur� nieprawid�owego koloru lub puste pole

	//Pobieramy mo�liwe ruchy dla figury na polu from
	FillTheMoveTabHelper(game, Move_tab, from);

	//Przypisujemy typ pola ko�cowego
	move = Move_tab[to.row][to.column];
	//Sprawdzamy czy ruch jest mo�liwy
	switch(move)
	{//Wykonany ruch nie powoduje zbicia i jest dozwolony
	case MOVE_VALID://Ruch poprawny
	case MOVE_VALID_DANGER://Figura kt�ra wykonuje ruch b�dzie znajdowa� si� na polu zagro�onym zbiciem
			AddAnElement(from, to, &game->pHead);
			MakeAMove(game, from, to);
			return MS_SUCESS_MOVE;
	case MOVE_VALID_KILLED://Ruch powoduje zbicie figury przeciwnika
	case MOVE_VALID_KILLED_DANGER://Ruch powoduje zbicie, figura b�dzie sta�a na polu zagro�onym zbiciem
		AddAnElement(from, to, &game->pHead);
		MakeAMove(game, from, to);
		return MS_SUCESS_MOVE_KILLED;
	case MOVE_IS_INVALID://ruch jest niepoprawny dla danej figury
		return MS_INVALID_MOVE;
	case MOVE_INVALID_KING_DANGER://Ruch spowodowa�by, �e aktualny gracz by�by w szachu
		return MS_INVALID_MOVE_KING_IN_DANGER;
	default:
		break;
	}
	return MS_INVALID_MOVE;
}

/**Funkcja sprawdza czy figura stoj�ca na polu sq ma jeszcze mo�liwe ruchy
@param game aktualnie rozgrywana partia
@param sq pole na kt�rym stoi figura
@return true, je�li figura mo�e wykona� dozwolony ruch w przeciwnym wypadku false*/
static bool HasPieceValidMoves(Game* game, Square sq)
{
	movetab Move_tab = { {MOVE_IS_INVALID} }; //Ustawiamy warto�� pocz�tkow�
	FillTheMoveTabHelper(game, Move_tab,sq);//Wype�niamy tablic� rodzajami ruch�w
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (IsAValidMove(Move_tab[i][j]))//Szukamy pola na kt�re mo�emy wykona� ruch
				return true;//Gdy je znajdziemy mo�emy wyj�� z funkcji
		}
	}
	return false;
}

/**Sprawdza czy aktualny gracz ma jeszcze mo�liwe ruchy do wykonania
@param game aktualnie rozgrywana partia
@return true je�li gracz mo�e wykona� ruch, false je�li nie mo�e wykona� ruchu*/
static bool CanActualPlayerMakeAMove(Game* game)
{
	bool next = false;
	bool IsWhitePlayer = (game->CurrentPlayer == white);
	if (IsWhitePlayer == false)
		PrepareForNextPlayerTurn(game);//Je�li gracz jest czarny musimy obr�ci� szachownic�
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (game->Chessboard[i][j] > 0)
			{
				Square sq = { i, j };
				if (HasPieceValidMoves(game, sq))
				{
					next = true;//Je�eli znaleziono mo�liwy ruch mo�na zako�czy� szukanie

				}
			}
		}
	}
	if (IsWhitePlayer == false)
		PrepareForNextPlayerTurn(game);//Je�eli gracz by� czarny ponownie obracamy szachownic�
	return next;
}

EndOfGame_MS IsTheEndOfGame(Game* game)
{
	//Je�li aktualny gracz ma jeszcze mo�liwe ruchy do wykonania to gra nie zosta�a zako�czona
	if (CanActualPlayerMakeAMove(game))
		return CONTINUE;
	//Je�li gracz nie ma ju� mo�liwych ruch�w to zwyci�y� gracz przeciwny
	if (IsActualPlayerInCheck(game))
	{
		game->HasGameEnded = true;
		return OPPONENT_PLAYER_WINNER;

	}
	//W innym przypadku gra zosta�a zako�czona remisem
	return DRAW;
}

Message SetMoveHelper(Game* game, Square from, movetab Move_tab)
{
	if (IsSquareOnTheChessboard(from) == false)//pole nie znajdowa�o si� na szachownicy
	{
		return MS_INVALID_SQUARE;
	}
	if (game->Chessboard[from.row][from.column] == EMPTY||BelongsToActualPlayer(game, from)==false)
	{
		return MS_INVALID_PIECE;//Na polu nie by�o figury lub by�a niew�a�ciwego koloru
	}
	FillTheMoveTabHelper(game, Move_tab, from);
	    return MS_GAME_SUCCESS;
}




