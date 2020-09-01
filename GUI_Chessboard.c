#include "GUI_Chessboard.h"

/*Funkcja wy�wietlaj�ca wiadomo�� na ekranie kt�ry z graczy zwyci�y� lub informacj� o remisie. Zwraca informacj�, czy gra zosta�a zako�czona.
@param Chessboard szachownica
@return false je�li gra nie zosta�a zako�czona lub true je�li gra zosta�a zako�czona*/
static bool GUI_EndOfGame(GUI_Chessboard *Chessboard)
{
	switch (IsTheEndOfGame(Chessboard->game))
	{
	case CONTINIUE:
		Chessboard->game->HasGameEnded = false;
		return false;
	case DRAW:
		Chessboard->game->HasGameEnded = true;
		GUI_UserEventPush(USER_EVENT_MESSAGE, "Koniec gry", "Remis!");
		return true;
	case OPPONENT_PLAYER_WINNER:
		Chessboard->game->HasGameEnded = true;
		if(Chessboard->game->CurrentPlayer==white)
		GUI_UserEventPush(USER_EVENT_MESSAGE, "Koniec gry", "Wygra� gracz czarny!");
		else GUI_UserEventPush(USER_EVENT_MESSAGE, "Koniec gry", "Wygra� gracz bia�y!");
		Chessboard->game->HasGameEnded = true;
		return true;

	}
	return false;
}

/*Funkcja zwraca informacj� czy kr�l aktualnego gracza jest w szachu
@param Chessboard szachownica*/
static void UpdateTheChessboard(GUI_Chessboard* Chessboard)
{
	//Przywracamy warto�ci pocz�tkowe
	Chessboard->from.column = -1;
	Chessboard->from.row = -1;
	Chessboard->Moves.column = -1;
	Chessboard->Moves.row = -1;

	Chessboard->game->IsSaved = false;

	if (GUI_EndOfGame(Chessboard))//Je�li gra zosta�a zako�czona
		return;

	//Sprawdzamy czy kr�l aktualnego gracza jest w szachu
	if (IsActualPlayerInCheck(Chessboard->game))
	{
		if (Chessboard->game->CurrentPlayer == white)
			GUI_UserEventPush(USER_EVENT_MESSAGE, "Szach!", "Bia�y kr�l jest w szachu!");
		else
			GUI_UserEventPush(USER_EVENT_MESSAGE, "Szach!", "Czarny kr�l jest w szachu!");
	}
}
GUI_Widget* GUI_CreateChessboard(SDL_Renderer* renderer, SDL_Rect location, void(*ChessboardAction)(void), Game* game)
{
	//Je�eli nie uda�o si� zaalokowa� gry w pami�ci
	if (game == NULL)
		return NULL;

	//Tworzymy wid�et
	GUI_Widget* widget = (GUI_Widget*)malloc(sizeof(GUI_Widget));
	if (widget == NULL)//je�eli nie uda�o si� zaalokowa� wid�etu
		return NULL;

	//Tworzymy struktur� szachownicy, kt�r� przypiszemy do wid�etu
	GUI_Chessboard* guichessboard = (GUI_Chessboard*)malloc(sizeof(GUI_Chessboard));
	if (guichessboard == NULL) //je�li nie uda�o si� zaalokowa� szachownicy
	{
		free(widget);//usuwamy wid�et
		return NULL;
	}

	//Tworzymy tekstury pionk�w
	//Pionki bia�ego gracza
	guichessboard->Pawn_white_tx = GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/pawn_white.bmp", 159, 176, 143);
	guichessboard->Rook_white_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/rook_white.bmp", 159, 176, 143);
	guichessboard->Knight_white_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/knight_white.bmp", 159, 176, 143);
	guichessboard->Bishop_white_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/bishop_white.bmp", 159, 176, 143);
	guichessboard->Queen_white_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/queen_white.bmp", 159, 176, 143);
	guichessboard->King_white_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/king_white.bmp", 159, 176, 143);
	//Pionki czarnego gracza
	guichessboard->Pawn_black_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/pawn_black.bmp", 159, 176, 143);
	guichessboard->Rook_black_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/rook_black.bmp", 159, 176, 143);
	guichessboard->Knight_black_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/knight_black.bmp", 159, 176, 143);
	guichessboard->Bishop_black_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/bishop_black.bmp", 159, 176, 143);
	guichessboard->Queen_black_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/queen_black.bmp", 159, 176, 143);
	guichessboard->King_black_tx= GUI_TextureBMPWithoutBackground(renderer, "./Graphics/pieces/king_black.bmp", 159, 176, 143);

	if (guichessboard->Pawn_white_tx == NULL || guichessboard->Pawn_black_tx == NULL || guichessboard->Rook_white_tx == NULL || guichessboard->Rook_black_tx == NULL
		|| guichessboard->Knight_black_tx == NULL || guichessboard->Knight_white_tx == NULL || guichessboard->Bishop_black_tx == NULL
		|| guichessboard->Bishop_white_tx == NULL || guichessboard->Queen_white_tx == NULL || guichessboard->Queen_black_tx == NULL || guichessboard->King_white_tx == NULL ||
		guichessboard->King_black_tx == NULL)
	{
		//Je�eli nie uda�o si� za�adowa� poprawnie wszystkich tekstur, zwalniamy dotychczas zaalokowan� pami�� i zwracamy NULL
		SDL_DestroyTexture(guichessboard->Pawn_white_tx);
		SDL_DestroyTexture(guichessboard->Pawn_black_tx);
		SDL_DestroyTexture(guichessboard->Rook_white_tx);
		SDL_DestroyTexture(guichessboard->Rook_black_tx);
		SDL_DestroyTexture(guichessboard->Knight_black_tx);
		SDL_DestroyTexture(guichessboard->Knight_white_tx);
		SDL_DestroyTexture(guichessboard->Bishop_white_tx);
		SDL_DestroyTexture(guichessboard->Bishop_black_tx);
		SDL_DestroyTexture(guichessboard->Queen_white_tx);
		SDL_DestroyTexture(guichessboard->Queen_black_tx);
		SDL_DestroyTexture(guichessboard->King_white_tx);
		SDL_DestroyTexture(guichessboard->King_black_tx);
		free(guichessboard);
		free(widget);
		return NULL;
	}
	//Przypisujemy polom warto�ci pocz�tkowe (poza szachownic�)
	guichessboard->from.column = -1;
	guichessboard->from.row = -1;
	guichessboard->Moves.column = -1;
	guichessboard->Moves.row = -1;

	//Przypisujemy pozosta�e pola dla szachownicy 
	guichessboard->location = location;
	guichessboard->game = game;
	guichessboard->renderer = renderer;
	guichessboard->ChessboardAction = ChessboardAction;

	//Przypisujemy odpowiednie pola dla wid�etu
	widget->gui_widget_data = guichessboard;
	widget->WidgetDestroy = GUI_DestroyChessboard;//Usuwanie szachownicy z pami�ci
	widget->WidgetDraw = GUI_DrawChessboard;//wy�wietlanie szachownicy
	widget->WidgetHandleEvent = GUI_handleChessboardEvent;//obs�uga zdarze�

	//Je�li struktura zosta�a stworzona poprawnie, mo�emy j� zwr�ci�
	return widget;
}

