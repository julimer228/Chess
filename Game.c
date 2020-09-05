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
	new_game->IsSaved = false;
	new_game->CurrentPlayer = white;
	new_game->pHead = NULL;
	//Ustawiamy pola dotycz¹ce ostatniego wykonanego ruchu na wartoœci pocz¹tkowe (poza szachownic¹)
	new_game->From.row = -1;
	new_game->From.column = -1;
	new_game->To.column = -1;
	new_game->To.row = -1;
	new_game->blackcheck_t = false;
	new_game->whitecheck_t = false;
	new_game->piece_killed = EMPTY;
	InitializeTheChessboard(new_game->Chessboard); /*Ustawienie pocz¹tkowe na szachownicy*/
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
		if ((from.row == 1) && (Chessboard[from.row + 2][from.column] == EMPTY))//Je¿eli wykonujemy pierwszy ruch pionkiem to mo¿emy go przesun¹æ o dwa pola do przodu
		{
			tab[from.row + 2][from.column] = true;
		}
	}
	//Zbicia po skosie (jeœli stoi tam bierka przeciwnika)
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
	bool first_enemy = true; //Sprawdzamy czy ju¿ jakiœ pionek by³ zbity (nie mo¿emy kilku figur w jednym ruchu)
	for (int i = 1; ((i + from.row )< SIZE)&&((from.column+i)<SIZE); i++)
	{
		if (Chessboard[from.row + i][from.column + i] > 0)//Jeœli na przek¹tnej znajduje siê bia³a figura, to nie mo¿emy stan¹æ na tym polu, nie mo¿emy go tak¿e "przeskoczyæ"
			break;
			if(((Chessboard[from.row+i][from.column+i] == EMPTY) || (Chessboard[from.row+i][from.column+i] < 0))&& (first_enemy == true))
			{
				if (Chessboard[from.row+i][from.column+i] < 0)//Jeœli na przek¹tnej znajduje siê czarna figura, to mo¿emy j¹ zbiæ i stan¹æ na zajmowanym przez ni¹ polu, ale nie mo¿emy iœæ dalej
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
	for (int i = 0; i < SIZE/2; i++)//Obracamy tylko do po³owy poniewa¿ wrócilibyœmy do tego samego ustawienia 
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
	Square sq = { -1,-1 };//Jeœli króla nie znaleziono zwróci pole o niedozwolonych indeksach
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
	bool tab[SIZE][SIZE] = { {false} };//Tworzymy tablicê dozwolonych ruchów
	Square BlackKingPosition = FindTheBlackKing(Chessboard);//Szukamy czarnego króla na szachownicy

	GetAllMovesOfTheWhitePlayer(Chessboard, tab);
	if (tab[BlackKingPosition.row][BlackKingPosition.column] == true)
		return true;
	return false;
}

bool BlackPieceInDanger(chessboard Chessboard, Square black_square)
{
	bool tab[SIZE][SIZE] = {{ false }};
	if (Chessboard[black_square.row][black_square.column] < 0)//Je¿eli na polu stoi czarna figura
	{
		GetAllMovesOfTheWhitePlayer(Chessboard, tab);
		if (tab[black_square.row][black_square.column])
			return true;
	}
	return false;
}

void PrepareForNextPlayerTurn(Game* game)
{
	TurnTheBoardChangeColor(game->Chessboard);//Obrót planszy
	SwitchPlayers(game);//zamiana graczy
}

bool IsPieceInDanger(chessboard Chessboard, Square sq)
{
	bool t = false;
	if (Chessboard[sq.row][sq.column] < 0)//Figura na polu sq jest czarna
		return BlackPieceInDanger(Chessboard, sq);
	//Na polu które sprawdzamy stoi bia³a figura, musimy obróciæ plansze
	if (Chessboard[sq.row][sq.column] > 0)
	{
		TurnTheBoardChangeColor(Chessboard);
		//Musimy "obróciæ" tak¿e wspó³rzêdne pola sq
		sq.row = SIZE - 1 - sq.row;
		sq.column = SIZE - 1 - sq.column;
		bool t = BlackPieceInDanger(Chessboard, sq);
		TurnTheBoardChangeColor(Chessboard);//Musimy obróciæ plansze z powrotem
	}
		return t;
}

 void DeleteLastMove(Game* game)
{
	//Przestawiamy figurê z pola to na pole from
	game->Chessboard[game->From.row][game->From.column] = game->Chessboard[game->To.row][game->To.column];
	//Ustawiamy figurê która zosta³a zbita (lub puste pole)
	game->Chessboard[game->To.row][game->To.column] = game->piece_killed;

	//zmiana graczy;
	SwitchPlayers(game);
	//jeœli w poprzednim ruchu król by³ w szachu
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

	//Zapisz informacjê o tym czy król któregoœ z graczy jest w szachu
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
	if (game->CurrentPlayer == white)//jeœli aktualny gracz jest bia³y zmieñ na czrnego
		game->CurrentPlayer = black;
	else game->CurrentPlayer = white;//aktualny gracz by³ czarny, zamiana na bia³ego
}

bool IsKingChecked(chessboard Chessboard, Player player)
{
	bool check = false;
	if (player == white)
	{
		TurnTheBoardChangeColor(Chessboard);//Zmieniamy kolory figur i obracamy planszê
		check = IsBlackKingChecked(Chessboard);//sprawdzamy czy czarny król jest w szachu
		TurnTheBoardChangeColor(Chessboard);//Obracamy planszê i zmieniamy kolor
	}
	else if(player==black)
	{
		check = IsBlackKingChecked(Chessboard);//Sprawdzamy czy czarny król jest w szachu
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
		//Obracamy szachownicê
		TurnTheBoardChangeColor(Chessboard);
		from.row = SIZE - 1 - from.row;
		from.column = SIZE - 1 - from.column;
	}

	GetMovesOfTheWhitePiece(Chessboard, tab, from);//wype³niamy tablicê dozwolonych ruchów

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
				Move_Tab[i][j] = MOVE_IS_INVALID;//Je¿eli pole w tablicy dozwolonych ruchów->false to ruch jest niedozwolony
			else
			{
				if (game->Chessboard[i][j] != EMPTY)//Na polu na który chcemy przesun¹æ figurê stoi jakaœ bierka przeciwnika
					PieceKilled = true;//Ruch spowoduje zbicie
				else PieceKilled = false;
				Square to = { i,j };
				CheckIfPieceOrKingWillBeInDanger(game, sq, to, &KingInDanger,&PieceInDanger);

				//Je¿eli ruch powoduje, ¿e król aktualnego gracza by³by zagro¿ony to ruch jest niedozwolony
				if (KingInDanger)
				{
					Move_Tab[i][j] = MOVE_INVALID_KING_DANGER;//Król aktualnego gracza by³by w szachu
					continue;
				}
				else if (PieceKilled && PieceInDanger)
					Move_Tab[i][j] = MOVE_VALID_KILLED_DANGER;//zbicie i figura na zagro¿onym polu
				else if (PieceKilled&&(!PieceInDanger))
					Move_Tab[i][j] = MOVE_VALID_KILLED;//zbicie
				else if (PieceInDanger&&(!PieceKilled))
					Move_Tab[i][j] = MOVE_VALID_DANGER;//figura na zagro¿onym polu
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
	bool tab[SIZE][SIZE] = { {false} };//Tablica dozwolonych ruchów
	GetValidMoves(game->Chessboard, tab, sq);//Wype³nij tablicê dozwolonych ruchów
	FillTheMoveTab(game, tab, sq,Move_tab);//Wype³nij tablicê rodzajami ruchów
}

Message SetMove(Game* game, Square from, Square to)
{
	movetab Move_tab = { {MOVE_IS_INVALID} };//Pocz¹tkowa wartoœæ tablicy zawieraj¹cej rodzaje ruchów
	MoveTab move;

	if (IsSquareOnTheChessboard(from) == false || IsSquareOnTheChessboard(to) == false)
		return MS_INVALID_SQUARE;//Któreœ z pól nie znajdowa³o siê na planszy
	if (BelongsToActualPlayer(game, from)==false||game->Chessboard[from.row][from.column]==EMPTY)
		return MS_INVALID_PIECE;//Gracz wybra³ figurê nieprawid³owego koloru lub puste pole

	//Pobieramy mo¿liwe ruchy dla figury na polu from
	FillTheMoveTabHelper(game, Move_tab, from);

	//Przypisujemy typ pola koñcowego
	move = Move_tab[to.row][to.column];
	//Sprawdzamy czy ruch jest mo¿liwy
	switch(move)
	{//Wykonany ruch nie powoduje zbicia i jest dozwolony
	case MOVE_VALID://Ruch poprawny
	case MOVE_VALID_DANGER://Figura która wykonuje ruch bêdzie znajdowaæ siê na polu zagro¿onym zbiciem
			AddAnElement(from, to, &game->pHead);
			MakeAMove(game, from, to);
			return MS_SUCESS_MOVE;
	case MOVE_VALID_KILLED://Ruch powoduje zbicie figury przeciwnika
	case MOVE_VALID_KILLED_DANGER://Ruch powoduje zbicie, figura bêdzie sta³a na polu zagro¿onym zbiciem
		AddAnElement(from, to, &game->pHead);
		MakeAMove(game, from, to);
		return MS_SUCESS_MOVE_KILLED;
	case MOVE_IS_INVALID://ruch jest niepoprawny dla danej figury
		return MS_INVALID_MOVE;
	case MOVE_INVALID_KING_DANGER://Ruch spowodowa³by, ¿e aktualny gracz by³by w szachu
		return MS_INVALID_MOVE_KING_IN_DANGER;
	default:
		break;
	}
	return MS_INVALID_MOVE;
}

/**Funkcja sprawdza czy figura stoj¹ca na polu sq ma jeszcze mo¿liwe ruchy
@param game aktualnie rozgrywana partia
@param sq pole na którym stoi figura
@return true, jeœli figura mo¿e wykonaæ dozwolony ruch w przeciwnym wypadku false*/
static bool HasPieceValidMoves(Game* game, Square sq)
{
	movetab Move_tab = { {MOVE_IS_INVALID} }; //Ustawiamy wartoœæ pocz¹tkow¹
	FillTheMoveTabHelper(game, Move_tab,sq);//Wype³niamy tablicê rodzajami ruchów
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (IsAValidMove(Move_tab[i][j]))//Szukamy pola na które mo¿emy wykonaæ ruch
				return true;//Gdy je znajdziemy mo¿emy wyjœæ z funkcji
		}
	}
	return false;
}

