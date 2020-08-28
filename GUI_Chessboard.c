#include "GUI_Chessboard.h"


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

	//Tworzymy pola, ustawiamy ich wsp�rz�dne poza plansz�
	guichessboard->from = CreateNewSquare(-1, -1);
	if (guichessboard->from == NULL)
	{
		free(guichessboard);
		free(widget);
		return NULL;
	}
	guichessboard->Moves = CreateNewSquare(-1, -1);
	if (guichessboard->Moves == NULL)
	{
		free(guichessboard->from);
		free(guichessboard);
		free(widget);
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
		free(guichessboard->from);
		free(guichessboard->Moves);
		free(guichessboard);
		free(widget);
		return NULL;
	}
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

/*Funkcja obs�uguje klikni�cie lewym przyciskiem myszy w pole szachownicy
@param guichessboard szachownica
@param i numer wiersza w kt�rym znajduje si� pole
@param numer kolumny w kt�rej znajduje si� pole*/
static void GUI_MouseButtonLeftClickSquare(GUI_Chessboard* guichessboard, int i, int j)
{
	//Je�li ponownie wybrano ten sam kwadrat ruch jest nieprawid�owy
	if (guichessboard->from->row == i && guichessboard->from->column == j)
	{
		guichessboard->from->row = -1;
		guichessboard->from->column = -1;
	}
	else
	{
		//Je�eli pionek na wybranym polu nale�y do aktualnego gracza -> przypisz go do pola from
		if (false)
		{
				guichessboard->from->row=i;
				guichessboard->from->column=j;
		}
		else if (guichessboard->from->column != -1&&guichessboard->from->row!=-1)
		{
			Square* to=CreateNewSquare(i, j);
			switch (true)//tutaj funkcja kt�ra sprawdza ruch
			{
				//Tutaj b�dzie zwracana wiadomo�� ze struktury game
			case INVALID_SQUARE:
				break;
			case INVALID_PIECE:
				break;
			case INVALID_MOVE:
				break;
			case KING_IN_DANGER:
			case KING_STILL_IN_DANGER:
				if (true)//Je�li aktualny gracz jest w szachu
				{
					GUI_Messagebox("Chess", "King is threatened");
				}
				else
				{
					GUI_Messagebox("Chess", "King will be threatened");
				}
				break;
			case VALID_KING_DANGER:
			case VALID_MOVE:
				//Wykonaj ruch bo szachownica si� zmieni�a i trzeba b�dzie nanie�� zmiany
			default:
				break;
			}

			//Sprawdzi� czy nie ma wyciek�w!!!
			AddAnElement(&guichessboard->from, &to, &guichessboard->game->pHead);
			
		}


	}
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

void GUI_handleChessboardEvent(GUI_Widget* widget, SDL_Event* event)
{
	GUI_Chessboard* guichessboard = (GUI_Chessboard*)widget->gui_widget_data;

	//Je�li gra si� zako�czy�a, mo�emy tylko wr�ci� do menu g��wnego
	if ((guichessboard->game->HasGameEnded == false)&&(event->type!=SDL_USEREVENT||event->user.code!=USER_EVENT_BACK_TO_MENU_WINDOW))
	return;

	if (event->type == SDL_USEREVENT&&event->user.code==USER_EVENT_BACK_TO_MENU_WINDOW)
	{
			  //wr�� do okna menu ->odpowiednia funkcja
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		//Tworzymy punkt o wsp�rz�dnych klikni�cia
		SDL_Point point;
		point.x = event->button.x;
		point.y = event->button.y;

		//Sprawdzamy czy punkt znajduje si� na szachownicy
		if (SDL_PointInRect(&point, &guichessboard->location))
		{
			//Szukamy pola na szachownicy kt�re zosta�o klikni�te
			for (int i = 0; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE; j++)
				{
					SDL_Rect square_click = GUI_ChessboardGetSquare(i, j);
					if (SDL_PointInRect(&point, &square_click))
					{
						//Je�eli zosta�o klikni�te lewym przyciskiem myszy 
						if (event->button.button == SDL_BUTTON_LEFT)
							//GUI_MouseButtonLeftClickSquare();
					}
				}
			}
		}
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
	SDL_SetRenderDrawColor(renderer, 118, 150, 86, 0);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//malujemy co drugie pole - suma indeks�w musi by� nieparzysta
			if ((i + j) % 2 == 1)
			{
				SDL_Rect guisquare = GUI_ChessboardGetSquare(i, j); // tworzymy kwadrat 
				SDL_RenderFillRect(renderer, &guisquare); //wype�niamy kolorem
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
			//Przypisujemy liczb� odpowiadaj�c� pionkowi na danym polu (lub pustemu polu)
			int piece_number = guichessboard->game->Chessboard[i][j];
			//Przypisujemy odpowiedni� tekstur� lub NULL w przypadku gdy pole jest puste
			if (piece_number < 0)//Czarne figury
			{
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
				}
			}
			else //Bia�e figury
				switch (piece_number)
				{
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
	//Rysujemy figury na szachownicy
	GUI_DrawPieces(guichessboard, renderer);

}