void GUI_DestroyChessboard(GUI_Widget* widget)
{
	//Tworzymy wska�nik na szachownic�
	GUI_Chessboard* guichessboard = (GUI_Chessboard*)widget->gui_widget_data;
	//Usuwamy j� z pami�ci
	free(guichessboard);
	//Usuwamy struktur� wid�etu z pami�ci
	free(widget);
}

/*Funkcja zwracaj�ca wybrany kwadrat szachownicy
@param i numer wiersza
@param j numer kolumny
@return pole znajduj�ce si� w i-tym wierszu i j-otej kolumnie*/
static SDL_Rect GUI_ChessboardGetSquare(int i, int j)
{
	SDL_Rect getSquare;
	//Do wsp�rz�dnej startowej dodajemy szeroko�� kwadratu przemno�on� razy ilo�� kolumn (Otrzymujemy wsp�rz�dn� x lewego g�rnego rogu kwadratu)
	getSquare.x = START_X + j * GUI_SQUARE;
	//Obliczenie wsp�rz�dnej y
	getSquare.y = START_Y + (SIZE - 1 - i) * GUI_SQUARE;
	//Przypisujemy odpowiedni� szeroko�� i wysoko��
	getSquare.h = GUI_SQUARE;
	getSquare.w = GUI_SQUARE;
	return getSquare;
}


