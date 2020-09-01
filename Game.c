#include "Game.h"
/**Funkcja zapisuje ustawienie pocz�tkowe figur na szachownicy
@param Chessboard szachownica na kt�rej b�d� rozk�adane figury
*/
static void InitializeTheChessboard(chessboard Chessboard)
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
	InitializeTheChessboard(new_game->Chessboard); /*Ustawienie pocz�tkowe na szachownicy*/
	return new_game;
}

void DestroyGame(Game** game)
{
	if (game == NULL)
		return;
	free(game);
}

/*Funkcja wy�wietlaj�ca szachownic� na ekranie konsoli (pomocnicza)
@param new_game aktualnie rozgrywana partia*/
static void PrintChessboard(Game* new_game)
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

/*Funkcja sprawdza czy pole znajduje si� na szachownicy
@param sq pole kt�re chcemy sprawdzi�
@return true, je�li pole znajduje si� na szachownicy w przeciwnym wypadku false*/
static bool IsSquareOnTheChessboard(Square sq)
{
	if (sq.column < SIZE && sq.column >= 0 && sq.row >= 0 && sq.row < SIZE)
		return true;
	return false;
}

/*Funkcja zwraca informacj� czy pole jest puste
@param to pole kt�re chcemy sprawdzi� 
@param game aktualnie rozgrywana partia
@return true je�li pole jest puste false je�li nie jest puste*/
static bool IsEmpty(Square to, Game* game)
{
	if (game->Chessboard[to.row][to.column] == EMPTY)
		return true;
	return false;
}

/*Funkcja sprawdza na kt�re pola z pola from mo�na wykona� ruch pionkiem. Je�li ruch jest mo�liwy zapisuje warto�� true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z kt�rego ma zosta� wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruch�w*/
static void PawnMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	if (Chessboard[from.row + 1][from.column + 1] == EMPTY)
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

/*Funkcja sprawdza na kt�re pole z pola from mo�na wykona� ruch wie��. Je�li ruch jest mo�liwy zapisuje warto�� true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z kt�rego ma zosta� wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruch�w*/
static void RookMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
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


/*Funkcja sprawdza na kt�re pole z pola from mo�na wykona� ruch skoczkiem. Je�li ruch jest mo�liwy zapisuje warto�� true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z kt�rego ma zosta� wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruch�w*/
static void KnightMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
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


/*Funkcja sprawdza na kt�re pole z pola from mo�na wykona� ruch go�cem. Je�li ruch jest mo�liwy zapisuje warto�� true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z kt�rego ma zosta� wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruch�w*/
static void BishopMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
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


/*Funkcja sprawdza na kt�re pole z pola from mo�na wykona� ruch hetmanem. Je�li ruch jest mo�liwy zapisuje warto�� true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z kt�rego ma zosta� wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruch�w*/
static void QueenMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
{
	BishopMove(Chessboard, from, tab);
	RookMove(Chessboard, from, tab);
}

/*Funkcja sprawdza na kt�re pole z pola from mo�na wykona� ruch kr�lem. Je�li ruch jest mo�liwy zapisuje warto�� true w tablicy dwuwymiarowej
@param Chessboard szachownica
@param from, pole z kt�rego ma zosta� wykonany ruch
@param tab tablica dozwolonych i niedozwolonych ruch�w*/
static void KingMove(chessboard Chessboard, Square from, bool tab[SIZE][SIZE])
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
	
/*Zapisuje w tablicy tab wszystkie mo�liwe ruchy bia�ej bierki stoj�cej na polu from
@param Chessboard szachownica
@param tab tablica dozwolonych ruch�w
@param from pole z kt�rego ma zosta� wykonany ruch*/
static void GetMovesOfTheWhitePiece(chessboard Chessboard, bool tab[SIZE][SIZE], Square from)
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

/*Funkcja zapisuje wszystkie mo�liwe ruchy bierek bia�ego gracza
@param Chessboard szachownica
@param tab tablica dozwolonych ruch�w*/
static void GetAllMoves(chessboard Chessboard, bool tab[SIZE][SIZE])
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

/*Funkcja obraca szachownic� o 180 stopni i zamienia kolor bierek na przeciwny. Dzi�ki temu mo�na u�ywa� funkcji definiuj�cych ruchy figur 
r�wnie� dla czarnego gracza
@param Chessboar szachownica kt�r� obracamy*/
static void TurnTheBoardChangeColor(chessboard Chessboard)
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