/**Sprawdza czy aktualny gracz ma jeszcze mo¿liwe ruchy do wykonania
@param game aktualnie rozgrywana partia
@return true jeœli gracz mo¿e wykonaæ ruch, false jeœli nie mo¿e wykonaæ ruchu*/
static bool CanActualPlayerMakeAMove(Game* game)
{
	bool next = false;
	bool IsWhitePlayer = (game->CurrentPlayer == white);
	if (IsWhitePlayer == false)
		PrepareForNextPlayerTurn(game);//Jeœli gracz jest czarny musimy obróciæ szachownicê
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (game->Chessboard[i][j] > 0)
			{
				Square sq = { i, j };
				if (HasPieceValidMoves(game, sq))
				{
					next = true;//Je¿eli znaleziono mo¿liwy ruch mo¿na zakoñczyæ szukanie

				}
			}
		}
	}
	if (IsWhitePlayer == false)
		PrepareForNextPlayerTurn(game);//Je¿eli gracz by³ czarny ponownie obracamy szachownicê
	return next;
}

EndOfGame_MS IsTheEndOfGame(Game* game)
{
	//Jeœli aktualny gracz ma jeszcze mo¿liwe ruchy do wykonania to gra nie zosta³a zakoñczona
	if (CanActualPlayerMakeAMove(game))
		return CONTINUE;
	//Jeœli gracz nie ma ju¿ mo¿liwych ruchów to zwyciê¿y³ gracz przeciwny
	if (IsActualPlayerInCheck(game))
	{
		game->HasGameEnded = true;
		return OPPONENT_PLAYER_WINNER;

	}
	//W innym przypadku gra zosta³a zakoñczona remisem
	return DRAW;
}

Message SetMoveHelper(Game* game, Square from, movetab Move_tab)
{
	if (IsSquareOnTheChessboard(from) == false)//pole nie znajdowa³o siê na szachownicy
	{
		return MS_INVALID_SQUARE;
	}
	if (game->Chessboard[from.row][from.column] == EMPTY||BelongsToActualPlayer(game, from)==false)
	{
		return MS_INVALID_PIECE;//Na polu nie by³o figury lub by³a niew³aœciwego koloru
	}
	FillTheMoveTabHelper(game, Move_tab, from);
	    return MS_GAME_SUCCESS;
}