/*Funkcja obs�uguje klikni�cie lewym przyciskiem myszy w pole na szachownicy
@param guichessboard szachownica
@param i numer wiersza w kt�rym znajduje si� pole
@param j numer kolumny w kt�rej znajduje si� pole*/
static void GUI_MouseButtonLeftClick(GUI_Chessboard* guichessboard, int i, int j)
{
	//Je�li klikni�to to samo pole, przywracamy warto�ci pocz�tkowe
	if (guichessboard->from.row == i && guichessboard->from.column == j)
	{
		guichessboard->from.row = -1;
		guichessboard->from.column = -1;
	}
	else
	{
		Square sq = { i,j };
		//Je�eli klikni�to w pole z figur� aktualnego gracza to przypisz je do pola from
		if (BelongsToActualPlayer(guichessboard->game, sq))
			guichessboard->from = sq;
		else if(guichessboard->from.column!=-1)//Je�eli wybrano ju� poprawn� figur� (pole from to pole na kt�rym stoi figura kt�r� gracz chce wykona� ruch
			switch (SetMove(guichessboard->game,guichessboard->from,sq))//Pole sq to pole na kt�re ma zosta� wykonany ruch
			{
			case MS_INVALID_PIECE://niepoprawna figura
				break;
			case MS_INVALID_SQUARE://niepoprawne pole
				break;
			case MS_INVALID_MOVE://niepoprawny ruch
				break;
			case MS_INVALID_MOVE_KING_IN_DANGER://kr�l w szachu
				if (IsActualPlayerInCheck(guichessboard->game))
					GUI_Messagebox("Niedozwolony ruch", "Tw�j kr�l by�by w szachu!");
				else
					GUI_Messagebox("Niedozwolony ruch", "Tw�j kr�l nadal jest w szachu!");
				break;
			case MS_VALID_MOVE_KILLED://nast�pi�o zbicie
			case MS_SUCESS_MOVE://inny poprawny ruch
				UpdateTheChessboard(guichessboard); //Sprawd� czy przeciwnik jest w szachu i wy�wietl informacj� na ekranie
				break;
			default:
				break;
			}

	}


}

/*Funkcja obs�uguje klikni�cie prawym przyciskiem myszy w pole na szachownicy
Zostaje wype�niona tabilca dozwolonych ruch�w, je�eli klikni�to w�a�ciw pole.
@param guichessboard szachownica
@param i numer wiersza w kt�rym znajduje si� pole
@param j numer kolumny w kt�rej znajduje si� pole*/
static void GUI_MouseButtonRightClick(GUI_Chessboard* guichessboard, int i, int j)
{
	//Klikni�to ponownie na to samo pole -> wy��czamy pokazywanie dozwolonych ruch�w
	if (guichessboard->Moves.row == i && guichessboard->Moves.column == j)
	{
		guichessboard->Moves.row = -1;
		guichessboard->Moves.column = -1;
	}
	Square sq = { i,j };
	switch (SetMoveHelper(guichessboard->game, sq, guichessboard->Move_Tab))
	{
	case MS_GAME_SUCCESS://Ustawiamy figur� kt�ra zosta�a klikni�ta
		guichessboard->Moves = sq;
		break;
	case MS_INVALID_PIECE://Naklikni�to na niew�a�ciwe pole, nic nie r�b
		guichessboard->Moves.column = -1;
		guichessboard->Moves.row = -1;
		break;
	}
}

void GUI_handleChessboardEvent(GUI_Widget* widget, SDL_Event* event)
{
	GUI_Chessboard* guichessboard = (GUI_Chessboard*)widget->gui_widget_data;
	if (event->type == SDL_MOUSEBUTTONUP)
	{
		SDL_Point click = { .x = event->button.x, .y = event->button.y };//Przypisujemy punktowi wsp�rz�dne miejsca klikni�cia
		if (SDL_PointInRect(&click, &guichessboard->location))//Je�eli klikni�to w obszar zajmowany przez szachownic�
		{
			//Szukamy pola kt�re zosta�o klikni�te
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					SDL_Rect sq = GUI_ChessboardGetSquare(i, j);
					if (SDL_PointInRect(&click, &sq))
					{
						if (event->button.button == SDL_BUTTON_RIGHT)
							GUI_MouseButtonRightClick;//klikni�to prawym przyciskiem myszy
						else if (event->button.button == SDL_BUTTON_LEFT)
							GUI_MouseButtonLeftClick;//klikni�to lewym przyciskiem myszy

						return;//klikni�cie innym przyciskiem myszy np. �rodkowym nie zostanie obs�u�one
							
					}
				}
			}
		}
	}
}

/*Funkcja koloruje kwadraty ze wzgl�du na rodzaj ruchu jaki mo�e zosta� wykonany poprawnie wybran� figur�
@param guichessboard szachownica
@param renderer render*/
static void GUI_ColorTheMoveSquares(GUI_Chessboard* guichessboard, SDL_Renderer* renderer)
{
	//Je�li nie zosta�o wybrane poprawne pole, nic nie r�b
	if (guichessboard->Moves.column == -1)
		return;

	//Sprawdzamy rodzaj ruchu ka�dego pola szachownicy
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
				switch (guichessboard->Move_Tab[i][j])
				{
				case MOVE_VALID://ruch poprawny kolorujemy
					SDL_SetRenderDrawColor(renderer, 246, 246, 131, 0);
					break;
				case MOVE_VALID_DANGER:
					SDL_SetRenderDrawColor(renderer, 244, 63, 48, 0);
					break;
				case MOVE_VALID_KILLED_DANGER:
					SDL_SetRenderDrawColor(renderer, 63, 78, 2, 0);
					break;
				case MOVE_VALID_KILLED:
					SDL_SetRenderDrawColor(renderer, 5, 255, 1, 0);
					break;
				case MOVE_INVALID_KING_DANGER:
				case MOVE_IS_INVALID:
					break;
				default:
					break;
				}
			

		}
	}

}