/*Funkcja obraca tablic� mo�liwych ruch�w o 180 stopni
@param tab tablica dozwolonych ruch�w (bool)*/
static void TurnTheValidMovesTab(bool tab[SIZE][SIZE])
{
	for (int i = 0; i < SIZE / 2; i++)//Zamiana kolor�w 
	{
		for (int j = 0; j < SIZE; j++)
		{
			int t = tab[i][j];
			tab[i][j] =(tab[SIZE - 1 - i][SIZE - 1 - j]);
			tab[SIZE - 1 - i][SIZE - 1 - j] = t;
		}
	}
}

/*Funkcja zwraca pole na kt�rym stoi czarny kr�l
@param Chessboard szachownica
@return pole na kt�rym znajduje si� kr�l, je�li pola nie znaleziono zwraca NULL*/
static Square FindTheBlackKing(chessboard Chessboard)
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
			}
		}
	}
	return sq;
}

/*Funkcja sprawdza czy czarny kr�l jest w szachu
@param Chessboard szachownica
@return true je�li czarny kr�l jest w szachu w przeciwnym wypadku false*/
static bool IsBlackKingChecked(chessboard Chessboard)
{
	bool blackcheck = false;
	bool tab[SIZE][SIZE] = { {false} };//Tworzymy tablic� dozwolonych ruch�w
	Square BlackKingPosition = FindTheBlackKing(Chessboard);//Szukamy czarnego kr�la na szachownicy
	GetAllMoves(Chessboard, tab);//Zapisujemy w tablicy wszystkie mo�liwe ruchy bia�ego gracza
	if (tab[BlackKingPosition.row][BlackKingPosition.column])//Je�li pole na kt�rym stoi kr�l jest polem atakowanym przez bia�� bierk� oznacza to �e czarny kr�l jest w szachu
		blackcheck = true;
	return blackcheck;//zwracamy informacj� czy kr�l jest w szachu
}

/*Funkcja sprawdza, czy czarna bierka jest zagro�ona zbiciem przez bia�ego gracza
@param Chessboard szachownica
@param black_square pole na kt�rym stoi czarna bierka
@return true je�li czarna bierka jest zagro�ona zbiciem przez bia�ego gracza w przeciwnym wypadku false*/
static bool BlackPieceInDanger(chessboard Chessboard, Square black_square)
{
	bool tab[SIZE][SIZE];
	GetAllMoves(Chessboard, tab);
	if (tab[black_square.row][black_square.column] == true)
		return true;
	return false;
}

/*Funkcja pozwalaj�ca kolejnemu graczowi wykona� ruch (zmienia kolor aktualnego gracza i obraca plansz� o 180 stopni)
@param game aktualnie rozgrywana partia*/
static void PrepareForNextPlayerTurn(Game* game)
{
	TurnTheBoardChangeColor(game->Chessboard);//Obr�t planszy
	SwitchPlayers(game);//zamiana graczy
}

/*Funkcja sprawdza czy figura stoj�ca na polu sq jest zagro�ona zbiciem przez figur� przciwnika
@param Chessboard szachownica
@param sq pole na kt�rym stoi figura
@return true, je�li figura jest zagro�ona false je�li nie jest zagro�ona*/
static bool IsPieceInDanger(chessboard Chessboard, Square sq)
{
	if (Chessboard[sq.row][sq.column] < 0)//Figura na polu sq jest czarna
		return BlackPieceInDanger(Chessboard, sq);
	//Na polu kt�re sprawdzamy stoi bia�a figura, musimy obr�ci� plansze
	TurnTheBoardChangeColor(Chessboard);
	//Musimy "obr�ci�" tak�e wsp�rz�dne pola sq
	sq.row = SIZE - 1 - sq.row;
	sq.column = SIZE - 1 - sq.column;
	bool t = BlackPieceInDanger(Chessboard, sq);
	TurnTheBoardChangeColor(Chessboard);//Musimy obr�ci� plansze z powrotem
	return t;
}

/*Funkcja cofa ostatni ruch jaki zosta� wykonany
@param game aktualnie rozgrywana partia*/
static DeleteLastMove(Game* game)
{
	//Przestawiamy figur� z pola to na pole from
	game->Chessboard[game->pHead->from.row][game->pHead->from.column] = game->Chessboard[game->pHead->to.row][game->pHead->to.column];
	//Ustawiamy figur� kt�ra zosta�a zbita (lub puste pole)
	game->Chessboard[game->pHead->to.row][game->pHead->to.column] = game->pHead->KilledPiece;
	//Usuwamy pierwszy element listy historii
	RemoveFirstElement(&game->pHead);

	//zmiana graczy;
	SwitchPlayers(game);

	//je�li w poprzednim ruchu kr�l by� w szachu
	game->BlackCheck = game->pHead->blackCheck;
	game->WhiteCheck = game->pHead->whiteCheck;
}