/*Funkcja koloruje wybrane pole
@param guichessboard szachownica
@param renderer render*/
static void GUI_ColorChosenSquare(GUI_Chessboard* guichessboard, SDL_Renderer* renderer)
{
	if (guichessboard->from.row != -1)
	{
		SDL_SetRenderDrawColor(renderer, 186, 202, 69, 0);
		SDL_Rect sq = GUI_ChessboardGetSquare(guichessboard->from.row, guichessboard->from.column);
		SDL_RenderFillRect(renderer, &sq);
	}
}

/*Funkcja rysuj�ca pust� szachownic�
@param guichessboard szachownica
@param renderer render*/
static void GUI_DrawEmptyChessboard(GUI_Chessboard* guichessboard, SDL_Renderer* renderer)
{
	// Na pocz�tku malujemy du�y jednokolorowy kwadrat
	SDL_SetRenderDrawColor(guichessboard->renderer, 238, 238, 210, 0);
	SDL_RenderFillRect(guichessboard->renderer, &(guichessboard->location));

	//Zmieniamy kolor
	SDL_SetRenderDrawColor(guichessboard->renderer, 7, 15, 86, 0);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//malujemy co drugie pole - suma indeks�w musi by� nieparzysta
			if ((i + j) % 2 == 1)
			{
				SDL_Rect guisquare = GUI_ChessboardGetSquare(i, j); // tworzymy kwadrat 
				SDL_RenderFillRect(guichessboard->renderer, &guisquare); //wype�niamy kolorem
			}
		}
	}
}

/*Funkcja rysuje figury w odpowiednich miejscach na szachownicy
@param guichessboard szachownica
@param renderer render*/
static void GUI_DrawPieces(GUI_Chessboard* guichessboard, SDL_Renderer* renderer)
{
	SDL_Texture* piece_tx=NULL;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			piece_tx = NULL;
			//Przypisujemy liczb� odpowiadaj�c� pionkowi na danym polu (lub pustemu polu)
			int piece_number = guichessboard->game->Chessboard[i][j];
			//Przypisujemy odpowiedni� tekstur� lub NULL w przypadku gdy pole jest puste
				switch(piece_number)
				{
					case PAWN_BLACK:
						piece_tx=guichessboard->Pawn_black_tx;
						break;
					case ROOK_BLACK:
						piece_tx = guichessboard->Rook_black_tx;
						break;
					case KNIGHT_BLACK:
						piece_tx = guichessboard->King_black_tx;
						break;
					case BISHOP_BLACK:
						piece_tx = guichessboard->Bishop_black_tx;
						break;
					case QUEEN_BLACK:
						piece_tx = guichessboard->Queen_black_tx;
						break;
					case KING_BLACK:
						piece_tx = guichessboard->King_black_tx;
						break;
				case EMPTY:
					break; 
				case PAWN_WHITE:
					piece_tx = guichessboard->Pawn_white_tx;
					break;
				case ROOK_WHITE:
					piece_tx = guichessboard->Rook_white_tx;
					break;
				case KNIGHT_WHITE:
					piece_tx = guichessboard->King_white_tx;
					break;
				case BISHOP_WHITE:
					piece_tx = guichessboard->Bishop_white_tx;
					break;
				case QUEEN_WHITE:
					piece_tx = guichessboard->Queen_white_tx;
					break;
				case KING_WHITE:
					piece_tx = guichessboard->King_white_tx;
				}
			//Kopiujemy tekstur�, je�eli na polu stoi pionek
			if (piece_tx!=NULL)
			{
				SDL_Rect piecesquare = GUI_ChessboardGetSquare(i, j);
				SDL_RenderCopy(renderer, piece_tx, NULL, &piecesquare);
			}
			
		}
	}
}

void GUI_DrawChessboard(GUI_Widget* widget, SDL_Renderer* renderer)
{
	//Tworzymy wska�nik na szachownic�
	GUI_Chessboard* guichessboard = (GUI_Chessboard*)widget->gui_widget_data;
	//Rysujemy pust� szachownic�
	GUI_DrawEmptyChessboard(guichessboard,renderer);
	//Kolorujemy pola ze wzgl�du na mo�liwe ruchy (je�li nast�pi�o prawid�owe klikni�cie prawym przyciskiem myszy)
	GUI_ColorTheMoveSquares(guichessboard, renderer);
	//Kolorujemy pole na kt�rym stoi figura wybrana lewym przyciskiem myszy
	GUI_ColorChosenSquare(guichessboard, renderer);
	//Rysujemy figury na szachownicy
	GUI_DrawPieces(guichessboard, renderer);

}