/*Funkcja sprawdza czy ruch powoduje, �e kr�l jest zagro�ony przez figur� przeciwnika lub dowolny pionek jest zagro�ony zbiciem
@param game aktualnie rozgrywana partia
@param from pole z kt�rego ma zosta� wykonany ruch
@param to pole na kt�re ma zosta� wwykonany ruch
@param KingInDanger pole informuj�ce czy kr�l by�by w szachu
@param PieceInDanger pole informuj�ce czy bierka by�aby zagro�ona zbiciem*/
static void CheckIfPieceOrKingWillBeInDanger(Game* game, Square from, Square to, bool* KingInDanger, bool* PieceInDanger)
{
	bool white_color = false;
	if (game->Chessboard[from.row][from.column] > 0)
		white_color = true;


	MakeAMove(game, from, to);
	if (white_color)
	{
		KingInDanger = game->WhiteCheck;
	}
	else
	{
		KingInDanger = game->BlackCheck;
	}

	PieceInDanger = IsPieceInDanger(game->Chessboard, to);
	DeleteLastMove(game);
}
void SwitchPlayers(Game* new_game)
{
	if (new_game->CurrentPlayer == white)//je�li aktualny gracz jest bia�y zmie� na czrnego
		new_game->CurrentPlayer = black;
	else new_game->CurrentPlayer = white;//aktualny gracz by� czarny, zamiana na bia�ego
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
	else check = IsBlackKingChecked(Chessboard);//Sprawdzamy czy czrny kr�l jest w szachu
	return check;
}

void MakeAMove(Game* game, Square from, Square to)
{
	//Dodanie ruchu do historii
	AddAnElement(from, to, &game->pHead, game->Chessboard[to.row][to.column]);

	//Wykonanie ruchu na szachownicy
	game->Chessboard[to.row][to.column] = game->Chessboard[from.row][from.column];
	game->Chessboard[from.row][from.column] = EMPTY;
	
	//Zamiana graczy
	SwitchPlayers(game);

	//Zapisz informacj� o tym czy kr�l kt�rego� z graczy jest w szachu
	game->WhiteCheck = IsKingChecked(game->Chessboard, white);
	game->BlackCheck = IsKingChecked(game->Chessboard, black);

}

bool IsActualPlayerInCheck(Game* game)
{
	if (game->CurrentPlayer == black)
		return game->BlackCheck;
	return game->WhiteCheck;
}

Player ColorOfActualPlayer(Game* game)
{
	if (game == NULL)
		return white;
	return game->CurrentPlayer;
}

Player ColorOfOpponentPlayer(Game* game)
{
	if (game->CurrentPlayer == white)
		return black;
	return white;
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
	if (Chessboard[from.row][from.column] > 0)
	{
		GetMovesOfTheWhitePiece(Chessboard, tab, from);
		return;
	}

	TurnTheBoardChangeColor(Chessboard);
	from.row = SIZE - 1 - from.row;
	from.column = SIZE - 1 - from.column;
	GetMovesOfTheWhitePiece(Chessboard, tab, from);
	TurnTheBoardChangeColor(Chessboard);
	TurnTheValidMovesTab(tab);
}

void FillTheMoveTab(Game* game, bool tab[SIZE][SIZE], Square sq, movetab Move_Tab)
{
	bool KingInDanger = false;
	bool PieceInDanger = false;
	bool PieceKilled = false;
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

				Square to = { i,j };
				CheckIfPieceOrKingWillBeInDanger(game, sq, to, &KingInDanger, &PieceInDanger);

				//Je�eli ruch powoduje, �e kr�l aktualnego gracza by�by zagro�ony to ruch jest niedozwolony
				if (KingInDanger)
					Move_Tab[i][j] = MOVE_INVALID_KING_DANGER;//Kr�l aktualnego gracza by�by w szachu
				else if (PieceKilled && PieceInDanger)
					Move_Tab[i][j] = MOVE_VALID_KILLED_DANGER;//zbicie i figura na zagro�onym polu
				else if (PieceKilled)
					Move_Tab[i][j] = MOVE_VALID_KILLED;//zbicie
				else if (PieceInDanger)
					Move_Tab[i][j] = MOVE_VALID_DANGER;//figura na zagro�onym polu
				else
					Move_Tab[i][j] = MOVE_VALID;//poprawny ruch


			}
		}
	}
}

bool IsAValidMove(MoveTab moveType)
{
	return(moveType == MOVE_VALID || moveType == MOVE_VALID_DANGER || moveType == MOVE_VALID_KILLED || moveType == MOVE_VALID_KILLED_DANGER);
		
}

/*Funkcja pomocnicza, wype�nia tablic� ruch�w, nie potrzebuje tablicy dozwolonych ruch�w jako argumentu
@param game aktualnie rozgrywana partia
@param Move_Tab tablica z rodzajami ruch�w
@param sq pole z kt�rego ma zosta� wykonany ruch*/
static void FillTheMoveTabHelper(Game* game, movetab Move_tab, Square sq)
{
	bool tab[SIZE][SIZE] = { {false} };//Tablica dozwolonych ruch�w
	GetValidMoves(game->Chessboard, tab, sq);//Wype�nij tablic� dozwolonych ruch�w
	FillTheMoveTab(game, tab, sq, Move_tab);//Wype�nij tablic� rodzajami ruch�w
}

Message SetMove(Game* game, Square from, Square to)
{
	movetab Move_tab = { {MOVE_IS_INVALID} };//Pocz�tkowa warto�� tablicy zawieraj�cej rodzaje ruch�w
	MoveTab move;
	if (game == NULL)
		return MS_GAME_ERROR;//Gra zsta�a nieprawid�owo utworzona
	if (IsSquareOnTheChessboard(from) == false || IsSquareOnTheChessboard(to) == false)
		return MS_INVALID_SQUARE;//Kt�re� z p�l nie znajdowa�o si� na planszy
	if (BelongsToActualPlayer(game, from)==false)
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
		MakeAMove(game, from, to);
		return MS_SUCESS_MOVE;
	case MOVE_VALID_KILLED://Ruch powoduje zbicie figury przeciwnika
	case MOVE_VALID_KILLED_DANGER://Ruch powoduje zbicie, figura b�dzie sta�a na polu zagro�onym zbiciem
		MakeAMove(game, from, to);
		return MS_VALID_MOVE_KILLED;
	case MOVE_IS_INVALID://ruch jest niepoprawny dla danej figury
		return MS_INVALID_MOVE;
	case MOVE_INVALID_KING_DANGER://Ruch spowodowa�by, �e aktualny gracz by�by w szachu
		return MS_INVALID_MOVE_KING_IN_DANGER;
	default:
		break;
	}
	return MS_INVALID_MOVE;



}

/*Funkcja sprawdza czy figura stoj�ca na polu sq ma jeszcze mo�liwe ruchy
@param game aktualnie rozgrywana partia
@param sq pole na kt�rym stoi figura
@return true, je�li figura mo�e wykona� dozwolony ruch w przeciwnym wypadku false*/
static bool HasPieceValidMoves(Game* game, Square sq)
{
	movetab Move_tab = { {MOVE_IS_INVALID} }; //Ustawiamy warto�� pocz�tkow�
	FillTheMoveTabHelper(game, Move_tab, sq);//Wype�niamy tablic� rodzajami ruch�w
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

/*Sprawdza czy aktualny gracz ma jeszcze mo�liwe ruchy do wykonania
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
					next = true;//Je�eli znalexiono mo�liwy ruch mo�na zako�czy� szukanie
					break;

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
		return CONTINIUE;
	//Je�li gracz nie ma ju� mo�liwych ruch�w to zwyci�y� gracz przeciwny
	if (IsActualPlayerInCheck(game))
		return OPPONENT_PLAYER_WINNER;
	//W innym przypadku gra zosta�a zako�czona remisem
	return DRAW;
}

Message SetMoveHelper(Game* game, Square from, movetab Move_tab)
{
	if (IsSquareOnTheChessboard(from))//pole nie znajdowa�o si� na szachownicy
		return MS_INVALID_SQUARE;
	if (IsEmpty(from, game))
		return MS_INVALID_PIECE;//Na polu nie by�o figury

	FillTheMoveTabHelper(game, Move_tab, from);
	    return MS_GAME_SUCCESS;
}

/*	bool SaveHistoryToFile(Game * game, char* file_name) {
		FILE* file = fopen(file_name, "w");

		if (file == NULL)
			return false;

		//Tutaj funkcja zapisuj�ca histori� do pliku

		if (fclose(file) == 0) 
		{ 
			game->IsSaved = true;
			return true;
		}

		return false;
	}

*/




